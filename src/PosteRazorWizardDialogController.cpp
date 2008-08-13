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

PosteRazorWizardDialogController::PosteRazorWizardDialogController(QObject *wizardDialog, QObject *parent)
	: QObject(parent)
	, m_wizardStep(ePosteRazorWizardStepInputImage)
	, m_imageWasLoaded(false)
{
	connect(this, SIGNAL(wizardStepChanged(int)), wizardDialog, SLOT(setWizardStep(int)));
	connect(this, SIGNAL(prevButtonEnabled(bool)), wizardDialog, SLOT(setPrevButtonEnabled(bool)));
	connect(this, SIGNAL(nextButtonEnabled(bool)), wizardDialog, SLOT(setNextButtonEnabled(bool)));
	connect(this, SIGNAL(previewStateChanged(const QString&)), wizardDialog, SLOT(setPreviewState(const QString&)));
	connect(wizardDialog, SIGNAL(imageLoaded()), SLOT(handleImageLoaded()));
	connect(wizardDialog, SIGNAL(prevButtonPressed()), SLOT(handlePrevButtonPressed()));
	connect(wizardDialog, SIGNAL(nextButtonPressed()), SLOT(handleNextButtonPressed()));

	updateDialogWizardStep();
}

void PosteRazorWizardDialogController::handleImageLoaded()
{
	m_imageWasLoaded = true;
	updateDialogWizardStep();
}

void PosteRazorWizardDialogController::handlePrevButtonPressed()
{
	m_wizardStep =
		m_wizardStep == ePosteRazorWizardStepSavePoster?ePosteRazorWizardStepPosterSize
		:m_wizardStep == ePosteRazorWizardStepPosterSize?ePosteRazorWizardStepOverlapping
		:m_wizardStep == ePosteRazorWizardStepOverlapping?ePosteRazorWizardStepPaperSize
		:/* m_wizardStep == ePosteRazorWizardStepPaperSize? */ePosteRazorWizardStepInputImage;

	updateDialogWizardStep();
}

void PosteRazorWizardDialogController::handleNextButtonPressed()
{
	m_wizardStep =
		m_wizardStep == ePosteRazorWizardStepInputImage?ePosteRazorWizardStepPaperSize
		:m_wizardStep == ePosteRazorWizardStepPaperSize?ePosteRazorWizardStepOverlapping
		:m_wizardStep == ePosteRazorWizardStepOverlapping?ePosteRazorWizardStepPosterSize
		:/* m_wizardStep == ePosteRazorWizardStepPosterSize? */ePosteRazorWizardStepSavePoster;

	updateDialogWizardStep();
}

void PosteRazorWizardDialogController::updateDialogWizardStep()
{
	emit wizardStepChanged(m_wizardStep);
	emit previewStateChanged(
		m_wizardStep == ePosteRazorWizardStepInputImage?QLatin1String("image")
		:m_wizardStep == ePosteRazorWizardStepOverlapping?QLatin1String("overlapping")
		:m_wizardStep == ePosteRazorWizardStepPaperSize?QLatin1String("paper")
		:m_wizardStep == ePosteRazorWizardStepPosterSize?QLatin1String("poster")
		:QLatin1String("poster")
	);
	emit prevButtonEnabled(m_wizardStep != ePosteRazorWizardStepInputImage);
	emit nextButtonEnabled(
		m_wizardStep != ePosteRazorWizardStepSavePoster
		&& m_imageWasLoaded
	);
}
