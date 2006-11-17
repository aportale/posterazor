@echo off

call ..\..\thirdparty\FreeImage\clean.bat > nul
devenv.exe ..\..\thirdparty\FreeImage\FreeImage.sln /rebuild Release /project FreeImageLib
devenv.exe ..\..\thirdparty\FreeImage\FreeImage.sln /rebuild Debug /project FreeImageLib

devenv.exe ..\..\thirdparty\fltk-1.1\vcnet\fltk.sln /rebuild Release /project fltk
devenv.exe ..\..\thirdparty\fltk-1.1\vcnet\fltk.sln /rebuild Debug /project fltk
devenv.exe ..\..\thirdparty\fltk-1.1\vcnet\fltk.sln /rebuild Release /project fltkgl
devenv.exe ..\..\thirdparty\fltk-1.1\vcnet\fltk.sln /rebuild Debug /project fltkgl

devenv.exe PosteRazor.sln /rebuild Release /project PosteRazorUI.vcproj
devenv.exe PosteRazor.sln /rebuild Debug /project PosteRazorUI.vcproj
