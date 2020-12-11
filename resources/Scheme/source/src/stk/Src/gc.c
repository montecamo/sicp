/*
 *
 *  g c . c			-- Mark and Sweep Garbage Collector 
 *
 *
 * Copyright � 1993-1999 Erick Gallesio - I3S-CNRS/ESSI <eg@unice.fr>
 * 
 *
 * Permission to use, copy, modify, distribute,and license this
 * software and its documentation for any purpose is hereby granted,
 * provided that existing copyright notices are retained in all
 * copies and that this notice is included verbatim in any
 * distributions.  No written agreement, license, or royalty fee is
 * required for any of the authorized uses.
 * This software is provided ``AS IS'' without express or implied
 * warranty.
 *
 *            Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: 17-Feb-1993 12:27
 * Last file update:  3-Sep-1999 20:20 (eg)
 *
 */

#include "stk.h"
#include "gc.h"
#include "extend.h"
#ifdef USE_STKLOS
#  include "stklos.h"
#endif
#ifdef USE_TK
#  include "tk-glue.h"
#endif


#define MIN_HEAP	100	/* A too small value cause an infinite loop */
#define VALID_ADDRESS(heap_org, p)					    \
	((p >= heap_org) && (p < heap_org + heap_size) &&		    \
	 (((((char *)p) - ((char *)heap_org)) % sizeof(struct obj)) == 0))

#define HEAPS_INCREMENT 10

#define gc_mark(ptr)	STk_gc_mark(ptr)

struct gc_protected {
  SCM *location;
  struct gc_protected *next;
};


/* exported vars */
SCM 	STk_freelist;
SCM 	*STk_stack_start_ptr;
double  STk_total_gc_time = 0.0;
long    STk_alloc_cells;
int	STk_gc_requested = 0;

/* internal vars */
static jmp_buf	save_regs_gc_mark;
static long	gc_cells_collected;
static long	heap_size      = INITIAL_HEAP_SIZE;
static int	gc_verbose     = 0;
static int	gc_calls       = 0;
static SCM 	*heaps 	       = NULL;
static int 	heaps_length   = 0;
static int	heaps_used     = 0;
static double   time_gc_start;

static struct gc_protected  *protected_registers = NULL;

static void no_memory(void)
{
  panic("No more memory. Cannot allocate a new heap.");
}

static void allocate_new_heap(void)
{
  SCM ptr, next;
  SCM heap_org, heap_end;

  /* Don't use must_malloc here since it can conduct to call GC when 
   * allocating large heaps (typically with large -cells xxx)
   */

  if (heaps_used == heaps_length) {
    /* Realloc heaps */
    heaps_length += HEAPS_INCREMENT;
    heaps         = (heaps_used) ?  realloc(heaps, heaps_length*sizeof(SCM)):
				    malloc(heaps_length*sizeof(SCM));
    if (!heaps) no_memory();
  }
  ptr = (SCM) malloc(sizeof(struct obj)*heap_size);
  if (ptr) {
    heap_org =  heaps[heaps_used++] = ptr;
    heap_end = heap_org + heap_size;
  }
  else 
    no_memory();

  /* Prepare heap space */
  for(ptr = heap_org, next=ptr+1; ptr < heap_end; ptr=next, next=ptr+1) {
    ptr->type      = tc_free_cell;
    ptr->cell_info = 0;
    ptr->gc_mark   = 0;
    CDR(ptr) = (next < heap_end) ? next : STk_freelist;
  }
  STk_freelist = heap_org;

  if (gc_verbose)
    Fprintf(STk_curr_eport,
	    ";; [new heap allocated (%d/%d)]\n",
	    heaps_used,heaps_length);
}

void STk_gc_count_cells(long *allocated, long *used, long* calls)
{
  register SCM ptr, heap_org, heap_end;
  register long used_cells = 0L;
  int i;

  for (i=0; i < heaps_used; i++) {
    heap_org = heaps[i];
    heap_end = heap_org + heap_size;

    for(ptr = heap_org; ptr < heap_end; ptr++) 
      if (NTYPEP(ptr, tc_free_cell)) used_cells	+= 1;
  }

  *allocated = heaps_used * heap_size;
  *used      = used_cells;
  *calls     = (long) gc_calls;
}


int STk_valid_address(SCM p)	/* True if p is a valid address. Used for #Pxyz */
{
  int i;
  
  for(i=0; i < heaps_used; i++) {
    register SCM heap_org=heaps[i];
    
    if (VALID_ADDRESS(heap_org, p)) return TRUE;
  }

  return FALSE;
}


void STk_gc_mark(SCM ptr)
{
Top:
   if (NULLP(ptr) || SMALL_CSTP(ptr)) return;
   if (ptr->gc_mark)		      return;

   ptr->gc_mark = GC_MARK;

   switch (TYPE(ptr)) {
     case tc_nil: 	  return;
     case tc_cons:	  gc_mark(CAR(ptr));ptr = CDR(ptr); goto Top;
     case tc_flonum:	  return;
     case tc_integer:	  return;
     case tc_bignum:	  return;
     case tc_symbol:      ptr = VCELL(ptr);goto Top;
     case tc_keyword:	  return;  
     case tc_subr_0:	  return;
     case tc_subr_1:	  return;
     case tc_subr_2:	  return;
     case tc_subr_3:	  return;
     case tc_subr_0_or_1: return;
     case tc_subr_1_or_2: return;
     case tc_subr_2_or_3: return;
     case tc_lsubr:	  return;
     case tc_ssubr:	  return;
     case tc_fsubr:	  return;
     case tc_syntax:	  return;
     case tc_closure:	  gc_mark(CLOSCODE(ptr));
			  ptr = CLOSENV(ptr);
			  goto Top;
     case tc_free_cell:	  /* -----> Error */
     case tc_char:	  return;
     case tc_string:	  return;
     case tc_vector:	  {
       			    long j;
			    for(j = 0;j < ptr->storage_as.vector.dim; j++)
			      gc_mark(ptr->storage_as.vector.data[j]);
			    return;
			  }
     case tc_eof:      	  return;
     case tc_undefined:	  return;
     case tc_iport:	  
     case tc_oport:	  gc_mark(PORT_REVENT(ptr)); 
			  ptr = PORT_WEVENT(ptr);       
			  goto Top;
     case tc_isport:	  return;
     case tc_osport:	  return;
     case tc_ivport:	  
     case tc_ovport:	  STk_mark_virtual_port(ptr);
			  return;  
     case tc_boolean:	  return;
     case tc_macro:	  ptr = ptr->storage_as.macro.code; goto Top;
     case tc_localvar:	  ptr = ptr->storage_as.localvar.symbol; goto Top;
     case tc_globalvar:	  ptr = VCELL(ptr); goto Top;
     case tc_modulevar:	  ptr = CAR(ptr); goto Top;
     case tc_cont:	  STk_mark_continuation(ptr);
       			  return;
     case tc_env:
     case tc_address:	  ptr = ptr->storage_as.env.data;
			  goto Top;
     case tc_autoload:	  gc_mark(CAR(ptr)); ptr = CDR(ptr); goto Top;
     case tc_Cpointer:    return;
     case tc_module:      STk_mark_module(ptr); return;
     case tc_frame:	  gc_mark(CAR(ptr));ptr = CDR(ptr); goto Top;
     case tc_values:	  ptr = CAR(ptr); goto Top;
#ifdef USE_STKLOS
     case tc_instance: 	  {
       			    /* ACCESSORS_OF(ptr) doesn't need to be marked since it 
			     * is always accessible from SLOTS_OF(CLASS_OF(ptr))
			     */
       			    long j;

			    gc_mark(CLASS_OF(ptr));
			    for (j = 0; j < NUMBER_OF_SLOTS(ptr); j++)
			      gc_mark(THE_SLOT_OF(ptr, j));
			    return;
			  }
     case tc_next_method: gc_mark(CAR(ptr)); ptr = CDR(ptr); goto Top;
#endif
#ifdef USE_TK
     case tc_tkcommand:	  ptr = ptr->storage_as.tk.l_data; goto Top;
     case tc_tclobject:	  ptr = CAR(ptr); if (ptr) goto Top;
       			  return;
#endif
     case tc_quote:	  return;
     case tc_lambda:	  return;
     case tc_if:	  return;
     case tc_setq:	  return;
     case tc_cond:	  return;
     case tc_and:	  return;
     case tc_or:	  return;
     case tc_let:	  return;
     case tc_letstar:	  return;
     case tc_letrec:	  return;
     case tc_begin:	  return;
     case tc_promise: 	  ptr = ptr->storage_as.promise.expr; goto Top;
     case tc_apply:
     case tc_call_cc:	  return;
     case tc_dynwind:	  return;
     case tc_extend_env:  return;
     case tc_unbound:     return;
     case tc_arbiter:	  ptr = CDR(ptr); if (ptr) goto Top; return;
     default:		  if (EXTENDEDP(ptr)) {STk_extended_mark(ptr); return;}
   }
   /* if we are here, it's an implementation error. Signal it */
   Fprintf(STk_curr_eport, "INTERNAL ERROR: trying to mark %lx (type=%d)\n", 
	   		   (unsigned long) ptr, TYPE(ptr));
}

static void gc_sweep(void)
{
  SCM ptr, heap_org, heap_end, nfreelist;
  long n;
  int  i;

  n 	    =  0;
  nfreelist = NIL;

  for (i = 0; i < heaps_used; i++) {
    /* Sweep a heap */
    heap_org = heaps[i];
    heap_end = heap_org + heap_size;

    for (ptr=heap_org; ptr < heap_end; ptr++) {
      if (ptr->gc_mark == 0) {
	switch (TYPE(ptr)) {
          case tc_nil: 	       break;
	  case tc_cons:	       break;
	  case tc_flonum:      break;
	  case tc_integer:     break;
	  case tc_bignum:      mpz_clear(BIGNUM(ptr)); free(BIGNUM(ptr)); break;
	  case tc_symbol:      STk_free_symbol(ptr); break;
	  case tc_keyword:     STk_free_keyword(ptr); break;
	  case tc_subr_0:      break;
	  case tc_subr_1:      break;
	  case tc_subr_2:      break;
	  case tc_subr_3:      break;
	  case tc_subr_0_or_1: break;
	  case tc_subr_1_or_2: break;
	  case tc_subr_2_or_3: break;
	  case tc_lsubr:       break;
	  case tc_ssubr:       break;
	  case tc_fsubr:       break;
	  case tc_syntax:      break;
	  case tc_closure:     break;
	  case tc_free_cell:   break;
	  case tc_char:	       break;
	  case tc_string:      free(ptr->storage_as.string.data); break;
	  case tc_vector:      free(ptr->storage_as.vector.data); break;
	  case tc_eof:         break;
	  case tc_undefined:   break;
	  case tc_iport:       
	  case tc_oport:       STk_freeport(ptr); break;
	  case tc_isport:      
	  case tc_osport:      STk_free_string_port(ptr); break;
	  case tc_ivport:      
	  case tc_ovport:      STk_free_virtual_port(ptr); break;
	  case tc_boolean:     break;
	  case tc_macro:       break;
	  case tc_localvar:    break;
	  case tc_globalvar:   break;
	  case tc_modulevar:   break;
	  case tc_cont:	       free(ptr->storage_as.cont.data); break;
	  case tc_env:	       break;
	  case tc_address:     break;
	  case tc_autoload:    break;
	  case tc_Cpointer:    if (!EXTSTATICP(ptr)) free(EXTDATA(ptr)); break;
	  case tc_module:      STk_free_module(ptr); break;
	  case tc_frame:       break;
	  case tc_values:      break;
#ifdef USE_STKLOS
	  case tc_instance:    STk_free_instance(ptr); 	break;
	  case tc_next_method: break;
#endif
#ifdef USE_TK
	  case tc_tkcommand:  if (! ptr->storage_as.tk.data->deleted)
	    			 STk_internal_Tcl_DeleteCommand
				     (STk_main_interp, ptr->storage_as.tk.data->Id);
			       free(ptr->storage_as.tk.data);
			       break;
	  case tc_tclobject:   break;
#endif
	  case tc_quote:       break;
	  case tc_lambda:      break;
	  case tc_if:	       break;
	  case tc_setq:	       break;
	  case tc_cond:	       break;
	  case tc_and:	       break;
	  case tc_or:	       break;
	  case tc_let:	       break;
	  case tc_letstar:     break;
	  case tc_letrec:      break;
	  case tc_begin:       break;
	  case tc_promise:     break;
	  case tc_apply:       break;
	  case tc_call_cc:     break;
	  case tc_dynwind:     break;
	  case tc_extend_env:  break;
	  case tc_unbound:     break;
      case tc_arbiter:     break;
	  default:	       if (EXTENDEDP(ptr))
	    			STk_extended_sweep(ptr);
	  		       else 
				 Fprintf(STk_curr_eport,
				     "FATAL ERROR: trying to sweep %lx (type=%d)\n",
				     (unsigned long) ptr, TYPE(ptr));
        }
	
	/* Declare this cell free and put it in free list */
	ptr->type	= tc_free_cell;
	ptr->cell_info  = 0;
	CDR(ptr)	= nfreelist;
	nfreelist	= ptr;
	n              += 1;
      }
      else 
	ptr->gc_mark = 0;
    }
  }
  gc_cells_collected = n;
  STk_freelist 	     = nfreelist;
}

void STk_mark_stack(SCM *start, SCM *end)
{
  register SCM p, heap_org;
  register long i, j, n;
  
  if (start > end) {
    SCM *tmp;
    tmp = start; start = end; end = tmp;
  }
  n = end - start;

  if (gc_verbose)
    Fprintf(STk_curr_eport, "[Marking zone <0x%lx->0x%lx> (%ld words)]\n",
	    (unsigned long) start, (unsigned long) end, (unsigned long) n);

  for(j=0; j<n; j++) {
    p = start[j];
    /* if p looks as a SCM pointer mark location */
    for (i=0; i < heaps_used; i++) {
      heap_org = heaps[i];
      if (VALID_ADDRESS(heap_org, p) && NTYPEP(p,tc_free_cell)) gc_mark(p);
    }
  }
}

static void mark_protected(void)
{
  struct gc_protected *reg;

  /* Mark protected vars */
  for(reg = protected_registers; reg; reg = reg->next) gc_mark(*(reg->location));
  
  /* Mark all objects accessible from obarray */
  STk_mark_symbol_table();

  /* Mark the module table */
  STk_mark_module_table();

  /* Mark the signal table */
  STk_mark_signal_table();

  /* Mark the table of traced variables */
  STk_mark_tracevar_table();

#ifdef USE_TK
  /* Mark all Tcl/Tk callbacks */
  STk_mark_callbacks();
#endif
}


static void gc_start(void)
{
  time_gc_start       = STk_my_time();
  gc_calls           += 1;
  gc_cells_collected  = 0;
  gc_verbose	      = STk_lookup_variable(GC_VERBOSE, NIL) != Ntruth;

  if (gc_verbose) Puts(";; [starting GC]\n", STk_curr_eport);
}

static void gc_end(void)
{
  long total_cells, used_cells;
  double time_for_this_gc;

  total_cells = heaps_used * heap_size;
  used_cells  = total_cells - gc_cells_collected;

  time_for_this_gc   = STk_my_time() - time_gc_start;
  STk_total_gc_time += time_for_this_gc;

  /* 
   * If heap is more than 75% filled after gc, allocate a new heap to 
   * avoid continuous GCs
   */
  if (((float) used_cells / total_cells) > 0.75) allocate_new_heap();

  STk_gc_requested = 0;

  if (gc_verbose) 
    Fprintf(STk_curr_eport, ";; [end of GC (cells used: %ld/%ld; time: %.2fms)]\n", 
	    used_cells, total_cells, time_for_this_gc);
}

static void gc_mark_and_sweep(void)
{
  long prev_context = STk_err_handler->context;
  SCM stack_end;     /* The topmost variable (at least a SCM) allocated on stack */


  /**** Disallow interrupts while GC'ing because signal handlers may cons */
  STk_ignore_signals();
  STk_err_handler->context = ERR_FATAL;
  gc_start();

  /**** Marking phase */
  setjmp(save_regs_gc_mark);	  				    /* registers */
  STk_mark_stack((SCM *) save_regs_gc_mark,
		 (SCM *) (((char *) save_regs_gc_mark)+
			  sizeof(save_regs_gc_mark)));
  STk_mark_stack((SCM *) STk_stack_start_ptr, (SCM *) &stack_end);  /* stack */
  mark_protected();						    /* globals */

  /**** Sweep phase */
  gc_sweep();

  /* Re-allow signals */
  gc_end();
  STk_err_handler->context = prev_context;
  STk_allow_signals();

  /* send the pseudo-signal SIGHADGC to say that we had a finished GC'ing */
  STk_signal_GC();
}

void STk_gc_for_newcell(void)
{
  if (STk_err_handler->context != ERR_FATAL) {
    gc_mark_and_sweep();
    if (NNULLP(STk_freelist)) return;
  }
  panic("Out of storage");
}


PRIMITIVE STk_gc(void)
{
  gc_mark_and_sweep();
  return UNDEFINED;
}

void STk_gc_protect(SCM *location)
{
  struct gc_protected *reg;

  reg = (struct gc_protected *) must_malloc(sizeof(struct gc_protected));
  
  reg->location 	= location;
  reg->next     	= protected_registers;
  protected_registers 	= reg;
}

void STk_gc_unprotect(SCM *location)
{
  struct gc_protected *reg, *prev;

  for (prev=NULL, reg=protected_registers; reg; prev=reg, reg=reg->next) 
    if (reg->location == location) {
      if (prev) 
	prev->next = reg->next;
      else
	protected_registers = reg->next;
      free(reg);
      return;
    }
}


PRIMITIVE STk_gc_stats(void)
{
  int i, freq[tc_stop_extd+1];
  register SCM ptr, heap_org, heap_end;
  long used_cells = 0L;

  /* Reset array of frequencies */
  for (i=0; i <=tc_stop_extd; i++) freq[i] =  0;
  
  /* Fill the frequencies array */
  for (i=0; i < heaps_used; i++) {
    heap_org = heaps[i];
    heap_end = heap_org + heap_size;

    for(ptr = heap_org; ptr < heap_end; ptr++) {
      if (NTYPEP(ptr, tc_free_cell)) {
	used_cells 	+= 1;
	freq[TYPE(ptr)] += 1;
      }
    }
  }

  /* Print statistics */
  Puts(";; GC statistics\n", STk_curr_eport);
  Puts(";; -------------\n", STk_curr_eport);
  Fprintf(STk_curr_eport, ";; cells used %ld/%ld\n", used_cells, 
	  					     heaps_used*heap_size);
  Fprintf(STk_curr_eport, ";; # of used heaps %d\n", heaps_used); 
  Fprintf(STk_curr_eport, ";; # of GC calls %d (time spent in GC %.2fms)\n", 
	  gc_calls, STk_total_gc_time);

  for (i=0; i <= tc_stop_extd; i++)
    if (freq[i]) Fprintf(STk_curr_eport, "(%d %d) ", i,  freq[i]);

  Puts("\n;;\n", STk_curr_eport);
  Flush(STk_curr_eport);
 
  return UNDEFINED;
}

#ifdef DEBUG_STK
PRIMITIVE STk_find_cells(SCM type)
{
  SCM ptr, z, heap_org, heap_end;
  int i,t,l;

  if (NINTEGERP(type)) Err("%find-cells: bad integer", type);
  t = INTEGER(type);

  /* Count how many items we have */
  for (i=l=0; i < heaps_used; i++) {
    heap_org = heaps[i];
    heap_end = heap_org + heap_size;
    
    for (ptr=heap_org; ptr < heap_end; ptr++)
      if (TYPEP(ptr, t)) l += 1;
  }

  /* Allocate a vector for the result */
  z = STk_makevect(l, NULL);
  l = 0;
  
  /* Place all the items in the newly created vector */
  for (i=l=0; i < heaps_used; i++) {
    heap_org = heaps[i];
    heap_end = heap_org + heap_size;
  
    for (ptr=heap_org; ptr < heap_end; ptr++)
      if (ptr != z && TYPEP(ptr, t))
	VECT(z)[l++] = ptr;
  }
  return z;
}
#endif

PRIMITIVE STk_expand_heap(SCM arg)
{
  int i, number_of_heaps, wanted;

  if (NINTEGERP(arg)) Err("expand-heap: bad value", arg);

  gc_verbose      = STk_lookup_variable(GC_VERBOSE, NIL) != Ntruth;
  wanted	  = INTEGER(arg);
  number_of_heaps = (wanted + heap_size - 1) / heap_size;
  
  for (i = heaps_used; i < number_of_heaps; i++)
    allocate_new_heap();
  return UNDEFINED;
}

/*=============================================================================*/
/*				i n i t 				       */
/*=============================================================================*/

#ifndef max
#define max(a,b) (((a)<(b))?(b):(a))
#endif 

void STk_init_gc(void)
{
  STk_freelist = NIL;
  if (STk_arg_cells) {
    /* Set the heap size to the specified value */
    int tmp = atoi(STk_arg_cells);
    if (tmp > 0) heap_size = max(tmp,MIN_HEAP);
  }
  allocate_new_heap();
}
