#ifndef POSTERAZORDIALOGCONTROLLER_H
#define POSTERAZORDIALOGCONTROLLER_H

#include "PosteRazor.h"

class PosteRazorDialogInterface: public PosteRazorSettersInterface
{
public:
	virtual void UpdatePreview(void) = 0;
	virtual void UpdateImageInfoFields(int imageWidthInPixels, int imageHeightInPixels, double imageWidth, double imageHeight, UnitsOfLength::eUnitsOfLength unitOfLength, double verticalDpi, double horizontalDpi, ColorTypes::eColorTypes colorType, int bitsPerPixel) = 0;
};

class PosteRazorDialogController: public PosteRazorSettersInterface, public PosteRazorActionsInterface
{
public:
	virtual void SetPosteRazorModel(PosteRazor *model) = 0;
	virtual void UpdateDialog(void) = 0;
	virtual void SetPosteRazorDialog(PosteRazorDialogInterface *dialog) = 0;
	virtual void SetPaperFormatByName(const char *name) = 0;
	virtual ~PosteRazorDialogController() {};
	static PosteRazorDialogController* CreatePosteRazorDialogController();
};

#endif
