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

#include <stdio.h>
#include <string.h>
#include "PaintCanvasInterface.h"
#include "pdfwriter.h"
#include <time.h>
#include <QRectF>
#define LINEFEED "\012"
#define CM2PT(cm) ((cm) / 2.54 * 72)
#define JPEGFILECOPYBUFFERSIZE 10000

PDFWriter::PDFWriter(QObject *parent)
    : QObject(parent)
    , m_outputFile(NULL)
    , m_pdfObjectCount(0)
    , m_objectPagesID(0)
    , m_objectResourcesID(0)
    , m_objectImageID(0)
    , m_mediaboxWidth(5000.0)
    , m_mediaboxHeight(5000.0)
{
    m_pageContent[0] = '\0';
}

void PDFWriter::addOffsetToXref()
{
    char xrefLine[25];
    m_pdfObjectCount++;
    sprintf(xrefLine, "%.10d %.5d n " LINEFEED, (int)ftell(m_outputFile), 0);
    strcat(m_xref, xrefLine);
}

int PDFWriter::addImageResourcesAndXObject()
{
    int err = 0;

    addOffsetToXref();
    m_objectResourcesID = m_pdfObjectCount;
    fprintf (
        m_outputFile,
        LINEFEED "%d 0 obj" LINEFEED
        "<</XObject %d 0 R" LINEFEED
        "/ProcSet [/PDF /Text /ImageC /ImageI /ImageB]" LINEFEED
        ">>" LINEFEED
        "endobj",
        m_pdfObjectCount, m_pdfObjectCount + 1
    );

    addOffsetToXref();
    fprintf (
        m_outputFile,
        LINEFEED "%d 0 obj" LINEFEED
        "<</Im1 %d 0 R" LINEFEED
        ">>" LINEFEED
        "endobj",
        m_pdfObjectCount, m_pdfObjectCount + 1
    );

    return err;
}

int PDFWriter::saveJpegImage(const QString &jpegFileName, const QSize &sizePixels, ColorTypes::eColorTypes colorType)
{
    int err = 0;

    err = addImageResourcesAndXObject();

    FILE *jpegFile = NULL;
    if (!err) {
        jpegFile = fopen(jpegFileName.toAscii(), "rb");
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
        addOffsetToXref();
        fprintf (
            m_outputFile,
            LINEFEED "%d 0 obj" LINEFEED
            "<</ColorSpace %s" LINEFEED
            "/Subtype /Image" LINEFEED
            "/Length %d" LINEFEED
            "/Width %d" LINEFEED
            "/Type /XObject" LINEFEED
            "/Height %d" LINEFEED
            "/BitsPerComponent 8" LINEFEED
            "/Filter /DCTDecode" LINEFEED
            ">>" LINEFEED
            "stream" LINEFEED,
            m_pdfObjectCount,
            colorType==ColorTypes::eColorTypeCMYK?"/DeviceCMYK":"/DeviceRGB ", // Leaving space after RGB for eventual manual patching to CMYK
            jpegFileSize, sizePixels.width(), sizePixels.height()
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
            LINEFEED "endstream" LINEFEED
            "endobj"
        );
    }

    if (buffer)
        delete[] buffer;

    fclose(jpegFile);

    return err;
}

int PDFWriter::saveImage(const QByteArray &imageData, const QSize &sizePixels, int bitPerPixel, ColorTypes::eColorTypes colorType, const QVector<QRgb> &colorTable)
{
    int err = 0;
    err = addImageResourcesAndXObject();

    const QByteArray imageDataCompressed = qCompress(imageData, 9);

    // qCompress adds 4 extra bytes before and after the compressed
    // results. In the prepended bytes, we have the original size
    // of the uncompressed data. We need to chop these bytes off
    // from both ends when inserting into the PDF document...
    const int compressedByteArrayPrependedBytes = 4;
    const int compressedByteArrayAppendedBytes = 4;

    char colorSpaceString[5000] = "";
    switch (colorType) {
    case ColorTypes::eColorTypeRGB:
        strcpy(colorSpaceString, "/DeviceRGB");
        break;
    case ColorTypes::eColorTypeGreyscale:
        strcpy(colorSpaceString, "/DeviceGray");
        break;
    case ColorTypes::eColorTypeCMYK:
        strcpy(colorSpaceString, "/DeviceCMYK");
        break;
    default:
        sprintf(colorSpaceString, "[/Indexed /DeviceRGB %d <", colorTable.count()-1); // -1, because PDF wants the highest index, not the number of entries
        foreach (const QRgb &paletteEntry, colorTable) {
            char rgbHex[20];
            sprintf(rgbHex, "%.2x%.2x%.2x", qRed(paletteEntry), qGreen(paletteEntry), qBlue(paletteEntry));
            strcat(colorSpaceString, rgbHex);
        }
        strcat(colorSpaceString, ">]");
    }
    addOffsetToXref();
    m_objectImageID = m_pdfObjectCount;
    fprintf (
        m_outputFile,
        LINEFEED "%d 0 obj" LINEFEED
        "<</ColorSpace %s" LINEFEED
        "/Subtype /Image" LINEFEED
        "/Length %d" LINEFEED
        "/Width %d" LINEFEED
        "/Type /XObject" LINEFEED
        "/Height %d" LINEFEED
        "/Filter /FlateDecode" LINEFEED
        "/BitsPerComponent %d" LINEFEED
        ">>" LINEFEED
        "stream" LINEFEED,
        m_pdfObjectCount, colorSpaceString,
        imageDataCompressed.size() - compressedByteArrayPrependedBytes - compressedByteArrayAppendedBytes,
        sizePixels.width(), sizePixels.height(),
        (
            colorType == ColorTypes::eColorTypePalette?bitPerPixel
            :colorType == ColorTypes::eColorTypeMonochrome?bitPerPixel
            :colorType == ColorTypes::eColorTypeGreyscale?bitPerPixel
            :colorType == ColorTypes::eColorTypeCMYK?(bitPerPixel/4)
            :(bitPerPixel/3)
        )
    );
    fwrite(
        imageDataCompressed.constData() + compressedByteArrayPrependedBytes,
        sizeof(char),
        imageDataCompressed.size() - compressedByteArrayPrependedBytes - compressedByteArrayAppendedBytes,
        m_outputFile
    );
    fprintf(
        m_outputFile,
        LINEFEED "endstream" LINEFEED
        "endobj"
    );

    return err;
}

int PDFWriter::startPage()
{
    int err = 0;
    m_pageContent[0] = '\0';

    addOffsetToXref();
    fprintf (
        m_outputFile,
        LINEFEED "%d 0 obj" LINEFEED
        "<</Group <</CS /DeviceRGB" LINEFEED
        "/I true" LINEFEED
        "/S /Transparency" LINEFEED
        ">>" LINEFEED
        "/Parent %d 0 R" LINEFEED
        "/MediaBox [0 0 %f %f]" LINEFEED
        "/Resources %d 0 R" LINEFEED
        "/Contents %d 0 R" LINEFEED
        "/Type /Page" LINEFEED
        ">>" LINEFEED
        "endobj",
        m_pdfObjectCount, m_objectPagesID, m_mediaboxWidth, m_mediaboxHeight, m_objectResourcesID, m_pdfObjectCount+1
    );

    return err;
}

int PDFWriter::finishPage()
{
    int err = 0;

    addOffsetToXref();
    fprintf (
        m_outputFile,
        LINEFEED "%d 0 obj" LINEFEED
        "<</Length %d" LINEFEED
        ">>" LINEFEED
        "stream" LINEFEED
        "%s" LINEFEED
        "endstream" LINEFEED
        "endobj",
        m_pdfObjectCount, (int)strlen(m_pageContent), m_pageContent
    );

    return err;
}

int PDFWriter::startSaving(const QString &fileName, int pages, double widthCm, double heightCm)
{
    int err = 0;

    m_mediaboxWidth = CM2PT(widthCm);
    m_mediaboxHeight = CM2PT(heightCm);

    m_outputFile = fopen(fileName.toAscii(), "wb");
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

         addOffsetToXref();
        fprintf (
            m_outputFile,
            LINEFEED "%d 0 obj" LINEFEED
            "<</Creator (PosteRazor)" LINEFEED
            "/Producer (PosteRazor.SourceForge.net)" LINEFEED
            "/CreationDate (D:%s)" LINEFEED
            ">>" LINEFEED
            "endobj",
            m_pdfObjectCount,
            dateStr
        );

        addOffsetToXref();
        fprintf (
            m_outputFile,
            LINEFEED "%d 0 obj" LINEFEED
            "<</Pages %d 0 R" LINEFEED
            "/Type /Catalog" LINEFEED
            ">>" LINEFEED
            "endobj",
            m_pdfObjectCount, m_pdfObjectCount+1
        );

        addOffsetToXref();
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
            LINEFEED "%d 0 obj" LINEFEED
            "<</MediaBox [0 0 %f %f]" LINEFEED
            "/Resources %d 0 R" LINEFEED
            "/Kids [%s]" LINEFEED
            "/Count %d" LINEFEED
            "/Type /Pages" LINEFEED
            ">>" LINEFEED
            "endobj",
            m_pdfObjectCount, 50.0, 50.0, m_pdfObjectCount + 1, kidsStr, pages
        );
        delete[] kidsStr;
    }
    return err;
}

int PDFWriter::finishSaving()
{
    int err = 0;

    const unsigned int startxref = ftell(m_outputFile);
    fprintf(m_outputFile, m_xref);

    fprintf (
        m_outputFile,
        "trailer" LINEFEED
        "<</Info 1 0 R" LINEFEED
        "/Root 2 0 R" LINEFEED
        "/Size %d" LINEFEED
        ">>" LINEFEED
        "startxref" LINEFEED
        "%d" LINEFEED
        "%%%%EOF" LINEFEED,
        m_pdfObjectCount + 1, startxref
    );

    if (m_xref)
        delete[] m_xref;
    fclose(m_outputFile);
    return err;
}

void PDFWriter::drawFilledRect(const QRectF&, const QBrush &brush) {}
QSizeF PDFWriter::getSize() const {return QSizeF();}

void PDFWriter::drawImage(const QRectF &rect)
{
    char imageCode[2048]="";

    sprintf (
        imageCode,
        "0 w" LINEFEED
        "q 0 0 %.4f %.4f re W* n" LINEFEED
        "q %.4f 0 0 %.4f %.4f %.4f cm" LINEFEED
        "  /Im1 Do Q" LINEFEED
        "Q "
        ,
        m_mediaboxWidth, m_mediaboxHeight,
        CM2PT(rect.width()), CM2PT(rect.height()), CM2PT(rect.x()), m_mediaboxHeight-CM2PT(rect.y())-CM2PT(rect.height())
    );

    strcat(m_pageContent, imageCode);
}
