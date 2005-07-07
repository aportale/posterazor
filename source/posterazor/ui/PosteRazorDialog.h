#ifndef PosteRazorDialog_h
#define PosteRazorDialog_h

#include <FL/Fl_Image.H>
#include "PosteRazor.h"
#include "PosteRazorDialogUI.h"

class PosteRazorDialog : public PosteRazorDialogUI
{
private:
	unsigned char *m_previewImageData;
	Fl_RGB_Image  *m_previewImage;
	PosteRazor    *m_posteRazor;

	void DisposePreviewImage(void);
public:
	~PosteRazorDialog();
	PosteRazorDialog();

	void next(void);
	void prev(void);

	void LoadInputImage(void);
	void UpdatePreviewImage(void);

};

#endif