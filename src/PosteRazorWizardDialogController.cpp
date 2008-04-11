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
