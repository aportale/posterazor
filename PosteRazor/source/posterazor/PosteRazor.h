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

#ifndef PosteRazor_h
#define PosteRazor_h

#include "PaperFormats.h"
#include "ColorTypes.h"
#include "ImageIOTypes.h"
#include "PaintCanvasInterface.h"
#include "PersistentPreferencesInterface.h"

class PosteRazorEnums
{
public:
	enum eOverlappingPositions
	{
		eOverlappingPositionTopRight,
		eOverlappingPositionBottomRight,
		eOverlappingPositionBottomLeft,
		eOverlappingPositionTopLeft
	};

	enum ePosterSizeModes
	{
		ePosterSizeModeAbsolute,
		ePosterSizeModePercentual,
		ePosterSizeModePages
	};

	enum eVerticalAlignments
	{
		eVerticalAlignmentTop,
		eVerticalAlignmentMiddle,
		eVerticalAlignmentBottom
	};

	enum eHorizontalAlignments
	{
		eHorizontalAlignmentLeft,
		eHorizontalAlignmentCenter,
		eHorizontalAlignmentRight
	};
};

class PosteRazorSettersInterface
{
public:
	virtual void SetUnitOfLength(UnitsOfLength::eUnitsOfLength unit) = 0;

	virtual void SetPaperFormat(PaperFormats::ePaperFormats format) = 0;
	virtual void SetPaperOrientation(PaperFormats::ePaperOrientations orientation) = 0;

	virtual void SetPaperBorderTop(double border) = 0;
	virtual void SetPaperBorderRight(double border) = 0;
	virtual void SetPaperBorderBottom(double border) = 0;
	virtual void SetPaperBorderLeft(double border) = 0;

	virtual void SetCustomPaperWidth(double width) = 0;
	virtual void SetCustomPaperHeight(double height) = 0;
	virtual void SetUseCustomPaperSize(bool useIt) = 0;

	virtual void SetOverlappingWidth(double width) = 0;
	virtual void SetOverlappingHeight(double height) = 0;
	virtual void SetOverlappingPosition(PosteRazorEnums::eOverlappingPositions position) = 0;

	virtual void SetPosterWidth(PosteRazorEnums::ePosterSizeModes mode, double width) = 0;
	virtual void SetPosterHeight(PosteRazorEnums::ePosterSizeModes mode, double height) = 0;
	virtual void SetPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignments alignment) = 0;
	virtual void SetPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignments alignment) = 0;

	virtual void SetPosterOutputFormat(ImageIOTypes::eImageFormats format) = 0;
	virtual void SetLaunchPDFApplication(bool launch) = 0;
};

class PosteRazorGettersInterface
{
public:
	virtual int GetInputImageWidthPixels(void) const = 0;
	virtual int GetInputImageHeightPixels(void) const = 0;

	virtual double GetInputImageHorizontalDpi(void) const = 0;
	virtual double GetInputImageVerticalDpi(void) const = 0;

	virtual double GetInputImageWidth(void) const = 0;
	virtual double GetInputImageHeight(void) const = 0;

	virtual int GetInputImageBitsPerPixel(void) const = 0;
	virtual ColorTypes::eColorTypes GetInputImageColorType(void) const = 0;

	virtual UnitsOfLength::eUnitsOfLength GetUnitOfLength(void) const = 0;
	virtual const char* GetUnitOfLengthName(void) const = 0;

	virtual PaperFormats::ePaperFormats GetPaperFormat(void) const = 0;
	virtual PaperFormats::ePaperOrientations GetPaperOrientation(void) const = 0;
	virtual double GetPaperBorderTop(void) const = 0;
	virtual double GetPaperBorderRight(void) const = 0;
	virtual double GetPaperBorderBottom(void) const = 0;
	virtual double GetPaperBorderLeft(void) const = 0;

	virtual double GetCustomPaperWidth(void) const = 0;
	virtual double GetCustomPaperHeight(void) const = 0;
	virtual bool GetUseCustomPaperSize(void) const = 0;
	virtual double GetPaperWidth(void) const = 0;
	virtual double GetPaperHeight(void) const = 0;
	virtual double GetPrintablePaperAreaWidth(void) const = 0;
	virtual double GetPrintablePaperAreaHeight(void) const = 0;

	virtual double GetOverlappingWidth(void) const = 0;
	virtual double GetOverlappingHeight(void) const = 0;
	virtual PosteRazorEnums::eOverlappingPositions GetOverlappingPosition(void) const = 0;

	virtual double GetPosterWidth(PosteRazorEnums::ePosterSizeModes mode) const = 0;
	virtual double GetPosterHeight(PosteRazorEnums::ePosterSizeModes mode) const = 0;
	virtual PosteRazorEnums::ePosterSizeModes GetPosterSizeMode(void) const = 0;
	virtual PosteRazorEnums::eHorizontalAlignments GetPosterHorizontalAlignment(void) const  = 0;
	virtual PosteRazorEnums::eVerticalAlignments GetPosterVerticalAlignment(void) const = 0;

	virtual ImageIOTypes::eImageFormats GetPosterOutputFormat(void) const = 0;

	virtual bool GetLaunchPDFApplication(void) const = 0;
};

class PosteRazorActionsInterface
{
public:
	virtual bool ReadPersistentPreferences(PersistentPreferencesInterface *preferences) = 0;
	virtual bool WritePersistentPreferences(PersistentPreferencesInterface *preferences) const = 0;

	virtual bool LoadInputImage(const char *imageFileName, char *errorMessage, int errorMessageSize) = 0;
	virtual bool IsImageLoaded(void) const = 0;

	virtual int SavePoster(const char *fileName) const = 0;
};

class PosteRazor: public PosteRazorSettersInterface, public PosteRazorGettersInterface, public PosteRazorActionsInterface, public PainterInterface
{
public:
	virtual ~PosteRazor() {};
	static PosteRazor* CreatePosteRazor();
};

#endif
