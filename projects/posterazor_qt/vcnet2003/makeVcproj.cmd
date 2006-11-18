copy ..\qmake\*.pro .
qmake -tp vc
del *.pro /Q /F
