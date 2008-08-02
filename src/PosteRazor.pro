TEMPLATE = app

SOURCES += \
	PaperFormats.cpp \
	PaintCanvasBase.cpp \
	UnitsOfLength.cpp \
	ImageIOTypes.cpp \
	PosteRazor.cpp \
	PosteRazorImageIO.cpp \
	PosteRazorPDFOutput.cpp \
	QtPosteRazorDialog.cpp \
	QtPosteRazorSpinBox.cpp \
	QtPaintCanvas.cpp \
	PosteRazorDialogController.cpp \
	PosteRazorWizardDialogController.cpp

HEADERS += \
	ColorTypes.h \
	ImageIOTypes.h \
	UnitsOfLength.h \
	PaperFormats.h \
	PaintCanvasBase.h \
	PaintCanvasInterface.h \
	PosteRazor.h \
	PosteRazorImageIO.h \
	PosteRazorPDFOutput.h \
	QtPosteRazorDialog.h \
	QtPosteRazorSpinBox.h \
	QtPaintCanvas.h \
	PosteRazorDialogController.h \
	PosteRazorWizardDialogController.h

INCLUDEPATH += \
	tools \
	posterazor \
	posterazor_ui_qt \
	posterazor_ui_common \
	thirdparty/FreeImage/Dist

win32:LIBS += \
	thirdparty/FreeImage/Dist/FreeImage.lib
unix:LIBS += \
	-L/usr/lib \
	-lfreeimage

DEFINES += \
	FREEIMAGE_LIB
	
DEFINES -= \
	UNICODE

FORMS += \
	QtPosteRazorDialog.ui

RESOURCES += \
	QtPosteRazorDialogResources.qrc
