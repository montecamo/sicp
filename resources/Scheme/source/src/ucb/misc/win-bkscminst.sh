#!/bin/ksh

INSTALLROOT="$1"
LIBDIR="${INSTALLROOT}"

if [ ! -d "$LIBDIR" ]; then
    echo "Aborting - no directory $LIBDIR"
    exit 1
fi

SITESCHEMEDIR="${LIBDIR}/site-scheme"
mkdir "$SITESCHEMEDIR"

##############Copy Files to Site-Scheme###############
cp brg/berkeley.scm "${SITESCHEMEDIR}/berkeley.scm"
cp brg/simply.scm "${SITESCHEMEDIR}/simply.scm"
cp brg/explorin.scm "${SITESCHEMEDIR}/explorin.scm"
cp brg/modeler.stk "${SITESCHEMEDIR}/modeler.stk"
#cp brg/cs3-modeler.stk "${SITESCHEMEDIR}/cs3-modeler.stk"
#cp brg/cs3s-modeler.stk "${SITESCHEMEDIR}/cs3s-modeler.stk"
cp brg/turtle-grfx.scm  "${SITESCHEMEDIR}/turtle-grfx.scm"
cp brg/obj.scm "${SITESCHEMEDIR}/obj.scm"
cp brg/which-modeler.scm "${SITESCHEMEDIR}/which-modeler.scm"

#############Create files for class scripts to load###############

echo ";;explorin.scm must be loaded after simply.scm
      (load \"${SITESCHEMEDIR}/berkeley.scm\")
      (load \"${SITESCHEMEDIR}/simply.scm\")
      (load \"${SITESCHEMEDIR}/explorin.scm\")
      (load \"${SITESCHEMEDIR}/modeler.stk\")
      (load \"${SITESCHEMEDIR}/obj.scm\")
      (load \"${SITESCHEMEDIR}/turtle-grfx.scm\")
      (load \"${SITESCHEMEDIR}/which-modeler.scm\")" >  "${SITESCHEMEDIR}/load-explorin"


echo ";;simply.scm must be loaded after explorin.scm
      (load \"${SITESCHEMEDIR}/berkeley.scm\")
       (load \"${SITESCHEMEDIR}/explorin.scm\")
      (load \"${SITESCHEMEDIR}/simply.scm\")
      (load \"${SITESCHEMEDIR}/modeler.stk\")
      (load \"${SITESCHEMEDIR}/obj.scm\")
      (load \"${SITESCHEMEDIR}/turtle-grfx.scm\")
      (load \"${SITESCHEMEDIR}/which-modeler.scm\")"  > "${SITESCHEMEDIR}/load-simply"

echo ";;load-grfx (for CS9D and CS47B)
      (load \"${SITESCHEMEDIR}/obj.scm\")
      (load \"${SITESCHEMEDIR}/turtle-grfx.scm\")" > "${SITESCHEMEDIR}/load-grfx"


##############Create class loading file###########

cp brg/class-load.stk "${SITESCHEMEDIR}/class-load.stk"
cp brg/userinit.stk "${LIBDIR}/STk/userinit.stk"

#######Create .bat files##########
echo "stk -load \"${SITESCHEMEDIR}/load-explorin\" %1 %2 %3 %4 %5 %6 %7 %8 %9" > \
  "${LIBDIR}/MS-WIN32/stk-explorin.bat"

echo "stk -load \"${SITESCHEMEDIR}/load-simply\" %1 %2 %3 %4 %5 %6 %7 %8 %9" > \
  "${LIBDIR}/MS-WIN32/stk-simply.bat"

echo "stk -load \"${SITESCHEMEDIR}/load-grfx\" %1 %2 %3 %4 %5 %6 %7 %8 %9" > \
  "${LIBDIR}/MS-WIN32/stk-grfx.bat"


###### Set permissions for .bat files########

chmod 755 "${LIBDIR}/MS-WIN32/stk-explorin.bat"

chmod 755 "${LIBDIR}/MS-WIN32/stk-simply.bat"

chmod 755 "${LIBDIR}/MS-WIN32/stk-grfx.bat"

###########################

exit 0

