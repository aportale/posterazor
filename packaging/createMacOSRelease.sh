#!/bin/bash

# PosteRazor macOS Release Build Script
# This script builds and packages PosteRazor for macOS distribution

set -e  # Exit on error

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
SRC_DIR="$PROJECT_ROOT/src"
BUILD_DIR="$SRC_DIR/build"
VERSION="1.9.7"
APP_NAME="PosteRazor"
APP_BUNDLE="$BUILD_DIR/$APP_NAME.app"
DMG_NAME="${APP_NAME}-${VERSION}-macOS.dmg"

echo "========================================="
echo "PosteRazor macOS Release Build"
echo "========================================="
echo ""

# Check if qmake is available
if ! command -v qmake &> /dev/null; then
    echo "Error: qmake not found. Please install Qt and ensure qmake is in your PATH."
    echo "You can install Qt via Homebrew: brew install qt"
    exit 1
fi

# Check if macdeployqt is available
if ! command -v macdeployqt &> /dev/null; then
    echo "Error: macdeployqt not found. Please install Qt and ensure macdeployqt is in your PATH."
    echo "macdeployqt is typically located in Qt's bin directory."
    exit 1
fi

# Change to source directory
cd "$SRC_DIR"

# Clean previous builds
echo "Cleaning previous builds..."
if [ -d "$BUILD_DIR" ]; then
    rm -rf "$BUILD_DIR"
fi
mkdir -p "$BUILD_DIR"

# Clean qmake artifacts
echo "Running qmake distclean..."
if [ -f Makefile ]; then
    make distclean 2>/dev/null || true
fi

# Generate Makefile
echo "Running qmake..."
qmake -o "$BUILD_DIR/Makefile" "$SRC_DIR/posterazor.pro"

# Build the project
echo "Building PosteRazor..."
cd "$BUILD_DIR"
make -j$(sysctl -n hw.ncpu)

# Check if app bundle was created
if [ ! -d "$APP_BUNDLE" ]; then
    echo "Error: App bundle not found at $APP_BUNDLE"
    echo "Build may have failed. Please check the output above."
    exit 1
fi

echo ""
echo "Build successful! App bundle created at: $APP_BUNDLE"
echo ""

# Deploy Qt dependencies
echo "Deploying Qt dependencies with macdeployqt..."
macdeployqt "$APP_BUNDLE" -verbose=2

echo ""
echo "========================================="
echo "Build and deployment complete!"
echo "========================================="
echo ""
echo "App bundle location: $APP_BUNDLE"
echo ""
echo "To create a DMG for distribution, you can use:"
echo "  hdiutil create -volname \"$APP_NAME\" -srcfolder \"$APP_BUNDLE\" -ov -format UDZO \"$DMG_NAME\""
echo ""

# Optional: Create DMG if create-dmg is available or using hdiutil
read -p "Create DMG file? (y/n) " -n 1 -r
echo
if [[ $REPLY =~ ^[Yy]$ ]]; then
    DMG_PATH="$PROJECT_ROOT/$DMG_NAME"
    if [ -f "$DMG_PATH" ]; then
        rm "$DMG_PATH"
    fi
    
    echo "Creating DMG..."
    hdiutil create -volname "$APP_NAME" -srcfolder "$APP_BUNDLE" -ov -format UDZO "$DMG_PATH"
    
    if [ -f "$DMG_PATH" ]; then
        echo ""
        echo "DMG created successfully: $DMG_PATH"
    else
        echo "Warning: DMG creation may have failed."
    fi
fi

echo ""
echo "Done!"

