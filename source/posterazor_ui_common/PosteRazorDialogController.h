#ifndef POSTERAZORDIALOGCONTROLLER_H
#define POSTERAZORDIALOGCONTROLLER_H

#include "PosteRazor.h"

class PosteRazorDialogInterface: public PosteRazorSettersInterface
{
public:
	virtual void updatePreview(void) = 0;
	virtual void showImageFileName(const char *fileName) = 0;
	virtual void updateImageInfoFields(int imageWidthInPixels, int imageHeightInPixels, double imageWidth, double imageHeight, UnitsOfLength::eUnitsOfLength unitOfLength, double verticalDpi, double horizontalDpi, ColorTypes::eColorTypes colorType, int bitsPerPixel) = 0;
	virtual ~PosteRazorDialogInterface() {};
};

class PosteRazorDialogController: public PosteRazorSettersInterface, public PosteRazorActionsInterface
{
public:
	PosteRazorDialogController();
	virtual ~PosteRazorDialogController() {};

	void setPosteRazorModel(PosteRazor *model);
	void updateDialog(void);
	void setPosteRazorDialog(PosteRazorDialogInterface *dialog);
	void setPaperFormatByName(const char *name);

	void updatePreview(void);
	void setUnitOfLength(UnitsOfLength::eUnitsOfLength unit);
	void setPaperFormat(PaperFormats::ePaperFormats format);
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
	void setPosterWidth(PosteRazorEnums::ePosterSizeModes mode, double width);
	void setPosterHeight(PosteRazorEnums::ePosterSizeModes mode, double height);
	void setPosterSizeMode(PosteRazorEnums::ePosterSizeModes mode);
	void setPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignments alignment);
	void setPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignments alignment);
	void setPosterOutputFormat(ImageIOTypes::eImageFormats format);
	void setLaunchPDFApplication(bool launch);
	bool readPersistentPreferences(PersistentPreferencesInterface *preferences);
	bool writePersistentPreferences(PersistentPreferencesInterface *preferences) const;
	bool loadInputImage(const char *imageFileName, char *errorMessage, int errorMessageSize);
	int savePoster(const char *fileName) const;

protected:
	PosteRazor *m_PosteRazor;
	PosteRazorDialogInterface *m_Dialog;

	void SetDialogSaveOptions(void);
	void SetDialogPosterSizeMode(void);
	void SetDialogPosterOptions(void);
	void SetDialogPosterDimensions(PosteRazorEnums::ePosterSizeModes excludedMode, bool widthExcluded);
	void SetDialogPaperOptions(void);
	void SetDialogPaperBorders(void);
	void SetDialogCustomPaperDimensions(void);
	void SetDialogImageInfoFields(void);
	void SetDialogOverlappingDimensions(void);
	void SetDialogOverlappingOptions(void);
};

#endif
