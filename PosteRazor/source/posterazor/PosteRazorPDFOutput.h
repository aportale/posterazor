/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2007 by Alessandro Portale
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

#ifndef PosteRazorPDFOutput_h
#define PosteRazorPDFOutput_h

#include "ColorTypes.h"
#include "PaintCanvasInterface.h"

class PosteRazorPDFOutput: public PaintCanvasInterface
{
public:
	virtual ~PosteRazorPDFOutput() {};
	static PosteRazorPDFOutput* createPosteRazorPDFOutput();

	static unsigned int getImageBitsPerLineCount(int widthPixels, int bitPerPixel);
	static unsigned int getImageBytesPerLineCount(int widthPixels, int bitPerPixel);
	static unsigned int getImageBytesCount(int widthPixels, int heightPixels, int bitPerPixel);

	virtual int saveImage(unsigned char *imageData, int widthPixels, int heightPixels, int bitPerPixel, ColorTypes::eColorTypes colorType, unsigned char *rgbPalette, int paletteEntries) = 0;
	virtual int saveImage(const char *jpegFileName, int widthPixels, int heightPixels, ColorTypes::eColorTypes colorType) = 0;

	virtual int startPage(void) = 0;
	virtual int finishPage(void) = 0;

	virtual int startSaving(const char* fileName, int pages, double widthCm, double heightCm) = 0;
	virtual int finishSaving() = 0;
};

#endif
