#include "FreeImage.h"
#include "PosteRazorImageIO.h"

class PosteRazorImageIOImplementation: public PosteRazorImageIO
{
private:
	FIBITMAP  *m_bitmap;

	int       m_pixelWidth;
	int       m_pixelHeight;

public:
	PosteRazorImageIOImplementation(const char* imgFileName)
	{
		m_bitmap = FreeImage_Load(FreeImage_GetFileType(imgFileName, 0), imgFileName);

		if (m_bitmap)
		{
			m_pixelWidth = FreeImage_GetWidth(m_bitmap);
			m_pixelHeight = FreeImage_GetHeight(m_bitmap);
		}
	}

	~PosteRazorImageIOImplementation()
	{
		if (m_bitmap)
			FreeImage_Unload(m_bitmap);
	}

	FIBITMAP *GetBitmap(void) {return m_bitmap;}

	int GetPixelWidth(void) {return m_pixelWidth;}
	int GetPixelHeight(void) {return m_pixelHeight;}
};

PosteRazorImageIO* PosteRazorImageIO::CreatePosteRazorImageIO(const char* imgFileName)
{
	PosteRazorImageIOImplementation *impl = new PosteRazorImageIOImplementation(imgFileName);

	if (impl && !impl->GetBitmap())
	{
		delete impl;
		impl = 0;
	}

	return (PosteRazorImageIO*)(new PosteRazorImageIOImplementation(imgFileName));
}