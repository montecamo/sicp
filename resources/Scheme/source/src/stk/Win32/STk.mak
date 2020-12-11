# Microsoft Developer Studio Generated NMAKE File, Based on STk.dsp
!IF "$(CFG)" == ""
CFG=STk - Win32 Release
!MESSAGE No configuration specified. Defaulting to STk - Win32 Release.
!ENDIF 

!IF "$(CFG)" != "STk - Win32 Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "STk.mak" CFG="STk - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "STk - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe
OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\STk.exe" "$(OUTDIR)\STk.bsc"

!ELSE 

ALL : "addpmstk - Win32 Release" "libtk - Win32 Release" "libtcl - Win32 Release" "libgmp - Win32 Release" "$(OUTDIR)\STk.exe" "$(OUTDIR)\STk.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"libgmp - Win32 ReleaseCLEAN" "libtcl - Win32 ReleaseCLEAN" "libtk - Win32 ReleaseCLEAN" "addpmstk - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\address.obj"
	-@erase "$(INTDIR)\address.sbr"
	-@erase "$(INTDIR)\argv.obj"
	-@erase "$(INTDIR)\argv.sbr"
	-@erase "$(INTDIR)\base64.obj"
	-@erase "$(INTDIR)\base64.sbr"
	-@erase "$(INTDIR)\boolean.obj"
	-@erase "$(INTDIR)\boolean.sbr"
	-@erase "$(INTDIR)\char.obj"
	-@erase "$(INTDIR)\char.sbr"
	-@erase "$(INTDIR)\console.obj"
	-@erase "$(INTDIR)\console.sbr"
	-@erase "$(INTDIR)\cont.obj"
	-@erase "$(INTDIR)\cont.sbr"
	-@erase "$(INTDIR)\dummy.obj"
	-@erase "$(INTDIR)\dummy.sbr"
	-@erase "$(INTDIR)\dump.obj"
	-@erase "$(INTDIR)\dump.sbr"
	-@erase "$(INTDIR)\dynload.obj"
	-@erase "$(INTDIR)\dynload.sbr"
	-@erase "$(INTDIR)\env.obj"
	-@erase "$(INTDIR)\env.sbr"
	-@erase "$(INTDIR)\error.obj"
	-@erase "$(INTDIR)\error.sbr"
	-@erase "$(INTDIR)\eval.obj"
	-@erase "$(INTDIR)\eval.sbr"
	-@erase "$(INTDIR)\extend.obj"
	-@erase "$(INTDIR)\extend.sbr"
	-@erase "$(INTDIR)\gc.obj"
	-@erase "$(INTDIR)\gc.sbr"
	-@erase "$(INTDIR)\hash.obj"
	-@erase "$(INTDIR)\hash.sbr"
	-@erase "$(INTDIR)\html.obj"
	-@erase "$(INTDIR)\html.sbr"
	-@erase "$(INTDIR)\io.obj"
	-@erase "$(INTDIR)\io.sbr"
	-@erase "$(INTDIR)\keyword.obj"
	-@erase "$(INTDIR)\keyword.sbr"
	-@erase "$(INTDIR)\list.obj"
	-@erase "$(INTDIR)\list.sbr"
	-@erase "$(INTDIR)\locale.obj"
	-@erase "$(INTDIR)\locale.sbr"
	-@erase "$(INTDIR)\macros.obj"
	-@erase "$(INTDIR)\macros.sbr"
	-@erase "$(INTDIR)\module.obj"
	-@erase "$(INTDIR)\module.sbr"
	-@erase "$(INTDIR)\number.obj"
	-@erase "$(INTDIR)\number.sbr"
	-@erase "$(INTDIR)\pixmap.obj"
	-@erase "$(INTDIR)\pixmap.sbr"
	-@erase "$(INTDIR)\port.obj"
	-@erase "$(INTDIR)\port.sbr"
	-@erase "$(INTDIR)\posix.obj"
	-@erase "$(INTDIR)\posix.sbr"
	-@erase "$(INTDIR)\primitives.obj"
	-@erase "$(INTDIR)\primitives.sbr"
	-@erase "$(INTDIR)\print.obj"
	-@erase "$(INTDIR)\print.sbr"
	-@erase "$(INTDIR)\proc.obj"
	-@erase "$(INTDIR)\proc.sbr"
	-@erase "$(INTDIR)\process.obj"
	-@erase "$(INTDIR)\process.sbr"
	-@erase "$(INTDIR)\promise.obj"
	-@erase "$(INTDIR)\promise.sbr"
	-@erase "$(INTDIR)\read.obj"
	-@erase "$(INTDIR)\read.sbr"
	-@erase "$(INTDIR)\signal.obj"
	-@erase "$(INTDIR)\signal.sbr"
	-@erase "$(INTDIR)\slib.obj"
	-@erase "$(INTDIR)\slib.sbr"
	-@erase "$(INTDIR)\socket.obj"
	-@erase "$(INTDIR)\socket.sbr"
	-@erase "$(INTDIR)\sport.obj"
	-@erase "$(INTDIR)\sport.sbr"
	-@erase "$(INTDIR)\sregexp.obj"
	-@erase "$(INTDIR)\sregexp.sbr"
	-@erase "$(INTDIR)\stk.res"
	-@erase "$(INTDIR)\stklos.obj"
	-@erase "$(INTDIR)\stklos.sbr"
	-@erase "$(INTDIR)\str.obj"
	-@erase "$(INTDIR)\str.sbr"
	-@erase "$(INTDIR)\symbol.obj"
	-@erase "$(INTDIR)\symbol.sbr"
	-@erase "$(INTDIR)\syntax.obj"
	-@erase "$(INTDIR)\syntax.sbr"
	-@erase "$(INTDIR)\tcl-glue.obj"
	-@erase "$(INTDIR)\tcl-glue.sbr"
	-@erase "$(INTDIR)\tcl-lib.obj"
	-@erase "$(INTDIR)\tcl-lib.sbr"
	-@erase "$(INTDIR)\tcl-obj.obj"
	-@erase "$(INTDIR)\tcl-obj.sbr"
	-@erase "$(INTDIR)\tcl-util.obj"
	-@erase "$(INTDIR)\tcl-util.sbr"
	-@erase "$(INTDIR)\tk-glue.obj"
	-@erase "$(INTDIR)\tk-glue.sbr"
	-@erase "$(INTDIR)\tk-main.obj"
	-@erase "$(INTDIR)\tk-main.sbr"
	-@erase "$(INTDIR)\tk-util.obj"
	-@erase "$(INTDIR)\tk-util.sbr"
	-@erase "$(INTDIR)\toplevel.obj"
	-@erase "$(INTDIR)\toplevel.sbr"
	-@erase "$(INTDIR)\trace.obj"
	-@erase "$(INTDIR)\trace.sbr"
	-@erase "$(INTDIR)\unix.obj"
	-@erase "$(INTDIR)\unix.sbr"
	-@erase "$(INTDIR)\userinit.obj"
	-@erase "$(INTDIR)\userinit.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\vector.obj"
	-@erase "$(INTDIR)\vector.sbr"
	-@erase "$(INTDIR)\vport.obj"
	-@erase "$(INTDIR)\vport.sbr"
	-@erase "$(INTDIR)\wstk.obj"
	-@erase "$(INTDIR)\wstk.sbr"
	-@erase "$(OUTDIR)\STk.bsc"
	-@erase "$(OUTDIR)\STk.exe"
	-@erase "$(OUTDIR)\STk.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\STk.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\address.sbr" \
	"$(INTDIR)\argv.sbr" \
	"$(INTDIR)\base64.sbr" \
	"$(INTDIR)\boolean.sbr" \
	"$(INTDIR)\char.sbr" \
	"$(INTDIR)\console.sbr" \
	"$(INTDIR)\cont.sbr" \
	"$(INTDIR)\dummy.sbr" \
	"$(INTDIR)\dump.sbr" \
	"$(INTDIR)\dynload.sbr" \
	"$(INTDIR)\env.sbr" \
	"$(INTDIR)\error.sbr" \
	"$(INTDIR)\eval.sbr" \
	"$(INTDIR)\extend.sbr" \
	"$(INTDIR)\gc.sbr" \
	"$(INTDIR)\hash.sbr" \
	"$(INTDIR)\html.sbr" \
	"$(INTDIR)\io.sbr" \
	"$(INTDIR)\keyword.sbr" \
	"$(INTDIR)\list.sbr" \
	"$(INTDIR)\locale.sbr" \
	"$(INTDIR)\macros.sbr" \
	"$(INTDIR)\module.sbr" \
	"$(INTDIR)\number.sbr" \
	"$(INTDIR)\pixmap.sbr" \
	"$(INTDIR)\port.sbr" \
	"$(INTDIR)\posix.sbr" \
	"$(INTDIR)\primitives.sbr" \
	"$(INTDIR)\print.sbr" \
	"$(INTDIR)\proc.sbr" \
	"$(INTDIR)\process.sbr" \
	"$(INTDIR)\promise.sbr" \
	"$(INTDIR)\read.sbr" \
	"$(INTDIR)\signal.sbr" \
	"$(INTDIR)\slib.sbr" \
	"$(INTDIR)\socket.sbr" \
	"$(INTDIR)\sport.sbr" \
	"$(INTDIR)\sregexp.sbr" \
	"$(INTDIR)\stklos.sbr" \
	"$(INTDIR)\str.sbr" \
	"$(INTDIR)\symbol.sbr" \
	"$(INTDIR)\syntax.sbr" \
	"$(INTDIR)\tcl-glue.sbr" \
	"$(INTDIR)\tcl-lib.sbr" \
	"$(INTDIR)\tcl-obj.sbr" \
	"$(INTDIR)\tcl-util.sbr" \
	"$(INTDIR)\tk-glue.sbr" \
	"$(INTDIR)\tk-main.sbr" \
	"$(INTDIR)\tk-util.sbr" \
	"$(INTDIR)\toplevel.sbr" \
	"$(INTDIR)\trace.sbr" \
	"$(INTDIR)\unix.sbr" \
	"$(INTDIR)\userinit.sbr" \
	"$(INTDIR)\vector.sbr" \
	"$(INTDIR)\vport.sbr" \
	"$(INTDIR)\wstk.sbr"

"$(OUTDIR)\STk.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Wsock32.lib libtcl.lib libtk.lib libgmp.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\STk.pdb" /debug /machine:I386 /out:"$(OUTDIR)\STk.exe" /libpath:"Win32libs" 
LINK32_OBJS= \
	"$(INTDIR)\address.obj" \
	"$(INTDIR)\argv.obj" \
	"$(INTDIR)\base64.obj" \
	"$(INTDIR)\boolean.obj" \
	"$(INTDIR)\char.obj" \
	"$(INTDIR)\console.obj" \
	"$(INTDIR)\cont.obj" \
	"$(INTDIR)\dummy.obj" \
	"$(INTDIR)\dump.obj" \
	"$(INTDIR)\dynload.obj" \
	"$(INTDIR)\env.obj" \
	"$(INTDIR)\error.obj" \
	"$(INTDIR)\eval.obj" \
	"$(INTDIR)\extend.obj" \
	"$(INTDIR)\gc.obj" \
	"$(INTDIR)\hash.obj" \
	"$(INTDIR)\html.obj" \
	"$(INTDIR)\io.obj" \
	"$(INTDIR)\keyword.obj" \
	"$(INTDIR)\list.obj" \
	"$(INTDIR)\locale.obj" \
	"$(INTDIR)\macros.obj" \
	"$(INTDIR)\module.obj" \
	"$(INTDIR)\number.obj" \
	"$(INTDIR)\pixmap.obj" \
	"$(INTDIR)\port.obj" \
	"$(INTDIR)\posix.obj" \
	"$(INTDIR)\primitives.obj" \
	"$(INTDIR)\print.obj" \
	"$(INTDIR)\proc.obj" \
	"$(INTDIR)\process.obj" \
	"$(INTDIR)\promise.obj" \
	"$(INTDIR)\read.obj" \
	"$(INTDIR)\signal.obj" \
	"$(INTDIR)\slib.obj" \
	"$(INTDIR)\socket.obj" \
	"$(INTDIR)\sport.obj" \
	"$(INTDIR)\sregexp.obj" \
	"$(INTDIR)\stklos.obj" \
	"$(INTDIR)\str.obj" \
	"$(INTDIR)\symbol.obj" \
	"$(INTDIR)\syntax.obj" \
	"$(INTDIR)\tcl-glue.obj" \
	"$(INTDIR)\tcl-lib.obj" \
	"$(INTDIR)\tcl-obj.obj" \
	"$(INTDIR)\tcl-util.obj" \
	"$(INTDIR)\tk-glue.obj" \
	"$(INTDIR)\tk-main.obj" \
	"$(INTDIR)\tk-util.obj" \
	"$(INTDIR)\toplevel.obj" \
	"$(INTDIR)\trace.obj" \
	"$(INTDIR)\unix.obj" \
	"$(INTDIR)\userinit.obj" \
	"$(INTDIR)\vector.obj" \
	"$(INTDIR)\vport.obj" \
	"$(INTDIR)\wstk.obj" \
	"$(INTDIR)\stk.res" \
	".\Win32libs\libgmp.lib" \
	".\Win32libs\libtcl.lib" \
	".\Win32libs\libtk.lib"

"$(OUTDIR)\STk.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

CPP_PROJ=/nologo /ML /W3 /GX /Zi /Od /I "..\Mp\fgmp-1.0b5" /I "..\Tcl" /I "..\Src" /I "..\Tk\generic" /I "..\Tk\xlib" /I "..\Tk\win" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "USE_TK" /D "STk_CODE" /D "SCM_CODE" /D "USE_STKLOS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\stk.res" /d "NDEBUG" 

!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("STk.dep")
!INCLUDE "STk.dep"
!ELSE 
!MESSAGE Warning: cannot find "STk.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "STk - Win32 Release"

!IF  "$(CFG)" == "STk - Win32 Release"

"libgmp - Win32 Release" : 
   cd ".\libgmp"
   $(MAKE) /$(MAKEFLAGS) /F .\libgmp.mak CFG="libgmp - Win32 Release" 
   cd ".."

"libgmp - Win32 ReleaseCLEAN" : 
   cd ".\libgmp"
   $(MAKE) /$(MAKEFLAGS) /F .\libgmp.mak CFG="libgmp - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 

!IF  "$(CFG)" == "STk - Win32 Release"

"libtcl - Win32 Release" : 
   cd ".\libtcl"
   $(MAKE) /$(MAKEFLAGS) /F .\libtcl.mak CFG="libtcl - Win32 Release" 
   cd ".."

"libtcl - Win32 ReleaseCLEAN" : 
   cd ".\libtcl"
   $(MAKE) /$(MAKEFLAGS) /F .\libtcl.mak CFG="libtcl - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 

!IF  "$(CFG)" == "STk - Win32 Release"

"libtk - Win32 Release" : 
   cd ".\libtk"
   $(MAKE) /$(MAKEFLAGS) /F .\libtk.mak CFG="libtk - Win32 Release" 
   cd ".."

"libtk - Win32 ReleaseCLEAN" : 
   cd ".\libtk"
   $(MAKE) /$(MAKEFLAGS) /F .\libtk.mak CFG="libtk - Win32 Release" RECURSE=1 CLEAN 
   cd ".."

!ENDIF 

!IF  "$(CFG)" == "STk - Win32 Release"

"addpmstk - Win32 Release" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\addpmstk.mak CFG="addpmstk - Win32 Release" 
   cd "."

"addpmstk - Win32 ReleaseCLEAN" : 
   cd "."
   $(MAKE) /$(MAKEFLAGS) /F .\addpmstk.mak CFG="addpmstk - Win32 Release" RECURSE=1 CLEAN 
   cd "."

!ENDIF 

SOURCE=..\Src\address.c

"$(INTDIR)\address.obj"	"$(INTDIR)\address.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\argv.c

"$(INTDIR)\argv.obj"	"$(INTDIR)\argv.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Extensions\base64.c

"$(INTDIR)\base64.obj"	"$(INTDIR)\base64.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\boolean.c

"$(INTDIR)\boolean.obj"	"$(INTDIR)\boolean.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\char.c

"$(INTDIR)\char.obj"	"$(INTDIR)\char.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\console.c

"$(INTDIR)\console.obj"	"$(INTDIR)\console.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\cont.c

"$(INTDIR)\cont.obj"	"$(INTDIR)\cont.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\dummy.c

"$(INTDIR)\dummy.obj"	"$(INTDIR)\dummy.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\dump.c

"$(INTDIR)\dump.obj"	"$(INTDIR)\dump.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\dynload.c

"$(INTDIR)\dynload.obj"	"$(INTDIR)\dynload.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\env.c

"$(INTDIR)\env.obj"	"$(INTDIR)\env.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\error.c

"$(INTDIR)\error.obj"	"$(INTDIR)\error.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\eval.c

"$(INTDIR)\eval.obj"	"$(INTDIR)\eval.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\extend.c

"$(INTDIR)\extend.obj"	"$(INTDIR)\extend.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\gc.c

"$(INTDIR)\gc.obj"	"$(INTDIR)\gc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Extensions\hash.c

"$(INTDIR)\hash.obj"	"$(INTDIR)\hash.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Extensions\html.c

"$(INTDIR)\html.obj"	"$(INTDIR)\html.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\io.c

"$(INTDIR)\io.obj"	"$(INTDIR)\io.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\keyword.c

"$(INTDIR)\keyword.obj"	"$(INTDIR)\keyword.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\list.c

"$(INTDIR)\list.obj"	"$(INTDIR)\list.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Extensions\locale.c

"$(INTDIR)\locale.obj"	"$(INTDIR)\locale.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\macros.c

"$(INTDIR)\macros.obj"	"$(INTDIR)\macros.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\module.c

"$(INTDIR)\module.obj"	"$(INTDIR)\module.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\number.c

"$(INTDIR)\number.obj"	"$(INTDIR)\number.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Extensions\pixmap.c

"$(INTDIR)\pixmap.obj"	"$(INTDIR)\pixmap.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\port.c

"$(INTDIR)\port.obj"	"$(INTDIR)\port.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Extensions\posix.c

"$(INTDIR)\posix.obj"	"$(INTDIR)\posix.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\primitives.c

"$(INTDIR)\primitives.obj"	"$(INTDIR)\primitives.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\print.c

"$(INTDIR)\print.obj"	"$(INTDIR)\print.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\proc.c

"$(INTDIR)\proc.obj"	"$(INTDIR)\proc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Extensions\process.c

"$(INTDIR)\process.obj"	"$(INTDIR)\process.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\promise.c

"$(INTDIR)\promise.obj"	"$(INTDIR)\promise.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\read.c

"$(INTDIR)\read.obj"	"$(INTDIR)\read.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\signal.c

"$(INTDIR)\signal.obj"	"$(INTDIR)\signal.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\slib.c

"$(INTDIR)\slib.obj"	"$(INTDIR)\slib.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Extensions\socket.c

"$(INTDIR)\socket.obj"	"$(INTDIR)\socket.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\sport.c

"$(INTDIR)\sport.obj"	"$(INTDIR)\sport.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Extensions\sregexp.c

"$(INTDIR)\sregexp.obj"	"$(INTDIR)\sregexp.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Tk\win\rc\stk.rc

"$(INTDIR)\stk.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) /l 0x40c /fo"$(INTDIR)\stk.res" /i "\Temp\stk\Tk\win\rc" /d "NDEBUG" $(SOURCE)


SOURCE=..\Src\stklos.c

"$(INTDIR)\stklos.obj"	"$(INTDIR)\stklos.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\str.c

"$(INTDIR)\str.obj"	"$(INTDIR)\str.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\symbol.c

"$(INTDIR)\symbol.obj"	"$(INTDIR)\symbol.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\syntax.c

"$(INTDIR)\syntax.obj"	"$(INTDIR)\syntax.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\Src\tcl-glue.c"

"$(INTDIR)\tcl-glue.obj"	"$(INTDIR)\tcl-glue.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\Src\tcl-lib.c"

"$(INTDIR)\tcl-lib.obj"	"$(INTDIR)\tcl-lib.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\Src\tcl-obj.c"

"$(INTDIR)\tcl-obj.obj"	"$(INTDIR)\tcl-obj.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\Src\tcl-util.c"

"$(INTDIR)\tcl-util.obj"	"$(INTDIR)\tcl-util.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\Src\tk-glue.c"

"$(INTDIR)\tk-glue.obj"	"$(INTDIR)\tk-glue.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\Src\tk-main.c"

"$(INTDIR)\tk-main.obj"	"$(INTDIR)\tk-main.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE="..\Src\tk-util.c"

"$(INTDIR)\tk-util.obj"	"$(INTDIR)\tk-util.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\toplevel.c

"$(INTDIR)\toplevel.obj"	"$(INTDIR)\toplevel.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\trace.c

"$(INTDIR)\trace.obj"	"$(INTDIR)\trace.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\unix.c

"$(INTDIR)\unix.obj"	"$(INTDIR)\unix.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\userinit.c

"$(INTDIR)\userinit.obj"	"$(INTDIR)\userinit.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\vector.c

"$(INTDIR)\vector.obj"	"$(INTDIR)\vector.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\vport.c

"$(INTDIR)\vport.obj"	"$(INTDIR)\vport.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\Src\wstk.c

"$(INTDIR)\wstk.obj"	"$(INTDIR)\wstk.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

