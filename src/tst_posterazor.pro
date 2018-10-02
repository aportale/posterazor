QT += testlib widgets printsupport

# Uncomment the following line in order to build PosteRazor with FreeImage
#DEFINES += FREEIMAGE_LIB

SOURCES += \
    tst_posterazor.cpp

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
    contains(CONFIG, static) {
        QTPLUGIN += \
            qgif \
            qjpeg \
            qsvg \
            qtiff
    }
}

include (posterazor.pri)

!contains(CONFIG, build_pass) system(lrelease posterazor.pro)
