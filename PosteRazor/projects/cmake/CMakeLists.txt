PROJECT(PosteRazor)

ADD_DEFINITIONS(
	-DFREEIMAGE_LIB
)

SET(POSTERAZOR_SRCS
	../../source/posterazor/PosteRazor.cxx
	../../source/posterazor/PosteRazorImageIO.cxx
	../../source/posterazor/PosteRazorPDFOutput.cxx
	../../source/posterazor/ui/Fl_Paint_Canvas_Base.cpp
	../../source/posterazor/ui/Fl_Paint_Canvas_Group.cpp
	../../source/posterazor/ui/Fl_Draw_Paint_Canvas.cpp
	../../source/posterazor/ui/Fl_Persistent_Preferences.cxx
	../../source/posterazor/ui/Fl_Image_Text_Button.cpp
	../../source/posterazor/ui/PosteRazorDialog.cxx
	../../source/posterazor/ui/PosteRazorDialogUI.cxx
	../../source/tools/UnitsOfLength.cxx
	../../source/tools/PaperFormats.cxx
	../../thirdparty/Fl_Native_File_Chooser/Fl_Native_File_Chooser.cxx
	../../source/posterazor/ui/translations/Translations.cxx
)

IF (NOT UNIX)
	SET(POSTERAZOR_SRCS
		${POSTERAZOR_SRCS}
		../../source/posterazor/ui/Fl_Gl_Paint_Canvas.cpp
	)
ENDIF (NOT UNIX)

INCLUDE_DIRECTORIES(
	${POSTERAZOR_SOURCE_DIR}../../source/posterazor
	${POSTERAZOR_SOURCE_DIR}../../source/posterazor/ui
	${POSTERAZOR_SOURCE_DIR}../../source/tools
	${POSTERAZOR_SOURCE_DIR}../../thirdparty/FreeImage/Dist
	${POSTERAZOR_SOURCE_DIR}../../thirdparty/Fl_Native_File_Chooser
)

LINK_DIRECTORIES(
	${POSTERAZOR_SOURCE_DIR}../../thirdparty/FreeImage/Dist
# This is unly needed for WIN32. It's here, because apparently CMake 2.4 doesn't allow to add LINK_DIRECTORIES in a second call
	${POSTERAZOR_SOURCE_DIR}../../thirdparty/fltk-1.1/lib
)


IF (WIN32)
	ADD_EXECUTABLE(PosteRazor WIN32 ${POSTERAZOR_SRCS} ../../source/posterazor/ui/windowsResources/PosteRazorUI.rc)
	INCLUDE_DIRECTORIES(
		${POSTERAZOR_SOURCE_DIR}../../thirdparty/fltk-1.1
	)
	LINK_DIRECTORIES(
		${POSTERAZOR_SOURCE_DIR}../../thirdparty/fltk-1.1/lib
	)
	TARGET_LINK_LIBRARIES(PosteRazor
		debug fltkgld
		optimized fltkgl
		wsock32
		comctl32
		glu32
		opengl32
	)
	SET_TARGET_PROPERTIES(PosteRazor PROPERTIES LINK_FLAGS "/nodefaultlib:LIBC")
ELSE (WIN32)
	ADD_EXECUTABLE(PosteRazor ${POSTERAZOR_SRCS})
ENDIF (WIN32)


IF (UNIX)
	ADD_DEFINITIONS(
		-DNO_OPENGL_PREVIEW
	)
#	FIND_PACKAGE(X11)
	LINK_DIRECTORIES(
		${POSTERAZOR_SOURCE_DIR}../../thirdparty/FreeImage/Dist
#		${X11_LIBRARIES}
		/usr/X11R6/lib
	)
	TARGET_LINK_LIBRARIES(PosteRazor
		debug fltk_imagesd
		optimized fltk_images
		X11
	)
ENDIF (UNIX)

IF (APPLE)
ENDIF(APPLE)

TARGET_LINK_LIBRARIES(PosteRazor
	debug fltkd
	optimized fltk
	debug FreeImaged
	optimized freeimage
)

