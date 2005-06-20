#include "PosteRazor.h"
#include "PosteRazorImageIO.h"

class PosteRazorImplementation: public PosteRazor
{
private:
	PosteRazorImageIO *m_imageIO;

	char      m_fileName[1024];
	char      m_documentName[1024];

	int       m_piecesColumns;
	int       m_piecesRows;

	int       m_sheetsColumns;
	int       m_sheetsRows;

	float     m_overlapWidth;
	float     m_overlapHeight;

	float     m_posterWidth;
	float     m_posterHeight;

	ePaperFormats m_paperFormat;
	enum eDistanceUnit m_distanceUnit;
	eBorderPositions m_borderPosition;
	ePaperOrientations m_paperOrientation;

public:
	PosteRazorImplementation(const char* imgFileName)
	{
		m_imageIO = PosteRazorImageIO::CreatePosteRazorImageIO(imgFileName);

		m_piecesColumns = 3;
		m_piecesRows = 3;

		m_posterWidth = 0.0;
		m_posterHeight = 0.0;

		m_borderPosition = eBorderPositionRightBottom;
	}

	~PosteRazorImplementation()
	{
		delete m_imageIO;
	}

	PosteRazorImageIO *GetImageIO(void) {return m_imageIO;}

	int GetPixelWidth(void) {return m_imageIO->GetPixelWidth();}
	int GetPixelHeight(void) {return m_imageIO->GetPixelHeight();}

	void SetPaperFormatAndBorders(enum ePaperFormats, enum ePaperOrientations, double borderTop, double borderRight, double borderBottom, double borderLeft)
	{
	}
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
