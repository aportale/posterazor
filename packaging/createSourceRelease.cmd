SET LISTFILENAME=files.txt
SET ARCHIVEFILENAME=PosteRazor-1.9.5-Source.zip
del %LISTFILENAME%
del %ARCHIVEFILENAME%
FOR /F %%i IN ('svn list -R ../src/') DO call :addtolistfile %%i
pushd ..\
7z a -tzip packaging\%ARCHIVEFILENAME% @packaging\%LISTFILENAME%
7z a -tzip packaging\%ARCHIVEFILENAME% CHANGES README LICENSE
popd
goto :eof

:addtolistfile
set ENTRYTOADDTOLISTFILE=%1
if not %ENTRYTOADDTOLISTFILE:~-1%==/ echo src/%ENTRYTOADDTOLISTFILE% >> %LISTFILENAME%
goto :eof
