/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005 by Alessandro Portale
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
#include "PosteRazor.h"
#include "PosteRazorDialogUI.h"

class PosteRazorDragDropWidget : public Fl_Box
{
public:
	PosteRazorDragDropWidget(int x, int y, int w, int h, const char *label = 0);
	int handle(int event);
};

typedef struct
{
	enum PosteRazor::eDistanceUnits distanceUnit;
	enum Fl_Paint_Canvas_Group::ePaintCanvasTypes previewType;
} posteRazorSettings;

class SettingsChangementHandler
{
public:
	virtual void HandleOptionsChangement(posteRazorSettings *settings) = 0;
};

class PosteRazorDialog : public PosteRazorDialogUI, public SettingsChangementHandler
{
private:
	PosteRazor    *m_posteRazor;
	PosteRazorDragDropWidget *m_dragDropWidget;
	Fl_Menu_Item  *m_paperFormatMenuItems;
	posteRazorSettings m_settings;
	class PosteRazorSettingsDialog *m_settingsDialog;

public:
	~PosteRazorDialog();
	PosteRazorDialog();

	int handle(int event);

	void OpenSettingsDialog(void);
	void HandleOptionsChangement(posteRazorSettings *settings);
	void next(void);
	void prev(void);
	void UpdateNavigationButtons(void);
	void OpenHelpDialog(void);
	const char* GetCurrentWizardStepStepInfoString(void);
	int GetCurrentWizardStepNumber(void);
	void UpdateStepInfoBar(void);
	void UpdatePreviewState(void);
	void UpdateDimensionUnitLabels(void);

	void LoadInputImage(const char *fileName);
	void UpdateImageInfoFields(void);

	void SetPaperSizeFields(void);
	static void HandlePaperFormatChoice_cb(Fl_Widget *widget, void *userData);
	void HandlePaperSizeChangement(Fl_Widget *sourceWidget);

	void SetOverlappingFields(void);
	void HandleOverlappingChangement(Fl_Widget *sourceWidget);

	void UpdatePosterSizeFields(Fl_Valuator *sourceWidget);
	void UpdatePosterSizeGroupsState(void);
	void SetPosterImageAlignmentButtons(void);
	void HandlePosterImageAlignment(void);

	void SavePoster(void);
	void SetLaunchPDFApplication(void);
};

#endif