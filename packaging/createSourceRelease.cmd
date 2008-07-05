SET LISTFILENAME=files.txt
SET ARCHIVEFILENAME=PosteRazor-1.5-Source.zip
del %LISTFILENAME%
del %ARCHIVEFILENAME%
FOR /F %%i IN ('svn list -R ../') DO call :addtolistfile %%i
pushd ..\
7z a -tzip packaging\%ARCHIVEFILENAME% @packaging\%LISTFILENAME%
popd
goto :eof

:addtolistfile
set ENTRYTOADDTOLISTFILE=%1
if not %ENTRYTOADDTOLISTFILE:~-1%==/ echo %ENTRYTOADDTOLISTFILE% >> %LISTFILENAME%
goto :eof
