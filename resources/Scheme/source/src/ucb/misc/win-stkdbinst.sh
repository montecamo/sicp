#!/bin/ksh

INSTALLROOT="$1"
LIBDIR="${INSTALLROOT}/stkdb"
EMACSDIR="${INSTALLROOT}/lib/emacs/lisp"
INFODIR="${INSTALLROOT}/lib/emacs/info"

if [ ! -f VERSION ]; then
    echo "Must run from directory above the brg directory (no VERSION file)"
    exit 1
fi
# . VERSION doesn't seem to work; weird ksh bug
#eval `cat VERSION`
eval cat VERSION

if [ ! -d Stkdb ]; then
    echo "Aborting - no directory Stkdb"
    exit 1
fi

cd Stkdb
bash configure --infodir="${INFODIR}" --emacsdir="${EMACSDIR}" \
	       --scmdir="${LIBDIR}" 
make install

exit 0
