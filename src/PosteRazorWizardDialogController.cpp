/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2008 by Alessandro Portale
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

#include "PosteRazorWizardDialogController.h"

PosteRazorWizardDialogController::PosteRazorWizardDialogController()
	: m_WizardDialog(0)
	, m_wizardStep(PosteRazorWizardDialogEnums::ePosteRazorWizardStepInputImage)
{
}

void PosteRazorWizardDialogController::setPosteRazorWizardDialog(PosteRazorWizardDialogInterface *dialog)
{
	PosteRazorDialogController::setPosteRazorDialog(dialog);
	m_WizardDialog = dialog;
}

void PosteRazorWizardDialogController::handlePrevButtonPressed(void)
{
	m_wizardStep =
		m_wizardStep == PosteRazorWizardDialogEnums::ePosteRazorWizardStepSavePoster?PosteRazorWizardDialogEnums::ePosteRazorWizardStepPosterSize
		:m_wizardStep == PosteRazorWizardDialogEnums::ePosteRazorWizardStepPosterSize?PosteRazorWizardDialogEnums::ePosteRazorWizardStepOverlapping
		:m_wizardStep == PosteRazorWizardDialogEnums::ePosteRazorWizardStepOverlapping?PosteRazorWizardDialogEnums::ePosteRazorWizardStepPaperSize
		:/* m_wizardStep == PosteRazorWizardDialogEnums::ePosteRazorWizardStepPaperSize? */PosteRazorWizardDialogEnums::ePosteRazorWizardStepInputImage;

	updateDialogWizardStep();
}

void PosteRazorWizardDialogController::handleNextButtonPressed(void)
{
	m_wizardStep =
		m_wizardStep == PosteRazorWizardDialogEnums::ePosteRazorWizardStepInputImage?PosteRazorWizardDialogEnums::ePosteRazorWizardStepPaperSize
		:m_wizardStep == PosteRazorWizardDialogEnums::ePosteRazorWizardStepPaperSize?PosteRazorWizardDialogEnums::ePosteRazorWizardStepOverlapping
		:m_wizardStep == PosteRazorWizardDialogEnums::ePosteRazorWizardStepOverlapping?PosteRazorWizardDialogEnums::ePosteRazorWizardStepPosterSize
		:/* m_wizardStep == PosteRazorWizardDialogEnums::ePosteRazorWizardStepPosterSize? */PosteRazorWizardDialogEnums::ePosteRazorWizardStepSavePoster;

	updateDialogWizardStep();
}

void PosteRazorWizardDialogController::updateDialog(void)
{
	PosteRazorDialogController::updateDialog();
	updateDialogWizardStep();
}

void PosteRazorWizardDialogController::updateDialogWizardStep(void)
{
	m_WizardDialog->setWizardStep(m_wizardStep);
	m_WizardDialog->setPreviewState
	(
		m_wizardStep == PosteRazorWizardDialogEnums::ePosteRazorWizardStepInputImage?"image"
		:m_wizardStep == PosteRazorWizardDialogEnums::ePosteRazorWizardStepOverlapping?"overlapping"
		:m_wizardStep == PosteRazorWizardDialogEnums::ePosteRazorWizardStepPaperSize?"paper"
		:m_wizardStep == PosteRazorWizardDialogEnums::ePosteRazorWizardStepPosterSize?"poster"
		:/* m_wizardStep == PosteRazorWizardDialogEnums::ePosteRazorWizardStepSavePoster? */"poster"
	);
	m_WizardDialog->setPrevButtonEnabled(m_wizardStep != PosteRazorWizardDialogEnums::ePosteRazorWizardStepInputImage);
	m_WizardDialog->setNextButtonEnabled
	(
		m_wizardStep != PosteRazorWizardDialogEnums::ePosteRazorWizardStepSavePoster
		&& m_PosteRazor->getIsImageLoaded()
	);
}
