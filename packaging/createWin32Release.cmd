pushd ..\src
rd /s /q Release
nmake distclean
qmake
nmake release || pause
upx --best PosteRazor.exe || pause
popd
ISCC.exe iss\posterazor.iss || pause

SET ARCHIVEFILENAME=PosteRazor-1.9.5-Win32.zip
del %ARCHIVEFILENAME%
7z a -tzip %ARCHIVEFILENAME% ..\src\PosteRazor.exe ..\CHANGES ..\LICENSE ..\README || pause
