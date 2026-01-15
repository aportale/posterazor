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

#include "ui_wizard.h"
#include "types.h"

class Wizard : public QWidget, private Ui::Wizard
{
    Q_OBJECT

public:
    Wizard(QWidget *parent = nullptr);

    void changeEvent(QEvent *event) override;

public slots:
    void retranslateUi();
    void retranslateUiWithDimensionUnit();
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
    void setPosterSizeModeAvailable(Types::PosterSizeModes mode, bool available);
    void setPosterAlignment(Qt::Alignment alignment);
    void setLaunchPDFApplication(bool launch);
    void updatePreview();
    void showImageFileName(const QString &fileName);
    void updateImageInfoFields(const QSize &inputImageSizeInPixels, const QSizeF &imageSize, qreal verticalDpi, qreal horizontalDpi, Types::ColorTypes colorType, int bitsPerPixel);
    void setCurrentUnitOfLength(const QString &unit);
    void setPreviewImage(const QImage &image);
    void setPrevButtonEnabled(bool enabled);
    void setNextButtonEnabled(bool enabled);
    void setPosterSavingEnabled(bool enabled);
    void setWizardStep(int step);
    void setWizardStepDescription(const QString &number, const QString &description);
    void setPreviewState(const QString &state);
    void showWizardStepHelp(const QString &title, const QString &text);

private:
    QString m_currentUnitOfLength;
    // TODO: Find out if QButtonGroup is better than the following two hashes
    QHash<Qt::Alignment, QAbstractButton*> m_overlappingButtons;
    QHash<Qt::Alignment, QAbstractButton*> m_alignmentButtons;

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
    void savePosterSignal() const;
    void loadImageSignal() const;
    void needsPaint(PaintCanvasInterface *paintDevice, const QVariant &options) const;
    void imageLoaded() const;

private slots:
    void handlePaperFormatTabChanged(int index);
    void handlePaperOrientationPortraitSelected();
    void handlePaperOrientationLandscapeSelected();
    void emitOverlappingPositionChange(int alignmentInt) const;
    void emitPosterAlignmentChange(int alignmentInt) const;
    void updatePosterSizeGroupsState();
};
