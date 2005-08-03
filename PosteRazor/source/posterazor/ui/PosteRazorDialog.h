#ifndef PosteRazorDialog_h
#define PosteRazorDialog_h

#include <FL/Fl_Image.H>
#include <FL/Fl_Menu_Item.H>
#include "PosteRazor.h"
#include "PosteRazorDialogUI.h"

class PosteRazorDialog : public PosteRazorDialogUI
{
private:
	unsigned char *m_previewImageData;
	Fl_RGB_Image  *m_previewImage;
	PosteRazor    *m_posteRazor;
	
	bool          m_needPreviewImageUpdate;

	Fl_Menu_Item  *m_paperFormatMenuItems;

	void DisposePreviewImage(void);
	static void UpdatePreviewImage_cp(void *ptr);
public:
	~PosteRazorDialog();
	PosteRazorDialog();

	void resize(int x, int y, int w, int h);

	void next(void);
	void prev(void);
	void UpdateNavigationButtons(void);

	void LoadInputImage(void);
	void UpdatePreviewImage(void);

	void SetPageSizeFields(void);
	void SelectPageSizeGroup(bool useCustomPrintablePageSize);
	void UpdatePosterSizeFields(Fl_Valuator *sourceWidget);

	void HandlePaperFormatChoice(void);
	static void HandlePaperFormatChoice_cb(Fl_Widget *widget, void *userData);

	void HandlePaperOrientationChangement(void);
	void UpdatePosterSizeGroupsState(void);
};

#endif