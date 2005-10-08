PROJECT(PosteRazor)

ADD_DEFINITIONS(-DFREEIMAGE_LIB)

SET(POSTERAZOR_SRCS
	../../source/posterazor/PosteRazor.cxx
	../../source/posterazor/PosteRazorImageIO.cxx
	../../source/posterazor/PosteRazorPDFOutput.cxx
	../../source/posterazor/ui/Fl_Paint_Canvas.cpp
	../../source/posterazor/ui/Fl_Persistent_Preferences.cxx
	../../source/posterazor/ui/PosteRazorDialog.cxx
	../../source/posterazor/ui/PosteRazorDialogUI.cxx
	../../source/tools/DistanceUnits.cxx
	../../source/tools/PaperFormats.cxx
	../../thirdparty/Fl_Native_File_Chooser/Fl_Native_File_Chooser.cxx
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
)

SET_TARGET_PROPERTIES(PosteRazor PROPERTIES LINK_FLAGS "/nodefaultlib:LIBC")

ADD_EXECUTABLE(PosteRazor POSTERAZOR_SRCS)

TARGET_LINK_LIBRARIES(PosteRazor
	debug fltkd
	optimized fltk
	debug FreeImaged
	optimized FreeImage
	wsock32
	comctl32
)