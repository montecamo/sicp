/*
 *
 * e r r o r . c 			-- The error procedure
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
 *    Creation date: 14-Nov-1993 14:58
 * Last file update:  3-Sep-1999 20:19 (eg)
 */

#include "stk.h"

#ifdef DEBUG_STK
void print_error_handlers(void)			/* For debug only */
{
  struct error_handler *p;

  Fprintf(STk_stderr, "\t**** Error handlers\n");

  for (p = STk_err_handler;  ; p = p->prev) {
    Fprintf(STk_stderr, "\t\thandler(@%lx) = %02x =>",
	   (unsigned long) p, p->context);

    if (p->context & ERR_FATAL) 	   Fprintf(STk_stderr, "FATAL ");
    if (p->context & ERR_OK) 		   Fprintf(STk_stderr, "OK ");
    if (p->context & ERR_READ_FROM_STRING) Fprintf(STk_stderr, "READ_FROM_STRING ");
    if (p->context & ERR_IGNORED) 	   Fprintf(STk_stderr, "IGNORED ");
    if (p->context & ERR_TCL_BACKGROUND)   Fprintf(STk_stderr, "TCL_BACKGROUND ");
    if (p->context & ERR_IN_REPORT_ERROR)  Fprintf(STk_stderr, "IN_REPORT_ERROR ");
    if (p->context & ERR_IN_LOAD)          Fprintf(STk_stderr, "IN_LOAD ");
    Fprintf(STk_stderr, "\n");
    if (!p->prev) break;
  }
  Flush(STk_stderr);
}
#endif


		/***************************************************/

static void print_error_message(char *head, char *message, SCM who, 
				int uncode, int show_stack)
{
  if (uncode) who = STk_uncode(who);

  Fprintf(STk_curr_eport, "%s    %s", head, message);
  if (NNULLP(who)) {
    Puts(": ", STk_curr_eport);
    STk_write_star(who, STk_curr_eport);
  }
  if (show_stack) STk_show_eval_stack(10, uncode);
}



static void recursive_error(char *head, char *message, SCM x)
{
  Fprintf(STk_curr_eport,
	  "\n#### WARNING: error occurred while executing the body of %s!!\n", 
	  REPORT_ERROR);
  Fprintf(STk_curr_eport, "#### Error in %s was\n", REPORT_ERROR);
  print_error_message("", message, x, FALSE, TRUE);
  Fprintf(STk_curr_eport, "#### Going back to original error:\n");
  longjmp(STk_err_handler->j, JMP_ERROR);  /* Go back to previous call to error */
}


/*=============================================================================
 *
 * print-message 
 *
 *=============================================================================*/

static void print_message(char *message, SCM x)
{
  char head[MAX_PATH_LENGTH+50];
  int context = STk_err_handler->context;

  /*
   * Determine what the header of the message will contain depending of context
   */
  if (context & ERR_IN_REPORT_ERROR) {
    /* We have a recursive error (i.e. the printing function is buggy) */
    recursive_error(head, message, x);
  } else if (context & ERR_READ_FROM_STRING)
    strcpy(head,"*** Read from string error:\n");
#ifdef USE_TK
  else if (context & ERR_TCL_BACKGROUND)
    strcpy(head, "*** Background error:\n");
#endif
  else {
    /* ERR_FATAL or ERR_OK */
    if (STk_current_filename==UNBOUND)
      sprintf(head, "*** Error:\n");
    else {
      sprintf(head, "*** Error at line %d of file %s:\n",
	      STk_line_counter, CHARS(STk_current_filename));
      STk_current_filename = UNBOUND;
    }
  }

  /*
   * Header is constituted, call the report-error user procedure for
   * printing message (if available)
   */
  PUSH_ERROR_HANDLER
    {
       SCM tmp = STk_lookup_variable(REPORT_ERROR, NIL);

       STk_err_handler->context |= ERR_IN_REPORT_ERROR; /* for recursive errors */
       
       if (STk_procedurep(tmp) == Truth)
	 Apply(tmp, LIST3(STk_makestring(head),
			  STk_makestring(message),
			  STk_uncode(x)));
       else
	 print_error_message(head, message, x, TRUE, TRUE);
    }
  WHEN_ERROR
    {
      print_error_message(head, message, x, TRUE, FALSE);
      Putc('\n', STk_curr_eport);
    }
  POP_ERROR_HANDLER;

  Flush(STk_curr_oport); Flush(STk_curr_eport);
}


void STk_err(char *message, SCM x)
{
  STk_reset_eval_hook();

  /*  Retain the arguments of this error in global Scheme variables */
  STk_define_variable("*last-error-message*", STk_makestring(message), NIL);
  STk_define_variable("*last-error-arg*", x, NIL);
  
 /* Print a message if the error is not ignored */
  if (!(STk_err_handler->context & ERR_IGNORED)) {
    if (*message) print_message(message, x);
    STk_reset_eval_stack();
  }

  /* Propage the error if we are not in a critical section */
  if (STk_err_handler->context & ERR_FATAL)
    panic("FATAL ERROR IN CRITICAL CODE SECTION.");
  else
    longjmp(STk_err_handler->j, JMP_ERROR);
}


void STk_procedure_error(char *procedure, char *message, SCM x)
{
  char msg[200];

  sprintf(msg, "%s: %s", procedure, message);
  STk_err(msg, x);
}

PRIMITIVE STk_clear_recursive_error ()
{
  if (STk_err_handler)
    STk_err_handler->context &= ~ERR_IN_REPORT_ERROR;
  return UNDEFINED;
}
