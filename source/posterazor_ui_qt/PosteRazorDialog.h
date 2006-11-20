#ifndef POSTERAZORDIALOG_H
#define POSTERAZORDIALOG_H

#include <QDialog>
#include "ui_PosteRazorDialog.h"
#include "PosteRazorDialogController.h"

class PosteRazorDialog : public QDialog, private Ui::PosteRazorDialogUI, public PosteRazorDialogInterface
{
	Q_OBJECT

public:
	PosteRazorDialog::PosteRazorDialog(QWidget *parent = 0, Qt::WFlags flags = 0);

	virtual void SetUnitOfLength(UnitsOfLength::eUnitsOfLength unit);

	virtual void SetPaperFormat(PaperFormats::ePaperFormats format);
	virtual void SetPaperOrientation(PaperFormats::ePaperOrientations orientation);

	virtual void SetPaperBorderTop(double border);
	virtual void SetPaperBorderRight(double border);
	virtual void SetPaperBorderBottom(double border);
	virtual void SetPaperBorderLeft(double border);

	virtual void SetCustomPaperWidth(double width);
	virtual void SetCustomPaperHeight(double height);
	virtual void SetUseCustomPaperSize(bool useIt);

	virtual void SetOverlappingWidth(double width);
	virtual void SetOverlappingHeight(double height);
	virtual void SetOverlappingPosition(PosteRazorEnums::eOverlappingPositions position);

	virtual void SetPosterWidth(PosteRazorEnums::ePosterSizeModes mode, double width);
	virtual void SetPosterHeight(PosteRazorEnums::ePosterSizeModes mode, double height);
	virtual void SetPosterSizeMode(PosteRazorEnums::ePosterSizeModes mode);
	virtual void SetPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignments alignment);
	virtual void SetPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignments alignment);

	virtual void SetPosterOutputFormat(ImageIOTypes::eImageFormats format);
	virtual void SetLaunchPDFApplication(bool launch);

	virtual void UpdatePreview(void);
	virtual void UpdateImageInfoFields(int imageWidthInPixels, int imageHeightInPixels, double imageWidth, double imageHeight, UnitsOfLength::eUnitsOfLength unitOfLength, double verticalDpi, double horizontalDpi, ColorTypes::eColorTypes colorType, int bitsPerPixel);

private:
	PosteRazor *m_posteRazor;
	PosteRazorDialogController *m_posteRazorController;

	void createConnections(void);
	void createPosteRazorDialogController(void);
	void populateUI(void);

private slots:
	void handleNextButtonClicked(void);
	void handlePrevButtonClicked(void);
	void handlePaperFormatComboBoxActivated(int index);
	void handleImageLoadButtonClicked(void);

	void updatePosterSizeGroupsState(void);
	void loadInputImage(const QString &fileName);
};

#endif
