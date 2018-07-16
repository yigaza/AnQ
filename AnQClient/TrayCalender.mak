# Microsoft Developer Studio Generated NMAKE File, Based on TrayCalender.dsp
!IF "$(CFG)" == ""
CFG=TrayCalender - Win32 Debug UNICODE
!MESSAGE No configuration specified. Defaulting to TrayCalender - Win32 Debug\
 UNICODE.
!ENDIF 

!IF "$(CFG)" != "TrayCalender - Win32 Release" && "$(CFG)" !=\
 "TrayCalender - Win32 Debug" && "$(CFG)" !=\
 "TrayCalender - Win32 Debug UNICODE"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TrayCalender.mak" CFG="TrayCalender - Win32 Debug UNICODE"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TrayCalender - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TrayCalender - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "TrayCalender - Win32 Debug UNICODE" (based on\
 "Win32 (x86) Application")
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

!IF  "$(CFG)" == "TrayCalender - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\TrayCalender.exe"

!ELSE 

ALL : "$(OUTDIR)\TrayCalender.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\HyperLink.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Splash.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\SystemTray.obj"
	-@erase "$(INTDIR)\TrayCalender.obj"
	-@erase "$(INTDIR)\TrayCalender.pch"
	-@erase "$(INTDIR)\TrayCalender.res"
	-@erase "$(INTDIR)\TrayCalenderOptions.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\TrayCalender.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\TrayCalender.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\TrayCalender.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TrayCalender.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\TrayCalender.pdb" /machine:I386\
 /out:"$(OUTDIR)\TrayCalender.exe" 
LINK32_OBJS= \
	"$(INTDIR)\HyperLink.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Splash.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SystemTray.obj" \
	"$(INTDIR)\TrayCalender.obj" \
	"$(INTDIR)\TrayCalender.res" \
	"$(INTDIR)\TrayCalenderOptions.obj"

"$(OUTDIR)\TrayCalender.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TrayCalender - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\TrayCalender.exe"

!ELSE 

ALL : "$(OUTDIR)\TrayCalender.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\HyperLink.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Splash.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\SystemTray.obj"
	-@erase "$(INTDIR)\TrayCalender.obj"
	-@erase "$(INTDIR)\TrayCalender.pch"
	-@erase "$(INTDIR)\TrayCalender.res"
	-@erase "$(INTDIR)\TrayCalenderOptions.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\TrayCalender.exe"
	-@erase "$(OUTDIR)\TrayCalender.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W4 /Gm- /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\TrayCalender.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\TrayCalender.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TrayCalender.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\TrayCalender.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\TrayCalender.exe" 
LINK32_OBJS= \
	"$(INTDIR)\HyperLink.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Splash.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SystemTray.obj" \
	"$(INTDIR)\TrayCalender.obj" \
	"$(INTDIR)\TrayCalender.res" \
	"$(INTDIR)\TrayCalenderOptions.obj"

"$(OUTDIR)\TrayCalender.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TrayCalender - Win32 Debug UNICODE"

OUTDIR=.\Debug UNICODE
INTDIR=.\Debug UNICODE
# Begin Custom Macros
OutDir=.\Debug UNICODE
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\TrayCalender.exe"

!ELSE 

ALL : "$(OUTDIR)\TrayCalender.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\HyperLink.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\Splash.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\SystemTray.obj"
	-@erase "$(INTDIR)\TrayCalender.obj"
	-@erase "$(INTDIR)\TrayCalender.pch"
	-@erase "$(INTDIR)\TrayCalender.res"
	-@erase "$(INTDIR)\TrayCalenderOptions.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\TrayCalender.exe"
	-@erase "$(OUTDIR)\TrayCalender.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W4 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /D "_UNICODE" /Fp"$(INTDIR)\TrayCalender.pch"\
 /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=".\Debug UNICODE/"
CPP_SBRS=.
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\TrayCalender.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TrayCalender.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /entry:"wWinMainCRTStartup" /subsystem:windows\
 /incremental:no /pdb:"$(OUTDIR)\TrayCalender.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\TrayCalender.exe" 
LINK32_OBJS= \
	"$(INTDIR)\HyperLink.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\Splash.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SystemTray.obj" \
	"$(INTDIR)\TrayCalender.obj" \
	"$(INTDIR)\TrayCalender.res" \
	"$(INTDIR)\TrayCalenderOptions.obj"

"$(OUTDIR)\TrayCalender.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(CFG)" == "TrayCalender - Win32 Release" || "$(CFG)" ==\
 "TrayCalender - Win32 Debug" || "$(CFG)" ==\
 "TrayCalender - Win32 Debug UNICODE"
SOURCE=.\HyperLink.cpp

!IF  "$(CFG)" == "TrayCalender - Win32 Release"

DEP_CPP_HYPER=\
	".\HyperLink.h"\
	

"$(INTDIR)\HyperLink.obj" : $(SOURCE) $(DEP_CPP_HYPER) "$(INTDIR)"\
 "$(INTDIR)\TrayCalender.pch"


!ELSEIF  "$(CFG)" == "TrayCalender - Win32 Debug"

DEP_CPP_HYPER=\
	"..\..\..\inetsdk\include\rpcasync.h"\
	".\HyperLink.h"\
	

"$(INTDIR)\HyperLink.obj" : $(SOURCE) $(DEP_CPP_HYPER) "$(INTDIR)"\
 "$(INTDIR)\TrayCalender.pch"


!ELSEIF  "$(CFG)" == "TrayCalender - Win32 Debug UNICODE"

DEP_CPP_HYPER=\
	"..\..\..\inetsdk\include\rpcasync.h"\
	".\HyperLink.h"\
	

"$(INTDIR)\HyperLink.obj" : $(SOURCE) $(DEP_CPP_HYPER) "$(INTDIR)"\
 "$(INTDIR)\TrayCalender.pch"


!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "TrayCalender - Win32 Release"

DEP_CPP_MAINF=\
	".\MainFrm.h"\
	".\Splash.h"\
	".\StdAfx.h"\
	".\SystemTray.h"\
	".\TrayCalender.h"\
	".\TrayCalenderOptions.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\TrayCalender.pch"


!ELSEIF  "$(CFG)" == "TrayCalender - Win32 Debug"

DEP_CPP_MAINF=\
	"..\..\..\inetsdk\include\rpcasync.h"\
	".\MainFrm.h"\
	".\Splash.h"\
	".\SystemTray.h"\
	".\TrayCalender.h"\
	".\TrayCalenderOptions.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\TrayCalender.pch"


!ELSEIF  "$(CFG)" == "TrayCalender - Win32 Debug UNICODE"

DEP_CPP_MAINF=\
	"..\..\..\inetsdk\include\rpcasync.h"\
	".\MainFrm.h"\
	".\Splash.h"\
	".\SystemTray.h"\
	".\TrayCalender.h"\
	".\TrayCalenderOptions.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\TrayCalender.pch"


!ENDIF 

SOURCE=.\Splash.cpp
DEP_CPP_SPLAS=\
	".\Splash.h"\
	

"$(INTDIR)\Splash.obj" : $(SOURCE) $(DEP_CPP_SPLAS) "$(INTDIR)"\
 "$(INTDIR)\TrayCalender.pch"


SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "TrayCalender - Win32 Release"

CPP_SWITCHES=/nologo /MD /W4 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\TrayCalender.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\TrayCalender.pch" : $(SOURCE)\
 $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "TrayCalender - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W4 /Gm- /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\TrayCalender.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\TrayCalender.pch" : $(SOURCE)\
 $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "TrayCalender - Win32 Debug UNICODE"

CPP_SWITCHES=/nologo /MDd /W4 /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /Fp"$(INTDIR)\TrayCalender.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\TrayCalender.pch" : $(SOURCE)\
 $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\SystemTray.cpp

!IF  "$(CFG)" == "TrayCalender - Win32 Release"

DEP_CPP_SYSTE=\
	".\StdAfx.h"\
	".\SystemTray.h"\
	

"$(INTDIR)\SystemTray.obj" : $(SOURCE) $(DEP_CPP_SYSTE) "$(INTDIR)"\
 "$(INTDIR)\TrayCalender.pch"


!ELSEIF  "$(CFG)" == "TrayCalender - Win32 Debug"

DEP_CPP_SYSTE=\
	"..\..\..\inetsdk\include\rpcasync.h"\
	".\SystemTray.h"\
	

"$(INTDIR)\SystemTray.obj" : $(SOURCE) $(DEP_CPP_SYSTE) "$(INTDIR)"\
 "$(INTDIR)\TrayCalender.pch"


!ELSEIF  "$(CFG)" == "TrayCalender - Win32 Debug UNICODE"

DEP_CPP_SYSTE=\
	"..\..\..\inetsdk\include\rpcasync.h"\
	".\SystemTray.h"\
	

"$(INTDIR)\SystemTray.obj" : $(SOURCE) $(DEP_CPP_SYSTE) "$(INTDIR)"\
 "$(INTDIR)\TrayCalender.pch"


!ENDIF 

SOURCE=.\TrayCalender.cpp

!IF  "$(CFG)" == "TrayCalender - Win32 Release"

DEP_CPP_TRAYC=\
	".\HyperLink.h"\
	".\MainFrm.h"\
	".\Splash.h"\
	".\StdAfx.h"\
	".\SystemTray.h"\
	".\TrayCalender.h"\
	

"$(INTDIR)\TrayCalender.obj" : $(SOURCE) $(DEP_CPP_TRAYC) "$(INTDIR)"\
 "$(INTDIR)\TrayCalender.pch"


!ELSEIF  "$(CFG)" == "TrayCalender - Win32 Debug"

DEP_CPP_TRAYC=\
	"..\..\..\inetsdk\include\rpcasync.h"\
	".\HyperLink.h"\
	".\MainFrm.h"\
	".\Splash.h"\
	".\SystemTray.h"\
	".\TrayCalender.h"\
	

"$(INTDIR)\TrayCalender.obj" : $(SOURCE) $(DEP_CPP_TRAYC) "$(INTDIR)"\
 "$(INTDIR)\TrayCalender.pch"


!ELSEIF  "$(CFG)" == "TrayCalender - Win32 Debug UNICODE"

DEP_CPP_TRAYC=\
	"..\..\..\inetsdk\include\rpcasync.h"\
	".\HyperLink.h"\
	".\MainFrm.h"\
	".\Splash.h"\
	".\SystemTray.h"\
	".\TrayCalender.h"\
	

"$(INTDIR)\TrayCalender.obj" : $(SOURCE) $(DEP_CPP_TRAYC) "$(INTDIR)"\
 "$(INTDIR)\TrayCalender.pch"


!ENDIF 

SOURCE=.\TrayCalender.rc
DEP_RSC_TRAYCA=\
	".\res\cursor1.cur"\
	".\res\icon1.ico"\
	".\res\icon10.ico"\
	".\res\icon11.ico"\
	".\res\icon12.ico"\
	".\res\icon13.ico"\
	".\res\icon14.ico"\
	".\res\icon15.ico"\
	".\res\icon16.ico"\
	".\res\icon17.ico"\
	".\res\icon18.ico"\
	".\res\icon19.ico"\
	".\res\icon2.ico"\
	".\res\icon20.ico"\
	".\res\icon21.ico"\
	".\res\icon22.ico"\
	".\res\icon23.ico"\
	".\res\icon24.ico"\
	".\res\icon25.ico"\
	".\res\icon26.ico"\
	".\res\icon27.ico"\
	".\res\icon28.ico"\
	".\res\icon29.ico"\
	".\res\icon3.ico"\
	".\res\icon30.ico"\
	".\res\icon31.ico"\
	".\res\icon4.ico"\
	".\res\icon5.ico"\
	".\res\icon6.ico"\
	".\res\icon7.ico"\
	".\res\icon8.ico"\
	".\res\icon9.ico"\
	".\res\TrayCalender.rc2"\
	".\res\TrayDay.ico"\
	".\Splsh16.bmp"\
	

"$(INTDIR)\TrayCalender.res" : $(SOURCE) $(DEP_RSC_TRAYCA) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\TrayCalenderOptions.cpp

!IF  "$(CFG)" == "TrayCalender - Win32 Release"

DEP_CPP_TRAYCAL=\
	".\StdAfx.h"\
	".\SystemTray.h"\
	".\TrayCalender.h"\
	".\TrayCalenderOptions.h"\
	

"$(INTDIR)\TrayCalenderOptions.obj" : $(SOURCE) $(DEP_CPP_TRAYCAL) "$(INTDIR)"\
 "$(INTDIR)\TrayCalender.pch"


!ELSEIF  "$(CFG)" == "TrayCalender - Win32 Debug"

DEP_CPP_TRAYCAL=\
	"..\..\..\inetsdk\include\rpcasync.h"\
	".\SystemTray.h"\
	".\TrayCalender.h"\
	".\TrayCalenderOptions.h"\
	

"$(INTDIR)\TrayCalenderOptions.obj" : $(SOURCE) $(DEP_CPP_TRAYCAL) "$(INTDIR)"\
 "$(INTDIR)\TrayCalender.pch"


!ELSEIF  "$(CFG)" == "TrayCalender - Win32 Debug UNICODE"

DEP_CPP_TRAYCAL=\
	"..\..\..\inetsdk\include\rpcasync.h"\
	".\SystemTray.h"\
	".\TrayCalender.h"\
	".\TrayCalenderOptions.h"\
	

"$(INTDIR)\TrayCalenderOptions.obj" : $(SOURCE) $(DEP_CPP_TRAYCAL) "$(INTDIR)"\
 "$(INTDIR)\TrayCalender.pch"


!ENDIF 


!ENDIF 

