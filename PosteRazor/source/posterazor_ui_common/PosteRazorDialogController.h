#ifndef POSTERAZORDIALOGCONTROLLER_H
#define POSTERAZORDIALOGCONTROLLER_H

#include "PosteRazor.h"

class PosteRazorDialogInterface: public PosteRazorSettersInterface
{
public:
	virtual void updatePreview(void) = 0;
	virtual void updateImageInfoFields(int imageWidthInPixels, int imageHeightInPixels, double imageWidth, double imageHeight, UnitsOfLength::eUnitsOfLength unitOfLength, double verticalDpi, double horizontalDpi, ColorTypes::eColorTypes colorType, int bitsPerPixel) = 0;
};

class PosteRazorDialogController: public PosteRazorSettersInterface, public PosteRazorActionsInterface
{
public:
	virtual void setPosteRazorModel(PosteRazor *model) = 0;
	virtual void updateDialog(void) = 0;
	virtual void setPosteRazorDialog(PosteRazorDialogInterface *dialog) = 0;
	virtual void setPaperFormatByName(const char *name) = 0;
	virtual ~PosteRazorDialogController() {};
	static PosteRazorDialogController* createPosteRazorDialogController();
};

#endif
