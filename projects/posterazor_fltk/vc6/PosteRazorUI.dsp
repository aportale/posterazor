# Microsoft Developer Studio Project File - Name="PosteRazorUI" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=PosteRazorUI - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PosteRazorUI.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PosteRazorUI.mak" CFG="PosteRazorUI - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PosteRazorUI - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "PosteRazorUI - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PosteRazorUI - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "..\..\..\source\posterazor_ui_common" /I "..\..\..\source\posterazor_ui_common\windowsResources" /I "..\..\..\source\posterazor_ui_common\translations" /I "..\..\..\source\tools" /I "..\..\..\source\posterazor" /I "..\..\..\thirdparty\fltk-1.1" /I "..\..\..\thirdparty\Fl_Native_File_Chooser" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "WIN32_LEAN_AND_MEAN" /D "VC_EXTRA_LEAN" /D "WIN32_EXTRA_LEAN" /D "OPENGL_PREVIEW" /FR /YX /FD /c
# ADD BASE RSC /l 0x407 /d "NDEBUG"
# ADD RSC /l 0x407 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 opengl32.lib wsock32.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"LIBC.lib" /nodefaultlib:"LIBCMT.lib"
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "PosteRazorUI - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "..\..\..\source\posterazor_ui_common" /I "..\..\..\source\posterazor_ui_common\windowsResources" /I "..\..\..\source\posterazor_ui_common\translations" /I "..\..\..\source\tools" /I "..\..\..\source\posterazor" /I "..\..\..\thirdparty\fltk-1.1" /I "..\..\..\thirdparty\Fl_Native_File_Chooser" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "WIN32_LEAN_AND_MEAN" /D "VC_EXTRA_LEAN" /D "WIN32_EXTRA_LEAN" /D "OPENGL_PREVIEW" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x407 /d "_DEBUG"
# ADD RSC /l 0x407 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib wsock32.lib comctl32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /nodefaultlib:"LIBCD.lib" /nodefaultlib:"LIBCMTD.lib" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "PosteRazorUI - Win32 Release"
# Name "PosteRazorUI - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_fltk\Fl_Draw_Paint_Canvas.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_fltk\Fl_Gl_Paint_Canvas.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_fltk\Fl_Image_Text_Button.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_fltk\Fl_Paint_Canvas_Group.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_fltk\Fl_Persistent_Preferences.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_fltk\Fl_PosteRazor_Spinner.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\tools\PaintCanvasBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_fltk\PosteRazorDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_common\PosteRazorDialogController.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_fltk\PosteRazorDialogUI.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_fltk\PosteRazorHelpDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_fltk\PosteRazorSettingsDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_common\windowsResources\PosteRazorUI.rc
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_common\PosteRazorWizardDialogController.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_common\translations\Translations.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_fltk\Fl_Draw_Paint_Canvas.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_fltk\Fl_Gl_Paint_Canvas.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_fltk\Fl_Image_Text_Button.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_fltk\Fl_Paint_Canvas_Group.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_fltk\Fl_Persistent_Preferences.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_fltk\Fl_PosteRazor_Spinner.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\tools\PaintCanvasBase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_fltk\PosteRazorDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_common\PosteRazorDialogController.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_fltk\PosteRazorDialogUI.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_fltk\PosteRazorHelpDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_fltk\PosteRazorSettingsDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_common\PosteRazorWizardDialogController.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_common\translations\TranslationConstants.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_common\translations\TranslationEnglish.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_common\translations\TranslationFrench.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_common\translations\TranslationGerman.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_common\translations\TranslationInterface.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_common\translations\TranslationItalian.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_common\translations\TranslationPolish.h
# End Source File
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_common\translations\Translations.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_common\windowsResources\PosteRazor.ico
# End Source File
# End Group
# Begin Group "Fl_Native_File_Chooser"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\thirdparty\Fl_Native_File_Chooser\Fl_Native_File_Chooser.cxx
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\source\posterazor_ui_fltk\PosteRazorDialogUI.fl
# End Source File
# Begin Source File

SOURCE="..\..\..\thirdparty\fltk-1.1\lib\fltk.lib"

!IF  "$(CFG)" == "PosteRazorUI - Win32 Release"

!ELSEIF  "$(CFG)" == "PosteRazorUI - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\thirdparty\fltk-1.1\lib\fltkd.lib"

!IF  "$(CFG)" == "PosteRazorUI - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "PosteRazorUI - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\thirdparty\fltk-1.1\lib\fltkgld.lib"

!IF  "$(CFG)" == "PosteRazorUI - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "PosteRazorUI - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\thirdparty\fltk-1.1\lib\fltkgl.lib"

!IF  "$(CFG)" == "PosteRazorUI - Win32 Release"

!ELSEIF  "$(CFG)" == "PosteRazorUI - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Target
# End Project
