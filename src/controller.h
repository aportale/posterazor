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

#include "types.h"
#include <QObject>

QT_BEGIN_NAMESPACE
class QAction;
class QSettings;
class QTranslator;
QT_END_NAMESPACE

class PosteRazorCore;
class WizardController;

class Controller: public QObject
{
    Q_OBJECT

public:
    Controller(PosteRazorCore *posteRazorCore, QWidget *view, QObject *parent = 0);

    void updateDialog();
    void updatePreview();

public slots:
    void setUnitOfLength(Types::UnitsOfLength unit);
    void setPaperFormat(const QString &format);
    void setPaperOrientation(QPrinter::Orientation orientation);
    void setPaperBorderTop(qreal border);
    void setPaperBorderRight(qreal border);
    void setPaperBorderBottom(qreal border);
    void setPaperBorderLeft(qreal border);
    void setCustomPaperWidth(qreal width);
    void setCustomPaperHeight(qreal height);
    void setUseCustomPaperSize(bool useIt);
    void setOverlappingWidth(qreal width);
    void setOverlappingHeight(qreal height);
    void setOverlappingPosition(Qt::Alignment position);
    void setPosterWidthAbsolute(qreal width);
    void setPosterHeightAbsolute(qreal height);
    void setPosterWidthPages(qreal width);
    void setPosterHeightPages(qreal height);
    void setPosterSizePercentual(qreal percent);
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
    void openPosteRazorWebsite();
    void setImageLoadingAvailable(bool available);
    void setPosterSizeModeAvailable(Types::PosterSizeModes mode, bool available);

signals:
    void previewChanged() const;
    void imageFileNameChanged(const QString &fileName) const;
    void imageInfoChanged(int imageWidthInPixels, int imageHeightInPixels, qreal imageWidth,
        qreal imageHeight, Types::UnitsOfLength unitOfLength, qreal verticalDpi, qreal horizontalDpi,
        Types::ColorTypes colorType, int bitsPerPixel) const;

    /* Privately used signals */
    void setPaperFormatSignal(const QString &format);
    void setPaperOrientationSignal(QPrinter::Orientation orientation);
    void setPaperBorderTopSignal(qreal border);
    void setPaperBorderRightSignal(qreal border);
    void setPaperBorderBottomSignal(qreal border);
    void setPaperBorderLeftSignal(qreal border);
    void setCustomPaperSizeSignal(const QSizeF &size);
    void setUseCustomPaperSizeSignal(bool useIt);
    void setOverlappingWidthSignal(qreal width);
    void setOverlappingHeightSignal(qreal height);
    void setOverlappingPositionSignal(Qt::Alignment position);
    void setPosterWidthAbsoluteSignal(qreal width);
    void setPosterHeightAbsoluteSignal(qreal height);
    void setPosterWidthPagesSignal(qreal width);
    void setPosterHeightPagesSignal(qreal height);
    void setPosterSizePercentualSignal(qreal percent);
    void setPosterSizeModeSignal(Types::PosterSizeModes mode);
    void setPosterAlignmentSignal(Qt::Alignment alignment);
    void setLaunchPDFApplicationSignal(bool launch);
    void updatePreviewSignal();
    void showImageFileNameSignal(const QString &fileName);
    void updateImageInfoFieldsSignal(const QSize &inputImageSizeInPixels, const QSizeF &imageSize, qreal verticalDpi, qreal horizontalDpi, Types::ColorTypes colorType, int bitsPerPixel);
    void setCurrentTranslationSignal(const QString &translation);
    void addAboutDialogActionSignal(QAction *action);
    void readSettingsSignal(const QSettings *settings);
    void writeSettingsSignal(QSettings *settings) const;
    void setCurrentUnitOfLengthSignal(const QString &unit);
    void setPosterSavingEnabledSignal(bool enabled);
    void setPosterSizeModeAvailableSignal(Types::PosterSizeModes mode, bool available);

private slots:
    void showExtraAboutDialog();
    void imageSuffixSupported(const QString &suffix, bool &outIsSupported) const;

protected:
    PosteRazorCore *m_posteRazorCore;
    QWidget *m_view;
    bool m_launchPDFApplication;
    WizardController *m_wizardController;
    QTranslator *m_translator;
    QString m_translationName;

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
