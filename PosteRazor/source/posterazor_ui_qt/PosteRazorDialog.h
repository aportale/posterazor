#ifndef POSTERAZORDIALOG_H
#define POSTERAZORDIALOG_H

#include <QDialog>
#include "ui_PosteRazorDialog.h"
#include "PosteRazorWizardDialogController.h"

class PosteRazorDialog : public QDialog, private Ui::PosteRazorDialogUI, public PosteRazorWizardDialogInterface
{
	Q_OBJECT

public:
	PosteRazorDialog(QWidget *parent = 0, Qt::WFlags flags = 0);
	~PosteRazorDialog();

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

	void setPrevButtonEnabled(bool enabled);
	void setNextButtonEnabled(bool enabled);
	void setWizardStep(PosteRazorWizardDialogEnums::ePosteRazorWizardSteps step);
	void setPreviewState(const char *state);

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
	void handleLaunchPDFApplicationChanged(int state);

	void updatePosterSizeGroupsState(void);
	bool loadInputImage(const QString &fileName);
};

#endif
