TEMPLATE = app

SOURCES += \
	../../../source/tools/PaperFormats.cpp \
	../../../source/tools/PaintCanvasBase.cpp \
	../../../source/tools/UnitsOfLength.cpp \
	../../../source/tools/ImageIOTypes.cpp \
	../../../source/posterazor/PosteRazor.cpp \
	../../../source/posterazor/PosteRazorImageIO.cpp \
	../../../source/posterazor/PosteRazorPDFOutput.cpp \
	../../../source/posterazor_ui_qt/PosteRazorDialog.cpp \
	../../../source/posterazor_ui_qt/QPersistentPreferences.cpp \
	../../../source/posterazor_ui_qt/QPosteRazorSpinBox.cpp \
	../../../source/posterazor_ui_qt/QPaintCanvas.cpp \
	../../../source/posterazor_ui_common/PosteRazorDialogController.cpp \
	../../../source/posterazor_ui_common/PosteRazorWizardDialogController.cpp

HEADERS += \
	../../../source/tools/ColorTypes.h \
	../../../source/tools/ImageIOTypes.h \
	../../../source/tools/UnitsOfLength.h \
	../../../source/tools/PaperFormats.h \
	../../../source/tools/PaintCanvasBase.h \
	../../../source/tools/PaintCanvasInterface.h \
	../../../source/tools/PersistentPreferencesInterface.h \
	../../../source/posterazor/PosteRazor.h \
	../../../source/posterazor/PosteRazorImageIO.h \
	../../../source/posterazor/PosteRazorPDFOutput.h \
	../../../source/posterazor_ui_qt/PosteRazorDialog.h \
	../../../source/posterazor_ui_qt/QPersistentPreferences.h \
	../../../source/posterazor_ui_qt/QPosteRazorSpinBox.h \
	../../../source/posterazor_ui_qt/QPaintCanvas.h \
	../../../source/posterazor_ui_common/PosteRazorDialogController.h \
	../../../source/posterazor_ui_common/PosteRazorWizardDialogController.h

INCLUDEPATH += \
	../../../source/tools \
	../../../source/posterazor \
	../../../source/posterazor_ui_qt \
	../../../source/posterazor_ui_common \
	../../../thirdparty/FreeImage/Dist

win32:LIBS += \
	../../../thirdparty/FreeImage/Dist/FreeImage.lib
unix:LIBS += \
	-L/usr/lib \
	-lfreeimage

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
