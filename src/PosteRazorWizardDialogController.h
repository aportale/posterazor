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

#ifndef POSTERAZORWIZARDDIALOGCONTROLLER_H
#define POSTERAZORWIZARDDIALOGCONTROLLER_H

#include "PosteRazorDialogController.h"

class PosteRazorWizardDialogEnums
{
public:
	enum ePosteRazorWizardSteps	{
		ePosteRazorWizardStepInputImage,
		ePosteRazorWizardStepPaperSize,
		ePosteRazorWizardStepOverlapping,
		ePosteRazorWizardStepPosterSize,
		ePosteRazorWizardStepSavePoster
	};
};

class PosteRazorWizardDialogInterface: public PosteRazorDialogInterface
{
public:
	virtual void setPrevButtonEnabled(bool enabled) = 0;
	virtual void setNextButtonEnabled(bool enabled) = 0;
	virtual void setWizardStep(PosteRazorWizardDialogEnums::ePosteRazorWizardSteps step) = 0;
	virtual void setPreviewState(const char *state) = 0;
};

class PosteRazorWizardDialogController: public PosteRazorDialogController
{
public:
	PosteRazorWizardDialogController();
	virtual ~PosteRazorWizardDialogController() {};
	void setPosteRazorWizardDialog(PosteRazorWizardDialogInterface *dialog);
	void handlePrevButtonPressed(void);
	void handleNextButtonPressed(void);
	void updateDialog(void);

private:
	PosteRazorWizardDialogInterface *m_WizardDialog;
	PosteRazorWizardDialogEnums::ePosteRazorWizardSteps m_wizardStep;
	void updateDialogWizardStep(void);
};

#endif
