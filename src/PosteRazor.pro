SOURCES += \
    PaperFormats.cpp \
    UnitsOfLength.cpp \
    ImageIOTypes.cpp \
    PosteRazor.cpp \
    PosteRazorPDFOutput.cpp \
    mainwindow.cpp \
    QtPosteRazorSpinBox.cpp \
    paintcanvas.cpp \
    controller.cpp \
    PosteRazorWizardDialogController.cpp \
    main.cpp

HEADERS += \
    ColorTypes.h \
    imageiointerface.h \
    ImageIOTypes.h \
    UnitsOfLength.h \
    PaperFormats.h \
    PaintCanvasInterface.h \
    PosteRazor.h \
    PosteRazorPDFOutput.h \
    mainwindow.h \
    QtPosteRazorSpinBox.h \
    paintcanvas.h \
    controller.h \
    PosteRazorWizardDialogController.h

win32:DEFINES -= \
    UNICODE

FORMS += \
    mainwindow.ui

RESOURCES += \
    QtPosteRazorDialogResources.qrc

RC_FILE += \
    PosteRazorUI.rc

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

DEFINES += FREEIMAGE_LIB

contains (DEFINES, FREEIMAGE_LIB) {
    SOURCES += \
        imageiofreeimage.cpp

    HEADERS += \
        imageiofreeimage.h

    win32:INCLUDEPATH += \
        thirdparty/FreeImage/Dist

    win32:LIBS += \
        thirdparty/FreeImage/Dist/FreeImage.lib

    unix:LIBS += \
        -lfreeimage
} else {
    SOURCES += \
        imageioqt.cpp

    HEADERS += \
        imageioqt.h
}
