SOURCES += \
    controller.cpp \
    mainwindow.cpp \
    paintcanvas.cpp \
    pdfwriter.cpp \
    posterazorcore.cpp \
    snapspinbox.cpp \
    types.cpp \
    wizardcontroller.cpp \
    main.cpp

HEADERS += \
    controller.h \
    imageloaderinterface.h \
    mainwindow.h \
    paintcanvas.h \
    paintcanvasinterface.h \
    pdfwriter.h \
    posterazorcore.h \
    snapspinbox.h \
    types.h \
    wizardcontroller.h

win32:DEFINES -= \
    UNICODE
    
macx:QMAKE_INFO_PLIST = \
    Info.plist

macx:ICON = \
    posterazor.icns

FORMS += \
    mainwindow.ui

RESOURCES += \
    posterazor.qrc

RC_FILE += \
    posterazor.rc

TRANSLATIONS += \
    de.ts \
    en.ts \
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

    !unix:QTPLUGIN += \
        qjpeg \
        qtiff
}
