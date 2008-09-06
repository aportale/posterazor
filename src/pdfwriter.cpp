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

#include "paintcanvasinterface.h"
#include "pdfwriter.h"
#include <QRectF>
#include <QBrush>
#include <QFile>
#include <QFileInfo>
#include <QDateTime>
#define LINEFEED "\x0A"
#define CM2PT(cm) ((cm) / 2.54 * 72)

// TODO: Qt-ify also the jpeg case.

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
}

void PDFWriter::addOffsetToXref()
{
    char xrefLine[25];
    m_pdfObjectCount++;
    m_outStream.flush();
    sprintf(xrefLine, "%.10d %.5d n " LINEFEED, (int)m_outStream.device()->size(), 0);
    m_xref.append(xrefLine);
}

int PDFWriter::addImageResourcesAndXObject()
{
    int err = 0;

    addOffsetToXref();
    m_objectResourcesID = m_pdfObjectCount;
    m_outStream << QString(
        LINEFEED "%1 0 obj" LINEFEED
        "<</XObject %2 0 R" LINEFEED
        "/ProcSet [/PDF /Text /ImageC /ImageI /ImageB]" LINEFEED
        ">>" LINEFEED
        "endobj")
        .arg(m_pdfObjectCount)
        .arg(m_pdfObjectCount + 1);

    addOffsetToXref();
    m_outStream << QString(
        LINEFEED "%1 0 obj" LINEFEED
        "<</Im1 %2 0 R" LINEFEED
        ">>" LINEFEED
        "endobj")
        .arg(m_pdfObjectCount)
        .arg(m_pdfObjectCount + 1);

    return err;
}

int PDFWriter::saveJpegImage(const QString &jpegFileName, const QSize &sizePixels, Types::ColorTypes colorType)
{
    int err = 0;
/*
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
            colorType==Types::ColorTypeCMYK?"/DeviceCMYK"
            :colorType==Types::ColorTypeRGB?"/DeviceRGB ":"/DeviceGray ", // Leaving space after RGB for eventual manual patching to CMYK
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
*/
    return err;
}

int PDFWriter::saveImage(const QByteArray &imageData, const QSize &sizePixels, int bitPerPixel, Types::ColorTypes colorType, const QVector<QRgb> &colorTable)
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

    QString colorSpaceString;
    switch (colorType) {
    case Types::ColorTypeRGB:
        colorSpaceString = "/DeviceRGB";
        break;
    case Types::ColorTypeGreyscale:
        colorSpaceString = "/DeviceGray";
        break;
    case Types::ColorTypeCMYK:
        colorSpaceString = "/DeviceCMYK";
        break;
    default:
        colorSpaceString = QString("[/Indexed /DeviceRGB %1 <").arg(colorTable.count()-1); // -1, because PDF wants the highest index, not the number of entries
        foreach (const QRgb &paletteEntry, colorTable) {
            QString rgbHex = QString("%1%2%3")
                .arg(qRed(paletteEntry), 2, 16)
                .arg(qGreen(paletteEntry), 2, 16)
                .arg(qBlue(paletteEntry), 2, 16);
            colorSpaceString.append(rgbHex);
        }
        colorSpaceString.append(">]");
    }

    const int bitsPerComponent =
        colorType == Types::ColorTypePalette?bitPerPixel
        :colorType == Types::ColorTypeMonochrome?bitPerPixel
        :colorType == Types::ColorTypeGreyscale?bitPerPixel
        :colorType == Types::ColorTypeCMYK?(bitPerPixel/4)
        :(bitPerPixel/3);
    addOffsetToXref();
    m_objectImageID = m_pdfObjectCount;
    m_outStream << QString(
        LINEFEED "%1 0 obj" LINEFEED
        "<</ColorSpace %2" LINEFEED
        "/Subtype /Image" LINEFEED
        "/Length %3" LINEFEED
        "/Width %4" LINEFEED
        "/Type /XObject" LINEFEED
        "/Height %5" LINEFEED
        "/Filter /FlateDecode" LINEFEED
        "/BitsPerComponent %6" LINEFEED
        ">>" LINEFEED
        "stream" LINEFEED)
        .arg(m_pdfObjectCount)
        .arg(colorSpaceString)
        .arg(imageDataCompressed.size() - compressedByteArrayPrependedBytes - compressedByteArrayAppendedBytes)
        .arg(sizePixels.width())
        .arg(sizePixels.height())
        .arg(bitsPerComponent);

    m_outStream.flush(); // Important to flush stream before writing to device

    m_outStream.device()->write(
        imageDataCompressed.constData() + compressedByteArrayPrependedBytes,
        imageDataCompressed.size() - compressedByteArrayPrependedBytes - compressedByteArrayAppendedBytes);

    m_outStream <<
        LINEFEED "endstream" LINEFEED
        "endobj";

    return err;
}

int PDFWriter::startPage()
{
    int err = 0;

    m_pageContent.clear();
    addOffsetToXref();
    m_outStream << QString(
        LINEFEED "%1 0 obj" LINEFEED
        "<</Group <</CS /DeviceRGB" LINEFEED
        "/I true" LINEFEED
        "/S /Transparency" LINEFEED
        ">>" LINEFEED
        "/Parent %2 0 R" LINEFEED
        "/MediaBox [0 0 %3 %4]" LINEFEED
        "/Resources %5 0 R" LINEFEED
        "/Contents %6 0 R" LINEFEED
        "/Type /Page" LINEFEED
        ">>" LINEFEED
        "endobj")
        .arg(m_pdfObjectCount)
        .arg(m_objectPagesID)
        .arg(m_mediaboxWidth, 0, 'f', 6)
        .arg(m_mediaboxHeight, 0, 'f', 6)
        .arg(m_objectResourcesID)
        .arg(m_pdfObjectCount+1);

    return err;
}

int PDFWriter::finishPage()
{
    int err = 0;

    addOffsetToXref();
    m_outStream << QString(
        LINEFEED "%1 0 obj" LINEFEED
        "<</Length %2" LINEFEED
        ">>" LINEFEED
        "stream" LINEFEED
        "%3" LINEFEED
        "endstream" LINEFEED
        "endobj")
        .arg(m_pdfObjectCount)
        .arg(m_pageContent.length())
        .arg(m_pageContent);

    return err;
}

int PDFWriter::startSaving(const QString &fileName, int pages, double widthCm, double heightCm)
{
    int err = 0;

    m_mediaboxWidth = CM2PT(widthCm);
    m_mediaboxHeight = CM2PT(heightCm);

    if (m_outputFile) {
        m_outputFile->close();
        delete m_outputFile;
    }
    m_outputFile = new QFile(fileName, this);
    if (!m_outputFile->open(QIODevice::WriteOnly))
        return 1;

    m_outStream.setDevice(m_outputFile);
    m_outStream << "%PDF-1.3" LINEFEED "%";

    addOffsetToXref();
    m_outStream << QString(
        LINEFEED "%1 0 obj" LINEFEED
        "<</Creator (PosteRazor)" LINEFEED
        "/Producer (PosteRazor.SourceForge.net)" LINEFEED
        "/CreationDate (D:%2)" LINEFEED
        ">>" LINEFEED
        "endobj")
        .arg(m_pdfObjectCount)
        .arg(QDateTime::currentDateTime().toString("yyyyMMddHHmmss"));

    addOffsetToXref();
    m_outStream << QString(
        LINEFEED "%1 0 obj" LINEFEED
        "<</Pages %2 0 R" LINEFEED
        "/Type /Catalog" LINEFEED
        ">>" LINEFEED
        "endobj")
        .arg(m_pdfObjectCount)
        .arg(m_pdfObjectCount+1);

    addOffsetToXref();
    m_objectPagesID = m_pdfObjectCount;
    QString kids;
    for (int i = 0; i < pages; i++)
        kids.append(QString("%1%2 0 R").arg(i != 0?" ":"").arg(i*2 + (m_pdfObjectCount) + 4));
    m_outStream << QString(
        LINEFEED "%1 0 obj" LINEFEED
        "<</MediaBox [0 0 %2 %3]" LINEFEED
        "/Resources %4 0 R" LINEFEED
        "/Kids [%5]" LINEFEED
        "/Count %6" LINEFEED
        "/Type /Pages" LINEFEED
        ">>" LINEFEED
        "endobj")
        .arg(m_pdfObjectCount)
        .arg(50.0, 0, 'f')
        .arg(50.0, 0, 'f')
        .arg(m_pdfObjectCount + 1)
        .arg(kids)
        .arg(pages);

    return err;
}

int PDFWriter::finishSaving()
{
    int err = 0;

    m_outStream.flush();
    const qint64 startxref = m_outStream.device()->size();
    m_outStream << m_xref << QString(
        "trailer" LINEFEED
        "<</Info 1 0 R" LINEFEED
        "/Root 2 0 R" LINEFEED
        "/Size %1" LINEFEED
        ">>" LINEFEED
        "startxref" LINEFEED
        "%2" LINEFEED
        "%%EOF" LINEFEED)
        .arg(m_pdfObjectCount + 1)
        .arg(startxref);

    m_xref.clear();
    return err;
}

void PDFWriter::drawFilledRect(const QRectF& rect, const QBrush &brush)
{
    Q_UNUSED(rect)
    Q_UNUSED(brush)
}

QSizeF PDFWriter::size() const
{
    return QSizeF();
}

void PDFWriter::drawImage(const QRectF &rect)
{
    const QString imageCode = QString(
        "0 w" LINEFEED
        "q 0 0 %1 %2 re W* n" LINEFEED
        "q %3 0 0 %4 %5 %6 cm" LINEFEED
        "  /Im1 Do Q" LINEFEED
        "Q ")
        .arg(m_mediaboxWidth, 0, 'f', 4)
        .arg(m_mediaboxHeight, 0, 'f', 4)
        .arg(CM2PT(rect.width()), 0, 'f', 4)
        .arg(CM2PT(rect.height()), 0, 'f', 4)
        .arg(CM2PT(rect.x()), 0, 'f', 4)
        .arg(m_mediaboxHeight-CM2PT(rect.y())-CM2PT(rect.height()), 0, 'f', 4);

    m_pageContent.append(imageCode);
}
