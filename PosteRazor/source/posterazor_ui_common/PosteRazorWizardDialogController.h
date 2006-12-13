#ifndef POSTERAZORWIZARDDIALOGCONTROLLER_H
#define POSTERAZORWIZARDDIALOGCONTROLLER_H

#include "PosteRazorDialogController.h"

class PosteRazorWizardDialogInterface: public PosteRazorDialogInterface
{
};

class PosteRazorWizardDialogController: public PosteRazorDialogController
{
public:
	PosteRazorWizardDialogController();
	virtual ~PosteRazorWizardDialogController() {};
	void setPosteRazorWizardDialog(PosteRazorWizardDialogInterface *dialog);

private:
	PosteRazorWizardDialogInterface *m_WizardDialog;
};

#endif
