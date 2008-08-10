/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2008 by Alessandro Portale
	http://posterazor.sourceforge.net/

	This file is part of PosteRazor

	PosteRazor is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
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
#include <QObject>

class QSettings;
class PosteRazorImageIO;

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

class PosteRazor: public QObject, public PainterInterface
{
	Q_OBJECT

public:
	PosteRazor();
	~PosteRazor();

	bool readSettings(const QSettings *settings);
	bool writeSettings(QSettings *settings) const;
	bool loadInputImage(const char *imageFileName, char *errorMessage, int errorMessageSize);
	int savePoster(const char *fileName) const;

	int getInputImageWidthPixels(void) const;
	int getInputImageHeightPixels(void) const;
	double getInputImageHorizontalDpi(void) const;
	double getInputImageVerticalDpi(void) const;
	double getInputImageWidth(void) const;
	double getInputImageHeight(void) const;
	int getInputImageBitsPerPixel(void) const;
	ColorTypes::eColorTypes getInputImageColorType(void) const;
	UnitsOfLength::eUnitsOfLength getUnitOfLength(void) const;
	const char* getUnitOfLengthName(void) const;
	const QString getPaperFormat(void) const;
	PaperFormats::ePaperOrientations getPaperOrientation(void) const;
	double getPaperBorderTop(void) const;
	double getPaperBorderRight(void) const;
	double getPaperBorderBottom(void) const;
	double getPaperBorderLeft(void) const;
	double getCustomPaperWidth(void) const;
	double getCustomPaperHeight(void) const;
	bool getUseCustomPaperSize(void) const;
	double getPaperWidth(void) const;
	double getPaperHeight(void) const;
	double getPrintablePaperAreaWidth(void) const;
	double getPrintablePaperAreaHeight(void) const;
	double getOverlappingWidth(void) const;
	double getOverlappingHeight(void) const;
	PosteRazorEnums::eOverlappingPositions getOverlappingPosition(void) const;
	double getPosterWidth(PosteRazorEnums::ePosterSizeModes mode) const;
	double getPosterHeight(PosteRazorEnums::ePosterSizeModes mode) const;
	PosteRazorEnums::ePosterSizeModes getPosterSizeMode(void) const;
	PosteRazorEnums::eHorizontalAlignments getPosterHorizontalAlignment(void) const;
	PosteRazorEnums::eVerticalAlignments getPosterVerticalAlignment(void) const;
	ImageIOTypes::eImageFormats getPosterOutputFormat(void) const;
	bool getIsImageLoaded(void) const;

	void setUnitOfLength(UnitsOfLength::eUnitsOfLength unit);
	void setPaperFormat(const QString &format);
	void setPaperOrientation(PaperFormats::ePaperOrientations orientation);
	void setPaperBorderTop(double border);
	void setPaperBorderRight(double border);
	void setPaperBorderBottom(double border);
	void setPaperBorderLeft(double border);
	void setCustomPaperWidth(double width);
	void setCustomPaperHeight(double height);
	void setUseCustomPaperSize(bool useIt);
	void setOverlappingWidth(double width);
	void setOverlappingHeight(double height);
	void setOverlappingPosition(PosteRazorEnums::eOverlappingPositions position);
	void setPosterWidth(PosteRazorEnums::ePosterSizeModes mode, double width);
	void setPosterHeight(PosteRazorEnums::ePosterSizeModes mode, double height);
	void setPosterSizeMode(PosteRazorEnums::ePosterSizeModes mode);
	void setPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignments alignment);
	void setPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignments alignment);
	void setPosterOutputFormat(ImageIOTypes::eImageFormats format);

public slots:
	void paintOnCanvas(PaintCanvasInterface *paintCanvas, const QVariant &options) const;

private:
	double convertDistanceToCm(double distance) const;
	double convertCmToDistance(double cm) const;
	void createPreviewImage(double maxWidth, double maxHeight) const;
	double getMaximalVerticalPaperBorder(void) const;
	double getMaximalHorizontalPaperBorder(void) const;
	double getCustomMinimalPaperWidth(void) const;
	double getCustomMinimalPaperHeight(void) const;
	double getCustomMaximalPaperWidth(void) const;
	double getCustomMaximalPaperHeight(void) const;
	double convertBetweenAbsoluteAndPagesPosterDimension(double dimension, bool pagesToAbsolute, bool width) const;
	double calculateOtherPosterDimension() const;
	void setPosterDimension(PosteRazorEnums::ePosterSizeModes mode, double dimension, bool dimensionIsWidth);
	double getMaximalOverLappingWidth(void) const;
	double getMaximalOverLappingHeight(void) const;
	double getPosterDimension(PosteRazorEnums::ePosterSizeModes mode, bool width) const;
	void getPreviewSize(double imageWidth, double imageHeight, int boxWidth, int boxHeight, int &previewWidth, int &previewHeight, bool enlargeToFit) const;
	void getInputImagePreviewSize(int boxWidth, int boxHeight, int &previewWidth, int &previewHeight) const;
	void getPaperPreviewSize(int boxWidth, int boxHeight, int &previewWidth, int &previewHeight) const;
	void paintImageOnCanvas(PaintCanvasInterface *paintCanvas) const;
	void paintPaperOnCanvas(PaintCanvasInterface *paintCanvas, bool paintOverlapping) const;
	void paintPosterOnCanvas(PaintCanvasInterface *paintCanvas) const;
	void paintPosterPageOnCanvas(PaintCanvasInterface *paintCanvas, int page) const;

signals:
	void previewImageChanged(const unsigned char *rgbData, const QSize &size) const;

private:
	PosteRazorImageIO*                      m_imageIO;

	PosteRazorEnums::ePosterSizeModes       m_posterSizeMode;
	double                                  m_posterDimension;
	bool                                    m_posterDimensionIsWidth;
	PosteRazorEnums::eHorizontalAlignments  m_posterHorizontalAlignment;
	PosteRazorEnums::eVerticalAlignments    m_posterVerticalAlignment;

	bool                                    m_useCustomPaperSize;
	QString                                 m_paperFormat;
	PaperFormats::ePaperOrientations        m_paperOrientation;
	double                                  m_paperBorderTop;
	double                                  m_paperBorderRight;
	double                                  m_paperBorderBottom;
	double                                  m_paperBorderLeft;
	double                                  m_customPaperWidth;
	double                                  m_customPaperHeight;

	double                                  m_overlappingWidth;
	double                                  m_overlappingHeight;
	PosteRazorEnums::eOverlappingPositions  m_overlappingPosition;

	UnitsOfLength::eUnitsOfLength           m_unitOfLength;

	ImageIOTypes::eImageFormats             m_posterOutputFormat;
};

#endif // POSTERAZOR_H
