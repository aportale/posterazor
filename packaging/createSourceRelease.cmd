SET ARCHIVEFILENAME=PosteRazor-1.5-Source.zip
del %ARCHIVEFILENAME%
7z a -tzip -r %ARCHIVEFILENAME% -x!.svn ..\src ..\packaging ..\CHANGES ..\LICENSE ..\README
