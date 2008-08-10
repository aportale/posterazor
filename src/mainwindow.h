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

	virtual void setUnitOfLength(UnitsOfLength::eUnitsOfLength unit);

	virtual void setPaperFormat(const QString &format);
	virtual void setPaperOrientation(PaperFormats::ePaperOrientations orientation);

	virtual void setPaperBorderTop(double border);
	virtual void setPaperBorderRight(double border);
	virtual void setPaperBorderBottom(double border);
	virtual void setPaperBorderLeft(double border);

	virtual void setCustomPaperWidth(double width);
	virtual void setCustomPaperHeight(double height);
	virtual void setUseCustomPaperSize(bool useIt);

	virtual void setOverlappingWidth(double width);
	virtual void setOverlappingHeight(double height);
	virtual void setOverlappingPosition(PosteRazorEnums::eOverlappingPositions position);

	virtual void setPosterWidth(PosteRazorEnums::ePosterSizeModes mode, double width);
	virtual void setPosterHeight(PosteRazorEnums::ePosterSizeModes mode, double height);
	virtual void setPosterSizeMode(PosteRazorEnums::ePosterSizeModes mode);
	virtual void setPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignments alignment);
	virtual void setPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignments alignment);

	virtual void setPosterOutputFormat(ImageIOTypes::eImageFormats format);
	virtual void setLaunchPDFApplication(bool launch);

	virtual void updatePreview(void);
	virtual void showImageFileName(const char *fileName);
	virtual void updateImageInfoFields(int imageWidthInPixels, int imageHeightInPixels, double imageWidth, double imageHeight, UnitsOfLength::eUnitsOfLength unitOfLength, double verticalDpi, double horizontalDpi, ColorTypes::eColorTypes colorType, int bitsPerPixel);
	virtual void launchPdfApplication(const char *pdfFileName) const;

	void setPrevButtonEnabled(bool enabled);
	void setNextButtonEnabled(bool enabled);
	void setWizardStep(int step);
	void setPreviewState(const char *state);

public slots:
	void setPreviewImage(const unsigned char* rgbData, const QSize &size);

private:
	PosteRazor *m_posteRazor;

	void createConnections(void);
	void populateUI(void);

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
	void overlappingPositionChanged(PosteRazorEnums::eHorizontalAlignments, PosteRazorEnums::eVerticalAlignments);
	void posterWidthAbsoluteChanged(double width);
	void posterHeightAbsoluteChanged(double height);
	void posterWidthPagesChanged(double width);
	void posterHeightPagesChanged(double height);
	void posterSizePercentualChanged(double percent);
	void posterAlignmentChanged(PosteRazorEnums::eHorizontalAlignments, PosteRazorEnums::eVerticalAlignments);
	void savePosterSelected(void);
	void launchPDFApplicationChanged(bool launch);
	void nextButtonClicked(void);
	void prevButtonClicked(void);
	void savePosterSignal(void);
	void loadImageSignal(void);
	void needsPaint(PaintCanvasInterface *paintDevice, const QVariant &options) const;

private slots:
	void handlePaperFormatTabChanged(int index);
	void handlePaperOrientationPortraitSelected(void);
	void handlePaperOrientationLandscapeSelected(void);

	void handleOverlappingPositionTopLeftSelected(void);
	void handleOverlappingPositionTopRightSelected(void);
	void handleOverlappingPositionBottomRightSelected(void);
	void handleOverlappingPositionBottomLeftSelected(void);

	void handlePosterHorizontalAlignmentLeftSelected(void);
	void handlePosterHorizontalAlignmentCenterSelected(void);
	void handlePosterHorizontalAlignmentRightSelected(void);
	void handlePosterVerticalAlignmentTopSelected(void);
	void handlePosterVerticalAlignmentMiddleSelected(void);
	void handlePosterVerticalAlignmentBottomSelected(void);

	void updatePosterSizeGroupsState(void);
};

#endif // MAINWINDOW_H
