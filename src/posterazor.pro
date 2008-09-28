TARGET = PosteRazor

DESTDIR = $$PWD

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

macx:CONFIG += \
    x86 ppc

macx:QMAKE_MAC_SDK = \
    /Developer/SDKs/MacOSX10.4u.sdk

macx:QMAKE_MACOSX_DEPLOYMENT_TARGET = \
    10.3

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

    macx: INCLUDEPATH += \
        /usr/local/include

    unix:LIBS += \
        -lfreeimage
} else {
    SOURCES += \
        imageloaderqt.cpp

    HEADERS += \
        imageloaderqt.h

    QTPLUGIN += \
        qgif \
        qjpeg \
        qtiff
}

!contains(CONFIG, build_pass) system(lrelease posterazor.pro)
