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
	if (m_wizardStep == PosteRazorWizardDialogEnums::ePosteRazorWizardStepSavePoster)
		m_wizardStep = PosteRazorWizardDialogEnums::ePosteRazorWizardStepPosterSize;
	else if (m_wizardStep == PosteRazorWizardDialogEnums::ePosteRazorWizardStepPosterSize)
		m_wizardStep = PosteRazorWizardDialogEnums::ePosteRazorWizardStepOverlapping;
	else if (m_wizardStep == PosteRazorWizardDialogEnums::ePosteRazorWizardStepOverlapping)
		m_wizardStep = PosteRazorWizardDialogEnums::ePosteRazorWizardStepPaperSize;
	else if (m_wizardStep == PosteRazorWizardDialogEnums::ePosteRazorWizardStepPaperSize)
		m_wizardStep = PosteRazorWizardDialogEnums::ePosteRazorWizardStepInputImage;

	updateDialogWizardStep();
}

void PosteRazorWizardDialogController::handleNextButtonPressed(void)
{
	if (m_wizardStep == PosteRazorWizardDialogEnums::ePosteRazorWizardStepInputImage)
		m_wizardStep = PosteRazorWizardDialogEnums::ePosteRazorWizardStepPaperSize;
	else if (m_wizardStep == PosteRazorWizardDialogEnums::ePosteRazorWizardStepPaperSize)
		m_wizardStep = PosteRazorWizardDialogEnums::ePosteRazorWizardStepOverlapping;
	else if (m_wizardStep == PosteRazorWizardDialogEnums::ePosteRazorWizardStepOverlapping)
		m_wizardStep = PosteRazorWizardDialogEnums::ePosteRazorWizardStepPosterSize;
	else if (m_wizardStep == PosteRazorWizardDialogEnums::ePosteRazorWizardStepPosterSize)
		m_wizardStep = PosteRazorWizardDialogEnums::ePosteRazorWizardStepSavePoster;

	updateDialogWizardStep();
}

void PosteRazorWizardDialogController::updateDialog(void)
{
	updateDialogWizardStep();
}

void PosteRazorWizardDialogController::updateDialogWizardStep(void)
{
	m_WizardDialog->setWizardStep(m_wizardStep);
	m_WizardDialog->setPrevButtonEnabled(m_wizardStep != PosteRazorWizardDialogEnums::ePosteRazorWizardStepInputImage);
	m_WizardDialog->setNextButtonEnabled
	(
		m_wizardStep != PosteRazorWizardDialogEnums::ePosteRazorWizardStepSavePoster
		&& m_PosteRazor->getIsImageLoaded()
	);
}
