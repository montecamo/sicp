#!/bin/bash

DEST="$1"
mkdir "$DEST"

cp Win32/Doc/install.doc   "$DEST"

## ============ STk executable & libraries
mkdir "$DEST/MS-Win32"
cp Win32/Release/STk.exe  "$DEST/MS-Win32"
cp Win32/Release/addpmstk.exe "$DEST/MS-Win32/AddStart.exe"
cp Win32/Win32libs/*.lib  "$DEST/MS-Win32"

## ============ Header files
mkdir "$DEST/Include"
cp Tcl/tcl.h     "$DEST/Include"
cp Tcl/tclInt.h   "$DEST/Include"
cp Tcl/tclRegexp.h   "$DEST/Include"

cp Tk/tk.h    "$DEST/Include"
cp Tk/tkInt.h    "$DEST/Include"

cp Mp/fgmp-1.05b/gmp.h  "$DEST/Include"

cp Src/stk.h    "$DEST/Include"
cp Src/tcl-glue.h   "$DEST/Include"
cp Src/tk-glue.h   "$DEST/Include"

## ============ The Library directory
mkdir "$DEST/STk"
mkdir "$DEST/STk/Match"

cp Lib/*.stk    "$DEST/STk"
cp Lib/*.stklos    "$DEST/STk"
cp Lib/Match/*.scm   "$DEST/STk/Match"

## ============= The STklos directory
cp STklos/*.stk   "$DEST/STk"
cp STklos/*.stklos   "$DEST/STk"
cp STklos/Tk/*.stklos  "$DEST/STk"
cp STklos/Tk/Composite/*.stklos  "$DEST/STk"

## ============= Images
mkdir "$DEST/Images"
cp Lib/Images/*.*   "$DEST/Images"
cp Lib/Images/*   "$DEST/Images"

## ============== Demos
mkdir "$DEST/Demos"
cp Demos/*.stk   "$DEST/Demos"
cp Demos/*.stklos   "$DEST/Demos"
cp Demos/Widget/*.stklos  "$DEST/Demos"
mkdir "$DEST/Demos/Html-Demos"
mkdir "$DEST/Demos/Html-Demos/Images"
cp Demos/Html-Demos/*.*  "$DEST/Demos/Html-Demos"
cp Demos/Html-Demos/Images/*.* "$DEST/Demos/Html-Demos/Images"

## ============== Help pages
mkdir "$DEST/Help"
mkdir "$DEST/Help/Img"
cp Help/*.html   "$DEST/Help"
cp Help/Img/*.*   "$DEST/Help/Img"

bash brg/win-slibinst.sh "$DEST"
bash brg/win-bkscminst.sh "$DEST"
bash brg/win-envdinst.sh "$DEST"
bash brg/win-stkdbinst.sh "$DEST"
echo "*** Installation completed in $DEST"


