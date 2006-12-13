#include "PosteRazorWizardDialogController.h"

PosteRazorWizardDialogController::PosteRazorWizardDialogController()
	: m_WizardDialog(0)
{
}

void PosteRazorWizardDialogController::setPosteRazorWizardDialog(PosteRazorWizardDialogInterface *dialog)
{
	PosteRazorDialogController::setPosteRazorDialog(dialog);
	m_WizardDialog = dialog;
}
