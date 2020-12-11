dnl	This file is an input file used by the GNU "autoconf" program to
dnl	generate the file "configure", which is run during installation
dnl	to configure the system for the local environment.
dnl
dnl              Author: Erick Gallesio [eg@unice.fr]
dnl       Creation date: 27-Sep-1997 20:02
dnl    Last file update:  8-Apr-1998 10:54

AC_INIT(configure)

dnl AC_PROG_CC
AC_PROG_INSTALL

AC_PATH_PROG(UNZIP_PROGRAM, unzip)
AC_PATH_PROG(SED_PROGRAM, sed)
AC_PATH_PROG(MKDIR, mkdir)

dnl ==================================================================
dnl Generate makefiles
dnl ==================================================================

AC_CONFIG_FILES(Makefile bscheme/Makefile slib/Makefile envdraw/Makefile stkdb/Makefile)
AC_OUTPUT
