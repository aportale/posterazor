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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "UnitsOfLength.h"
#include "PaperFormats.h"
#include "PosteRazor.h"

class MainWindow : public QMainWindow, private Ui::MainWindow 
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainWindow();

	void setUnitOfLength(UnitsOfLength::eUnitsOfLength unit);

	void setPaperFormat(const QString &format);
	void setPaperOrientation(PaperFormats::ePaperOrientations orientation);

	void setPaperBorderTop(double border);
	void setPaperBorderRight(double border);
	void setPaperBorderBottom(double border);
	void setPaperBorderLeft(double border);

	void setCustomPaperWidth(double width);
	void setCustomPaperHeight(double height);
	void setUseCustomPaperSize(bool useIt);

	void setOverlappingWidth(double width);
	void setOverlappingHeight(double height);
	void setOverlappingPosition(PosteRazorEnums::eOverlappingPositions position);

	void setPosterWidthAbsolute(double width);
	void setPosterHeightAbsolute(double height);
	void setPosterWidthPages(double width);
	void setPosterHeightPages(double height);
	void setPosterSizePercentual(double percent);
	void setPosterSizeMode(PosteRazorEnums::ePosterSizeModes mode);
	void setPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignments alignment);
	void setPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignments alignment);

	void setPosterOutputFormat(ImageIOTypes::eImageFormats format);
	void setLaunchPDFApplication(bool launch);

	void updatePreview();
	void showImageFileName(const char *fileName);
	void updateImageInfoFields(int imageWidthInPixels, int imageHeightInPixels, double imageWidth, double imageHeight, UnitsOfLength::eUnitsOfLength unitOfLength, double verticalDpi, double horizontalDpi, ColorTypes::eColorTypes colorType, int bitsPerPixel);
	void launchPdfApplication(const char *pdfFileName) const;

public slots:
	void setPreviewImage(const unsigned char* rgbData, const QSize &size);
	void setPrevButtonEnabled(bool enabled);
	void setNextButtonEnabled(bool enabled);
	void setWizardStep(int step);
	void setPreviewState(const QString &state);

private:
	PosteRazor *m_posteRazor;

	void createConnections();
	void populateUI();

signals:
	void paperFormatChanged(const QString &format);
	void paperOrientationChanged(PaperFormats::ePaperOrientations orientation);
	void paperCustomWidthChanged(double width);
	void paperCustomHeightChanged(double height);
	void paperBorderTopChanged(double border);
	void paperBorderRightChanged(double border);
	void paperBorderBottomChanged(double border);
	void paperBorderLeftChanged(double border);
	void overlappingWidthChanged(double width);
	void overlappingHeightChanged(double height);
	void overlappingPositionChanged(PosteRazorEnums::eOverlappingPositions);
	void posterWidthAbsoluteChanged(double width);
	void posterHeightAbsoluteChanged(double height);
	void posterWidthPagesChanged(double width);
	void posterHeightPagesChanged(double height);
	void posterSizePercentualChanged(double percent);
	void posterAlignmentChanged(PosteRazorEnums::eHorizontalAlignments, PosteRazorEnums::eVerticalAlignments);
	void savePosterSelected();
	void launchPDFApplicationChanged(bool launch);
	void nextButtonPressed();
	void prevButtonPressed();
	void savePosterSignal();
	void loadImageSignal();
	void needsPaint(PaintCanvasInterface *paintDevice, const QVariant &options) const;
	void imageLoaded() const;

private slots:
	void handlePaperFormatTabChanged(int index);
	void handlePaperOrientationPortraitSelected();
	void handlePaperOrientationLandscapeSelected();

	void handleOverlappingPositionTopLeftSelected();
	void handleOverlappingPositionTopRightSelected();
	void handleOverlappingPositionBottomRightSelected();
	void handleOverlappingPositionBottomLeftSelected();

	void handlePosterHorizontalAlignmentLeftSelected();
	void handlePosterHorizontalAlignmentCenterSelected();
	void handlePosterHorizontalAlignmentRightSelected();
	void handlePosterVerticalAlignmentTopSelected();
	void handlePosterVerticalAlignmentMiddleSelected();
	void handlePosterVerticalAlignmentBottomSelected();

	void updatePosterSizeGroupsState();
};

#endif // MAINWINDOW_H
