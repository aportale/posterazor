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
	QtPersistentPreferences.cpp \
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
	PersistentPreferencesInterface.h \
	PosteRazor.h \
	PosteRazorImageIO.h \
	PosteRazorPDFOutput.h \
	QtPosteRazorDialog.h \
	QtPersistentPreferences.h \
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

win32:debug:LIBS += \
	thirdparty/FreeImage/Dist/FreeImaged.lib
win32:release:LIBS += \
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
