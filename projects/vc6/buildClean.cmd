@echo off

call ..\..\thirdparty\FreeImage\clean.bat > nul
msdev.exe ..\..\thirdparty\FreeImage\FreeImage.dsw /make "FreeImageLib - ALL" /rebuild 

msdev.exe ..\..\thirdparty\fltk-1.1\visualc\fltk.dsw /make "fltk - ALL" /rebuild
msdev.exe ..\..\thirdparty\fltk-1.1\visualc\fltk.dsw /make "fltkgl - ALL" /rebuild

msdev.exe PosteRazor.dsw /make "PosteRazorUI - All" /rebuild
