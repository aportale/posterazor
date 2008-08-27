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

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QSettings>
#include "types.h"

class PosteRazorCore;
class MainWindow;
class QTranslator;

class Controller: public QObject
{
    Q_OBJECT

public:
    Controller(PosteRazorCore *posteRazorCore, MainWindow *mainWindow, QObject *parent = 0);

    void updateDialog();
    void updatePreview();

public slots:
    void setUnitOfLength(Types::UnitsOfLength unit);
    void setPaperFormat(const QString &format);
    void setPaperOrientation(QPrinter::Orientation orientation);
    void setPaperBorderTop(double border);
    void setPaperBorderRight(double border);
    void setPaperBorderBottom(double border);
    void setPaperBorderLeft(double border);
    void setCustomPaperWidth(double width);
    void setCustomPaperHeight(double height);
    void setUseCustomPaperSize(bool useIt);
    void setOverlappingWidth(double width);
    void setOverlappingHeight(double height);
    void setOverlappingPosition(Qt::Alignment position);
    void setPosterWidthAbsolute(double width);
    void setPosterHeightAbsolute(double height);
    void setPosterWidthPages(double width);
    void setPosterHeightPages(double height);
    void setPosterSizePercentual(double percent);
    void setPosterSizeMode(Types::PosterSizeModes mode);
    void setPosterAlignment(Qt::Alignment alignment);
    void setLaunchPDFApplication(bool launch);
    void readSettings(const QSettings *settings);
    void writeSettings(QSettings *settings) const;
    void loadInputImage();
    bool loadInputImage(const QString &fileName);
    bool loadInputImage(const QString &fileName, QString &errorMessage);
    int savePoster(const QString &fileName) const;
    void savePoster() const;
    void loadTranslation(const QString &localeName);
    void setUnitOfLength(const QString &unit);

signals:
    virtual void previewChanged() const;
    virtual void imageFileNameChanged(const QString &fileName) const;
    virtual void imageInfoChanged(int imageWidthInPixels, int imageHeightInPixels, double imageWidth,
        double imageHeight, Types::UnitsOfLength unitOfLength, double verticalDpi, double horizontalDpi,
        Types::ColorTypes colorType, int bitsPerPixel) const;
    virtual void pddfLaunch(const QString &pdfFileName) const;

protected:
    PosteRazorCore *m_posteRazorCore;
    MainWindow *m_mainWindow;
    bool m_launchPDFApplication;
    QTranslator *m_translator;

    void setDialogSaveOptions();
    void setDialogPosterSizeMode();
    void setDialogPosterOptions();
    void setDialogPosterDimensions(Types::PosterSizeModes excludedMode, bool widthExcluded);
    void setDialogPaperOptions();
    void setDialogPaperBorders();
    void setDialogCustomPaperDimensions();
    void setDialogImageInfoFields();
    void setDialogOverlappingDimensions();
    void setDialogOverlappingOptions();
};

#endif // CONTROLLER_H
