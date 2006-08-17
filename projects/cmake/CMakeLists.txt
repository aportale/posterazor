PROJECT(PosteRazor)

ADD_DEFINITIONS(-DFREEIMAGE_LIB, -DNO_OPENGL_PREVIEW)

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
	${POSTERAZOR_SOURCE_DIR}../../thirdparty/fltk-1.1
	${POSTERAZOR_SOURCE_DIR}../../thirdparty/FreeImage/Dist
	${POSTERAZOR_SOURCE_DIR}../../thirdparty/Fl_Native_File_Chooser
)

LINK_DIRECTORIES(
	${POSTERAZOR_SOURCE_DIR}../../thirdparty/fltk-1.1/lib
	${POSTERAZOR_SOURCE_DIR}../../thirdparty/FreeImage/Dist
	/usr/X11R6/lib
)

SET_TARGET_PROPERTIES(PosteRazor PROPERTIES LINK_FLAGS "/nodefaultlib:LIBC")

ADD_EXECUTABLE(PosteRazor ${POSTERAZOR_SRCS})

TARGET_LINK_LIBRARIES(PosteRazor
	debug fltkd
	optimized fltk
	debug fltk_imagesd
	optimized fltk_images
#	debug fltkgld
#	optimized fltkgl
	debug FreeImaged
	optimized freeimage
	X11
#	wsock32
#	comctl32
#	glu32
#	opengl32
)