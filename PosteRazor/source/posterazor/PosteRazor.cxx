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

#include "PosteRazor.h"
#include "PosteRazorImageIO.h"
#include <stdio.h>
#include <string.h>
#ifdef WIN32
  #include <windows.h>
#else
  #include <stdlib.h>
#endif
#include <math.h>

#define MIN(a, b) ((a)<=(b)?(a):(b))
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MINMAX(a, min, max) (MIN((max), MAX((a), (min))))

const char preferencesKey_PosterSizeMode[] = "PosterSizeMode";
const char preferencesKey_PosterDimension[] = "PosterDimension";
const char preferencesKey_PosterDimensionIsWidth[] = "PosterDimensionIsWidth";
const char preferencesKey_PosterHorizontalAlignment[] = "PosterHorizontalAlignment";
const char preferencesKey_PosterVerticalAlignment[] = "PosterVerticalAlignment";
const char preferencesKey_UseCustomPaperSize[] = "UseCustomPaperSize";
const char preferencesKey_PaperFormat[] = "PaperFormat";
const char preferencesKey_PaperOrientation[] = "PaperOrientation";
const char preferencesKey_PaperBorderTop[] = "PaperBorderTop";
const char preferencesKey_PaperBorderRight[] = "PaperBorderRight";
const char preferencesKey_PaperBorderBottom[] = "PaperBorderBottom";
const char preferencesKey_PaperBorderLeft[] = "PaperBorderLeft";
const char preferencesKey_CustomPaperWidth[] = "CustomPaperWidth";
const char preferencesKey_CustomPaperHeight[] = "CustomPaperHeight";
const char preferencesKey_OverlappingWidth[] = "OverlappingWidth";
const char preferencesKey_OverlappingHeight[] = "OverlappingHeight";
const char preferencesKey_OverlappingPosition[] = "OverlappingPosition";
const char preferencesKey_UnitOfLength[] = "UnitOfLength";
const char preferencesKey_PosterOutputFormat[] = "PosterOutputFormat";
const char preferencesKey_LaunchPDFApplication[] = "LaunchPDFApplication";

class PosteRazorImplementation: public PosteRazor
{
private:
	PosteRazorImageIO*     m_imageIO;

	UnitsOfLength::eUnitsOfLength     m_UnitOfLength;

	double                            m_overlappingWidth;
	double                            m_overlappingHeight;
	PosteRazorEnums::eOverlappingPositions m_overlappingPosition;

	PosteRazorEnums::ePosterSizeModes                  m_posterSizeMode;
	double                            m_posterDimension;
	bool                              m_posterDimensionIsWidth;
	PosteRazorEnums::eHorizontalAlignments             m_posterHorizontalAlignment;
	PosteRazorEnums::eVerticalAlignments               m_posterVerticalAlignment;

	bool                              m_useCustomPaperSize;
	PaperFormats::ePaperFormats       m_paperFormat;
	PaperFormats::ePaperOrientations  m_paperOrientation;
	double                            m_paperBorderTop;
	double                            m_paperBorderRight;
	double                            m_paperBorderBottom;
	double                            m_paperBorderLeft;
	double                            m_customPaperWidth;
	double                            m_customPaperHeight;

	ImageIOTypes::eImageFormats     m_posterOutputFormat;

	bool                   m_launchPDFApplication;

public:
	PosteRazorImplementation()
	{
		m_imageIO                      = PosteRazorImageIO::CreatePosteRazorImageIO();

		m_posterSizeMode               = PosteRazorEnums::ePosterSizeModePages;
		m_posterDimension              = 2.0;
		m_posterDimensionIsWidth       = true;
		m_posterHorizontalAlignment    = PosteRazorEnums::eHorizontalAlignmentLeft;
		m_posterVerticalAlignment      = PosteRazorEnums::eVerticalAlignmentTop;

		m_useCustomPaperSize           = false;
		m_paperFormat                  = PaperFormats::ePaperFormatA4;
		m_paperOrientation             = PaperFormats::ePaperOrientationPortrait;
		m_paperBorderTop               = 1.5;
		m_paperBorderRight             = 1.5;
		m_paperBorderBottom            = 1.5;
		m_paperBorderLeft              = 1.5;
		m_customPaperWidth             = 20;
		m_customPaperHeight            = 20;

		m_overlappingWidth             = 1.0;
		m_overlappingHeight            = 1.0;
		m_overlappingPosition          = PosteRazorEnums::eOverlappingPositionBottomRight;

		m_UnitOfLength                 = UnitsOfLength::eUnitOfLengthCentimeter;

		m_posterOutputFormat           = ImageIOTypes::eImageFormatPDF;

		m_launchPDFApplication         = true;
	}

	~PosteRazorImplementation()
	{
		delete m_imageIO;
	}

	virtual bool ReadPersistentPreferences(PersistentPreferencesInterface *preferences)
	{
		bool returnValue = true;
		
		m_posterSizeMode               = (PosteRazorEnums::ePosterSizeModes)preferences->GetInteger(preferencesKey_PosterSizeMode, (int)m_posterSizeMode);
		m_posterDimension              = preferences->GetDouble(preferencesKey_PosterDimension, m_posterDimension);
		m_posterDimensionIsWidth       = preferences->GetBoolean(preferencesKey_PosterDimensionIsWidth, m_posterDimensionIsWidth);
		m_posterHorizontalAlignment    = (PosteRazorEnums::eHorizontalAlignments)preferences->GetInteger(preferencesKey_PosterHorizontalAlignment, (int)m_posterHorizontalAlignment);
		m_posterVerticalAlignment      = (PosteRazorEnums::eVerticalAlignments)preferences->GetInteger(preferencesKey_PosterVerticalAlignment, (int)m_posterVerticalAlignment);
		m_useCustomPaperSize           = preferences->GetBoolean(preferencesKey_UseCustomPaperSize, m_useCustomPaperSize);
		m_paperFormat                  = (PaperFormats::ePaperFormats)preferences->GetInteger(preferencesKey_PaperFormat, (int)m_paperFormat);
		m_paperOrientation             = (PaperFormats::ePaperOrientations)preferences->GetInteger(preferencesKey_PaperOrientation, (int)m_paperOrientation);
		m_paperBorderTop               = preferences->GetDouble(preferencesKey_PaperBorderTop, m_paperBorderTop);
		m_paperBorderRight             = preferences->GetDouble(preferencesKey_PaperBorderRight, m_paperBorderRight);
		m_paperBorderBottom            = preferences->GetDouble(preferencesKey_PaperBorderBottom, m_paperBorderBottom);
		m_paperBorderLeft              = preferences->GetDouble(preferencesKey_PaperBorderLeft, m_paperBorderLeft);
		m_customPaperWidth             = preferences->GetDouble(preferencesKey_CustomPaperWidth, m_customPaperWidth);
		m_customPaperHeight            = preferences->GetDouble(preferencesKey_CustomPaperHeight, m_customPaperHeight);
		m_overlappingWidth             = preferences->GetDouble(preferencesKey_OverlappingWidth, m_overlappingWidth);
		m_overlappingHeight            = preferences->GetDouble(preferencesKey_OverlappingHeight, m_overlappingHeight);
		m_overlappingPosition          = (PosteRazorEnums::eOverlappingPositions)preferences->GetInteger(preferencesKey_OverlappingPosition, (int)m_overlappingPosition);
		m_UnitOfLength                 = (UnitsOfLength::eUnitsOfLength)preferences->GetInteger(preferencesKey_UnitOfLength, (int)m_UnitOfLength);
		m_posterOutputFormat           = (ImageIOTypes::eImageFormats)preferences->GetInteger(preferencesKey_PosterOutputFormat, (int)m_posterOutputFormat);
		m_launchPDFApplication         = preferences->GetBoolean(preferencesKey_LaunchPDFApplication, m_launchPDFApplication);

		return returnValue;
	}

	virtual bool WritePersistentPreferences(PersistentPreferencesInterface *preferences) const
	{
		bool returnValue = true;

		preferences->SetInteger((int)m_posterSizeMode, preferencesKey_PosterSizeMode);
		preferences->SetDouble(m_posterDimension, preferencesKey_PosterDimension);
		preferences->SetBoolean(m_posterDimensionIsWidth, preferencesKey_PosterDimensionIsWidth);
		preferences->SetInteger((int)m_posterHorizontalAlignment, preferencesKey_PosterHorizontalAlignment);
		preferences->SetInteger((int)m_posterVerticalAlignment, preferencesKey_PosterVerticalAlignment);
		preferences->SetBoolean(m_useCustomPaperSize, preferencesKey_UseCustomPaperSize);
		preferences->SetInteger((int)m_paperFormat, preferencesKey_PaperFormat);
		preferences->SetInteger((int)m_paperOrientation, preferencesKey_PaperOrientation);
		preferences->SetDouble(m_paperBorderTop, preferencesKey_PaperBorderTop);
		preferences->SetDouble(m_paperBorderRight, preferencesKey_PaperBorderRight);
		preferences->SetDouble(m_paperBorderBottom, preferencesKey_PaperBorderBottom);
		preferences->SetDouble(m_paperBorderLeft, preferencesKey_PaperBorderLeft);
		preferences->SetDouble(m_customPaperWidth, preferencesKey_CustomPaperWidth);
		preferences->SetDouble(m_customPaperHeight, preferencesKey_CustomPaperHeight);
		preferences->SetDouble(m_overlappingWidth, preferencesKey_OverlappingWidth);
		preferences->SetDouble(m_overlappingHeight, preferencesKey_OverlappingHeight);
		preferences->SetInteger((int)m_overlappingPosition, preferencesKey_OverlappingPosition);
		preferences->SetInteger((int)m_UnitOfLength, preferencesKey_UnitOfLength);
		preferences->SetInteger((int)m_posterOutputFormat, preferencesKey_PosterOutputFormat);
		preferences->SetBoolean(m_launchPDFApplication, preferencesKey_LaunchPDFApplication);

		return returnValue;
	}

	PosteRazorImageIO *GetImageIO(void)
	{
		return m_imageIO;
	}

	double ConvertDistanceToCm(double distance) const
	{
		return UnitsOfLength::ConvertBetweenUnitsOfLength(distance, GetUnitOfLength(), UnitsOfLength::eUnitOfLengthCentimeter);
	}

	double ConvertCmToDistance(double cm) const
	{
		return UnitsOfLength::ConvertBetweenUnitsOfLength(cm, UnitsOfLength::eUnitOfLengthCentimeter, GetUnitOfLength());
	}

	bool LoadInputImage(const char *imageFileName, char *errorMessage, int errorMessageSize)
	{
		return m_imageIO->LoadInputImage(imageFileName, errorMessage, errorMessageSize);
	}

	bool IsImageLoaded(void) const
	{
		return m_imageIO->IsImageLoaded();
	}

	int GetInputImageWidthPixels(void) const
	{
		return m_imageIO->GetWidthPixels();
	}

	int GetInputImageHeightPixels(void) const
	{
		return m_imageIO->GetHeightPixels();
	}

	double GetInputImageHorizontalDpi(void) const
	{
		return m_imageIO->GetHorizontalDotsPerUnitOfLength(UnitsOfLength::eUnitOfLengthInch);
	}

	double GetInputImageVerticalDpi(void) const
	{
		return m_imageIO->GetVerticalDotsPerUnitOfLength(UnitsOfLength::eUnitOfLengthInch);
	}

	double GetInputImageWidth(void) const
	{
		return m_imageIO->GetWidth(m_UnitOfLength);
	}

	double GetInputImageHeight(void) const
	{
		return m_imageIO->GetHeight(m_UnitOfLength);
	}

	int GetInputImageBitsPerPixel(void) const
	{
		return m_imageIO->GetBitsPerPixel();
	}

	ColorTypes::eColorTypes GetInputImageColorType(void) const
	{
		return m_imageIO->GetColorDataType();
	}

	void SetUnitOfLength(UnitsOfLength::eUnitsOfLength unit)
	{
		m_UnitOfLength = unit;
	}

	UnitsOfLength::eUnitsOfLength GetUnitOfLength(void) const
	{
		return m_UnitOfLength;
	}

	const char* GetUnitOfLengthName(void) const
	{
		return UnitsOfLength::GetUnitOfLengthName(m_UnitOfLength);
	}

	void SetPaperFormat(PaperFormats::ePaperFormats format)
	{
		m_paperFormat = format;
	}

	void SetPaperOrientation(PaperFormats::ePaperOrientations orientation)
	{
		m_paperOrientation = orientation;
	}

	void SetPaperBorderTop(double border)
	{
		m_paperBorderTop = ConvertDistanceToCm(border);
	}

	void SetPaperBorderRight(double border)
	{
		m_paperBorderRight = ConvertDistanceToCm(border);
	}

	void SetPaperBorderBottom(double border)
	{
		m_paperBorderBottom = ConvertDistanceToCm(border);
	}

	void SetPaperBorderLeft(double border)
	{
		m_paperBorderLeft = ConvertDistanceToCm(border);
	}

	PaperFormats::ePaperFormats GetPaperFormat(void) const
	{
		return m_paperFormat;
	}

	PaperFormats::ePaperOrientations GetPaperOrientation(void) const
	{
		return m_paperOrientation;
	}

	double GetPaperBorderTop(void) const
	{
		return MINMAX(ConvertCmToDistance(m_paperBorderTop), 0, GetMaximalHorizontalPaperBorder());
	}

	double GetPaperBorderRight(void) const
	{
		return MINMAX(ConvertCmToDistance(m_paperBorderRight), 0, GetMaximalVerticalPaperBorder());
	}

	double GetPaperBorderBottom(void) const
	{
		return MINMAX(ConvertCmToDistance(m_paperBorderBottom), 0, GetMaximalHorizontalPaperBorder());
	}

	double GetPaperBorderLeft(void) const
	{
		return MINMAX(ConvertCmToDistance(m_paperBorderLeft), 0, GetMaximalVerticalPaperBorder());
	}

	double GetMaximalVerticalPaperBorder(void) const
	{
		return GetPaperWidth() / 2.0 - ConvertCmToDistance(1.0);
	}

	double GetMaximalHorizontalPaperBorder(void) const
	{
		return GetPaperHeight() / 2.0 - ConvertCmToDistance(1.0);
	}

	void SetCustomPaperWidth(double width)
	{
		m_customPaperWidth = ConvertDistanceToCm(width);
	}

	void SetCustomPaperHeight(double height)
	{
		m_customPaperHeight = ConvertDistanceToCm(height);
	}

	double GetCustomPaperWidth(void) const
	{
		return MINMAX(ConvertCmToDistance(m_customPaperWidth), GetCustomMinimalPaperWidth(), GetCustomMaximalPaperWidth());
	}

	double GetCustomPaperHeight(void) const
	{
		return MINMAX(ConvertCmToDistance(m_customPaperHeight), GetCustomMinimalPaperHeight(), GetCustomMaximalPaperHeight());
	}

	double GetCustomMinimalPaperWidth(void) const
	{
		return ConvertCmToDistance(4.0);
	}

	double GetCustomMinimalPaperHeight(void) const
	{
		return ConvertCmToDistance(4.0);
	}

	double GetCustomMaximalPaperWidth(void) const
	{
		return ConvertCmToDistance(500.0); // Maximum of PDF page
	}

	double GetCustomMaximalPaperHeight(void) const
	{
		return ConvertCmToDistance(500.0);
	}

	void SetUseCustomPaperSize(bool useIt)
	{
		m_useCustomPaperSize = useIt;
	}

	bool GetUseCustomPaperSize(void) const
	{
		return m_useCustomPaperSize;
	}

	double GetPaperWidth(void) const
	{
		return GetUseCustomPaperSize()?GetCustomPaperWidth():PaperFormats::GetPaperWidth(GetPaperFormat(), GetPaperOrientation(), m_UnitOfLength);
	}

	double GetPaperHeight(void) const
	{
		return GetUseCustomPaperSize()?GetCustomPaperHeight():PaperFormats::GetPaperHeight(GetPaperFormat(), GetPaperOrientation(), m_UnitOfLength);
	}

	double GetPrintablePaperAreaWidth(void) const
	{
		return GetPaperWidth() - GetPaperBorderLeft() - GetPaperBorderRight();
	}

	double GetPrintablePaperAreaHeight(void) const
	{
		return GetPaperHeight() - GetPaperBorderTop() - GetPaperBorderBottom();
	}

	double ConvertBetweenAbsoluteAndPagesPosterDimension(double dimension, bool pagesToAbsolute, bool width) const
	{
		double posterDimension = dimension;

		double printablePaperAreaWidth = GetPrintablePaperAreaWidth();
		double printablePaperAreaHeight = GetPrintablePaperAreaHeight();
		double printablePaperAreaDimension = ConvertDistanceToCm(width?printablePaperAreaWidth:printablePaperAreaHeight);
		double overlappingDimension = ConvertDistanceToCm(width?GetOverlappingWidth():GetOverlappingHeight());

		if (pagesToAbsolute)
		{
			double posterDimensionAbsolute = 0;
			if (posterDimension >= 1.0)
			{
				posterDimension -= 1.0;
				posterDimensionAbsolute += printablePaperAreaDimension;
			}
			else
			{
				posterDimensionAbsolute = posterDimension * printablePaperAreaDimension;
				posterDimension = 0;
			}

			if (posterDimension > 0)
	                        posterDimensionAbsolute += (posterDimension * (printablePaperAreaDimension - overlappingDimension));

			posterDimension = posterDimensionAbsolute;
		}
		else
		{
			double posterDimensionPages = 0;
			if (posterDimension >= printablePaperAreaDimension)
			{
				posterDimension -= printablePaperAreaDimension;
				posterDimensionPages += 1.0;
			}
			else if (posterDimension < printablePaperAreaDimension)
			{
				posterDimensionPages = posterDimension / printablePaperAreaDimension;
				posterDimension = 0;
			}

			if (posterDimension > 0)
	                        posterDimensionPages += (posterDimension / (printablePaperAreaDimension - overlappingDimension));

			posterDimension = posterDimensionPages;
		}

		return posterDimension;
	}

	// Since m_posterDimension holds only height or width of the poster,
	// here we calculate the other dimension considering the aspect ratio.
	double CalculateOtherPosterDimension() const
	{
		double otherDimension = 0;

		if (m_posterSizeMode != PosteRazorEnums::ePosterSizeModePercentual)
		{
			double sourceReference = m_posterDimensionIsWidth?GetInputImageWidth():GetInputImageHeight();
			double targetReference = m_posterDimensionIsWidth?GetInputImageHeight():GetInputImageWidth();
			
			double aspectRatio = sourceReference/targetReference;

			if (m_posterSizeMode != PosteRazorEnums::ePosterSizeModePages)
			{
				otherDimension = m_posterDimension / aspectRatio;
			}
			else
			{
				double sourceAbsolute = ConvertBetweenAbsoluteAndPagesPosterDimension(m_posterDimension, true, m_posterDimensionIsWidth);
				double targetAbsolute = sourceAbsolute/aspectRatio;
				otherDimension = ConvertBetweenAbsoluteAndPagesPosterDimension(targetAbsolute, false, !m_posterDimensionIsWidth);
			}
		}
		else
			otherDimension = m_posterDimension;

		return otherDimension;
	}

	void SetPosterDimension(PosteRazorEnums::ePosterSizeModes mode, double dimension, bool dimensionIsWidth)
	{
		m_posterSizeMode = mode;

		if (m_posterSizeMode == PosteRazorEnums::ePosterSizeModeAbsolute)
			dimension = ConvertDistanceToCm(dimension);

		m_posterDimension = dimension;
		m_posterDimensionIsWidth = dimensionIsWidth;
	}

	void SetOverlappingWidth(double width)
	{
		m_overlappingWidth = ConvertDistanceToCm(width);
	}

	void SetOverlappingHeight(double height)
	{
		m_overlappingHeight = ConvertDistanceToCm(height);
	}

	double GetOverlappingWidth(void) const
	{
		return MINMAX(ConvertCmToDistance(m_overlappingWidth), 0, GetMaximalOverLappingWidth());
	}

	double GetOverlappingHeight(void) const
	{
		return MINMAX(ConvertCmToDistance(m_overlappingHeight), 0, GetMaximalOverLappingHeight());
	}

	double GetMaximalOverLappingWidth(void) const
	{
		return GetPaperWidth() - GetPaperBorderLeft() - GetPaperBorderRight() - ConvertCmToDistance(1.0);
	}

	double GetMaximalOverLappingHeight(void) const
	{
		return GetPaperHeight() - GetPaperBorderTop() - GetPaperBorderBottom() - ConvertCmToDistance(1.0);
	}

	void SetOverlappingPosition(PosteRazorEnums::eOverlappingPositions position)
	{
		m_overlappingPosition = position;
	}

	PosteRazorEnums::eOverlappingPositions GetOverlappingPosition(void) const
	{
		return m_overlappingPosition;
	}

	void SetPosterWidth(PosteRazorEnums::ePosterSizeModes mode, double width)
	{
		SetPosterDimension(mode, width, true);
	}

	void SetPosterHeight(PosteRazorEnums::ePosterSizeModes mode, double height)
	{
		SetPosterDimension(mode, height, false);
	}

	double GetPosterDimension(PosteRazorEnums::ePosterSizeModes mode, bool width) const
	{
		double posterDimension = (width==m_posterDimensionIsWidth)?m_posterDimension:CalculateOtherPosterDimension();
		
		posterDimension = MAX
		(
			(mode == PosteRazorEnums::ePosterSizeModeAbsolute)?0.001
			:(mode == PosteRazorEnums::ePosterSizeModePages)?0.001
			:0.001
			, posterDimension
		);

		if (m_posterSizeMode != mode) // anything to convert?
		{
			// These are needed for conversion from and to ePosterSizeModePercentual
			double inputImageDimension = width?GetInputImageWidth():GetInputImageHeight();
			inputImageDimension = ConvertDistanceToCm(inputImageDimension);

			// First convert to absolute size mode (cm)
			if (m_posterSizeMode == PosteRazorEnums::ePosterSizeModePages)
			{
				posterDimension = ConvertBetweenAbsoluteAndPagesPosterDimension(posterDimension, true, width);
			}
			else if (m_posterSizeMode == PosteRazorEnums::ePosterSizeModePercentual)
			{
				posterDimension *= inputImageDimension;
				posterDimension /= 100.0;
			}

			// Then convert to the wanted size mode
			if (mode == PosteRazorEnums::ePosterSizeModePages)
			{
				posterDimension = ConvertBetweenAbsoluteAndPagesPosterDimension(posterDimension, false, width);
			}
			else if (mode == PosteRazorEnums::ePosterSizeModePercentual)
			{
				posterDimension /= inputImageDimension;
				posterDimension *= 100.0;
			}
		}

		if (mode == PosteRazorEnums::ePosterSizeModeAbsolute)
			posterDimension = ConvertCmToDistance(posterDimension);

                return posterDimension;
	}

	double GetPosterWidth(PosteRazorEnums::ePosterSizeModes mode) const
	{
		return GetPosterDimension(mode, true);
	}

	double GetPosterHeight(PosteRazorEnums::ePosterSizeModes mode) const
	{
		return GetPosterDimension(mode, false);
	}

	PosteRazorEnums::ePosterSizeModes GetPosterSizeMode(void) const
	{
		return m_posterSizeMode;
	}

	void SetPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignments alignment) 
	{
		m_posterHorizontalAlignment = alignment;
	}

	void SetPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignments alignment)
	{
		m_posterVerticalAlignment = alignment;
	}

	PosteRazorEnums::eHorizontalAlignments GetPosterHorizontalAlignment(void) const
	{
		return m_posterHorizontalAlignment;
	}

	PosteRazorEnums::eVerticalAlignments GetPosterVerticalAlignment(void) const
	{
		return m_posterVerticalAlignment;
	}

	void GetPreviewSize(double imageWidth, double imageHeight, int boxWidth, int boxHeight, int &previewWidth, int &previewHeight, bool enlargeToFit) const
	{
		double aspectRatio = imageWidth / imageHeight;

		if (enlargeToFit)
		{
			double widthFactor = imageWidth/(double)boxWidth;
			double heightFactor = imageHeight/(double)boxHeight;
			double factor = widthFactor<heightFactor?widthFactor:heightFactor;
			imageWidth /= factor;
			imageHeight /= factor;
		}

		previewWidth = MIN((int)imageWidth, boxWidth);
		previewHeight = (int)((double)previewWidth / aspectRatio);

                if (previewHeight > boxHeight)
		{
			previewWidth = (int)((double)boxHeight * aspectRatio);
			previewHeight = boxHeight;
		}
	}

	void GetInputImagePreviewSize(int boxWidth, int boxHeight, int &previewWidth, int &previewHeight) const
	{
		GetPreviewSize(GetInputImageWidthPixels(), GetInputImageHeightPixels(), boxWidth, boxHeight, previewWidth, previewHeight, false);
	}

	virtual void GetPaperPreviewSize(int boxWidth, int boxHeight, int &previewWidth, int &previewHeight) const
	{
		GetPreviewSize(GetPaperWidth(), GetPaperHeight(), boxWidth, boxHeight, previewWidth, previewHeight, true);
	}
	
	void GetImage(PaintCanvasInterface *paintCanvas, double maxWidth, double maxHeight) const
	{
		unsigned char *rgbData = new unsigned char[m_imageIO->GetWidthPixels() * m_imageIO->GetHeightPixels() * 3];
		int imageWidth;
		int imageHeight;
		GetInputImagePreviewSize((int)maxWidth, (int)maxHeight, imageWidth, imageHeight);
		m_imageIO->GetImageAsRGB(rgbData, imageWidth, imageHeight);
		paintCanvas->SetImage(rgbData, imageWidth, imageHeight);
		delete[] rgbData;
	}

	void PaintImageOnCanvas(PaintCanvasInterface *paintCanvas) const
	{

		if (IsImageLoaded())
		{
			double canvasWidth = 0, canvasHeight = 0;
			paintCanvas->GetSize(canvasWidth, canvasHeight);
			int boxWidth = 0, boxHeight = 0;
			double x_offset, y_offset;

			GetPreviewSize(GetInputImageWidthPixels(), GetInputImageHeightPixels(), (int)canvasWidth, (int)canvasHeight, boxWidth, boxHeight, false);
			x_offset = (canvasWidth - boxWidth) / 2;
			y_offset = (canvasHeight - boxHeight) / 2;
			
			// If the image is not downscaled, make sure that the coordinates are integers in order
			// to prevent unneeded blurring (especially in OpenGL)
			if (canvasWidth >= GetInputImageWidthPixels() && canvasHeight >= GetInputImageHeightPixels())
			{
				x_offset = floor(x_offset);
				y_offset = floor(y_offset);
			}			

			paintCanvas->DrawImage(0 + x_offset, 0 + y_offset, boxWidth, boxHeight);
		}
	}

	void PaintPaperOnCanvas(PaintCanvasInterface *paintCanvas, bool paintOverlapping) const
	{
		double canvasWidth = 0, canvasHeight = 0;
		paintCanvas->GetSize(canvasWidth, canvasHeight);
		int boxWidth = 0, boxHeight = 0;

		double paperWidth = GetPaperWidth();
		double paperHeight = GetPaperHeight();
		GetPreviewSize(paperWidth, paperHeight, (int)canvasWidth, (int)canvasHeight, boxWidth, boxHeight, true);
		double x_offset = (canvasWidth - (double)boxWidth) / 2.0;
		double y_offset = (canvasHeight - (double)boxHeight) / 2.0;
		double UnitOfLengthToPixelfactor = (double)boxWidth/paperWidth;
		double borderTop = GetPaperBorderTop() * UnitOfLengthToPixelfactor;
		double borderRight = GetPaperBorderRight() * UnitOfLengthToPixelfactor;
		double borderBottom = GetPaperBorderBottom() * UnitOfLengthToPixelfactor;
		double borderLeft = GetPaperBorderLeft() * UnitOfLengthToPixelfactor;
		double printableAreaWidth = boxWidth - borderLeft - borderRight;
		double printableAreaHeight = boxHeight - borderTop - borderBottom;
		
		paintCanvas->DrawFilledRect(0 + x_offset, 0 + y_offset, boxWidth, boxHeight, 128, 128, 128, 255);
		paintCanvas->DrawFilledRect(0 + borderLeft + x_offset, 0 + borderTop + y_offset, printableAreaWidth, printableAreaHeight, 230, 230, 230, 255);

		if (paintOverlapping)
		{
			double overlappingWidth = GetOverlappingWidth() * UnitOfLengthToPixelfactor;
			double overlappingHeight = GetOverlappingHeight() * UnitOfLengthToPixelfactor;
			PosteRazorEnums::eOverlappingPositions overlappingPosition = GetOverlappingPosition();
			double overlappingTop =
				(overlappingPosition == PosteRazorEnums::eOverlappingPositionTopLeft || overlappingPosition == PosteRazorEnums::eOverlappingPositionTopRight)?
				borderTop
				:boxHeight - borderBottom - overlappingHeight;
			double overlappingLeft = 
				(overlappingPosition == PosteRazorEnums::eOverlappingPositionTopLeft || overlappingPosition == PosteRazorEnums::eOverlappingPositionBottomLeft)?
				borderLeft
				:boxWidth - borderRight - overlappingWidth;
			
			paintCanvas->DrawFilledRect(borderLeft + x_offset, overlappingTop + y_offset, printableAreaWidth, overlappingHeight, 255, 128, 128, 255);
			paintCanvas->DrawFilledRect(overlappingLeft + x_offset, borderTop + y_offset, overlappingWidth, printableAreaHeight, 255, 128, 128, 255);
		}
	}

	void PaintPosterOnCanvas(PaintCanvasInterface *paintCanvas) const
	{
		double canvasWidth = 0, canvasHeight = 0;
		paintCanvas->GetSize(canvasWidth, canvasHeight);
		int boxWidth = 0, boxHeight = 0;

		double pagePrintableAreaWidth = GetPrintablePaperAreaWidth();
		double pagePrintableAreaHeight = GetPrintablePaperAreaHeight();
		int pagesHorizontal = (int)ceil(GetPosterWidth(PosteRazorEnums::ePosterSizeModePages));
		int pagesVertical = (int)ceil(GetPosterHeight(PosteRazorEnums::ePosterSizeModePages));
		double posterWidth = pagesHorizontal*pagePrintableAreaWidth - (pagesHorizontal-1)*GetOverlappingWidth() + GetPaperBorderLeft() + GetPaperBorderRight();
		double posterHeight = pagesVertical*pagePrintableAreaHeight - (pagesVertical-1)*GetOverlappingHeight() + GetPaperBorderTop() + GetPaperBorderBottom();
		GetPreviewSize(posterWidth, posterHeight, (int)canvasWidth, (int)canvasHeight, boxWidth, boxHeight, true);
		double x_offset = (canvasWidth - boxWidth) / 2;
		double y_offset = (canvasHeight - boxHeight) / 2;
		double UnitOfLengthToPixelfactor = (double)boxWidth/posterWidth;

		double borderTop = GetPaperBorderTop() * UnitOfLengthToPixelfactor;
		double borderRight = GetPaperBorderRight() * UnitOfLengthToPixelfactor;
		double borderBottom = GetPaperBorderBottom() * UnitOfLengthToPixelfactor;
		double borderLeft = GetPaperBorderLeft() * UnitOfLengthToPixelfactor;
		double posterPrintableAreaWidth = boxWidth - borderLeft - borderRight;
		double posterPrintableAreaHeight = boxHeight - borderTop - borderBottom;

		paintCanvas->DrawFilledRect(x_offset, y_offset, boxWidth, boxHeight, 128, 128, 128, 255);
		paintCanvas->DrawFilledRect(borderLeft + x_offset, borderTop + y_offset, posterPrintableAreaWidth, posterPrintableAreaHeight, 230, 230, 230, 255);

		double imageWidth = GetPosterWidth(PosteRazorEnums::ePosterSizeModeAbsolute) * UnitOfLengthToPixelfactor;
		double imageHeight = GetPosterHeight(PosteRazorEnums::ePosterSizeModeAbsolute) * UnitOfLengthToPixelfactor;

		PosteRazorEnums::eVerticalAlignments verticalAlignment = GetPosterVerticalAlignment();
		PosteRazorEnums::eHorizontalAlignments horizontalAlignment = GetPosterHorizontalAlignment();

		paintCanvas->DrawImage
		(
			(
				horizontalAlignment == PosteRazorEnums::eHorizontalAlignmentLeft?borderLeft
				:horizontalAlignment == PosteRazorEnums::eHorizontalAlignmentCenter?
					MINMAX(((double)boxWidth - imageWidth) / 2, borderLeft, borderLeft + posterPrintableAreaWidth - imageWidth)
				:(borderLeft + posterPrintableAreaWidth - imageWidth)
			)
			+ x_offset,

			(
				verticalAlignment == PosteRazorEnums::eVerticalAlignmentTop?borderTop
				:verticalAlignment == PosteRazorEnums::eVerticalAlignmentMiddle?
					MINMAX(((double)boxHeight - imageHeight) / 2, borderTop, borderTop + posterPrintableAreaHeight - imageHeight)
				:(borderTop + posterPrintableAreaHeight - imageHeight)
				)
			+ y_offset,
			imageWidth, imageHeight
		);

		double overlappingHeight = GetOverlappingHeight() * UnitOfLengthToPixelfactor;
		double overlappingWidth = GetOverlappingWidth() * UnitOfLengthToPixelfactor;
		pagePrintableAreaWidth *= UnitOfLengthToPixelfactor;
		pagePrintableAreaHeight *= UnitOfLengthToPixelfactor;

		double overlappingRectangleYPosition = borderTop;
		for (int pagesRow = 0; pagesRow < pagesVertical - 1; pagesRow++)
		{
			overlappingRectangleYPosition += pagePrintableAreaHeight - overlappingHeight;
			paintCanvas->DrawFilledRect(x_offset, overlappingRectangleYPosition + y_offset, boxWidth, overlappingHeight, 255, 128, 128, 128);
		}

		double overlappingRectangleXPosition = borderLeft;
		for (int pagesColumn = 0; pagesColumn < pagesHorizontal - 1; pagesColumn++)
		{
			overlappingRectangleXPosition += pagePrintableAreaWidth - overlappingWidth;
			paintCanvas->DrawFilledRect(overlappingRectangleXPosition + x_offset, y_offset, overlappingWidth, boxHeight, 255, 128, 128, 128);
		}
	}

	void PaintPosterPageOnCanvas(PaintCanvasInterface *paintCanvas, int page) const
	{
		int columsCount = (int)(ceil(GetPosterWidth(PosteRazorEnums::ePosterSizeModePages)));
		int rowsCount = (int)(ceil(GetPosterHeight(PosteRazorEnums::ePosterSizeModePages)));
		int column = page % columsCount;
		int row = ((int)(floor((double)page / (double)columsCount)));

		double posterImageWidthCm = ConvertDistanceToCm(GetPosterWidth(PosteRazorEnums::ePosterSizeModeAbsolute));
		double posterImageHeightCm = ConvertDistanceToCm(GetPosterHeight(PosteRazorEnums::ePosterSizeModeAbsolute));
		double printablePaperAreaWidthCm = ConvertDistanceToCm(GetPrintablePaperAreaWidth());
		double printablePaperAreaHeightCm = ConvertDistanceToCm(GetPrintablePaperAreaHeight());
		double overlappingWidthCm = ConvertDistanceToCm(GetOverlappingWidth());
		double overlappingHeightCm = ConvertDistanceToCm(GetOverlappingHeight());
		double printablePosterAreaWidthCm = columsCount * printablePaperAreaWidthCm - (columsCount - 1) * overlappingWidthCm;
		double printablePosterAreaHeightCm = rowsCount * printablePaperAreaHeightCm - (rowsCount - 1) * overlappingHeightCm;
		double borderTopCm = ConvertDistanceToCm(GetPaperBorderTop());
		double borderRightCm = ConvertDistanceToCm(GetPaperBorderRight());
		double borderBottomCm = ConvertDistanceToCm(GetPaperBorderBottom());
		double borderLeftCm = ConvertDistanceToCm(GetPaperBorderLeft());
		double posterTotalWidthCm = printablePosterAreaWidthCm + borderLeftCm + borderRightCm;
		double posterTotalHeightCm = printablePosterAreaHeightCm + borderTopCm + borderBottomCm;
		double imageOffsetFromLeftPosterBorderCm = 
		(
			GetPosterHorizontalAlignment() == PosteRazorEnums::eHorizontalAlignmentRight?posterTotalWidthCm - posterImageWidthCm - borderLeftCm
			:GetPosterHorizontalAlignment() == PosteRazorEnums::eHorizontalAlignmentCenter?(posterTotalWidthCm - posterImageWidthCm)/2 - borderLeftCm
			:-borderLeftCm
		);
		imageOffsetFromLeftPosterBorderCm = MINMAX(imageOffsetFromLeftPosterBorderCm, 0.0, posterTotalWidthCm - posterImageWidthCm - borderLeftCm - borderRightCm);
		double imageOffsetFromTopPosterBorderCm = 
		(
			GetPosterVerticalAlignment() == PosteRazorEnums::eVerticalAlignmentBottom?posterTotalHeightCm - posterImageHeightCm - borderTopCm
			:GetPosterVerticalAlignment() == PosteRazorEnums::eVerticalAlignmentMiddle?(posterTotalHeightCm - posterImageHeightCm)/2 - borderTopCm
			:-borderTopCm
		);
		imageOffsetFromTopPosterBorderCm = MINMAX(imageOffsetFromTopPosterBorderCm, 0.0, posterTotalHeightCm - posterImageHeightCm - borderTopCm - borderBottomCm);
		double pageOffsetToImageFromLeftCm = column * (printablePaperAreaWidthCm - overlappingWidthCm) - imageOffsetFromLeftPosterBorderCm;
		double pageOffsetToImageFromTopCm = row * (printablePaperAreaHeightCm - overlappingHeightCm) - imageOffsetFromTopPosterBorderCm;
		
		paintCanvas->DrawImage(-pageOffsetToImageFromLeftCm, -pageOffsetToImageFromTopCm, posterImageWidthCm, posterImageHeightCm);
	}

	void PaintOnCanvas(PaintCanvasInterface *paintCanvas, void* options = 0) const
	{
		const char *state = (const char*)options;
		
		if (strcmp(state, "image") == 0)
		{
			PaintImageOnCanvas(paintCanvas);
		}
		else if (strcmp(state, "paper") == 0 || strcmp(state, "overlapping") == 0)
		{
			PaintPaperOnCanvas(paintCanvas, strcmp(state, "overlapping") == 0);
		}
		else if (strcmp(state, "poster") == 0)
		{
			PaintPosterOnCanvas(paintCanvas);
		}
		else if (strncmp(state, "posterpage", strlen("posterpage")) == 0)
		{
			int page;
			sscanf(state, "posterpage %d", &page);

			PaintPosterPageOnCanvas(paintCanvas, page);
		}
	}

	void SetPosterOutputFormat(ImageIOTypes::eImageFormats format)
	{
		m_posterOutputFormat = format;
	}

	ImageIOTypes::eImageFormats GetPosterOutputFormat(void) const
	{
		return m_posterOutputFormat;
	}

	int SavePoster(const char *fileName) const
	{
		int err = 0;
		int pagesCount = (int)(ceil(GetPosterWidth(PosteRazorEnums::ePosterSizeModePages))) * (int)(ceil(GetPosterHeight(PosteRazorEnums::ePosterSizeModePages)));
		err = m_imageIO->SavePoster(fileName, GetPosterOutputFormat(), this, pagesCount, ConvertDistanceToCm(GetPrintablePaperAreaWidth()), ConvertDistanceToCm(GetPrintablePaperAreaHeight()));
		if (!err && GetLaunchPDFApplication())
		{
#if defined(WIN32)
			ShellExecute(HWND_DESKTOP, "open", fileName, NULL, NULL, SW_SHOW);
#elif defined(__APPLE__)
			char commandStr[2048];
			sprintf(commandStr, "open \"%s\"", fileName);
			system(commandStr);
#endif
		}
		return err;
	}

	virtual void SetLaunchPDFApplication(bool launch) {m_launchPDFApplication = launch;}
	virtual bool GetLaunchPDFApplication(void) const {return m_launchPDFApplication;}
};

PosteRazor* PosteRazor::CreatePosteRazor()
{
	return (PosteRazor*)new PosteRazorImplementation();
}
