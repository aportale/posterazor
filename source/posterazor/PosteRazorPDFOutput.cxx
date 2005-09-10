#include "FreeImage.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "PaintCanvasInterface.h"
#include "PosteRazorPDFOutput.h"

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

public:
	PosteRazorPDFOutputImplementation()
	{
		m_outputFile = NULL;
		m_pdfObjectCount = 0;
	}

	void AddOffsetToXref(void)
	{
		char xrefLine[25];
		m_pdfObjectCount++;
		sprintf(xrefLine, "%.10d %.5d n \012", ftell(m_outputFile), 0);
		strcat(m_xref, xrefLine);
	}

	int StartSaving(const char* fileName, int pages)
	{
		int err = 0;
		m_outputFile = fopen(fileName, "wb");
		if (!m_outputFile)
			err = 1;
		if (!err)
		{
			m_contentPagesCount = pages;
			m_xref = new char[m_contentPagesCount * 20 + 100];
			sprintf(m_xref, "\nxref\n0 %d\n0000000000 65535 f \012", 7 + m_contentPagesCount*2);

			fprintf(m_outputFile, "%PDF-1.3");

 			AddOffsetToXref();
			fprintf
			(
				m_outputFile,
				"\n%d 0 obj\n"\
				"<</Creator (PosteRazor)\n"\
				"/Producer (PosteRazor, posterazor.sourceforge.net)\n"\
				">>\n"\
				"endobj",
				m_pdfObjectCount
			);

			AddOffsetToXref();
			fprintf
			(
				m_outputFile,
				"\n%d 0 obj\n"\
				"<</Pages %d 0 R\n"\
				"/Type /Catalog\n"\
				">>\n"\
				"endobj",
				m_pdfObjectCount, m_pdfObjectCount+1
			);

			AddOffsetToXref();
			char kidsStr[2048] = "";
			for (int i = 0; i < pages; i++)
			{
				char kidStr[10];
				sprintf(kidStr, "%s%d 0 R", i != 0?" ":"", i + (m_pdfObjectCount*2) + 2);
				strcat(kidsStr, kidStr);
			}
			fprintf
			(
				m_outputFile,
				"\n%d 0 obj\n"\
				"<</MediaBox [0 0 %f %f]\n"\
				"/Resources %d 0 R\n"\
				"/Kids [%s]\n"\
				"/Count %d\n"\
				"/Type /Pages\n"\
				">>\n"\
				"endobj",
				m_pdfObjectCount, 50.0, 50.0, m_pdfObjectCount + 1, kidsStr, pages
			);
		}
		return err;
	}

	int SaveImage(unsigned char *imageData, int widthPixels, int heightPixels, int bitPerPixel, enum ColorTypes::eColorTypes, unsigned char *rgbPalette, int paletteEntries)
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
		char colorSpaceString[5000] = "";

		AddOffsetToXref();
		fprintf
		(
			m_outputFile,
			"\n%d 0 obj\n"\
			"<</ColorSpace %s\n"\
			"/Subtype /Image\n"\
			"/Length %d\n"\
			"/Width %d\n"\
			"/Type /XObject\n"\
			"/Height %d\n"\
			"/BitsPerComponent %d\n"\
			">>\n"\
			"endobj",
			m_pdfObjectCount, colorSpaceString, (int)GetImageBytesCount(widthPixels, heightPixels, bitPerPixel), widthPixels, heightPixels, bitPerPixel
		);
		return err;
	}

	int FinishSaving()
	{
		int err = 0;
		err = fputs(m_xref, m_outputFile);
		if (m_xref)
			delete[] m_xref;
		fclose(m_outputFile);
		return err;
	}

	void DrawFilledRect(double x, double y, double width, double heigth, unsigned char red, unsigned char green, unsigned char blue) {}
	void DrawLine(double x1, double y1, double x2, double y2, unsigned char red, unsigned char green, unsigned char blue) {}
	void GetSize(double &width, double &height) {}
	void SetImage(const unsigned char* rgbData, double width, double height) {}
	void DrawImage(double x, double y, double width, double height)
	{
	}
};

PosteRazorPDFOutput* PosteRazorPDFOutput::CreatePosteRazorPDFOutput(void)
{
	return (PosteRazorPDFOutput*) new PosteRazorPDFOutputImplementation();
}