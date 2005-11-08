#ifndef TranslationInterface_h
#define TranslationInterface_h

class TranslationInterface
{
public:
	virtual const char* Borders(void) = 0;
	virtual const char* ImageInformations(void) = 0;
	virtual const char* InputImage(void) = 0;
	virtual const char* Settings(void) = 0;
	virtual const char* StepXOfY(void) = 0;

	virtual const char* StepTitle01(void) = 0;
	virtual const char* StepTitle02(void) = 0;
	virtual const char* StepTitle03(void) = 0;
	virtual const char* StepTitle04(void) = 0;
	virtual const char* StepTitle05(void) = 0;
	virtual const char* HelpHtml(void) = 0;
};

#endif