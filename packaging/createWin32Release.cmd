pushd ..\src
rd /s /q Release
rd /s /q CMakeFiles
del CMakeCache.txt
cmake . -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release || pause
nmake clean || pause
nmake || pause
upx --best PosteRazor.exe
popd
ISCC.exe iss\posterazor.iss

SET ARCHIVEFILENAME=PosteRazor-1.9.0-alpha-Win32.zip
del %ARCHIVEFILENAME%
7z a -tzip %ARCHIVEFILENAME% ..\src\PosteRazor.exe ..\CHANGES ..\LICENSE ..\README
