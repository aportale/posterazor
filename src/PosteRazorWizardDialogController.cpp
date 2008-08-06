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

#include "PosteRazorWizardDialogController.h"

PosteRazorWizardDialogController::PosteRazorWizardDialogController()
	: m_WizardDialog(0)
	, m_wizardStep(ePosteRazorWizardStepInputImage)
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
		m_wizardStep == ePosteRazorWizardStepSavePoster?ePosteRazorWizardStepPosterSize
		:m_wizardStep == ePosteRazorWizardStepPosterSize?ePosteRazorWizardStepOverlapping
		:m_wizardStep == ePosteRazorWizardStepOverlapping?ePosteRazorWizardStepPaperSize
		:/* m_wizardStep == ePosteRazorWizardStepPaperSize? */ePosteRazorWizardStepInputImage;

	updateDialogWizardStep();
}

void PosteRazorWizardDialogController::handleNextButtonPressed(void)
{
	m_wizardStep =
		m_wizardStep == ePosteRazorWizardStepInputImage?ePosteRazorWizardStepPaperSize
		:m_wizardStep == ePosteRazorWizardStepPaperSize?ePosteRazorWizardStepOverlapping
		:m_wizardStep == ePosteRazorWizardStepOverlapping?ePosteRazorWizardStepPosterSize
		:/* m_wizardStep == ePosteRazorWizardStepPosterSize? */ePosteRazorWizardStepSavePoster;

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
		m_wizardStep == ePosteRazorWizardStepInputImage?"image"
		:m_wizardStep == ePosteRazorWizardStepOverlapping?"overlapping"
		:m_wizardStep == ePosteRazorWizardStepPaperSize?"paper"
		:m_wizardStep == ePosteRazorWizardStepPosterSize?"poster"
		:/* m_wizardStep == ePosteRazorWizardStepSavePoster? */"poster"
	);
	m_WizardDialog->setPrevButtonEnabled(m_wizardStep != ePosteRazorWizardStepInputImage);
	m_WizardDialog->setNextButtonEnabled
	(
		m_wizardStep != ePosteRazorWizardStepSavePoster
		&& m_PosteRazor->getIsImageLoaded()
	);
}
