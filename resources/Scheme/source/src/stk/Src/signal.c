/*
 *
 * s i g n a l . c			-- Signal handling
 *
 * Copyright © 1993-1999 Erick Gallesio - I3S-CNRS/ESSI <eg@unice.fr>
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
 *    Creation date: 10-Oct-1995 07:55
 * Last file update:  3-Sep-1999 20:22 (eg)
 *
 */

#include "stk.h"
#include <signal.h>

#ifdef HAVE_SIGACTION
   static sigset_t global_sigset;
#  ifdef SA_RESTART
#    define SA_FLAGS SA_RESTART
#  else 
#    define SA_FLAGS 0
#  endif
#endif

#ifdef WIN32
# define SIGALRM 14
static UINT STk_alarm_timer = 0;
#endif /* WIN32 */

int STk_control_C = 0;

static SCM signals[MAX_SIGNAL];

/* Convention: signals[i] can be 
 * 			- #f if signal is ignored
 *			- #t if signal is set to default
 *			- a list of handlers
 */

static void execute_signal_handlers(int sig, SCM handlers)
{
  SCM arg = LIST1(STk_makeinteger(sig));

  for ( ; CONSP(handlers); handlers = CDR(handlers)) {
    if (Apply(CAR(handlers), arg) == Sym_break) break;
  } 
}


#ifdef SIGSEGV
static void handle_sigsegv_signal(void)
{
  SCM l = signals[SIGSEGV];
  
  if (l == NIL) {
    /* User has not redefined SIGSEGV action */
#ifdef HAVE_SIGACTION
    /* See comment in procedure above */
    sigset_t set;
    
    sigemptyset(&set);
    sigaddset(&set, SIGSEGV);
    sigprocmask(SIG_UNBLOCK, &set, NULL);
#endif
    /*  SEGV occurs generally when there is an error in the
     * interpreter. We cannot do a lot of things here, excepted
     * signalling this fact and go back to toplevel
     */
    Err("Segmentation violation: Returning to toplevel", NIL);
  }
  else 
    execute_signal_handlers(SIGSEGV, l);
}
#endif


void STk_handle_sigint_signal(void)
{
  SCM l = signals[SIGINT];
  
  if (l == NIL) {
    /* User has not redefined ^C action */
#ifdef HAVE_SIGACTION
    /* Empty the signal mask before calling a longjmp and don't let the
     *  system (at least Linux) a chance to restore the mask 
     */
    sigset_t set;
    
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigprocmask(SIG_UNBLOCK, &set, NULL);
#endif
    longjmp(STk_err_handler->j, JMP_INTERRUPT);
  }
  else {
    STk_eval_flag = STk_control_C = 0;
    execute_signal_handlers(SIGINT, l);
  }
}

/*===========================================================================*\
 *
 *				 STk_handle_signal
 *
\*===========================================================================*/

void STk_handle_signal(int sig)
{
#ifndef  HAVE_SIGACTION
  if (sig < MAX_SYSTEM_SIG)
    signal(sig, STk_handle_signal);
#endif

  if (sig == SIGINT) {			/* SIGINT */
    Puts("*** Interrupt ***\n", STk_curr_eport); Flush(STk_curr_eport);
    STk_control_C = 1; STk_eval_flag = 1;
  }
#ifdef SIGSEGV
  else if (sig == SIGSEGV) {		/* SIGSEGV */
    handle_sigsegv_signal();
  }
#endif
  else
#ifdef WIN32
  {
    if (sig == SIGALRM) KillTimer(NULL, STk_alarm_timer);
#endif /* WIN32 */
    execute_signal_handlers(sig, signals[sig]);
#ifdef WIN32
  }
#endif /* WIN32 */
}


static SCM set_handler(long s, SCM proc)
{
  void (*handler)(int);

  if (BOOLEANP(proc))
    /* Special case #f means ignore and #t means default */
    handler = (proc == Truth) ? SIG_DFL: SIG_IGN;
  else
    /* Use our handler */
    handler = STk_handle_signal;
     
  if (s < MAX_SYSTEM_SIG)
#ifdef HAVE_SIGACTION
    {
      struct sigaction sigact;
      
      sigfillset(&(sigact.sa_mask));
      /* FIXME: => handler non interruptible mais est-ce un problème en pratique? */
      /* sigdelset(&(sigact.sa_mask), SIGINT);  */
      sigact.sa_handler = handler;
      sigact.sa_flags   = SA_FLAGS;
      sigaction(s, &sigact, NULL);
    }
#else
    signal(s, handler);
#endif
  return signals[s] = proc;
}

/* Added by brg */
PRIMITIVE STk_try_arbiter(SCM arb)
{
  SCM rv;

  if (ARBITERP(arb)) {
    STk_ignore_signals();
    if (ARBLOCKEDP(arb)) {
      rv = Ntruth;
    } else {
      LOCKARB(arb);
      rv = Truth;
    }
    STk_allow_signals();
	return rv;
  }
  Err("try-arbiter: wrong type of argument", arb);
  return UNDEFINED; /* never reached */
}

/* Added by brg */
PRIMITIVE STk_make_arbiter(SCM name)
{
  SCM arb;

  NEWCELL(arb, tc_arbiter);
  UNLOCKARB(arb);
  CDR(arb) = name;
  return arb;
}

/* Added by brg */
PRIMITIVE STk_release_arbiter(SCM arb)
{
  if (ARBITERP(arb)) {
    if (! ARBLOCKEDP(arb)) {
      return Ntruth;
    }
    UNLOCKARB(arb);
    return Truth;
  }
  Err("release-arbiter: wrong type of argument", arb);
  return UNDEFINED; /* never reached */
}

/* Added by brg */
#ifdef WIN32
VOID CALLBACK STk_alarm_timer_proc(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	STk_handle_signal(SIGALRM); /* simulate signal receipt, and kill timer */
}

PRIMITIVE STk_alarm(SCM secs)
{
  long s = STk_integer_value(secs);

  ENTER_PRIMITIVE ("alarm");
  if (s < 0 || s > UINT_MAX) Serror ("invalid number of seconds", secs);
  if (s == 0) {
	  if (STk_alarm_timer) {
		if (! KillTimer(NULL, STk_alarm_timer)) {
			Serror("KillTimer failed", NIL);
		}
		STk_alarm_timer = 0;
	  }
  } else {
	  if (STk_alarm_timer) {
		  KillTimer(NULL, STk_alarm_timer);
	  }
	  if ((STk_alarm_timer = SetTimer(NULL, 0, 1000 * s, STk_alarm_timer_proc)) == 0) {
		Serror("SetTimer failed", NIL);
	  } else {
	    return STk_makeinteger(STk_alarm_timer);
	  }
  }
  return STk_makeinteger(-1);
}
#else /* WIN32 */
PRIMITIVE STk_alarm(SCM secs)
{
  long s = STk_integer_value(secs);
  unsigned int rv;

  ENTER_PRIMITIVE ("alarm");
  if (s < 0 || s > UINT_MAX) Serror ("invalid number of seconds", secs); 

  rv = alarm ((unsigned int) s);
  return STk_makeinteger (rv);
}
#endif /* WIN32 */

PRIMITIVE STk_set_signal_handler(SCM sig, SCM proc)
{
  long s = STk_integer_value(sig);

  ENTER_PRIMITIVE("set-signal-handler!");
  
  if (s == LONG_MIN || s < 0 || s >= MAX_SIGNAL) Serror("bad signal number", sig);

  if (BOOLEANP(proc))
    return set_handler(s, proc);
  else {
    if (STk_procedurep(proc) == Ntruth) Serror("bad procedure", proc);
    return set_handler(s, LIST1(proc));
  }
}

  
PRIMITIVE STk_add_signal_handler(SCM sig, SCM proc)
{
  long s = STk_integer_value(sig);

  ENTER_PRIMITIVE("add-signal-handler!");

  if (s == LONG_MIN || s < 0 || s >= MAX_SIGNAL) Serror("bad signal number", sig);

  if (STk_procedurep(proc) == Ntruth) Serror("bad procedure", proc);

  if (BOOLEANP(signals[s]))
    /* We add a handler on a defaulted or ignored signal */
    return  set_handler(s, LIST1(proc));
  else
    /* Just add the new signal in front of the list */
    return signals[s] = Cons(proc,signals[s]);
}

PRIMITIVE STk_get_signal_handlers(SCM sig)
{
  if (sig == UNBOUND) {				/* Return all handlers */
    SCM z;
  
    z = STk_makevect(MAX_SIGNAL, NULL);
    memcpy(VECT(z), signals, MAX_SIGNAL * sizeof(SCM));
    return z; 
  }
  else {					/* Return handlers of sig only */
    long s = STk_integer_value(sig);

    if (s == LONG_MIN || s < 0 || s >= MAX_SIGNAL)
      STk_err("get-signal-handlers: bad signal number", sig);
    return signals[s];
  }
}


PRIMITIVE STk_send_signal(SCM sig)
{
  long s = STk_integer_value(sig);
  
  ENTER_PRIMITIVE("send-signal");

  if (s < 0 || s >= MAX_SIGNAL) Serror("bad signal number", sig);
  
  STk_handle_signal(s);
  return UNDEFINED;
}


void STk_mark_signal_table(void)
{
  int i;

  for (i = 0; i < MAX_SIGNAL; i++) 
    STk_gc_mark(signals[i]);
}


void STk_ignore_signals(void)	/* Block all signals */
{
#ifdef HAVE_SIGACTION
  sigset_t new;

  sigfillset(&new);
  sigprocmask(SIG_BLOCK, &new, &global_sigset);
#endif
}

void STk_allow_signals(void)  /* Restore signals as  before ignore_signals */
{
#ifdef HAVE_SIGACTION
  sigprocmask(SIG_SETMASK, &global_sigset, NULL);
#endif
}


void STk_signal_GC(void)
{
  SCM old = signals[SIGHADGC];
  
  STk_ignore_signals();
  /* Ignore this signal while executing the handler */
  signals[SIGHADGC] = Ntruth;
  execute_signal_handlers(SIGHADGC, old);
  signals[SIGHADGC] = old;
  STk_allow_signals();
}
 
/*******************************************************************************/


void STk_init_signal(void)
{
  int i;

  for (i = 0; i < MAX_SIGNAL; i++) {
    set_handler(i, (i == SIGINT || i == SIGSEGV) ? NIL : Truth);
  }
  /* 
   * POSIX.1 signals 
   */
#ifdef SIGABRT
  STk_define_scheme_variable("SIGABRT", STk_makeinteger(SIGABRT));
#endif
#ifdef SIGALRM
  STk_define_scheme_variable("SIGALRM", STk_makeinteger(SIGALRM));
#endif
#ifdef SIGFPE
  STk_define_scheme_variable("SIGFPE", STk_makeinteger(SIGFPE));
#endif
#ifdef SIGHUP
  STk_define_scheme_variable("SIGHUP", STk_makeinteger(SIGHUP));
#endif
#ifdef SIGILL
  STk_define_scheme_variable("SIGILL", STk_makeinteger(SIGILL));
#endif
#ifdef SIGINT
  STk_define_scheme_variable("SIGINT", STk_makeinteger(SIGINT));
#endif
#ifdef SIGKILL
  STk_define_scheme_variable("SIGKILL", STk_makeinteger(SIGKILL));
#endif
#ifdef SIGPIPE
  STk_define_scheme_variable("SIGPIPE", STk_makeinteger(SIGPIPE));
#endif
#ifdef SIGQUIT
  STk_define_scheme_variable("SIGQUIT", STk_makeinteger(SIGQUIT));
#endif
#ifdef SIGSEGV
  STk_define_scheme_variable("SIGSEGV", STk_makeinteger(SIGSEGV));
#endif
#ifdef SIGTERM
  STk_define_scheme_variable("SIGTERM", STk_makeinteger(SIGTERM));
#endif
#ifdef SIGUSR1
  STk_define_scheme_variable("SIGUSR1", STk_makeinteger(SIGUSR1));
#endif
#ifdef SIGUSR2
  STk_define_scheme_variable("SIGUSR2", STk_makeinteger(SIGUSR2));
#endif

  /* 
   * Following signals exist only on system which support Job Control 
   */
#ifdef SIGCHLD
  STk_define_scheme_variable("SIGCHLD", STk_makeinteger(SIGCHLD));
#endif
#ifdef SIGCONT
  STk_define_scheme_variable("SIGCONT", STk_makeinteger(SIGCONT));
#endif
#ifdef SIGSTOP
  STk_define_scheme_variable("SIGSTOP", STk_makeinteger(SIGSTOP));
#endif
#ifdef SIGTSTP
  STk_define_scheme_variable("SIGTSTP", STk_makeinteger(SIGTSTP));
#endif
#ifdef SIGTTIN
  STk_define_scheme_variable("SIGTTIN", STk_makeinteger(SIGTTIN));
#endif
#ifdef SIGTTOU
  STk_define_scheme_variable("SIGTTOU", STk_makeinteger(SIGTTOU));
#endif

  /*
   * Non POSIX signals stolen on Sun and Linux
   */

#ifdef SIGTRAP
  STk_define_scheme_variable("SIGTRAP", STk_makeinteger(SIGTRAP));
#endif
#ifdef SIGIOT
  STk_define_scheme_variable("SIGIOT", STk_makeinteger(SIGIOT));
#endif
#ifdef SIGEMT
  STk_define_scheme_variable("SIGEMT", STk_makeinteger(SIGEMT));
#endif
#ifdef SIGBUS
  STk_define_scheme_variable("SIGBUS", STk_makeinteger(SIGBUS));
#endif
#ifdef SIGSYS
  STk_define_scheme_variable("SIGSYS", STk_makeinteger(SIGSYS));
#endif
#ifdef SIGURG
  STk_define_scheme_variable("SIGURG", STk_makeinteger(SIGURG));
#endif
#ifdef SIGCLD
  STk_define_scheme_variable("SIGCLD", STk_makeinteger(SIGCLD));
#endif
#ifdef SIGIO
  STk_define_scheme_variable("SIGIO", STk_makeinteger(SIGIO));
#endif
#ifdef SIGPOLL
  STk_define_scheme_variable("SIGPOLL", STk_makeinteger(SIGPOLL));
#endif
#ifdef SIGXCPU
  STk_define_scheme_variable("SIGXCPU", STk_makeinteger(SIGXCPU));
#endif
#ifdef SIGXFSZ
  STk_define_scheme_variable("SIGXFSZ", STk_makeinteger(SIGXFSZ));
#endif
#ifdef SIGVTALRM
  STk_define_scheme_variable("SIGVTALRM", STk_makeinteger(SIGVTALRM));
#endif
#ifdef SIGPROF
  STk_define_scheme_variable("SIGPROF", STk_makeinteger(SIGPROF));
#endif
#ifdef SIGWINCH
  STk_define_scheme_variable("SIGWINCH", STk_makeinteger(SIGWINCH));
#endif
#ifdef SIGLOST
  STk_define_scheme_variable("SIGLOST", STk_makeinteger(SIGLOST));
#endif

  /* Add GC signal */
  STk_define_scheme_variable("SIGHADGC", STk_makeinteger(SIGHADGC));
}
