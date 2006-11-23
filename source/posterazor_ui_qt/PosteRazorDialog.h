#ifndef POSTERAZORDIALOG_H
#define POSTERAZORDIALOG_H

#include <QDialog>
#include "ui_PosteRazorDialog.h"
#include "PosteRazorDialogController.h"

class PosteRazorDialog : public QDialog, private Ui::PosteRazorDialogUI, public PosteRazorDialogInterface
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
	virtual void updateImageInfoFields(int imageWidthInPixels, int imageHeightInPixels, double imageWidth, double imageHeight, UnitsOfLength::eUnitsOfLength unitOfLength, double verticalDpi, double horizontalDpi, ColorTypes::eColorTypes colorType, int bitsPerPixel);

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

	void handlePosterWidthAbsoluteChanged(double width);
	void handlePosterHeightAbsoluteChanged(double height);
	void handlePosterWidthPagesChanged(double width);
	void handlePosterHeightPagesChanged(double height);

	void updatePosterSizeGroupsState(void);
	void loadInputImage(const QString &fileName);
};

#endif
