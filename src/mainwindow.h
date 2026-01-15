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

#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
class QSettings;
QT_END_NAMESPACE

class PosteRazorCore;

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void retranslateUi();
    void retranslateUiWithDimensionUnit();
    void changeEvent(QEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

public slots:
    void setPaperFormat(const QString &format);
    void setPaperOrientation(QPageLayout::Orientation orientation);
    void setPaperBorderTop(qreal border);
    void setPaperBorderRight(qreal border);
    void setPaperBorderBottom(qreal border);
    void setPaperBorderLeft(qreal border);
    void setCustomPaperSize(const QSizeF &size);
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
    void updatePreview();
    void showImageFileName(const QString &fileName);
    void updateImageInfoFields(const QSize &inputImageSizeInPixels, const QSizeF &imageSize, qreal verticalDpi, qreal horizontalDpi, Types::ColorTypes colorType, int bitsPerPixel);
    void setCurrentTranslation(const QString &translation); // Only to set the right menu entry to checked
    void setCurrentUnitOfLength(const QString &unit);
    void addAboutDialogAction(QAction *action);
    void readSettings(const QSettings *settings);
    void writeSettings(QSettings *settings) const;
    void setPreviewImage(const QImage &image);
    void setPrevButtonEnabled(bool enabled);
    void setNextButtonEnabled(bool enabled);
    void setPosterSavingEnabled(bool enabled);
    void setWizardStep(int step);
    void setWizardStepDescription(const QString &number, const QString &description);
    void setPreviewState(const QString &state);
    void showWizardStepHelp(const QString &title, const QString &text);
    void showManual(const QString &title, const QString &text);

private:
    PosteRazorCore *m_posteRazor = nullptr;
    QString m_currentUnitOfLength;
    QActionGroup *m_unitOfLengthActions = nullptr;
    QHash<QString, QAction*> m_translationActions;

    void createConnections();
    void populateUI();
#ifdef Q_OS_MACOS
    void applyMacOSStyling();
#endif

signals:
    void paperFormatChanged(const QString &format) const;
    void useCustomPaperSizeChanged(bool useIt) const;
    void paperOrientationChanged(QPageLayout::Orientation orientation) const;
    void paperCustomWidthChanged(qreal width) const;
    void paperCustomHeightChanged(qreal height) const;
    void paperBorderTopChanged(qreal border) const;
    void paperBorderRightChanged(qreal border) const;
    void paperBorderBottomChanged(qreal border) const;
    void paperBorderLeftChanged(qreal border) const;
    void overlappingWidthChanged(qreal width) const;
    void overlappingHeightChanged(qreal height) const;
    void overlappingPositionChanged(Qt::Alignment position) const;
    void posterWidthAbsoluteChanged(qreal width) const;
    void posterHeightAbsoluteChanged(qreal height) const;
    void posterWidthPagesChanged(qreal width) const;
    void posterHeightPagesChanged(qreal height) const;
    void posterSizePercentualChanged(qreal percent) const;
    void posterAlignmentChanged(Qt::Alignment alignment) const;
    void savePosterSelected() const;
    void launchPDFApplicationChanged(bool launch) const;
    void nextButtonPressed() const;
    void prevButtonPressed() const;
    void wizardStepHelpSignal() const;
    void manualSignal() const;
    void savePosterSignal() const;
    void loadImageSignal() const;
    void loadImageSignal(const QString &fileName) const;
    void needsPaint(PaintCanvasInterface *paintDevice, const QVariant &options) const;
    void imageLoaded() const;
    void translationChanged(const QString &localeName = QString()) const;
    void unitOfLengthChanged(const QString &unit) const;
    void openPosteRazorWebsiteSignal() const;
    void imageSuffixSupportedSignal(const QString &suffix, bool &outIsSupported) const;

private slots:
    void handleTranslationAction(QAction *action) const;
    void handleUnitOfLengthAction(QAction *action) const;
    void showAboutQtDialog() const;
    void showAboutPosteRazorDialog();
};
