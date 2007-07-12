pushd projects\posterazor_fltk\vc6
call buildClean.cmd
call packageDistribution.cmd
move PosteRazor-1.4-Win32.zip ..\..\..\
popd
