#!/bin/sh

POSTERAZORVERSION=1.4
BASEPATH=/tmp/PosteRazor_source_release_$$
POSTERAZORPATH=$BASEPATH/PosteRazor-$POSTERAZORVERSION
FLNATIVEFILECHOOSERPATH=$BASEPATH/Fl_Native_File_Chooser
SOURCEARCHIVENAME=PosteRazor-$POSTERAZORVERSION-FlatSrc.tgz

PATHSTOCOPY="\
    source/tools \
    source/posterazor \
    source/posterazor_ui_common \
    source/posterazor_ui_common/translations \
    source/posterazor_ui_fltk \
"
FILESTOCOPY="\
    CHANGES \
    LICENSE \
    README \
    projects/posterazor_fltk/cmake/CMakeLists.txt \
    projects/posterazor_fltk/cmake/CMakeLists_flat_source_tree.txt \
    projects/posterazor_fltk/xcode2/info.plist \
    source/posterazor_ui_common/OSXResources/PosteRazor.icns \
    source/posterazor_ui_common/windowsResources/PosteRazor.ico \
    source/posterazor_ui_common/windowsResources/PosteRazorResource.h \
    source/posterazor_ui_common/windowsResources/PosteRazorUI.rc \
    source/posterazor_ui_common/x11Resources/PosteRazor.xpm \
"

if [ -d $BASEPATH ]; then
    rm -r $BASEPATH
fi

mkdir -p $BASEPATH
mkdir $POSTERAZORPATH
mkdir $FLNATIVEFILECHOOSERPATH

for pathtocopy in $PATHSTOCOPY; do
    cp $pathtocopy/*.{cpp,h} $POSTERAZORPATH;
done

for filetocopy in $FILESTOCOPY; do
    cp $filetocopy $POSTERAZORPATH;
done

cp -r thirdparty/Fl_Native_File_Chooser $BASEPATH
find $BASEPATH -type d -name ".svn" -exec rm -rf {} \;
find $BASEPATH -type f -name "*.o" -exec rm {} \;

tar -C $BASEPATH -czf $SOURCEARCHIVENAME .

rm -rf $BASEPATH
