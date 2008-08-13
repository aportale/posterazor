TEMPLATE = app

SOURCES += \
    PaperFormats.cpp \
    UnitsOfLength.cpp \
    ImageIOTypes.cpp \
    PosteRazor.cpp \
    imageiofreeimage.cpp \
    PosteRazorPDFOutput.cpp \
    mainwindow.cpp \
    QtPosteRazorSpinBox.cpp \
    QtPaintCanvas.cpp \
    controller.cpp \
    PosteRazorWizardDialogController.cpp \
    main.cpp

HEADERS += \
    ColorTypes.h \
    ImageIOTypes.h \
    UnitsOfLength.h \
    PaperFormats.h \
    PaintCanvasInterface.h \
    PosteRazor.h \
    imageiofreeimage.h \
    PosteRazorPDFOutput.h \
    mainwindow.h \
    QtPosteRazorSpinBox.h \
    QtPaintCanvas.h \
    controller.h \
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
    mainwindow.ui

RESOURCES += \
    QtPosteRazorDialogResources.qrc

TRANSLATIONS += \
    de.ts \
    es.ts \
    fi.ts \
    fr.ts \
    it.ts \
    nl.ts \
    pl.ts \
    pt_BR.ts \
    zh_CN.ts
