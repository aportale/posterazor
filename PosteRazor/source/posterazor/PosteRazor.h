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

#ifndef POSTERAZOR_H
#define POSTERAZOR_H

#include "PaperFormats.h"
#include "ColorTypes.h"
#include "ImageIOTypes.h"
#include "PaintCanvasInterface.h"

class PersistentPreferencesInterface;

class PosteRazorEnums
{
public:
	enum eOverlappingPositions {
		eOverlappingPositionTopRight,
		eOverlappingPositionBottomRight,
		eOverlappingPositionBottomLeft,
		eOverlappingPositionTopLeft
	};

	enum ePosterSizeModes {
		ePosterSizeModeAbsolute,
		ePosterSizeModePercentual,
		ePosterSizeModePages,
		ePosterSizeModeNone
	};

	enum eVerticalAlignments {
		eVerticalAlignmentTop,
		eVerticalAlignmentMiddle,
		eVerticalAlignmentBottom
	};

	enum eHorizontalAlignments {
		eHorizontalAlignmentLeft,
		eHorizontalAlignmentCenter,
		eHorizontalAlignmentRight
	};
};

class PosteRazorSettersInterface
{
public:
	virtual ~PosteRazorSettersInterface() {}

	virtual void setUnitOfLength(UnitsOfLength::eUnitsOfLength unit) = 0;

	virtual void setPaperFormat(PaperFormats::ePaperFormats format) = 0;
	virtual void setPaperOrientation(PaperFormats::ePaperOrientations orientation) = 0;

	virtual void setPaperBorderTop(double border) = 0;
	virtual void setPaperBorderRight(double border) = 0;
	virtual void setPaperBorderBottom(double border) = 0;
	virtual void setPaperBorderLeft(double border) = 0;

	virtual void setCustomPaperWidth(double width) = 0;
	virtual void setCustomPaperHeight(double height) = 0;
	virtual void setUseCustomPaperSize(bool useIt) = 0;

	virtual void setOverlappingWidth(double width) = 0;
	virtual void setOverlappingHeight(double height) = 0;
	virtual void setOverlappingPosition(PosteRazorEnums::eOverlappingPositions position) = 0;

	virtual void setPosterWidth(PosteRazorEnums::ePosterSizeModes mode, double width) = 0;
	virtual void setPosterHeight(PosteRazorEnums::ePosterSizeModes mode, double height) = 0;
	virtual void setPosterSizeMode(PosteRazorEnums::ePosterSizeModes mode) = 0;
	virtual void setPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignments alignment) = 0;
	virtual void setPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignments alignment) = 0;

	virtual void setPosterOutputFormat(ImageIOTypes::eImageFormats format) = 0;
	virtual void setLaunchPDFApplication(bool launch) = 0;
};

class PosteRazorGettersInterface
{
public:
	virtual ~PosteRazorGettersInterface() {}

	virtual int getInputImageWidthPixels(void) const = 0;
	virtual int getInputImageHeightPixels(void) const = 0;

	virtual double getInputImageHorizontalDpi(void) const = 0;
	virtual double getInputImageVerticalDpi(void) const = 0;

	virtual double getInputImageWidth(void) const = 0;
	virtual double getInputImageHeight(void) const = 0;

	virtual int getInputImageBitsPerPixel(void) const = 0;
	virtual ColorTypes::eColorTypes getInputImageColorType(void) const = 0;

	virtual UnitsOfLength::eUnitsOfLength getUnitOfLength(void) const = 0;
	virtual const char* getUnitOfLengthName(void) const = 0;

	virtual PaperFormats::ePaperFormats getPaperFormat(void) const = 0;
	virtual PaperFormats::ePaperOrientations getPaperOrientation(void) const = 0;
	virtual double getPaperBorderTop(void) const = 0;
	virtual double getPaperBorderRight(void) const = 0;
	virtual double getPaperBorderBottom(void) const = 0;
	virtual double getPaperBorderLeft(void) const = 0;

	virtual double getCustomPaperWidth(void) const = 0;
	virtual double getCustomPaperHeight(void) const = 0;
	virtual bool getUseCustomPaperSize(void) const = 0;
	virtual double getPaperWidth(void) const = 0;
	virtual double getPaperHeight(void) const = 0;
	virtual double getPrintablePaperAreaWidth(void) const = 0;
	virtual double getPrintablePaperAreaHeight(void) const = 0;

	virtual double getOverlappingWidth(void) const = 0;
	virtual double getOverlappingHeight(void) const = 0;
	virtual PosteRazorEnums::eOverlappingPositions getOverlappingPosition(void) const = 0;

	virtual double getPosterWidth(PosteRazorEnums::ePosterSizeModes mode) const = 0;
	virtual double getPosterHeight(PosteRazorEnums::ePosterSizeModes mode) const = 0;
	virtual PosteRazorEnums::ePosterSizeModes getPosterSizeMode(void) const = 0;
	virtual PosteRazorEnums::eHorizontalAlignments getPosterHorizontalAlignment(void) const = 0;
	virtual PosteRazorEnums::eVerticalAlignments getPosterVerticalAlignment(void) const = 0;

	virtual ImageIOTypes::eImageFormats getPosterOutputFormat(void) const = 0;

	virtual bool getLaunchPDFApplication(void) const = 0;

	virtual bool getIsImageLoaded(void) const = 0;
};

class PosteRazorActionsInterface
{
public:
	virtual ~PosteRazorActionsInterface() {}

	virtual bool readPersistentPreferences(PersistentPreferencesInterface *preferences) = 0;
	virtual bool writePersistentPreferences(PersistentPreferencesInterface *preferences) const = 0;

	virtual bool loadInputImage(const char *imageFileName, char *errorMessage, int errorMessageSize) = 0;

	virtual int savePoster(const char *fileName) const = 0;
};

class PosteRazor: public PosteRazorSettersInterface, public PosteRazorGettersInterface, public PosteRazorActionsInterface, public PainterInterface
{
public:
	virtual ~PosteRazor() {};
	static PosteRazor* createPosteRazor();
};

#endif // POSTERAZOR_H
