#include "PosteRazor.h"
#include "PosteRazorImageIO.h"

class PosteRazorImplementation: public PosteRazor
{
private:
	PosteRazorImageIO *m_imageIO;

	char                   m_fileName[1024];
	char                   m_documentName[1024];

	int                    m_piecesColumns;
	int                    m_piecesRows;

	int                    m_sheetsColumns;
	int                    m_sheetsRows;

	float                  m_overlapWidth;
	float                  m_overlapHeight;

	double                 m_posterWidth;
	double                 m_posterHeight;

	ePaperFormats          m_paperFormat;
	enum eDistanceUnits    m_distanceUnit;
	eBorderPositions       m_borderPosition;
	ePaperOrientations     m_paperOrientation;
	bool                   m_preserveAspectRatio;
	enum ePosterSizeModes  m_posterSizeMode;
	bool                   m_lastEditedSizeWasWidth;

public:
	PosteRazorImplementation(const char* imgFileName)
	{
		m_imageIO = PosteRazorImageIO::CreatePosteRazorImageIO(imgFileName);

		m_piecesColumns           = 3;
		m_piecesRows              = 3;

		m_posterWidth             = 2.0;
		m_posterHeight            = 2.0;

		m_borderPosition          = eBorderPositionRightBottom;
		m_distanceUnit            = eDistanceUnitCentimeter;
		m_preserveAspectRatio     = true;
		m_posterSizeMode          = ePosterSizeModePages;
		m_lastEditedSizeWasWidth  = true;

		CalculateAspectRatio();
	}

	~PosteRazorImplementation()
	{
		delete m_imageIO;
	}

	PosteRazorImageIO *GetImageIO(void) {return m_imageIO;}

	int GetInputImageWidthPixels(void) {return m_imageIO->GetWidthPixels();}
	int GetInputImageHeightPixels(void) {return m_imageIO->GetHeightPixels();}

	double GetInputImageHorizontalDpi(void) {return m_imageIO->GetHorizontalDotsPerDistanceUnit(eDistanceUnitInch);}
	double GetInputImageVerticalDpi(void) {return m_imageIO->GetVerticalDotsPerDistanceUnit(eDistanceUnitInch);}

	double GetInputImageWidth(void) {return m_imageIO->GetWidth(m_distanceUnit);}
	double GetInputImageHeight(void) {return m_imageIO->GetHeight(m_distanceUnit);}

	void SetDistanceUnit(enum eDistanceUnits unit) {m_distanceUnit = unit;}
	enum eDistanceUnits GetDistanceUnit(void) {return m_distanceUnit;}

	void SetPaperFormatAndBorders(enum ePaperFormats, enum ePaperOrientations, double borderTop, double borderRight, double borderBottom, double borderLeft)
	{
	}

	void CalculateAspectRatio()
	{
		double *source = m_lastEditedSizeWasWidth?&m_posterWidth:&m_posterHeight;
		double *target = m_lastEditedSizeWasWidth?&m_posterHeight:&m_posterWidth;

		int sourceReference = m_lastEditedSizeWasWidth?GetInputImageWidth():GetInputImageHeight();
		int targetReference = m_lastEditedSizeWasWidth?GetInputImageHeight():GetInputImageWidth();
		
		double aspectRatio = (double)sourceReference/(double)targetReference;

		*target = *source / aspectRatio;
	}

	void SetPreserveAspectRatio(bool preserveIt)
	{
		m_preserveAspectRatio = preserveIt;

		if (m_preserveAspectRatio)
			CalculateAspectRatio();
	}

	bool GetPreserveAspectRatio(void) {return m_preserveAspectRatio;}

	void SetPosterWidthOrHeight(enum ePosterSizeModes mode, double widthOrHeight, bool width)
	{
		m_posterSizeMode = mode;
		if (width)
			m_posterWidth = widthOrHeight;
		else
			m_posterHeight = widthOrHeight;

		m_lastEditedSizeWasWidth = width;

		if (m_preserveAspectRatio)
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

	double GetPosterWidth(enum ePosterSizeModes mode)
	{
		// Todo: mode dependant return
		return ConvertBetweenDistanceUnits(m_posterWidth, eDistanceUnitCentimeter, m_distanceUnit);
	}

	double GetPosterHeight(enum ePosterSizeModes mode)
	{
		return ConvertBetweenDistanceUnits(m_posterHeight, eDistanceUnitCentimeter, m_distanceUnit);
	}

	enum ePosterSizeModes GetPosterSizeMode(void) {return m_posterSizeMode;}
};

PosteRazor* PosteRazor::CreatePosteRazor(const char* imgFileName)
{
	PosteRazorImplementation *impl = new PosteRazorImplementation(imgFileName);

	if (impl && !impl->GetImageIO())
	{
		delete impl;
		impl = 0;
	}

	return (PosteRazor*)impl;
}
