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

#ifndef QTPOSTERAZORDIALOG_H
#define QTPOSTERAZORDIALOG_H

#include <QDialog>
#include "ui_QtPosteRazorDialog.h"
#include "PosteRazorWizardDialogController.h"

class QtPosteRazorDialog : public QDialog, private Ui::PosteRazorDialog, public PosteRazorWizardDialogInterface
{
	Q_OBJECT

public:
	QtPosteRazorDialog(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QtPosteRazorDialog();

	virtual void setUnitOfLength(UnitsOfLength::eUnitsOfLength unit);

	virtual void setPaperFormat(PaperFormats::ePaperFormats format);
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
	void setWizardStep(PosteRazorWizardDialogController::ePosteRazorWizardSteps step);
	void setPreviewState(const char *state);

public slots:
	bool loadInputImage(const QString &fileName);

private:
	PosteRazor *m_posteRazor;
	PosteRazorWizardDialogController *m_posteRazorController;

	void createConnections(void);
	void createPosteRazorDialogController(void);
	void populateUI(void);

private slots:
	void handleNextButtonClicked(void);
	void handlePrevButtonClicked(void);
	void handlePaperFormatComboBoxActivated(int index);
	void handleImageLoadButtonClicked(void);

	void handlePaperFormatTabChanged(int index);
	void handlePaperOrientationPortraitSelected(void);
	void handlePaperOrientationLandscapeSelected(void);
	void handlePaperCustomWidthChanged(double width);
	void handlePaperCustomHeightChanged(double height);
	void handlePaperBorderTopChanged(double border);
	void handlePaperBorderRightChanged(double border);
	void handlePaperBorderBottomChanged(double border);
	void handlePaperBorderLeftChanged(double border);

	void handleOverlappingWidthChanged(double width);
	void handleOverlappingHeightChanged(double height);
	void handleOverlappingPositionTopLeftSelected(void);
	void handleOverlappingPositionTopRightSelected(void);
	void handleOverlappingPositionBottomRightSelected(void);
	void handleOverlappingPositionBottomLeftSelected(void);

	void handlePosterWidthAbsoluteChanged(double width);
	void handlePosterHeightAbsoluteChanged(double height);
	void handlePosterWidthPagesChanged(double width);
	void handlePosterHeightPagesChanged(double height);
	void handlePosterSizePercentualChanged(double percent);

	void handlePosterHorizontalAlignmentLeftSelected(void);
	void handlePosterHorizontalAlignmentCenterSelected(void);
	void handlePosterHorizontalAlignmentRightSelected(void);
	void handlePosterVerticalAlignmentTopSelected(void);
	void handlePosterVerticalAlignmentMiddleSelected(void);
	void handlePosterVerticalAlignmentBottomSelected(void);

	void handleSavePosterButtonClicked(void);
	void handleLaunchPDFApplicationChanged(bool launch);

	void updatePosterSizeGroupsState(void);
};

#endif // QTPOSTERAZORDIALOG_H
