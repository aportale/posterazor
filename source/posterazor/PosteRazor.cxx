#include "PosteRazor.h"
#include "PosteRazorImageIO.h"
#include <string.h>

#define MIN(a, b) ((a)<=(b)?(a):(b))
#define MAX(a, b) ((a)>(b)?(a):(b))

class PosteRazorImplementation: public PosteRazor
{
private:
	PosteRazorImageIO*     m_imageIO;

	char                   m_fileName[1024];
	char                   m_documentName[1024];

	enum eDistanceUnits    m_distanceUnit;

	int                    m_sheetsColumns;
	int                    m_sheetsRows;

	double                 m_overlappingWidth;
	double                 m_overlappingHeight;

	enum ePosterSizeModes  m_posterSizeMode;
	double                 m_posterWidth;
	double                 m_posterHeight;

	bool                   m_useCustomPaperSize;
	ePaperFormats          m_paperFormat;
	ePaperOrientations     m_paperOrientation;
	double                 m_paperBorderStandardTop;
	double                 m_paperBorderStandardRight;
	double                 m_paperBorderStandardBottom;
	double                 m_paperBorderStandardLeft;
	double                 m_paperBorderCustomTop;
	double                 m_paperBorderCustomRight;
	double                 m_paperBorderCustomBottom;
	double                 m_paperBorderCustomLeft;
	double                 m_customPaperWidth;
	double                 m_customPaperHeight;
	eBorderPositions       m_borderPosition;
	bool                   m_lastEditedSizeWasWidth;
	
public:
	PosteRazorImplementation()
	{
		m_imageIO                      = PosteRazorImageIO::CreatePosteRazorImageIO();

		m_posterSizeMode               = ePosterSizeModePages;
		m_posterWidth                  = 2.0;
		m_posterHeight                 = 2.0;

		m_useCustomPaperSize           = false;
		m_paperFormat                  = ePaperFormatA4;
		m_paperOrientation             = ePaperOrientationPortrait;
		m_paperBorderStandardTop       = 1.5;
		m_paperBorderStandardRight     = 1.5;
		m_paperBorderStandardBottom    = 1.5;
		m_paperBorderStandardLeft      = 1.5;
		m_paperBorderCustomTop         = 1.5;
		m_paperBorderCustomRight       = 1.5;
		m_paperBorderCustomBottom      = 1.5;
		m_paperBorderCustomLeft        = 1.5;
		m_customPaperWidth             = 20;
		m_customPaperHeight            = 20;

		m_borderPosition               = eBorderPositionRightBottom;
		m_overlappingWidth             = 2.0;
		m_overlappingHeight            = 2.0;

		m_distanceUnit                 = eDistanceUnitCentimeter;
		m_lastEditedSizeWasWidth       = true;
	}

	~PosteRazorImplementation()
	{
		delete m_imageIO;
	}

	PosteRazorImageIO *GetImageIO(void) {return m_imageIO;}

	bool LoadInputImage(const char *imageFileName, char *errorMessage, int errorMessageSize)
	{
		bool result = m_imageIO->LoadImage(imageFileName, errorMessage, errorMessageSize);

		if (result)
			CalculateAspectRatio();

		return result;
	}
	bool IsImageLoaded(void) {return m_imageIO->IsImageLoaded();}

	int GetInputImageWidthPixels(void) {return m_imageIO->GetWidthPixels();}
	int GetInputImageHeightPixels(void) {return m_imageIO->GetHeightPixels();}

	double GetInputImageHorizontalDpi(void) {return m_imageIO->GetHorizontalDotsPerDistanceUnit(eDistanceUnitInch);}
	double GetInputImageVerticalDpi(void) {return m_imageIO->GetVerticalDotsPerDistanceUnit(eDistanceUnitInch);}

	double GetInputImageWidth(void) {return m_imageIO->GetWidth(m_distanceUnit);}
	double GetInputImageHeight(void) {return m_imageIO->GetHeight(m_distanceUnit);}

	int GetInputImageBitsPerPixel(void) {return m_imageIO->GetBitsPerPixel();}
	enum eColorTypes GetInputImageColorType(void) {return m_imageIO->GetColorDataType();}

	void SetDistanceUnit(enum eDistanceUnits unit) {m_distanceUnit = unit;}
	enum eDistanceUnits GetDistanceUnit(void) {return m_distanceUnit;}
	const char* GetDistanceUnitName(void) {return DistanceUnits::GetDistanceUnitName(m_distanceUnit);}

	void SetPaperFormat(enum ePaperFormats format) {m_paperFormat = format;}
	void SetPaperOrientation(enum ePaperOrientations orientation) {m_paperOrientation = orientation;}
	void SetPaperBorderTop(double border, bool customPaperSize) {(customPaperSize?m_paperBorderCustomTop:m_paperBorderStandardTop) = ConvertBetweenDistanceUnits(border, m_distanceUnit, eDistanceUnitCentimeter);}
	void SetPaperBorderRight(double border, bool customPaperSize) {(customPaperSize?m_paperBorderCustomRight:m_paperBorderStandardRight) = ConvertBetweenDistanceUnits(border, m_distanceUnit, eDistanceUnitCentimeter);}
	void SetPaperBorderBottom(double border, bool customPaperSize) {(customPaperSize?m_paperBorderCustomBottom:m_paperBorderStandardBottom) = ConvertBetweenDistanceUnits(border, m_distanceUnit, eDistanceUnitCentimeter);}
	void SetPaperBorderLeft(double border, bool customPaperSize) {(customPaperSize?m_paperBorderCustomLeft:m_paperBorderStandardLeft) = ConvertBetweenDistanceUnits(border, m_distanceUnit, eDistanceUnitCentimeter);}
	void SetPaperBorderTop(double border) {SetPaperBorderTop(border, GetUseCustomPaperSize());}
	void SetPaperBorderRight(double border) {SetPaperBorderRight(border, GetUseCustomPaperSize());}
	void SetPaperBorderBottom(double border) {SetPaperBorderBottom(border, GetUseCustomPaperSize());}
	void SetPaperBorderLeft(double border) {SetPaperBorderLeft(border, GetUseCustomPaperSize());}

	enum ePaperFormats GetPaperFormat(void) {return m_paperFormat;}
	enum ePaperOrientations GetPaperOrientation(void) {return m_paperOrientation;}
	double GetPaperBorderTop(bool customPaperSize) {return ConvertBetweenDistanceUnits(customPaperSize?m_paperBorderCustomTop:m_paperBorderStandardTop, eDistanceUnitCentimeter, m_distanceUnit);}
	double GetPaperBorderRight(bool customPaperSize) {return ConvertBetweenDistanceUnits(customPaperSize?m_paperBorderCustomRight:m_paperBorderStandardRight, eDistanceUnitCentimeter, m_distanceUnit);}
	double GetPaperBorderBottom(bool customPaperSize) {return ConvertBetweenDistanceUnits(customPaperSize?m_paperBorderCustomBottom:m_paperBorderStandardBottom, eDistanceUnitCentimeter, m_distanceUnit);}
	double GetPaperBorderLeft(bool customPaperSize) {return ConvertBetweenDistanceUnits(customPaperSize?m_paperBorderCustomLeft:m_paperBorderStandardLeft, eDistanceUnitCentimeter, m_distanceUnit);}
	double GetPaperBorderTop(void) {return GetPaperBorderTop(GetUseCustomPaperSize());}
	double GetPaperBorderRight(void) {return GetPaperBorderRight(GetUseCustomPaperSize());}
	double GetPaperBorderLeft(void) {return GetPaperBorderLeft(GetUseCustomPaperSize());}
	double GetPaperBorderBottom(void) {return GetPaperBorderBottom(GetUseCustomPaperSize());}

	void SetCustomPaperSize(double width, double height)
	{
		m_customPaperWidth = ConvertBetweenDistanceUnits(width, m_distanceUnit, eDistanceUnitCentimeter);
		m_customPaperHeight = ConvertBetweenDistanceUnits(height, m_distanceUnit, eDistanceUnitCentimeter);
	}

	void GetCustomPaperSize(double &width, double &height)
	{
		width = ConvertBetweenDistanceUnits(m_customPaperWidth, eDistanceUnitCentimeter, m_distanceUnit);
		height = ConvertBetweenDistanceUnits(m_customPaperHeight, eDistanceUnitCentimeter, m_distanceUnit);
	}

	void SetUseCustomPaperSize(bool useIt) {m_useCustomPaperSize = useIt;}
	bool GetUseCustomPaperSize(void) {return m_useCustomPaperSize;}

	void GetPaperSize(double &width, double &height)
	{
		if (GetUseCustomPaperSize())
		{
			GetCustomPaperSize(width, height);
		}
		else
		{
			GetPaperDimensions(GetPaperFormat(), GetPaperOrientation(), m_distanceUnit, width, height);
		}
	}

	void GetPrintablePaperAreaSize(double &width, double &height)
	{
		GetPaperSize(width, height);
		width -= (GetPaperBorderLeft() + GetPaperBorderRight());
		height -= (GetPaperBorderTop() + GetPaperBorderBottom());
	}

	double ConvertBetweenAbsoluteAndPagesPosterDimension(double dimension, bool pagesToAbsolute, bool width)
	{
		double posterDimension = dimension;

		double printablePaperAreaWidth, printablePaperAreaHeight;
		GetPrintablePaperAreaSize(printablePaperAreaWidth, printablePaperAreaHeight);
		double printablePaperAreaDimension = ConvertBetweenDistanceUnits(width?printablePaperAreaWidth:printablePaperAreaHeight, m_distanceUnit, eDistanceUnitCentimeter);
		double overlappingDimension = width?m_overlappingWidth:m_overlappingHeight;

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

	void CalculateAspectRatio()
	{
		double *source = m_lastEditedSizeWasWidth?&m_posterWidth:&m_posterHeight;
		double *target = m_lastEditedSizeWasWidth?&m_posterHeight:&m_posterWidth;

		if (m_posterSizeMode != ePosterSizeModePercentual)
		{
			double sourceReference = m_lastEditedSizeWasWidth?GetInputImageWidth():GetInputImageHeight();
			double targetReference = m_lastEditedSizeWasWidth?GetInputImageHeight():GetInputImageWidth();
			
			double aspectRatio = sourceReference/targetReference;

			if (m_posterSizeMode != ePosterSizeModePages)
			{
				*target = *source / aspectRatio;
			}
			else
			{
				double sourceAbsolute = ConvertBetweenAbsoluteAndPagesPosterDimension(*source, true, m_lastEditedSizeWasWidth);
				double targetAbsolute = sourceAbsolute/aspectRatio;
				*target = ConvertBetweenAbsoluteAndPagesPosterDimension(targetAbsolute, false, !m_lastEditedSizeWasWidth);
			}
		}
		else
			*target = *source;
	}

	void SetPosterWidthOrHeight(enum ePosterSizeModes mode, double widthOrHeight, bool width)
	{
		m_posterSizeMode = mode;

		if (m_posterSizeMode == ePosterSizeModeAbsolute)
			widthOrHeight = ConvertBetweenDistanceUnits(widthOrHeight, m_distanceUnit, eDistanceUnitCentimeter);

		if (width)
			m_posterWidth = widthOrHeight;
		else
			m_posterHeight = widthOrHeight;

		m_lastEditedSizeWasWidth = width;

		CalculateAspectRatio();
	}

	void SetOverlappingWidth(double width) {m_overlappingWidth = ConvertBetweenDistanceUnits(width, m_distanceUnit, eDistanceUnitCentimeter);}
	void SetOverlappingHeight(double height) {m_overlappingHeight = ConvertBetweenDistanceUnits(height, m_distanceUnit, eDistanceUnitCentimeter);}
	double GetOverlappingWidth(void) {return ConvertBetweenDistanceUnits(m_overlappingWidth, m_distanceUnit, eDistanceUnitCentimeter);}
	double GetOverlappingHeight(void) {return ConvertBetweenDistanceUnits(m_overlappingHeight, m_distanceUnit, eDistanceUnitCentimeter);}

	void SetPosterWidth(enum ePosterSizeModes mode, double width)
	{
		SetPosterWidthOrHeight(mode, width, true);
	}

	void SetPosterHeight(enum ePosterSizeModes mode, double height)
	{
		SetPosterWidthOrHeight(mode, height, false);
	}

	double GetPosterDimension(enum ePosterSizeModes mode, bool width)
	{
		double posterDimension = width?m_posterWidth:m_posterHeight;

		if (m_posterSizeMode != mode) // anything to convert?
		{
			// These are needed for conversion from and to ePosterSizeModePercentual
			double inputImageDimension = width?GetInputImageWidth():GetInputImageHeight();
			inputImageDimension = ConvertBetweenDistanceUnits(inputImageDimension, m_distanceUnit, eDistanceUnitCentimeter);

			// First convert to absolute size mode (cm)
			if (m_posterSizeMode == ePosterSizeModePages)
			{
				posterDimension = ConvertBetweenAbsoluteAndPagesPosterDimension(posterDimension, true, width);
			}
			else if (m_posterSizeMode == ePosterSizeModePercentual)
			{
				posterDimension *= inputImageDimension;
				posterDimension /= 100.0;
			}

			// Then convert to the wanted size mode
			if (mode == ePosterSizeModePages)
			{
				posterDimension = ConvertBetweenAbsoluteAndPagesPosterDimension(posterDimension, false, width);
			}
			else if (mode == ePosterSizeModePercentual)
			{
				posterDimension /= inputImageDimension;
				posterDimension *= 100.0;
			}
		}

		if (mode == ePosterSizeModeAbsolute)
			posterDimension = ConvertBetweenDistanceUnits(posterDimension, eDistanceUnitCentimeter, m_distanceUnit);

                return posterDimension;
	}

	double GetPosterWidth(enum ePosterSizeModes mode)
	{
		return GetPosterDimension(mode, true);
	}

	double GetPosterHeight(enum ePosterSizeModes mode)
	{
		return GetPosterDimension(mode, false);
	}

	enum ePosterSizeModes GetPosterSizeMode(void) {return m_posterSizeMode;}

	void GetPreviewSize(double imageWidth, double imageHeight, int boxWidth, int boxHeight, int &previewWidth, int &previewHeight, bool enlargeToFit)
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

		previewWidth = imageWidth<boxWidth?(int)imageWidth:boxWidth; //cheap min()
		previewHeight = (int)((double)previewWidth / aspectRatio);

                if (previewHeight > boxHeight)
		{
			previewWidth = (int)((double)boxHeight * aspectRatio);
			previewHeight = boxHeight;
		}
	}

	void GetInputImagePreviewSize(int boxWidth, int boxHeight, int &previewWidth, int &previewHeight)
	{
		GetPreviewSize(GetInputImageWidthPixels(), GetInputImageHeightPixels(), boxWidth, boxHeight, previewWidth, previewHeight, false);
	}

	virtual void GetPaperPreviewSize(int boxWidth, int boxHeight, int &previewWidth, int &previewHeight)
	{
		double paperWidth, paperHeight;
		GetPaperSize(paperWidth, paperHeight);
		GetPreviewSize(paperWidth, paperHeight, boxWidth, boxHeight, previewWidth, previewHeight, true);
	}
	
	void GetImage(PaintCanvasInterface *paintCanvas)
	{
		unsigned char *rgbData = NULL;
		int imageWidth;
		int imageHeight;
		
		m_imageIO->GetImageAsRGB(&rgbData, imageWidth, imageHeight);
		paintCanvas->SetImage(rgbData, imageWidth, imageHeight);
	}

	void PaintOnCanvas(PaintCanvasInterface *paintCanvas, void* options = 0)
	{
		int canvasWidth = 0, canvasHeight = 0;
		paintCanvas->GetSize(canvasWidth, canvasHeight);
		int boxWidth = 0, boxHeight = 0;
		int x_offset, y_offset;
		
		const char *state = (const char*)options;
		
		if (strcmp(state, "image") == 0)
		{
			if (IsImageLoaded())
			{
				GetPreviewSize(GetInputImageWidthPixels(), GetInputImageHeightPixels(), canvasWidth, canvasHeight, boxWidth, boxHeight, false);
				x_offset = (canvasWidth - boxWidth) / 2;
				y_offset = (canvasHeight - boxHeight) / 2;

				paintCanvas->DrawImage(0 + x_offset, 0 + y_offset, boxWidth, boxHeight);
			}
		}
		else if (strcmp(state, "paper") == 0 || strcmp(state, "overlapping") == 0)
		{
			double paperWidth, paperHeight;
			GetPaperSize(paperWidth, paperHeight);
			GetPreviewSize(paperWidth, paperHeight, canvasWidth, canvasHeight, boxWidth, boxHeight, true);
			x_offset = (canvasWidth - boxWidth) / 2;
			y_offset = (canvasHeight - boxHeight) / 2;
			double factor = (double)boxWidth/paperWidth;
			int borderTop = (int)(GetPaperBorderTop() * factor);
			int borderRight = (int)(GetPaperBorderRight() * factor);
			int borderBottom = (int)(GetPaperBorderBottom() * factor);
			int borderLeft = (int)(GetPaperBorderLeft() * factor);
			int printableAreaWidth = boxWidth - borderLeft - borderRight;
			int printableAreaHeight = boxHeight - borderTop - borderBottom;
			
			paintCanvas->DrawFilledRect(0 + x_offset, 0 + y_offset, boxWidth, boxHeight, 128, 128, 128);
			paintCanvas->DrawFilledRect(0 + borderLeft + x_offset, 0 + borderTop + y_offset, printableAreaWidth, printableAreaHeight, 230, 230, 230);

			if (strcmp(state, "overlapping") == 0)
			{
				int overlappingWidth = (int)(GetOverlappingWidth() * factor);
				int overlappingHeight = (int)(GetOverlappingHeight() * factor);
				int overlappingTop = boxHeight - borderBottom - overlappingHeight;
				int overlappingLeft = boxWidth - borderRight - overlappingWidth;
				
				paintCanvas->DrawFilledRect(borderLeft + x_offset, overlappingTop + y_offset, printableAreaWidth, overlappingHeight, 255, 128, 128);
				paintCanvas->DrawFilledRect(overlappingLeft + x_offset, borderTop + y_offset, overlappingWidth, printableAreaHeight, 255, 128, 128);
			}
		}
	}
};

PosteRazor* PosteRazor::CreatePosteRazor()
{
	return (PosteRazor*)new PosteRazorImplementation();
}
