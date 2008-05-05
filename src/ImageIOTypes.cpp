/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2008 by Alessandro Portale
	http://posterazor.sourceforge.net/

	This file is part of PosteRazor

	PosteRazor is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
	
	PosteRazor is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with PosteRazor; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#include "ImageIOTypes.h"

static const char* const g_imageFormats[] =
{
	"Windows, OS/2 Bitmap",           //  0
	"Dr. Halo",
	"DirectDraw Surface",
	"Graphic Interchange Format",
	"Windows Icon",                   //  4
	"Amiga IFF",
	"JBIG",
	"Independent JPEG Group",
	"Commodore 64 Koala",
	"Portable Bitmap",                //  9
	"Kodak PhotoCD",
	"PC Paintbrush Bitmap",
	"Portable Graymap",
	"Portable Network Graphics",
	"Portable Pixelmap",              // 14
	"Photoshop Document",
	"Sun Raster Graphic",
	"Targa",
	"Tagged Image File Format",
	"Wireless Bitmap",                // 19
	"X11 Bitmap",
	"X11 Pixmap"
};
static const int g_imageFormatsCount = sizeof(g_imageFormats)/sizeof(g_imageFormats[0]);

static const struct
{
	const char* const name;
	int imageFormatIndex;
} g_fileExtensions[] = {
	{"BMP",   0},
	{"CUT",   1},
	{"DDS",   2},
	{"GIF",   3},
	{"ICO",   4},
	{"IFF",   5}, {"LBM", 5},
	{"JBIG",  6},
	{"JPG",   7}, {"JPEG", 7}, {"JPE", 7}, {"JIF", 7},
	{"KOA",   8},
	{"PBM",   9},
	{"PCD",  10},
	{"PCX",  11},
	{"PGM",  12},
	{"PNG",  13},
	{"PPM",  14},
	{"PSD",  15},
	{"RAS",  16},
	{"TGA",  17},
	{"TIF",  18}, {"TIFF", 18},
	{"WBMP", 19},
	{"XBM",  20},
	{"XPM",  21}
};
static const int g_fileExtensionsCount = sizeof(g_fileExtensions)/sizeof(g_fileExtensions[0]);

int ImageIOTypes::getInputImageFormatsCount(void)
{
	return g_imageFormatsCount;
}

const char* ImageIOTypes::getInputImageFormat(int imageFormatIndex)
{
	return g_imageFormats[imageFormatIndex];
}

int ImageIOTypes::getFileExtensionsCount(int imageFormatIndex)
{
	int result = 0;

	for(int i = 0; i < g_fileExtensionsCount; i++) {
		if (g_fileExtensions[i].imageFormatIndex == imageFormatIndex) {
			result++;
		}
	}

	return result;
}

const char* ImageIOTypes::getFileExtensionForFormat(int extensionIndex, int imageFormatIndex)
{
	const char *result = g_fileExtensions[0].name;
	int nthFoundExtension = 0;
	
	for (int i = 0; i < g_fileExtensionsCount; i++) {
		if (imageFormatIndex == g_fileExtensions[i].imageFormatIndex) {
			result = g_fileExtensions[i].name;

			if (extensionIndex == nthFoundExtension)
				break;

			nthFoundExtension++;
		}
	}

	return result;
}
