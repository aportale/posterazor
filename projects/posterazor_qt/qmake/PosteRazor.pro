TEMPLATE = app

SOURCES += \
	../../../source/tools/PaperFormats.cxx \
	../../../source/tools/UnitsOfLength.cxx \
	../../../source/posterazor/PosteRazor.cxx \
	../../../source/posterazor/PosteRazorImageIO.cxx \
	../../../source/posterazor/PosteRazorPDFOutput.cxx \
	../../../source/posterazor_ui_qt/PosteRazorDialog.cpp \
	../../../source/posterazor_ui_common/PosteRazorDialogController.cpp

HEADERS += \
	../../../source/tools/ColorTypes.h \
	../../../source/tools/ImageIOTypes.h \
	../../../source/tools/PaintCanvasInterface.h \
	../../../source/tools/PersistentPreferencesInterface.h \
	../../../source/posterazor/PosteRazor.h \
	../../../source/posterazor/PosteRazorImageIO.h \
	../../../source/posterazor/PosteRazorPDFOutput.h \
	../../../source/posterazor_ui_qt/PosteRazorDialog.h \
	../../../source/posterazor_ui_common/PosteRazorDialogController.h

INCLUDEPATH += \
	../../../source/tools \
	../../../source/posterazor \
	../../../source/posterazor_ui_qt \
	../../../source/posterazor_ui_common \
	../../../thirdparty/FreeImage/Dist  \

LIBS += \
	../../../thirdparty/FreeImage/Dist/FreeImage.lib

DEFINES += \
	FREEIMAGE_LIB
	
DEFINES -= \
	UNICODE

UI_HEADERS_DIR = \
	../../../source/posterazor_ui_qt

UI_SOURCES_DIR = \
	../../../source/posterazor_ui_qt

FORMS += \
	../../../source/posterazor_ui_qt/PosteRazorDialog.ui

RESOURCES += \
	../../../source/posterazor_ui_qt/PosteRazorDialogResources.qrc
