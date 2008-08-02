#!/bin/sh

export ARCHIVEFILENAME=PosteRazor-1.9.0-alpha-Linux-x86.tgz
export SOURCEDIR=../src

pushd $SOURCEDIR
cmake .
make clean
make
strip PosteRazor
tar cfz $ARCHIVEFILENAME PosteRazor ../CHANGES  ../README  ../LICENSE
popd
mv -f $SOURCEDIR/$ARCHIVEFILENAME .
