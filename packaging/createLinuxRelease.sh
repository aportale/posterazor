#!/bin/sh

pushd ../src
cmake .
make clean
make
strip PosteRazor
tar cfz PosteRazor-1.5-preview-Linux-x86.tgz PosteRazor CHANGES  README  LICENSE
popd
mv -f ../src/PosteRazor-1.5-preview-Linux-x86.tgz .
