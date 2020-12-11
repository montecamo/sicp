Summary: 	Scheme Interpreter with access to the Tk toolkit
Name:    	STk
Version: 	4.0.1
Release:	UCB1.16
Copyright: 	distributable
Source: 	http://www-inst.eecs.berkeley.edu/~scheme/source/stk.tar.gz
Group:		Development/Languages
Packager:	Brian R. Gaeke <brg@EECS.Berkeley.EDU>


%description
STk is a R4RS Scheme interpreter which can access the Tk graphical
package.  Concretely it can be seen as John Ousterhout's Tk
package where the Tcl language has been replaced by Scheme.

STk also provides an efficient object oriented system called STklos.
STklos is an extensive OO system with multiple inheritance, generic
functions, multi-methods and a Meta-Object Protocol).

This package integrates the 8.0.3 version of the Tk toolkit.
This package has been modified by UC Berkeley's EECS Department
for Computer Science classes.


%prep
%setup -n stk

%build
./brg/build /usr/local
/usr/local/bin/stk < /dev/null

%install
true


%files
%doc README INSTALL CHANGES ChangeLog
/usr/local/bin/envdraw
/usr/local/bin/snow
/usr/local/bin/snow-4.0.1-ucb1.16
/usr/local/bin/stk
/usr/local/bin/stk-4.0.1-ucb1.16
/usr/local/lib/stk
/usr/local/bin/stk-explorin
/usr/local/bin/stk-simply
/usr/local/bin/stk-grfx
