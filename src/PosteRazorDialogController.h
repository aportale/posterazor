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

#ifndef POSTERAZORDIALOGCONTROLLER_H
#define POSTERAZORDIALOGCONTROLLER_H

#include "PosteRazor.h"

class PosteRazorDialogInterface: public PosteRazorSettersInterface
{
public:
	virtual ~PosteRazorDialogInterface() {}

	virtual void updatePreview(void) = 0;
	virtual void showImageFileName(const char *fileName) = 0;
	virtual void updateImageInfoFields(int imageWidthInPixels, int imageHeightInPixels, double imageWidth, double imageHeight, UnitsOfLength::eUnitsOfLength unitOfLength, double verticalDpi, double horizontalDpi, ColorTypes::eColorTypes colorType, int bitsPerPixel) = 0;
	virtual void setLaunchPDFApplication(bool launch) = 0;
	virtual void launchPdfApplication(const char *pdfFileName) const = 0;
};

class PosteRazorDialogController: public PosteRazorSettersInterface, public PosteRazorActionsInterface
{
public:
	PosteRazorDialogController();
	virtual ~PosteRazorDialogController() {}

	void setPosteRazorModel(PosteRazor *model);
	virtual void updateDialog(void);
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
	bool m_launchPDFApplication;

	void setDialogSaveOptions(void);
	void setDialogPosterSizeMode(void);
	void setDialogPosterOptions(void);
	void setDialogPosterDimensions(PosteRazorEnums::ePosterSizeModes excludedMode, bool widthExcluded);
	void setDialogPaperOptions(void);
	void setDialogPaperBorders(void);
	void setDialogCustomPaperDimensions(void);
	void setDialogImageInfoFields(void);
	void setDialogOverlappingDimensions(void);
	void setDialogOverlappingOptions(void);
};

#endif // POSTERAZORDIALOGCONTROLLER_H
