#!/bin/sh

pushd projects/posterazor_fltk/xcode2
rm -fr build
xcodebuild -project PosteRazor.xcodeproj -target PosteRazor -configuration Deployment clean build
sh stripBinary.command
hdiutil create -volname "PosteRazor" -ov -format UDZO -imagekey zlib-level=9 -srcfolder "build/Deployment" "../../../PosteRazor-1.4-OSX.dmg"
popd