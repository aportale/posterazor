/*
    PosteRazor - Make your own poster!
    Copyright (C) 2005-2018 by Alessandro Portale
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

#pragma once

#include "imageloaderinterface.h"
#include <QObject>

class ImageLoaderQt: public QObject, public ImageLoaderInterface
{
public:
    ImageLoaderQt(QObject *parent = nullptr);

    bool loadInputImage(const QString &imageFileName, QString &errorMessage) override;
    bool isImageLoaded() const override;
    bool isJpeg() const override;
    QString fileName() const override;
    QSize sizePixels() const override;
    qreal horizontalDotsPerUnitOfLength(Types::UnitsOfLength unit) const override;
    qreal verticalDotsPerUnitOfLength(Types::UnitsOfLength unit) const override;
    QSizeF size(Types::UnitsOfLength unit) const override;
    const QImage imageAsRGB(const QSize &size) const override;
    int bitsPerPixel() const override;
    Types::ColorTypes colorDataType() const override;
    int savePoster(const QString &fileName, const PainterInterface *painter, int pagesCount, const QSizeF &sizeCm) const;
    const QByteArray bits() const override;
    const QVector<QRgb> colorTable() const override;
    const QVector<QPair<QStringList, QString> > &imageFormats() const override;
    QString libraryName() const override;
    QString libraryAboutText() const override;

    void setQImage(const QImage &image);

private:
#ifdef POPPLER_QT5_LIB
    bool loadPdf(const QString &imageFileName, QString &errorMessage);
#endif

    QImage m_image;
    QString m_imageFileName;
};
