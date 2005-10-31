/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005 by Alessandro Portale
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

#ifndef PosteRazorImageIO_h
#define PosteRazorImageIO_h

#include "DistanceUnits.h"
#include "ColorTypes.h"
#include "PaintCanvasInterface.h"
#include "ImageIOTypes.h"

class PosteRazorImageIO: public ColorTypes
{
public:
	virtual ~PosteRazorImageIO() {};
	static PosteRazorImageIO* CreatePosteRazorImageIO();

	virtual bool LoadInputImage(const char *imageFileName, char *errorMessage, int errorMessageSize) = 0;
	virtual bool IsImageLoaded(void) const = 0;

	virtual int GetWidthPixels(void) const = 0;
	virtual int GetHeightPixels(void) const = 0;

	virtual double GetHorizontalDotsPerDistanceUnit(enum DistanceUnits::eDistanceUnits unit) const = 0;
	virtual double GetVerticalDotsPerDistanceUnit(enum DistanceUnits::eDistanceUnits unit) const = 0;

	virtual double GetWidth(enum DistanceUnits::eDistanceUnits unit) const = 0;
	virtual double GetHeight(enum DistanceUnits::eDistanceUnits unit) const = 0;

	virtual void GetImageAsRGB(unsigned char *buffer) const = 0;
	virtual void GetImageAsRGB(unsigned char *buffer, int width, int height) const = 0;
	
	virtual int GetBitsPerPixel(void) const = 0;
	virtual enum eColorTypes GetColorDataType(void) const = 0;

	virtual int SavePoster(const char *fileName, enum ImageIOTypes::eImageFormats format, const PainterInterface *painter, int pagesCount, double widthCm, double heightCm) const = 0;
};

#endif