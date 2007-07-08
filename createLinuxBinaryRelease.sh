pushd projects/posterazor_fltk/cmake
cmake .
make clean
make
strip PosteRazor
tar cfz PosteRazor-1.4-Linux-x86.tgz PosteRazor ../../../CHANGES  ../../../README  ../../../LICENSE
mv -f PosteRazor-1.4-Linux-x86.tgz ../../../
popd