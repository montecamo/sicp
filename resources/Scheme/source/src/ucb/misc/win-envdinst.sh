#!/bin/ksh

ENVDRAWSRC="brg/envdraw"
INSTALLROOT="$1"
LIBDIR="${INSTALLROOT}"

if [ ! -d "$LIBDIR" ]; then
    echo "Aborting - no directory $LIBDIR"
    exit 1
fi

SITESCHEMEDIR="${LIBDIR}/site-scheme"

cp -r "$ENVDRAWSRC" "$SITESCHEMEDIR"

cat <<EOF >> "${LIBDIR}/STk/userinit.stk"
(define (envdraw) 
  pp
  (set! *load-path* (cons (getenv "SCHEME_LIBRARY_PATH") *load-path*))
  (load "stk-init")
  (envdraw))
(define (view x)
  pp
  (set! *load-path* (cons (getenv "SCHEME_LIBRARY_PATH") *load-path*))
  (load "stk-init")
  (view x))
EOF

echo "installing envdraw wrapper in ${INSTALLROOT}/MS-Win32/envdraw.bat"
SITESCHEMEDIR=`echo "${SITESCHEMEDIR}" | \
          sed -e 's@/cygdrive/\(.\)/@\1:/@' -e 's@/@\\\\@g'`
LIBDIR=`echo "${LIBDIR}" | \
          sed -e 's@/cygdrive/\(.\)/@\1:/@' -e 's@/@\\\\@g'`
cat <<END > "${INSTALLROOT}/MS-Win32/envdraw.bat"
@ECHO OFF
REM EnvDraw STk launcher
set INSTHOME=${LIBDIR}\\MS-Win32
set STK_LIBRARY=${LIBDIR}\\
set ENVDRAW_LIBRARY_PATH=${SITESCHEMEDIR}\\envdraw\\
set STK_LOAD_PATH=%ENVDRAW_LIBRARY_PATH%\\lib\\
set SCHEME_LIBRARY_PATH=${LIBDIR}\\slib\\
"%INSTHOME%\\stk.exe" -name stk %1 %2 %3 %4 %5 %6 %7 %8 %9
END

chmod 755 "${INSTALLROOT}/MS-Win32/envdraw.bat"
exit 0
