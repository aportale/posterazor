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
