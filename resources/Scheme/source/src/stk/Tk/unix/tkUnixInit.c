/* 
 * tkUnixInit.c --
 *
 *	This file contains Unix-specific interpreter initialization
 *	functions.
 *
 * Copyright (c) 1995-1997 Sun Microsystems, Inc.
 *
 * See the file "license.terms" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 * SCCS: @(#) tkUnixInit.c 1.24 97/07/24 14:46:09
 */

#include "tkInt.h"
#include "tkUnixInt.h"

#ifndef SCM_CODE
/*
 * The Init script (common to Windows and Unix platforms) is
 * defined in tkInitScript.h
 */
#include "tkInitScript.h"
#endif


/*
 *----------------------------------------------------------------------
 *
 * TkpInit --
 *
 *	Performs Unix-specific interpreter initialization related to the
 *      tk_library variable.
 *
 * Results:
 *	Returns a standard Tcl result.  Leaves an error message or result
 *	in interp->result.
 *
 * Side effects:
 *	Sets "tk_library" Tcl variable, runs "tk.tcl" script.
 *
 *----------------------------------------------------------------------
 */

int
TkpInit(interp)
    Tcl_Interp *interp;
{
    TkCreateXEventSource();
#ifdef SCM_CODE
    return TCL_OK;
#else
    return Tcl_Eval(interp, initScript);
#endif
}

#ifndef SCM_CODE
/*
 *----------------------------------------------------------------------
 *
 * TkpGetAppName --
 *
 *	Retrieves the name of the current application from a platform
 *	specific location.  For Unix, the application name is the tail
 *	of the path contained in the tcl variable argv0.
 *
 * Results:
 *	Returns the application name in the given Tcl_DString.
 *
 * Side effects:
 *	None.
 *
 *----------------------------------------------------------------------
 */

void
TkpGetAppName(interp, namePtr)
    Tcl_Interp *interp;
    Tcl_DString *namePtr;	/* A previously initialized Tcl_DString. */
{
    char *p, *name;

    name = Tcl_GetVar(interp, "argv0", TCL_GLOBAL_ONLY);
    if ((name == NULL) || (*name == 0)) {
	name = "tk";
    } else {
	p = strrchr(name, '/');
	if (p != NULL) {
	    name = p+1;
	}
    }
    Tcl_DStringAppend(namePtr, name, -1);
}

/*
 *----------------------------------------------------------------------
 *
 * TkpDisplayWarning --
 *
 *	This routines is called from Tk_Main to display warning
 *	messages that occur during startup.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	Generates messages on stdout.
 *
 *----------------------------------------------------------------------
 */

void
TkpDisplayWarning(msg, title)
    char *msg;			/* Message to be displayed. */
    char *title;		/* Title of warning. */
{
    Tcl_Channel errChannel = Tcl_GetStdChannel(TCL_STDERR);
    if (errChannel) {
	Tcl_Write(errChannel, title, -1);
	Tcl_Write(errChannel, ": ", 2);
	Tcl_Write(errChannel, msg, -1);
	Tcl_Write(errChannel, "\n", 1);
    }
}
#endif
