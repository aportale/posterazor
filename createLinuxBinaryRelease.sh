#!/bin/sh

pushd src
cmake .
make clean
make
strip PosteRazor
tar cfz PosteRazor-1.5-preview-Linux-x86.tgz PosteRazor CHANGES  README  LICENSE
mv -f PosteRazor-1.5-preview-Linux-x86.tgz ../
popd