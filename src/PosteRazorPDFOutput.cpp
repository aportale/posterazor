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

#include "FreeImage.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "PaintCanvasInterface.h"
#include "PosteRazorPDFOutput.h"
#include <time.h>
#define LINEFEED "\012"
#define CM2PT(cm) ((cm) / 2.54 * 72)
#define JPEGFILECOPYBUFFERSIZE 10000

unsigned int PosteRazorPDFOutput::getImageBitsPerLineCount(int widthPixels, int bitPerPixel)
{
	return (widthPixels * bitPerPixel);
}

unsigned int PosteRazorPDFOutput::getImageBytesPerLineCount(int widthPixels, int bitPerPixel)
{
	return (int)(ceil((double)getImageBitsPerLineCount(widthPixels, bitPerPixel)/8.0f));
}

unsigned int PosteRazorPDFOutput::getImageBytesCount(int widthPixels, int heightPixels, int bitPerPixel)
{
	return getImageBytesPerLineCount(widthPixels, bitPerPixel) * heightPixels;
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
	const PainterInterface *m_painter;

public:
	PosteRazorPDFOutputImplementation()
		: m_outputFile(NULL)
		, m_pdfObjectCount(0)
		, m_objectPagesID(0)
		, m_objectResourcesID(0)
		, m_objectImageID(0)
		, m_mediaboxWidth(5000.0)
		, m_mediaboxHeight(5000.0)
		, m_painter(NULL)
	{
		m_pageContent[0] = '\0';
	}

	void setPainterInterface(const PainterInterface *painter)
	{
		m_painter = painter;
	}

	void AddOffsetToXref(void)
	{
		char xrefLine[25];
		m_pdfObjectCount++;
		sprintf(xrefLine, "%.10d %.5d n " LINEFEED, (int)ftell(m_outputFile), 0);
		strcat(m_xref, xrefLine);
	}

	int AddImageResourcesAndXObject()
	{
		int err = 0;

		AddOffsetToXref();
		m_objectResourcesID = m_pdfObjectCount;
		fprintf (
			m_outputFile,
			LINEFEED "%d 0 obj" LINEFEED\
			"<</XObject %d 0 R" LINEFEED\
			"/ProcSet [/PDF /Text /ImageC /ImageI /ImageB]" LINEFEED\
			">>" LINEFEED\
			"endobj",
			m_pdfObjectCount, m_pdfObjectCount + 1
		);

		AddOffsetToXref();
		fprintf (
			m_outputFile,
			LINEFEED "%d 0 obj" LINEFEED\
			"<</Im1 %d 0 R" LINEFEED\
			">>" LINEFEED\
			"endobj",
			m_pdfObjectCount, m_pdfObjectCount + 1
		);

		return err;
	}

	int saveImage(const char *jpegFileName, int widthPixels, int heightPixels, ColorTypes::eColorTypes colorType)
	{
		int err = 0;

		err = AddImageResourcesAndXObject();

		FILE *jpegFile = NULL;
		if (!err) {
			jpegFile = fopen(jpegFileName, "rb");
			if (!jpegFile)
				err = 2;
		}

		int jpegFileSize = 0;
		if (!err) {
			fseek(jpegFile, 0, SEEK_END);
			jpegFileSize = ftell(jpegFile);
			fseek(jpegFile, 0, SEEK_SET);
			if (jpegFileSize == 0)
				err = 6;
		}

		if (!err) {
			AddOffsetToXref();
			fprintf (
				m_outputFile,
				LINEFEED "%d 0 obj" LINEFEED\
				"<</ColorSpace %s" LINEFEED\
				"/Subtype /Image" LINEFEED\
				"/Length %d" LINEFEED\
				"/Width %d" LINEFEED\
				"/Type /XObject" LINEFEED\
				"/Height %d" LINEFEED\
				"/BitsPerComponent 8" LINEFEED\
				"/Filter /DCTDecode" LINEFEED\
				">>" LINEFEED\
				"stream" LINEFEED,
				m_pdfObjectCount,
				colorType==ColorTypes::eColorTypeCMYK?"/DeviceCMYK":"/DeviceRGB ", // Leaving space after RGB for eventual manual patching to CMYK
				jpegFileSize, widthPixels, heightPixels
			);
		}

		unsigned char* buffer = NULL;
		if (!err)
			buffer = new unsigned char[JPEGFILECOPYBUFFERSIZE];
		if (!buffer)
			err = 3;

		while(!err && !feof(jpegFile)) {
			size_t readBytes = fread(buffer, 1, JPEGFILECOPYBUFFERSIZE, jpegFile);
			if (!ferror(jpegFile)) {
				fwrite(buffer, 1, readBytes, m_outputFile);
				if (ferror(m_outputFile))
					err = 4;
			} else {
				err = 5;
			}
		}

		if (!err) {
			fprintf (
				m_outputFile,
				LINEFEED "endstream" LINEFEED\
				"endobj"
			);
		}

		if (buffer)
			delete[] buffer;

		fclose(jpegFile);

		return err;
	}

	int saveImage(unsigned char *imageData, int widthPixels, int heightPixels, int bitPerPixel, ColorTypes::eColorTypes colorType, unsigned char *rgbPalette, int paletteEntries)
	{
		int err = 0;
		err = AddImageResourcesAndXObject();

		const unsigned int imageBytesCount = getImageBytesCount(widthPixels, heightPixels, bitPerPixel);
		unsigned int imageBytesCountCompressed = (unsigned int)(ceil((double)imageBytesCount*1.05))+12;
		unsigned char *imageDataCompressed = NULL;

		if (!err) {
			imageDataCompressed = new unsigned char[imageBytesCountCompressed];
			if (!imageDataCompressed)
				err = 1;
		}

		if (!err) {
			imageBytesCountCompressed = FreeImage_ZLibCompress(imageDataCompressed, imageBytesCountCompressed, imageData, imageBytesCount);
			if (!imageBytesCountCompressed)
				err = 2;
		}

		char colorSpaceString[5000] = "";
		// TODO: convert to switch
		if (colorType == ColorTypes::eColorTypeRGB) {
			strcpy(colorSpaceString, "/DeviceRGB");
		} else if(colorType == ColorTypes::eColorTypeGreyscale) {
			strcpy(colorSpaceString, "/DeviceGray");
		} /* else if(colorType == ColorTypes::eColorTypeMonochrome)
		{
			sprintf(colorSpaceString, "/DeviceGray" LINEFEED "/BlackIs1 %s", rgbPalette[0]?"false":"true");
		} */ else if(colorType == ColorTypes::eColorTypeCMYK) {
			strcpy(colorSpaceString, "/DeviceCMYK");
		} else {
			sprintf(colorSpaceString, "[/Indexed /DeviceRGB %d <", paletteEntries-1); // -1, because PDF wants the highest index, not the number of entries
			for (int i = 0; i < paletteEntries; i++)
			{
				char rgbHex[20];
				sprintf(rgbHex, "%.2x%.2x%.2x", rgbPalette[i*3], rgbPalette[i*3 + 1], rgbPalette[i*3 + 2]);
				strcat(colorSpaceString, rgbHex);
			}
			strcat(colorSpaceString, ">]");
		}
		AddOffsetToXref();
		m_objectImageID = m_pdfObjectCount;
		fprintf (
			m_outputFile,
			LINEFEED "%d 0 obj" LINEFEED\
			"<</ColorSpace %s" LINEFEED\
			"/Subtype /Image" LINEFEED\
			"/Length %d" LINEFEED\
			"/Width %d" LINEFEED\
			"/Type /XObject" LINEFEED\
			"/Height %d" LINEFEED\
			"/Filter /FlateDecode" LINEFEED\
			"/BitsPerComponent %d" LINEFEED\
			">>" LINEFEED\
			"stream" LINEFEED,
			m_pdfObjectCount, colorSpaceString, (int)imageBytesCountCompressed, widthPixels, heightPixels,
			(
				colorType == ColorTypes::eColorTypePalette?bitPerPixel
				:colorType == ColorTypes::eColorTypeMonochrome?bitPerPixel
				:colorType == ColorTypes::eColorTypeGreyscale?bitPerPixel
				:colorType == ColorTypes::eColorTypeCMYK?(bitPerPixel/4)
				:(bitPerPixel/3)
			)
		);
		fwrite(imageDataCompressed, (int)imageBytesCountCompressed, 1, m_outputFile);
		fprintf (
			m_outputFile,
			LINEFEED "endstream" LINEFEED\
			"endobj"
		);
		
		if (imageDataCompressed)
			delete[] imageDataCompressed;

		return err;
	}

	int startPage(void)
	{
		int err = 0;
		m_pageContent[0] = '\0';

		AddOffsetToXref();
		fprintf (
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

	int finishPage(void)
	{
		int err = 0;
	
		AddOffsetToXref();
		fprintf (
			m_outputFile,
			LINEFEED "%d 0 obj" LINEFEED\
			"<</Length %d" LINEFEED\
			">>" LINEFEED\
			"stream" LINEFEED\
			"%s" LINEFEED\
			"endstream" LINEFEED\
			"endobj",
			m_pdfObjectCount, (int)strlen(m_pageContent), m_pageContent
		);

		return err;
	}

	int startSaving(const char* fileName, int pages, double widthCm, double heightCm)
	{
		int err = 0;

		m_mediaboxWidth = CM2PT(widthCm);
		m_mediaboxHeight = CM2PT(heightCm);

		m_outputFile = fopen(fileName, "wb");
		if (!m_outputFile)
			err = 1;
		if (!err) {
			m_contentPagesCount = pages;
			m_xref = new char[(m_contentPagesCount+15) * 50];
			sprintf(m_xref, LINEFEED "xref" LINEFEED "0 %d" LINEFEED "0000000000 65535 f " LINEFEED, 7 + m_contentPagesCount*2);

			fprintf(m_outputFile, "%%PDF-1.3" LINEFEED "%%âãÏÓ");

			time_t rawtime;
			struct tm * timeinfo;
			time(&rawtime);
			timeinfo = gmtime(&rawtime);
			char dateStr[1024];
			sprintf(dateStr, "%.4d%.2d%.2d%.2d%.2d%.2d", timeinfo->tm_year+1900, timeinfo->tm_mon+1, timeinfo->tm_mday, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

 			AddOffsetToXref();
			fprintf (
				m_outputFile,
				LINEFEED "%d 0 obj" LINEFEED\
				"<</Creator (PosteRazor)" LINEFEED\
				"/Producer (PosteRazor.SourceForge.net)" LINEFEED\
				"/CreationDate (D:%s)" LINEFEED\
				">>" LINEFEED\
				"endobj",
				m_pdfObjectCount,
				dateStr
			);

			AddOffsetToXref();
			fprintf (
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
			for (int i = 0; i < pages; i++) {
				char kidStr[10];
				sprintf(kidStr, "%s%d 0 R", i != 0?" ":"", i*2 + (m_pdfObjectCount) + 4);
				strcat(kidsStr, kidStr);
			}
			fprintf (
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

	int finishSaving()
	{
		int err = 0;

		const unsigned int startxref = ftell(m_outputFile);
		fprintf(m_outputFile, "%s", m_xref);

		fprintf (
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

	void setBackgroundColor(unsigned char, unsigned char, unsigned char) {}
	void drawFilledRect(double, double, double, double, unsigned char, unsigned char, unsigned char, unsigned char) {}
	void drawRect(double, double, double, double, unsigned char, unsigned char, unsigned char, unsigned char) {}
	void drawLine(double, double, double, double, unsigned char, unsigned char, unsigned char, unsigned char) {}
	void getSize(double &, double &) const {}
	void setImage(const unsigned char*, double, double ) {}
	void drawImage(double x, double y, double width, double height)
	{
		char imageCode[2048]="";

		sprintf (
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

PosteRazorPDFOutput* PosteRazorPDFOutput::createPosteRazorPDFOutput(void)
{
	return (PosteRazorPDFOutput*) new PosteRazorPDFOutputImplementation();
}
