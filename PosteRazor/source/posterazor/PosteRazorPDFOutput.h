/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2006 by Alessandro Portale
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
	static PosteRazorPDFOutput* CreatePosteRazorPDFOutput();

	static unsigned int GetImageBitsPerLineCount(int widthPixels, int bitPerPixel);
	static unsigned int GetImageBytesPerLineCount(int widthPixels, int bitPerPixel);
	static unsigned int GetImageBytesCount(int widthPixels, int heightPixels, int bitPerPixel);

	virtual int SaveImage(unsigned char *imageData, int widthPixels, int heightPixels, int bitPerPixel, enum ColorTypes::eColorTypes colorType, unsigned char *rgbPalette, int paletteEntries) = 0;
	virtual int SaveImage(const char *jpegFileName, int widthPixels, int heightPixels, enum ColorTypes::eColorTypes colorType) = 0;

	virtual int StartPage(void) = 0;
	virtual int FinishPage(void) = 0;

	virtual int StartSaving(const char* fileName, int pages, double widthCm, double heightCm) = 0;
	virtual int FinishSaving() = 0;
};

#endif
