#ifndef PosteRazorDialog_h
#define PosteRazorDialog_h

#include <FL/Fl_Image.H>
#include <FL/Fl_Menu_Item.H>
#include "PosteRazor.h"
#include "PosteRazorDialogUI.h"

class PosteRazorDialog : public PosteRazorDialogUI
{
private:
	PosteRazor    *m_posteRazor;
	
	Fl_Menu_Item  *m_paperFormatMenuItems;

public:
	~PosteRazorDialog();
	PosteRazorDialog();

	void next(void);
	void prev(void);
	void UpdateNavigationButtons(void);
	void UpdatePreviewState(void);

	void LoadInputImage(void);
	void UpdateImageInfoFields(void);

	void SetPaperSizeFields(void);
	static void HandlePaperFormatChoice_cb(Fl_Widget *widget, void *userData);
	void HandlePaperSizeChangement(Fl_Widget *sourceWidget);

	void SetOverlappingFields(void);
	void HandleOverlappingChangement(Fl_Widget *sourceWidget);

	void UpdatePosterSizeFields(Fl_Valuator *sourceWidget);
	void UpdatePosterSizeGroupsState(void);
};

#endif