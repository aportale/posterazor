/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2006 by Alessandro Portale
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
#include "PosteRazorDialogController.h"
#include "Translations.h"

class PosteRazorDragDropWidget : public Fl_Box
{
public:
	PosteRazorDragDropWidget(int x, int y, int w, int h, const char *label = 0);
	int handle(int event);
};

class PosteRazorDialog : public PosteRazorDialogUI, public SettingsChangementHandler, public PosteRazorDialogInterface
{
private:
	PosteRazor                      *m_posteRazor;
	PosteRazorDragDropWidget        *m_dragDropWidget;
	Fl_Menu_Item                    *m_paperFormatMenuItems;
	posteRazorSettings              m_settings;
	PosteRazorSettingsDialog        *m_settingsDialog;
	class PosteRazorHelpDialogUI    *m_helpDialog;
	char                            m_loadImageChooserLastPath[1024];
	char                            m_savePosterChooserLastPath[1024];
	bool                            m_UILanguageIsUndefined;
	PosteRazorDialogController      *m_posteRazorController;

public:
	~PosteRazorDialog();
	PosteRazorDialog();

	int handle(int event);

	void OpenSettingsDialog(void);
	void OpenHelpDialog(void);
	void HandleOptionsChangement(posteRazorSettings *settings);
	void next(void);
	void prev(void);
	void UpdateNavigationButtons(void);
	const char* GetCurrentWizardStepStepInfoString(void);
	int GetCurrentWizardStepNumber(void);
	void UpdateStepInfoBar(void);
	void UpdatePreview(void);
	void UpdatePreviewState(void);
	void UpdateLanguage(void);

	void LoadInputImage(const char *fileName);
	void UpdateImageInfoFields(int imageWidthInPixels, int imageHeightInPixels, double imageWidth, double imageHeight, UnitsOfLength::eUnitsOfLength unitOfLength, double verticalDpi, double horizontalDpi, ColorTypes::eColorTypes colorType, int bitsPerPixel);
	void UpdateImageInfoFields(void);

	static void HandlePaperFormatChoice_cb(Fl_Widget *widget, void *userData);
	void HandlePaperSizeChangement(Fl_Widget *sourceWidget);

	void HandleOverlappingChangement(Fl_Widget *sourceWidget);

	void UpdatePosterSizeFields(Fl_Widget *sourceWidget);
	void UpdatePosterSizeGroupsState(void);
	void HandlePosterImageAlignment(void);

	void SavePoster(void);
	void SetLaunchPDFApplication(void);

	void SetUnitOfLength(UnitsOfLength::eUnitsOfLength unit);

	void SetPaperFormat(PaperFormats::ePaperFormats format);
	void SetPaperOrientation(PaperFormats::ePaperOrientations orientation);

	void SetPaperBorderTop(double border);
	void SetPaperBorderRight(double border);
	void SetPaperBorderBottom(double border);
	void SetPaperBorderLeft(double border);

	void SetCustomPaperWidth(double width);
	void SetCustomPaperHeight(double height);
	void SetUseCustomPaperSize(bool useIt);

	void SetOverlappingWidth(double width);
	void SetOverlappingHeight(double height);
	void SetOverlappingPosition(PosteRazorEnums::eOverlappingPositions position);

	void SetPosterWidth(PosteRazorEnums::ePosterSizeModes mode, double width);
	void SetPosterHeight(PosteRazorEnums::ePosterSizeModes mode, double height);
	void SetPosterSizeMode(PosteRazorEnums::ePosterSizeModes mode);
	void SetPosterHorizontalAlignment(PosteRazorEnums::eHorizontalAlignments alignment);
	void SetPosterVerticalAlignment(PosteRazorEnums::eVerticalAlignments alignment);

	void SetPosterOutputFormat(ImageIOTypes::eImageFormats format);
	void SetLaunchPDFApplication(bool launch);
};

#endif
