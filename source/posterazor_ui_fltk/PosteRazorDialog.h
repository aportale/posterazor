/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2007 by Alessandro Portale
	http://posterazor.sourceforge.net/

	This file is part of PosteRazor

	PosteRazor is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
	
	PosteRazor is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with PosteRazor; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifndef PosteRazorDialog_h
#define PosteRazorDialog_h

#include <FL/Fl_Image.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Native_File_Chooser.H>
#include "PosteRazor.h"
#include "PosteRazorDialogUI.h"
#include "PosteRazorSettingsDialog.h"
#include "PosteRazorWizardDialogController.h"
#include "Translations.h"

class PosteRazorDragDropWidget : public Fl_Box
{
public:
	PosteRazorDragDropWidget(int x, int y, int w, int h, const char *label = 0);
	int handle(int event);
};

class PosteRazorDialog : public PosteRazorDialogUI, public SettingsChangementHandler, public PosteRazorWizardDialogInterface
{
private:
	PosteRazor                        *m_posteRazor;
	PosteRazorDragDropWidget          *m_dragDropWidget;
	Fl_Menu_Item                      *m_paperFormatMenuItems;
	posteRazorSettings                m_settings;
	PosteRazorSettingsDialog          *m_settingsDialog;
	class PosteRazorHelpDialogUI      *m_helpDialog;
	char                              m_loadImageChooserLastPath[1024];
	char                              m_savePosterChooserLastPath[1024];
	bool                              m_UILanguageIsUndefined;
	PosteRazorWizardDialogController  *m_posteRazorController;

public:
	PosteRazorDialog();
	~PosteRazorDialog();

	int handle(int event);

	bool getUseOpenGLForPreviewByDefault(void);
	void openSettingsDialog(void);
	void openHelpDialog(void);
	void handleOptionsChangement(posteRazorSettings *settings);
	void next(void);
	void prev(void);
	void updateNavigationButtons(void);
	const char* getWizardStepInfoString(PosteRazorWizardDialogEnums::ePosteRazorWizardSteps step);
	int getCurrentWizardStepNumber(void);
	void updateStepInfoBar(PosteRazorWizardDialogEnums::ePosteRazorWizardSteps step);
	void updatePreview(void);
	void updateLanguage(void);

	void loadInputImage(const char *fileName);
	void showImageFileName(const char *fileName);
	void updateImageInfoFields(int imageWidthInPixels, int imageHeightInPixels, double imageWidth, double imageHeight, UnitsOfLength::eUnitsOfLength unitOfLength, double verticalDpi, double horizontalDpi, ColorTypes::eColorTypes colorType, int bitsPerPixel);
	void updateImageInfoFields(void);

	static void handlePaperFormatChoice_cb(Fl_Widget *widget, void *userData);
	void handlePaperSizeChangement(Fl_Widget *sourceWidget);

	void handleOverlappingChangement(Fl_Widget *sourceWidget);

	void updatePosterSizeFields(Fl_Widget *sourceWidget);
	void updatePosterSizeGroupsState(void);
	void handlePosterImageAlignment(void);

	void savePoster(void);
	void setLaunchPDFApplication(void);

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

	void setPrevButtonEnabled(bool enabled);
	void setNextButtonEnabled(bool enabled);
	void setWizardStep(PosteRazorWizardDialogEnums::ePosteRazorWizardSteps step);
	void setPreviewState(const char *state);
};

#endif
