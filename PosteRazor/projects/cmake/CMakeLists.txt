PROJECT(PosteRazor)

IF (WIN32 OR APPLE)
	SET(POSTERAZOR_ENABLEGLPREVIEW TRUE)
ENDIF (WIN32 OR APPLE)

SET(POSTERAZOR_CORESOURCES
	../../source/posterazor/PosteRazor.cxx
	../../source/posterazor/PosteRazorImageIO.cxx
	../../source/posterazor/PosteRazorPDFOutput.cxx
	../../source/tools/UnitsOfLength.cxx
	../../source/tools/PaperFormats.cxx
)

SET(POSTERAZOR_UISOURCES
	../../source/posterazor/ui/Fl_Paint_Canvas_Base.cpp
	../../source/posterazor/ui/Fl_Paint_Canvas_Group.cpp
	../../source/posterazor/ui/Fl_Draw_Paint_Canvas.cpp
	../../source/posterazor/ui/Fl_Persistent_Preferences.cxx
	../../source/posterazor/ui/Fl_Image_Text_Button.cpp
	../../source/posterazor/ui/PosteRazorDialog.cxx
	../../source/posterazor/ui/PosteRazorHelpDialog.cxx
	../../source/posterazor/ui/PosteRazorSettingsDialog.cxx
	../../source/posterazor/ui/PosteRazorDialogUI.cxx
	../../source/posterazor/ui/translations/Translations.cxx
	../../thirdparty/Fl_Native_File_Chooser/Fl_Native_File_Chooser.cxx
)

SET(POSTERAZOR_SOURCES
	${POSTERAZOR_CORESOURCES}
	${POSTERAZOR_UISOURCES}
)

SET(POSTERAZOR_DEFINITIONS
	-DFREEIMAGE_LIB
)

SET(POSTERAZOR_LINKDIRECTORIES
	../../thirdparty/FreeImage/Dist
)

SET(POSTERAZOR_INCLUDEDIRECTORIES
	../../source/posterazor
	../../source/posterazor/ui
	../../source/posterazor/ui/translations
	../../source/tools
	../../thirdparty/FreeImage/Dist
	../../thirdparty/Fl_Native_File_Chooser
)

IF (POSTERAZOR_ENABLEGLPREVIEW)
	SET(POSTERAZOR_SOURCES
		${POSTERAZOR_SOURCES}
		../../source/posterazor/ui/Fl_Gl_Paint_Canvas.cpp
	)
ELSE (POSTERAZOR_ENABLEGLPREVIEW)
	SET(POSTERAZOR_DEFINITIONS
		${POSTERAZOR_DEFINITIONS}
		-DNO_OPENGL_PREVIEW
	)
ENDIF (POSTERAZOR_ENABLEGLPREVIEW)

IF (WIN32)
	ADD_EXECUTABLE(PosteRazor WIN32 ${POSTERAZOR_SOURCES}
		../../source/posterazor/ui/windowsResources/PosteRazorUI.rc
	)
	SET(POSTERAZOR_INCLUDEDIRECTORIES ${POSTERAZOR_INCLUDEDIRECTORIES}
		../../thirdparty/fltk-1.1
		../../source/posterazor/ui/windowsResources
	)
	SET(POSTERAZOR_LINKDIRECTORIES
		${POSTERAZOR_LINKDIRECTORIES}
		../../thirdparty/fltk-1.1/lib
	)
	SET(POSTERAZOR_LINKLIBRARIES
		debug FreeImaged
		optimized FreeImage
		debug fltkd
		optimized fltk
		wsock32
		comctl32
	)
	IF (POSTERAZOR_ENABLEGLPREVIEW)
		SET(POSTERAZOR_LINKLIBRARIES 
			${POSTERAZOR_LINKLIBRARIES}
			debug fltkgld
			optimized fltkgl
			glu32
			opengl32
		)
	ENDIF (POSTERAZOR_ENABLEGLPREVIEW)
	SET_TARGET_PROPERTIES(PosteRazor PROPERTIES LINK_FLAGS "/nodefaultlib:LIBC")
ENDIF (WIN32)

IF (APPLE)
	ADD_EXECUTABLE(PosteRazor MACOSX_BUNDLE ${POSTERAZOR_SOURCES})
# FreeImages make script on OSX doesn't finish and doesn't copy stuff into into the Dist directory
	SET(POSTERAZOR_INCLUDEDIRECTORIES
		${POSTERAZOR_INCLUDEDIRECTORIES}
		../../thirdparty/FreeImage/Source
	)
	SET_TARGET_PROPERTIES(PosteRazor PROPERTIES LINK_FLAGS "-L../../thirdparty/FreeImage")
	SET(POSTERAZOR_LINKLIBRARIES
		fltk
		fltk_gl
		freeimage
		"-framework Carbon -framework AGL -framework ApplicationServices -framework OpenGL -lz"
	)
ENDIF(APPLE)

IF (UNIX AND NOT APPLE)
	ADD_EXECUTABLE(PosteRazor ${POSTERAZOR_SOURCES})
#	FIND_PACKAGE(X11)
	SET(POSTERAZOR_LINKDIRECTORIES
		${POSTERAZOR_LINKDIRECTORIES}
#		${X11_LIBRARIES}
		/usr/X11R6/lib
	)
	SET(POSTERAZOR_LINKLIBRARIES
		fltk
		fltk_images
		freeimage
		X11
		Xpm
	)
ENDIF (UNIX AND NOT APPLE)

ADD_DEFINITIONS(${POSTERAZOR_DEFINITIONS})
LINK_DIRECTORIES(${POSTERAZOR_LINKDIRECTORIES})
INCLUDE_DIRECTORIES(${POSTERAZOR_INCLUDEDIRECTORIES})
TARGET_LINK_LIBRARIES(PosteRazor ${POSTERAZOR_LINKLIBRARIES})
