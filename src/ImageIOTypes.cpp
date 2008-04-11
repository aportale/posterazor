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
	"JPEG Network Graphics",
	"Independent JPEG Group",
	"Commodore 64 Koala",             //  9
	"Multiple Network Graphics",
	"Portable Bitmap",
	"Kodak PhotoCD",
	"PC Paintbrush Bitmap",
	"Portable Graymap",               // 14
	"Portable Network Graphics",
	"Portable Pixelmap",
	"Photoshop Document",
	"Sun Raster Graphic",
	"Targa",                          // 19
	"Tagged Image File Format",
	"Wireless Bitmap",
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
	{"JNG",   7},
	{"JPG",   8}, {"JPEG", 8}, {"JPE", 8}, {"JIF", 8},
	{"KOA",   9},
	{"MNG",  10},
	{"PBM",  11},
	{"PCD",  12},
	{"PCX",  13},
	{"PGM",  14},
	{"PNG",  15},
	{"PPM",  16},
	{"PSD",  17},
	{"RAS",  18},
	{"TGA",  19},
	{"TIF",  20}, {"TIFF", 20},
	{"WBMP", 21},
	{"XBM",  22},
	{"XPM",  23}
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
