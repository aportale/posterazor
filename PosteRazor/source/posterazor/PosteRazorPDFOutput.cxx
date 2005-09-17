#include "FreeImage.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "PaintCanvasInterface.h"
#include "PosteRazorPDFOutput.h"

#define LINEFEED "\012"
#define CM2PT(cm) ((cm) / 2.54 * 72)

unsigned int PosteRazorPDFOutput::GetImageBitsPerLineCount(int widthPixels, int bitPerPixel)
{
	return (widthPixels * bitPerPixel);
}

unsigned int PosteRazorPDFOutput::GetImageBytesPerLineCount(int widthPixels, int bitPerPixel)
{

	return (int)(ceil((double)GetImageBitsPerLineCount(widthPixels, bitPerPixel)/8.0f));
}

unsigned int PosteRazorPDFOutput::GetImageBytesCount(int widthPixels, int heightPixels, int bitPerPixel)
{
	return GetImageBytesPerLineCount(widthPixels, bitPerPixel) * heightPixels;
}


class PosteRazorPDFOutputImplementation: public PosteRazorPDFOutput
{
private:
	FILE *m_outputFile;
	char *m_xref;
	int m_pdfObjectCount;
	int m_contentPagesCount;
	int m_objectPagesID;
	int m_objectResourcesID;
	int m_objectImageID;
	char m_pageContent[2048];
	double m_mediaboxWidth;
	double m_mediaboxHeight;

public:
	PosteRazorPDFOutputImplementation()
	{
		m_outputFile                 = NULL;
		m_pdfObjectCount             = 0;
		m_objectPagesID              = 0;
		m_objectResourcesID          = 0;
		m_objectImageID              = 0;
		m_pageContent[0]             = '\0';
		m_mediaboxWidth              = 5000.0;
		m_mediaboxHeight             = 5000.0;
	}

	void AddOffsetToXref(void)
	{
		char xrefLine[25];
		m_pdfObjectCount++;
		sprintf(xrefLine, "%.10d %.5d n " LINEFEED, ftell(m_outputFile), 0);
		strcat(m_xref, xrefLine);
	}

	int SaveImage(unsigned char *imageData, int widthPixels, int heightPixels, int bitPerPixel, enum ColorTypes::eColorTypes colorType, unsigned char *rgbPalette, int paletteEntries)
	{
		int err = 0;
/*
5 0 obj
<</ColorSpace [/Indexed /DeviceRGB 15 <000204c48284a44244fc0204eceadcfc4244c40204fc8284c442000000ff00ff000000ffff0000ff00ffffff00ffffff>]
/Subtype /Image
/Length 170
/Width 19
/Type /XObject
/Height 17
/BitsPerComponent 4
>>
stream
abcdefghijklmnopqrstuvwxyz1234abcdefghijklmnopqrstuvwxyz1234abcdefghijklmnopqrstuvwxyz1234abcdefghijklmnopqrstuvwxyz1234abcdefghijklmnopqrstuvwxyz1234abcdefghijklmnopqrst
endstream
endobj
*/

		AddOffsetToXref();
		m_objectResourcesID = m_pdfObjectCount;
		fprintf
		(
			m_outputFile,
			LINEFEED "%d 0 obj" LINEFEED\
			"<</XObject %d 0 R" LINEFEED\
			"/ProcSet [/PDF /Text /ImageC /ImageI /ImageB]" LINEFEED\
			">>" LINEFEED\
			"endobj",
			m_pdfObjectCount, m_pdfObjectCount + 1
		);

		AddOffsetToXref();
		fprintf
		(
			m_outputFile,
			LINEFEED "%d 0 obj" LINEFEED\
			"<</Im1 %d 0 R" LINEFEED\
			">>" LINEFEED\
			"endobj",
			m_pdfObjectCount, m_pdfObjectCount + 1
		);

		char colorSpaceString[5000] = "";
		if (colorType == ColorTypes::eColorTypeRGB)
			strcpy(colorSpaceString, "/DeviceRGB");
		AddOffsetToXref();
		m_objectImageID = m_pdfObjectCount;
		fprintf
		(
			m_outputFile,
			LINEFEED "%d 0 obj" LINEFEED\
			"<</ColorSpace %s" LINEFEED\
			"/Subtype /Image" LINEFEED\
			"/Length %d" LINEFEED\
			"/Width %d" LINEFEED\
			"/Type /XObject" LINEFEED\
			"/Height %d" LINEFEED\
			"/BitsPerComponent %d" LINEFEED\
			">>" LINEFEED\
			"stream" LINEFEED,
			m_pdfObjectCount, colorSpaceString, (int)GetImageBytesCount(widthPixels, heightPixels, bitPerPixel), widthPixels, heightPixels, bitPerPixel/3
		);
		fwrite(imageData, (int)GetImageBytesCount(widthPixels, heightPixels, bitPerPixel), 1, m_outputFile);
		fprintf
		(
			m_outputFile,
			LINEFEED "endstream" LINEFEED\
			"endobj"
		);			
		return err;
	}

	int StartPage(void)
	{
		int err = 0;
		m_pageContent[0] = '\0';

		AddOffsetToXref();
		fprintf
		(
			m_outputFile,
			LINEFEED "%d 0 obj" LINEFEED\
			"<</Group <</CS /DeviceRGB" LINEFEED\
			"/I true" LINEFEED\
			"/S /Transparency" LINEFEED\
			">>" LINEFEED\
			"/Parent %d 0 R" LINEFEED\
			"/MediaBox [0 0 %f %f]" LINEFEED\
			"/Resources %d 0 R" LINEFEED\
			"/Contents %d 0 R" LINEFEED\
			"/Type /Page" LINEFEED\
			">>" LINEFEED\
			"endobj",
			m_pdfObjectCount, m_objectPagesID, m_mediaboxWidth, m_mediaboxHeight, m_objectResourcesID, m_pdfObjectCount+1
		);

		return err;
	}

	int FinishPage(void)
	{
		int err = 0;
	
		AddOffsetToXref();
		fprintf	
		(
			m_outputFile,
			LINEFEED "%d 0 obj" LINEFEED\
			"<</Length %d" LINEFEED\
			">>" LINEFEED\
			"stream" LINEFEED\
			"%s" LINEFEED\
			"endstream" LINEFEED\
			"endobj",
			m_pdfObjectCount, strlen(m_pageContent), m_pageContent
		);

		return err;
	}

	int StartSaving(const char* fileName, int pages, double widthCm, double heightCm)
	{
		int err = 0;

		m_mediaboxWidth = CM2PT(widthCm);
		m_mediaboxHeight = CM2PT(heightCm);

		m_outputFile = fopen(fileName, "wb");
		if (!m_outputFile)
			err = 1;
		if (!err)
		{
			m_contentPagesCount = pages;
			m_xref = new char[(m_contentPagesCount+15) * 50];
			sprintf(m_xref, LINEFEED "xref" LINEFEED "0 %d" LINEFEED "0000000000 65535 f " LINEFEED, 7 + m_contentPagesCount*2);

			fprintf(m_outputFile, "%%PDF-1.3" LINEFEED "%%‚„œ”");

 			AddOffsetToXref();
			fprintf
			(
				m_outputFile,
				LINEFEED "%d 0 obj" LINEFEED\
/*				"<</Creator (PosteRazor)" LINEFEED\ */
/*				"/Producer (PosteRazor, posterazor.sourceforge.net)" LINEFEED\ */

				"<</Creator <feff0044007200610077>" LINEFEED\
				"/Producer <feff004f00700065006e004f00660066006900630065002e006f0072006700200031002e0039002e003100320032>" LINEFEED\
				"/CreationDate (D:20050908001008+02'00')" LINEFEED\

				">>" LINEFEED\
				"endobj",
				m_pdfObjectCount
			);

			AddOffsetToXref();
			fprintf
			(
				m_outputFile,
				LINEFEED "%d 0 obj" LINEFEED\
				"<</Pages %d 0 R" LINEFEED\
				"/Type /Catalog" LINEFEED\
				">>" LINEFEED\
				"endobj",
				m_pdfObjectCount, m_pdfObjectCount+1
			);

			AddOffsetToXref();
			m_objectPagesID = m_pdfObjectCount;
			char *kidsStr = new char[pages * 20];
			kidsStr[0] = '\0';
			for (int i = 0; i < pages; i++)
			{
				char kidStr[10];
				sprintf(kidStr, "%s%d 0 R", i != 0?" ":"", i*2 + (m_pdfObjectCount) + 4);
				strcat(kidsStr, kidStr);
			}
			fprintf
			(
				m_outputFile,
				LINEFEED "%d 0 obj" LINEFEED\
				"<</MediaBox [0 0 %f %f]" LINEFEED\
				"/Resources %d 0 R" LINEFEED\
				"/Kids [%s]" LINEFEED\
				"/Count %d" LINEFEED\
				"/Type /Pages" LINEFEED\
				">>" LINEFEED\
				"endobj",
				m_pdfObjectCount, 50.0, 50.0, m_pdfObjectCount + 1, kidsStr, pages
			);
			delete[] kidsStr;
		}
		return err;
	}

	int FinishSaving()
	{
		int err = 0;

		unsigned int startxref = ftell(m_outputFile);
		fprintf(m_outputFile, m_xref);

		fprintf
		(
			m_outputFile,
			"trailer" LINEFEED\
			"<</Info 1 0 R" LINEFEED\
			"/Root 2 0 R" LINEFEED\
			"/Size %d" LINEFEED\
			">>" LINEFEED\
			"startxref" LINEFEED\
			"%d" LINEFEED\
			"%%%%EOF" LINEFEED,
			m_pdfObjectCount + 1, startxref
		);

		if (m_xref)
			delete[] m_xref;
		fclose(m_outputFile);
		return err;
	}

	void DrawFilledRect(double x, double y, double width, double heigth, unsigned char red, unsigned char green, unsigned char blue) {}
	void DrawLine(double x1, double y1, double x2, double y2, unsigned char red, unsigned char green, unsigned char blue) {}
	void GetSize(double &width, double &height) const {}
	void SetImage(const unsigned char* rgbData, double width, double height) {}
	void DrawImage(double x, double y, double width, double height)
	{
		char imageCode[2048]="";

		sprintf
		(
			imageCode,
			"0 w" LINEFEED\
			"q 0 0 %.4f %.4f re W* n" LINEFEED\
			"q %.4f 0 0 %.4f %.4f %.4f cm" LINEFEED\
			"  /Im1 Do Q" LINEFEED\
			"Q "
			,
			m_mediaboxWidth, m_mediaboxHeight,
			CM2PT(width), CM2PT(height), CM2PT(x), m_mediaboxHeight-CM2PT(y)-CM2PT(height)
		);

		strcat(m_pageContent, imageCode);
	}
};

PosteRazorPDFOutput* PosteRazorPDFOutput::CreatePosteRazorPDFOutput(void)
{
	return (PosteRazorPDFOutput*) new PosteRazorPDFOutputImplementation();
}