#!/bin/ksh
SLIBSRC="brg/slib2d5"
INSTALLROOT="$1"
LIBDIR="${INSTALLROOT}"
SLIBDIR="${LIBDIR}/slib"

if [ ! -f VERSION ]; then
	echo "Must run from directory above the brg directory (no VERSION file)"
	exit 1
fi
# . VERSION doesn't seem to work; weird ksh bug

#eval `cat VERSION`
eval cat VERSION


if [ ! -d "$LIBDIR" ]; then
	echo "Aborting - no directory $LIBDIR"
	exit 1
fi

if [ ! -d "${SLIBDIR}" ]; then
     mkdir "${SLIBDIR}"
fi
cp "${SLIBSRC}"/* "${SLIBDIR}"

IMPLVIC=`echo "${LIBDIR}/STk/" | \
          sed -e 's@/cygdrive/\(.\)/@\1:/@'` # -e 's@/@\\\\\\\\@g'`
SLIBDIR=`echo "${LIBDIR}/slib/" | \
          sed -e 's@/cygdrive/\(.\)/@\1:/@'` # -e 's@/@\\\\\\\\@g'`
sed \
 -e "/implementation-vicinity/s@\"[^\"]*\"@\"${IMPLVIC}\"@" \
 -e "/\/usr\/local\/lib\/slib\//s@@${SLIBDIR}@" \
   "${SLIBSRC}/STk.init" > "${SLIBDIR}/STk.init"
cp "${SLIBDIR}/STk.init" "${LIBDIR}/STk"

cd "$LIBDIR"

echo "(if (not (getenv \"ENVDRAW_LIBRARY_PATH\")) (begin" >> \
    "${LIBDIR}/STk/userinit.stk"

#SLIBDIR=`echo "${SLIBDIR}" | sed 's@\\\\\\\\@\\\\@g'`
echo "(load \"${SLIBDIR}STk.init\")" >> "${LIBDIR}/STk/userinit.stk"

echo "))" >> "${LIBDIR}/STk/userinit.stk"

exit 0
