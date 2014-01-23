import qbs 1.0

Project {
    Application {
        name: "PosteRazor"

        Depends {
            name: "Qt"
            submodules: ["gui", "printsupport"]
        }
        Depends { name: 'cpp' }

        cpp.includePaths: ['.', buildDirectory]
        cpp.defines: ['QT_SHARED']

        files : [
            "main.cpp",
            "controller.cpp",
            "mainwindow.cpp",
            "wizard.cpp",
            "paintcanvas.cpp",
            "pdfwriter.cpp",
            "posterazorcore.cpp",
            "snapspinbox.cpp",
            "types.cpp",
            "wizardcontroller.cpp",
            "controller.h",
            "imageloaderinterface.h",
            "mainwindow.h",
            "wizard.h",
            "paintcanvas.h",
            "paintcanvasinterface.h",
            "pdfwriter.h",
            "posterazorcore.h",
            "snapspinbox.h",
            "types.h",
            "wizardcontroller.h",
            "imageloaderqt.cpp",
            "imageloaderqt.h",
            "mainwindow.ui",
            "wizard.ui",
            "posterazor.qrc"
        ]
    }
}
