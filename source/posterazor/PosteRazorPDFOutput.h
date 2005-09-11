#ifndef PosteRazorPDFOutput_h
#define PosteRazorPDFOutput_h

#include "ColorTypes.h"
#include "PaintCanvasInterface.h"

class PosteRazorPDFOutput: public PaintCanvasInterface
{
public:
	virtual ~PosteRazorPDFOutput() {};
	static PosteRazorPDFOutput* CreatePosteRazorPDFOutput();

	static unsigned int GetImageBitsPerLineCount(int widthPixels, int bitPerPixel);
	static unsigned int GetImageBytesPerLineCount(int widthPixels, int bitPerPixel);
	static unsigned int GetImageBytesCount(int widthPixels, int heightPixels, int bitPerPixel);

	virtual int SaveImage(unsigned char *imageData, int widthPixels, int heightPixels, int bitPerPixel, enum ColorTypes::eColorTypes, unsigned char *rgbPalette, int paletteEntries) = 0;

	virtual int StartPage(void) = 0;
	virtual int FinishPage(void) = 0;

	virtual int StartSaving(const char* fileName, int pages) = 0;
	virtual int FinishSaving() = 0;
};

#endif