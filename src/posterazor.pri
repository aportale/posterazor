VPATH = $$PWD
INCLUDEPATH += \
    $$PWD

SOURCES += \
    controller.cpp \
    mainwindow.cpp \
    wizard.cpp \
    paintcanvas.cpp \
    pdfwriter.cpp \
    posterazorcore.cpp \
    snapspinbox.cpp \
    types.cpp \
    wizardcontroller.cpp

macx:SOURCES += \
    macosstylehelpers.cpp

HEADERS += \
    controller.h \
    imageloaderinterface.h \
    mainwindow.h \
    wizard.h \
    paintcanvas.h \
    paintcanvasinterface.h \
    pdfwriter.h \
    posterazorcore.h \
    snapspinbox.h \
    types.h \
    wizardcontroller.h

macx:HEADERS += \
    macosstylehelpers.h

!contains (DEFINES, FREEIMAGE_LIB) {
    SOURCES += \
        imageloaderqt.cpp

    HEADERS += \
        imageloaderqt.h
}

FORMS += \
    mainwindow.ui \
    wizard.ui

RESOURCES += \
    posterazor.qrc

TRANSLATIONS += \
    cs.ts \
    da.ts \
    de.ts \
    en.ts \
    es.ts \
    fi.ts \
    fr.ts \
    it.ts \
    nl.ts \
    pl.ts \
    pt_BR.ts \
    pt_PT.ts \
    ru_RU.ts \
    zh_CN.ts \
    zh_TW.ts
