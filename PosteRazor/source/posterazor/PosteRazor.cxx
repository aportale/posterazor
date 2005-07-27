#include "PosteRazor.h"
#include "PosteRazorImageIO.h"
#include <string.h>

class PosteRazorImplementation: public PosteRazor
{
private:
	PosteRazorImageIO*     m_imageIO;

	char                   m_fileName[1024];
	char                   m_documentName[1024];

	enum eDistanceUnits    m_distanceUnit;

	int                    m_sheetsColumns;
	int                    m_sheetsRows;

	float                  m_overlapWidth;
	float                  m_overlapHeight;

	enum ePosterSizeModes  m_posterSizeMode;
	double                 m_posterWidth;
	double                 m_posterHeight;

	bool                   m_useCustomPrintablePageSize;
	ePaperFormats          m_paperFormat;
	ePaperOrientations     m_paperOrientation;
	double                 m_paperBorderTop;
	double                 m_paperBorderRight;
	double                 m_paperBorderBottom;
	double                 m_paperBorderLeft;
	double                 m_customPrintablePageWidth;
	double                 m_customPrintablePageHeight;
	eBorderPositions       m_borderPosition;
	bool                   m_lastEditedSizeWasWidth;

public:
	PosteRazorImplementation()
	{
		m_imageIO                      = PosteRazorImageIO::CreatePosteRazorImageIO();

		m_posterSizeMode               = ePosterSizeModePages;
		m_posterWidth                  = 2.0;
		m_posterHeight                 = 2.0;

                m_useCustomPrintablePageSize   = false;
		m_paperFormat                  = ePaperFormatA4;
		m_paperOrientation             = ePaperOrientationPortrait;
		m_paperBorderTop               = 1.5;
		m_paperBorderRight             = 1.5;
		m_paperBorderBottom            = 1.5;
		m_paperBorderLeft              = 1.5;
		m_customPrintablePageWidth     = 20;
		m_customPrintablePageHeight    = 20;

		m_borderPosition               = eBorderPositionRightBottom;
		m_overlapWidth                 = 2.0;
		m_overlapHeight                = 2.0;

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

	void SetDistanceUnit(enum eDistanceUnits unit) {m_distanceUnit = unit;}
	enum eDistanceUnits GetDistanceUnit(void) {return m_distanceUnit;}

	void SetPaperFormat(enum ePaperFormats format) {m_paperFormat = format;}
	void SetPaperOrientation(enum ePaperOrientations orientation) {m_paperOrientation = orientation;}
	void SetPaperBorderTop(double borderTop) {m_paperBorderTop = ConvertBetweenDistanceUnits(borderTop, m_distanceUnit, eDistanceUnitCentimeter);}
	void SetPaperBorderRight(double borderRight) {m_paperBorderRight = ConvertBetweenDistanceUnits(borderRight, m_distanceUnit, eDistanceUnitCentimeter);}
	void SetPaperBorderBottom(double borderBottom) {m_paperBorderBottom = ConvertBetweenDistanceUnits(borderBottom, m_distanceUnit, eDistanceUnitCentimeter);}
	void SetPaperBorderLeft(double borderLeft) {m_paperBorderLeft = ConvertBetweenDistanceUnits(borderLeft, m_distanceUnit, eDistanceUnitCentimeter);}

	enum ePaperFormats GetPaperFormat(void) {return m_paperFormat;}
	enum ePaperOrientations GetPaperOrientation(void) {return m_paperOrientation;}
	double GetPaperBorderTop(void) {return ConvertBetweenDistanceUnits(m_paperBorderTop, eDistanceUnitCentimeter, m_distanceUnit);}
	double GetPaperBorderRight(void) {return ConvertBetweenDistanceUnits(m_paperBorderRight, eDistanceUnitCentimeter, m_distanceUnit);}
	double GetPaperBorderBottom(void) {return ConvertBetweenDistanceUnits(m_paperBorderBottom, eDistanceUnitCentimeter, m_distanceUnit);}
	double GetPaperBorderLeft(void) {return ConvertBetweenDistanceUnits(m_paperBorderLeft, eDistanceUnitCentimeter, m_distanceUnit);}

	void SetCustomPrintablePageSize(double width, double height)
	{
		m_customPrintablePageWidth = ConvertBetweenDistanceUnits(width, m_distanceUnit, eDistanceUnitCentimeter);
		m_customPrintablePageHeight = ConvertBetweenDistanceUnits(height, m_distanceUnit, eDistanceUnitCentimeter);
	}

	void GetCustomPrintablePageSize(double &width, double &height)
	{
		width = ConvertBetweenDistanceUnits(m_customPrintablePageWidth, eDistanceUnitCentimeter, m_distanceUnit);
		height = ConvertBetweenDistanceUnits(m_customPrintablePageHeight, eDistanceUnitCentimeter, m_distanceUnit);
	}

	void SetUseCustomPrintablePageSize(bool useIt) {m_useCustomPrintablePageSize = useIt;}
	bool GetUseCustomPrintablePageSize(void) {return m_useCustomPrintablePageSize;}

	void GetPrintablePageSize(double &width, double &height)
	{
		if (m_useCustomPrintablePageSize)
		{
			width = ConvertBetweenDistanceUnits(m_customPrintablePageWidth, eDistanceUnitCentimeter, m_distanceUnit);
			height = ConvertBetweenDistanceUnits(m_customPrintablePageWidth, eDistanceUnitCentimeter, m_distanceUnit);
		}
		else
		{
			GetPrintableArea(m_paperFormat, m_paperOrientation, m_distanceUnit, m_paperBorderTop, m_paperBorderRight, m_paperBorderBottom, m_paperBorderLeft, width, height);
		}
	}

	double ConvertBetweenAbsoluteAndPagesPosterDimension(double dimension, bool pagesToAbsolute, bool width)
	{
		double posterDimension = dimension;

		double printablePageWidth, printablePageHeight;
		GetPrintablePageSize(printablePageWidth, printablePageHeight);
		double printablePageDimension = ConvertBetweenDistanceUnits(width?printablePageWidth:printablePageHeight, m_distanceUnit, eDistanceUnitCentimeter);
		double overlapDimension = width?m_overlapWidth:m_overlapHeight;

		if (pagesToAbsolute)
		{
			double posterDimensionAbsolute = 0;
			if (posterDimension >= 1.0)
			{
				posterDimension -= 1.0;
				posterDimensionAbsolute += printablePageDimension;
			}
			else
			{
				posterDimensionAbsolute = posterDimension * printablePageDimension;
				posterDimension = 0;
			}

			if (posterDimension > 0)
	                        posterDimensionAbsolute += (posterDimension * (printablePageDimension - overlapDimension));

			posterDimension = posterDimensionAbsolute;
		}
		else
		{
			double posterDimensionPages = 0;
			if (posterDimension >= printablePageDimension)
			{
				posterDimension -= printablePageDimension;
				posterDimensionPages += 1.0;
			}
			else if (posterDimension < printablePageDimension)
			{
				posterDimensionPages = posterDimension / printablePageDimension;
				posterDimension = 0;
			}

			if (posterDimension > 0)
	                        posterDimensionPages += (posterDimension / (printablePageDimension - overlapDimension));

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

	void GetPreviewSize(double imageWidth, double imageHeight, int boxWidth, int boxHeight, int &previewWidth, int &previewHeight)
	{
		double aspectRatio = imageWidth / imageHeight;

		previewWidth = imageWidth<boxWidth?imageWidth:boxWidth; //cheap min()
		previewHeight = (double)previewWidth / aspectRatio;

                if (previewHeight > boxHeight)
		{
			previewWidth = (double)boxHeight * aspectRatio;
			previewHeight = boxHeight;
		}
	}

	void GetInputImagePreviewSize(int boxWidth, int boxHeight, int &previewWidth, int &previewHeight)
	{
		GetPreviewSize(GetInputImageWidthPixels(), GetInputImageHeightPixels(), boxWidth, boxHeight, previewWidth, previewHeight);
	}

	void GetInputImagePreview(unsigned char* buffer, int pixelWidth, int pixelHeight) {m_imageIO->GetPreview(buffer, pixelWidth, pixelHeight);}

	virtual void GetPaperPreviewSize(int boxWidth, int boxHeight, int &previewWidth, int &previewHeight)
	{
		double paperWidth, paperHeight;

		if (GetUseCustomPrintablePageSize())
		{
			GetPrintablePageSize(paperWidth, paperHeight);
		}
		else
		{
			GetPaperDimensions(GetPaperFormat(), GetPaperOrientation(), m_distanceUnit, paperWidth, paperHeight);
		}

		GetPreviewSize(paperWidth, paperHeight, boxWidth, boxHeight, previewWidth, previewHeight);
	}

	virtual void GetPaperPreview(unsigned char* buffer, int pixelWidth, int pixelHeight, bool withOverlap)
	{
		memset(buffer, 128, pixelWidth*pixelHeight*3);
	}
};

PosteRazor* PosteRazor::CreatePosteRazor()
{
	return (PosteRazor*)new PosteRazorImplementation();
}
