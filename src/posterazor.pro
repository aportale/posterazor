SOURCES += \
    PaperFormats.cpp \
    UnitsOfLength.cpp \
    posterazorcore.cpp \
    pdfwriter.cpp \
    mainwindow.cpp \
    QtPosteRazorSpinBox.cpp \
    paintcanvas.cpp \
    controller.cpp \
    PosteRazorWizardDialogController.cpp \
    main.cpp

HEADERS += \
    ColorTypes.h \
    imageloaderinterface.h \
    UnitsOfLength.h \
    PaperFormats.h \
    PaintCanvasInterface.h \
    posterazorcore.h \
    pdfwriter.h \
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

# Uncomment the following line in order to build PosteRazor with FreeImage
#DEFINES += FREEIMAGE_LIB

contains (DEFINES, FREEIMAGE_LIB) {
    SOURCES += \
        imageloaderfreeimage.cpp

    HEADERS += \
        imageloaderfreeimage.h

    win32:INCLUDEPATH += \
        thirdparty/FreeImage/Dist

    win32:LIBS += \
        thirdparty/FreeImage/Dist/FreeImage.lib

    unix:LIBS += \
        -lfreeimage
} else {
    SOURCES += \
        imageloaderqt.cpp

    HEADERS += \
        imageloaderqt.h

    QTPLUGIN += \
        qjpeg \
        qtiff
}
