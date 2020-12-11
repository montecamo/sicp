/*
 * s l i b . c				-- Misc functions
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
 *           Author: Erick Gallesio [eg@unice.fr]
 *    Creation date: ??-Oct-1993 ??:?? 
 * Last file update:  3-Sep-1999 20:22 (eg)
 *
 */

#ifdef WIN32
#  include <windows.h>
#endif

#include "stk.h"
/* #include "stkvers.h" */
#include "gc.h"
#include <sys/types.h>
#include <sys/stat.h>

#ifdef WIN32
#   include <time.h>
#   ifndef CYGWIN32
#      include <dos.h>
#   endif
#   include <process.h>
#   include <tclWinPort.h>
#else
#   include <limits.h>
#   include <stdarg.h>
#   include <sys/times.h>
#endif

#ifdef USE_TK
#   include "tk-glue.h"
#endif



#ifndef _DEBUG_MALLOC_INC

#ifdef malloc
#undef malloc
#endif

#ifdef realloc
#undef realloc
#endif

#define MAX_MALLOC_BEFORE_GC 1<<20	/* 1 Mb should suffice before calling GC */

static size_t malloc_count = 0;


static void cannot_allocate()
{
  Puts("**** Storage allocation from system failed\n", STk_curr_eport);
  Puts("**** Evaluation aborted\n", STk_curr_eport);
  
  STk_gc_requested = 1;

  STk_allow_signals();

  /* Use a null message to avoid a call to report-error (which uses conses) */
  Err("", NIL);
}

void *STk_must_malloc(size_t size)
{
  void *tmp;

/*  STk_ignore_signals(); */
  tmp = (void *) malloc(size);

  /* Test for size because some libc return NULL when doing malloc(0) */
  if (tmp == NULL && size) cannot_allocate();

  /* Idea of malloc limitation comes from Harvey J. Stein 
   * <hjstein@MATH.HUJI.AC.IL>. The following code provoke a GC when
   * MAX_MALLOC_BEFORE_GC have been allocated by must_malloc. This 
   * allows to GC before all cells have been exhausted 
   */
  malloc_count +=size;
  if (malloc_count > MAX_MALLOC_BEFORE_GC) {
    malloc_count     = 0;
    STk_gc_requested = 1;
  }

/*   STk_allow_signals(); */
  return tmp;
}

void *STk_must_realloc(void *ptr, size_t size)
{
  void *tmp;

  STk_ignore_signals();

  tmp = (void *) realloc(ptr, size);
  /* Since we cannot know (in a portable way) the size of area pointed by ptr,
   * we will make the assumption that it is half the new requested size. 
   * Of course, we are probably false here, but it seems more reasonable than 
   * brutally increment it with size. 
   */
  malloc_count +=size/2;
  if (malloc_count > MAX_MALLOC_BEFORE_GC) {
    malloc_count     = 0;
    STk_gc_requested = 1;
  }

  if (tmp == NULL) cannot_allocate();

  STk_allow_signals();
  return tmp;
}
#endif


SCM STk_internal_eval_string(char *s, long context, SCM env)
{
  SCM result, port;

  PUSH_ERROR_HANDLER
    {
      /* Create a string port to read the sexpr and evaluate it in a new context */
      STk_err_handler->context |= context;
      port   = STk_internal_open_input_string(s);
      result = STk_eval(STk_readf(port, FALSE), env);
    }
  WHEN_ERROR
    {
      /* Two cases:
       *    - if we are in a catch, propagate the error to go back in the
       *      context of the catch
       *    - otherwise error has already been signaled, do nothing
       */
      if ((STk_err_handler->context & ERR_TCL_BACKGROUND) && STk_control_C)
	result = Ntruth;
      else {
	if (STk_err_handler->context & ERR_IGNORED) PROPAGATE_ERROR();
	result = EVAL_ERROR;
      }
    }
  POP_ERROR_HANDLER;
  return result;
}


PRIMITIVE STk_catch(SCM expr, SCM env, int unused_len)
{
  SCM result;
  SCM l;
  
  PUSH_ERROR_HANDLER
    {
      /* Evaluate the list of expressions in a context where errors are ignored */
      STk_err_handler->context |= ERR_IGNORED;
      for (l = expr; NNULLP(l); l = CDR(l))
	STk_eval(CAR(l), env);
      result = Ntruth;
    }
  WHEN_ERROR
    {
      result = Truth;
    }
  POP_ERROR_HANDLER;

  return result;
}


PRIMITIVE STk_quit_interpreter(SCM retcode)
{
  long ret = 0;

  if (retcode != UNBOUND) {
    if ((ret=STk_integer_value(retcode)) == LONG_MIN)
      Err("quit: bad return code", retcode);
  }

  /* Execute all the terminal thunks of pending dynamic-wind */
  STk_unwind_all();

  /* call user finalization code */
  STk_user_cleanup();

  STk_transcript_off();

#ifdef USE_TK
  /* Unregister the interpreter from X server */
  if (Tk_initialized) Tcl_DeleteCommand(STk_main_interp, ".");
#endif

#if defined(WIN32) && defined(USE_SOCKET)
  /* Unregister the interpreter from Winsock */
  WSACleanup();  
#endif
  exit(ret);
  return UNDEFINED; /* never reached */
}

PRIMITIVE STk_version(void)
{
  return STk_makestring(STK_VERSION);
}

PRIMITIVE STk_machine_type(void)
{
  return STk_makestring(MACHINE);
}

PRIMITIVE STk_library_location(void)
{
  return STk_makestring(STk_library_path);
}

PRIMITIVE STk_random(SCM n)
{
  if (NEXACTP(n) || STk_negativep(n) == Truth || STk_zerop(n) == Truth)
    Err("random: bad number", n);
  return STk_modulo(STk_makeinteger(rand()), n);
}

PRIMITIVE STk_set_random_seed(SCM n)
{
  if (NEXACTP(n)) Err("set-random-seed!: bad number", n);
  srand((unsigned int) STk_integer_value_no_overflow(n));
  return UNDEFINED;
}

#ifndef HZ
#define HZ 60.0
#endif

#if defined(CLK_TCK)
#  define TIC CLK_TCK
#elif defined(CLOCKS_PER_SEC)
#  define TIC CLOCKS_PER_SEC
#else 
#  define TIC HZ
#endif

double STk_my_time(void)
{
#if defined (WIN32)
  return (long) 1000*(clock()/CLK_TCK);
#else
  struct tms time_buffer;
  times(&time_buffer);
  return (1000.0 * (time_buffer.tms_utime + time_buffer.tms_stime)) / TIC;
#endif
}


PRIMITIVE STk_get_internal_info(void)
{
  SCM z = STk_makevect(7, NIL);
  long allocated, used, calls;

  /* The result is a vector which contains
   *	0 The total cpu used in ms
   *	1 The number of cells currently in use.
   *    2 Total number of allocated cells
   *	3 The number of cells used since the last call to get-internal-info
   *	4 Number of gc calls
   *    5 Total time used in the gc
   *	6 A boolean indicating if Tk is initialized
   */

  STk_gc_count_cells(&allocated, &used, &calls);

  VECT(z)[0] = STk_makenumber(STk_my_time());
  VECT(z)[1] = STk_makeinteger(used);
  VECT(z)[2] = STk_makeinteger(allocated);
  VECT(z)[3] = STk_makenumber((double) STk_alloc_cells);
  VECT(z)[4] = STk_makeinteger(calls);
  VECT(z)[5] = STk_makenumber((double) STk_total_gc_time);
#ifdef USE_TK
  VECT(z)[6] = Tk_initialized ? Truth: Ntruth;
#else
  VECT(z)[6] = Ntruth;
#endif
  
  STk_alloc_cells = 0;
  return z;
}


PRIMITIVE STk_time(SCM expr, SCM env, int len)
{
  double rt, gc_time;
  SCM res;

  if (len != 1) Err("time: bad expression" , expr);

  STk_alloc_cells = 0;
  gc_time         = STk_total_gc_time;
  rt 	          = STk_my_time();
  res 	          = EVALCAR(expr);
  Fprintf(STk_curr_eport,
	  ";;    Time: %.2lfms\n;; GC time: %.2lfms\n;;   Cells: %ld\n",
	  STk_my_time()-rt, STk_total_gc_time-gc_time, STk_alloc_cells);
  return res;
}

      
/*
 * STk_delete_Tcl_child_Interp
 *
 * 	This function must be called by a child process just after a fork
 * It deletes the Tk commands associated to the interpreter (except send, 
 * to avoid interpreter unregistering).
 * 
 * This must probably rewritten
 */

void STk_delete_Tcl_child_Interp(void)
{
#ifdef USE_TK
  if (Tk_initialized) {
    struct Tk_command *W;
    Interp *iPtr = (Interp *) STk_main_interp;
    Tcl_HashEntry *hPtr;

    /* Try to find "send". Modify it's delproc to point NULL */
    hPtr = Tcl_FindHashEntry(&iPtr->globalNsPtr->cmdTable, "send");
    if (hPtr != NULL) {
      W = (struct Tk_command *) Tcl_GetHashValue(hPtr);
      W->delproc = NULL;
    }
    /* Now we can destroy the interpreter  (send will not be destroyed) */
    Tcl_DeleteInterp(STk_main_interp);
    
    /* Report-error points to a graphical procedure. Undefine it 
     * to display error messages on stderr in the child process
     */
    STk_define_variable(REPORT_ERROR, UNBOUND, NIL);

    /* Redefine exit to the standard STk exit function */
    STk_add_new_primitive("exit", tc_subr_0_or_1, STk_quit_interpreter);
  }
#else
  /* Nothing to do for Snow */
#endif
}


/* When STk evaluates an expression, it recodes it in a manner which permits it
   to be more efficient for further evaluations. The uncode functions permits to 
   do the reverse job: it takes an exppression and returns a form similar to the 
   original one. 
   Warning: when a macro has been expanded, there is no mean to "revert" it to 
   its original form 
*/


static SCM associate(SCM l1, SCM l2)
{
  SCM z;

  if (NULLP(l1)) return NIL;
  
  for(z= NIL; NNULLP(l1); l1=CDR(l1), l2=CDR(l2))
    z = Cons(LIST2(CAR(l1), STk_uncode(CAR(l2))), z);
  
  return Reverse(z);
}

static SCM uncode_let(char *type, SCM expr)
{
  return Cons(Intern(type),
	      Cons(associate(CAR(expr), CAR(CDR(expr))),
		   STk_uncode(CDR(CDR(expr)))));
}
  
PRIMITIVE STk_uncode(SCM expr)
{
  static int recursion_level = 0;
  SCM rv;
  recursion_level++;
  switch (TYPE(expr)) {
    case tc_cons: switch (TYPE(CAR(expr))) {
    		    case tc_let:     rv = uncode_let("let",    CDR(expr));  break;
      		    case tc_letstar: rv = uncode_let("let*",   CDR(expr));  break;
		    case tc_letrec:  rv = uncode_let("letrec", CDR(expr));  break;
		    case tc_if: 
		         expr = CDR(expr);
		         if (EQ(CAR(CDR(CDR(expr))), UNDEFINED)) 
			   rv = Cons(Intern("if"),
				       LIST2(STk_uncode(CAR(expr)),
					     STk_uncode(CAR(CDR(expr)))));
			 else
			   rv = Cons(Intern("if"),
				       LIST3(STk_uncode(CAR(expr)),
					     STk_uncode(CAR(CDR(expr))),
					     STk_uncode(CAR(CDR(CDR(expr))))));
				break;
		    default: if (recursion_level < 25) {
                       rv = Cons(STk_uncode(CAR(expr)),
					     STk_uncode(CDR(expr)));
                     } else {
                       rv = expr;
                     }
                       break;
		  }
		  break;
    case tc_quote:	rv = Intern("quote"); break;
    case tc_lambda:	rv = Intern("lambda"); break;
    case tc_if:		rv = Intern("if"); break;
    case tc_setq:	rv = Intern("set!"); break;
    case tc_cond:	rv = Intern("cond"); break;
    case tc_and:	rv = Intern("and"); break;
    case tc_or:		rv = Intern("or"); break;
    case tc_let:	rv = Intern("let"); break;
    case tc_letstar:	rv = Intern("letstar"); break;
    case tc_letrec: 	rv = Intern("letrec"); break;
    case tc_begin:	rv = Intern("begin"); break;
    case tc_globalvar:  rv = VCELL(expr); break;
    case tc_localvar:   rv = expr->storage_as.localvar.symbol; break;
    case tc_modulevar:	rv = CAR(CAR(expr)); break;
    case tc_apply:	rv = Intern("apply"); break;
    case tc_call_cc:	rv = Intern("call-with-current-continuation"); break;
    case tc_dynwind:    rv = Intern("dynamic-wind"); break;
    case tc_extend_env: rv = Intern("extend-environment"); break;
    default:		rv = expr; break;
  }
  recursion_level--;
  return rv;
}


#ifdef DEBUG_STK

/* Debug code to use with debugger */
void dbg(SCM obj); 
void dbgeval(void);

void dbg(SCM obj)
{
  Fprintf(STk_curr_eport, " <<#p%lx>> ", (unsigned long) obj);
  STk_print(obj, STk_curr_eport, WRT_MODE);
  Putc('\n', STk_curr_eport);
}

void dbgeval(void)
{
  SCM x;
  

  for ( ; ; ) {
    Fprintf(STk_curr_eport, "Debug STk> "); Flush(STk_curr_eport);
    if (EQ(x=STk_readf(STk_stdin, FALSE), STk_eof_object)) return;
    dbg(STk_eval(x, STk_selected_module));
  }
}

void Debug(char *message, SCM obj)
{
  Flush(STk_curr_oport); Flush(STk_curr_eport);
  Puts("****", STk_curr_eport); Puts(message, STk_curr_eport);
  dbg(obj);
  Flush(STk_curr_oport); Flush(STk_curr_eport);
}

#endif



/******************************************************************************
 *
 * The following declarations serve only for referencing symbols which are used
 * by Tcl or Tk and which are defined in this directory. Otherwise, the ld will
 * not find them and report an error
 *
 ******************************************************************************/
#ifndef WIN32
typedef void (*dumb)();

dumb STk_dumb[] = {
  (dumb) Tcl_TildeSubst,
  (dumb) Tcl_SetVar2,
  (dumb) Tcl_NewListObj
};
#endif
