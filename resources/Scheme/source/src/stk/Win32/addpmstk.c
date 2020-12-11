/* STk install program. */
/* Ripped off from: */
/* Add entries to the GNU emacs Program Manager folder.
   Copyright (C) 1995 Free Software Foundation, Inc.

This file is part of GNU emacs.

GNU emacs is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU emacs is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU emacs; see the file COPYING.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

/****************************************************************************
 *
 * Program: addpmstk	(adds stk to the Windows program manager)
 *
 * Usage:
 *   	argv[1] = install path for stk
 *	argv[2] = full path to icon for stk (optional)
 */

#include <windows.h>
#include <ddeml.h>
#include <stdlib.h>
#include <stdio.h>

HDDEDATA CALLBACK 
DdeCallback (UINT uType, UINT uFmt, HCONV hconv,
	     HSZ hsz1, HSZ hsz2, HDDEDATA hdata,
	     DWORD dwData1, DWORD dwData2)
{
  return ((HDDEDATA) NULL);
}

#define DdeCommand(str) 	\
	DdeClientTransaction (str, strlen (str)+1, HConversation, (HSZ)NULL, \
		              CF_TEXT, XTYP_EXECUTE, 30000, NULL)


int
main (argc, argv)
     int argc;
     char *argv[];			
{
  DWORD idDde = 0;
  HCONV HConversation;
  HSZ ProgMan;
  char modname[MAX_PATH];
  char additem[MAX_PATH*2 + 100];
  char *prog_name1, *prog_name2, *prog_name3, *prog_name4, *prog_name5;
  char *stk_path;
  char *p;

  /* If no args specified, use our location to set stk_path.  */

  if (argc > 1)
    stk_path = argv[1];
  else
    {
      if (!GetModuleFileName (NULL, modname, MAX_PATH) ||
	  (p = strrchr (modname, '\\')) == NULL)
	{
	  fprintf (stderr, "fatal error");
	  exit (1);
	}
      *p = 0;

      /* Set stk_path to stk_dir if we are in "%stk_dir%\bin".  */
      if ((p = strrchr (modname, '\\')) && stricmp (p, "\\MS-Win32") == 0)
	{
	  *p = 0;
	  stk_path = modname;
	}
      else
	{
	  fprintf (stderr, "usage: addpmstk stk_folder_path\n");
	  exit (1);
	}

      /* Tell user what we are going to do.  */
      {
	int result;

	char msg[ MAX_PATH ];
	sprintf (msg, "Install stk at %s?\n", stk_path);
	result = MessageBox (NULL, msg, "Install stk", MB_OKCANCEL | MB_ICONQUESTION);
	if (result != IDOK)
	  {
	    fprintf (stderr, "Install cancelled\n");
	    exit (1);
	  }
      }
    }

  prog_name1 = "stk.exe";
  prog_name2 = "envdraw.bat";
  prog_name3 = "stk-explorin.bat";
  prog_name4 = "stk-simply.bat";
  prog_name5 = "stk-grfx.bat";

  DdeInitialize (&idDde, (PFNCALLBACK)DdeCallback, APPCMD_CLIENTONLY, 0);

  ProgMan = DdeCreateStringHandle (idDde, "PROGMAN", CP_WINANSI);

  HConversation = DdeConnect (idDde, ProgMan, ProgMan, NULL);
  if (HConversation != 0)
    {
	/* Install UCB Scheme folder */
      DdeCommand ("[CreateGroup (\"UCB Scheme\")]");
	/* install STk */
	  DdeCommand ("[ReplaceItem (STk)]");      
	sprintf (additem, "[AddItem (\"%s\\MS-Win32\\%s\", STk)]",
		 stk_path, prog_name1);
	  DdeCommand (additem);
	/* install EnvDraw */
     DdeCommand ("[ReplaceItem (EnvDraw)]");
	sprintf (additem, "[AddItem (\"%s\\MS-Win32\\%s\", EnvDraw)]",
		 stk_path, prog_name2);
      DdeCommand (additem);

      	/* install stk-explorin  */
	  DdeCommand ("[ReplaceItem (STk-explorin)]");
	sprintf (additem, "[AddItem (\"%s\\MS-Win32\\%s\", STk-explorin)]",
		 stk_path, prog_name3);
      DdeCommand (additem);

	/* install stk-simply */
	  DdeCommand ("[ReplaceItem (STk-simply)]");
	sprintf (additem, "[AddItem (\"%s\\MS-Win32\\%s\", STk-simply)]",
		 stk_path, prog_name4);
      DdeCommand (additem);

	/* install stk-grfx */
	  DdeCommand ("[ReplaceItem (STk-grfx)]");
	sprintf (additem, "[AddItem (\"%s\\MS-Win32\\%s\", STk-grfx)]",
		 stk_path, prog_name5);
      DdeCommand (additem);

      
      DdeDisconnect (HConversation);
    }

  DdeFreeStringHandle (idDde, ProgMan);

  DdeUninitialize (idDde);

  return (0);
}
