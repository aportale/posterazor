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

INCLUDE_DIRECTORIES(
	${POSTERAZOR_SOURCE_DIR}../../source/posterazor
	${POSTERAZOR_SOURCE_DIR}../../source/posterazor/ui
	${POSTERAZOR_SOURCE_DIR}../../source/tools
	${POSTERAZOR_SOURCE_DIR}../../thirdparty/FreeImage/Dist
	${POSTERAZOR_SOURCE_DIR}../../thirdparty/Fl_Native_File_Chooser
)

LINK_DIRECTORIES(
	${POSTERAZOR_SOURCE_DIR}../../thirdparty/FreeImage/Dist
)

ADD_EXECUTABLE(PosteRazor ${POSTERAZOR_SRCS})

IF (WIN32)
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

TARGET_LINK_LIBRARIES(PosteRazor
	debug fltkd
	optimized fltk
	debug FreeImaged
	optimized freeimage
)
