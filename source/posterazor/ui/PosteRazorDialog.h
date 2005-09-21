#ifndef PosteRazorDialog_h
#define PosteRazorDialog_h

#include <FL/Fl_Image.H>
#include <FL/Fl_Menu_Item.H>
#include "PosteRazor.h"
#include "PosteRazorDialogUI.h"

class PosteRazorDragDropWidget : public Fl_Box
{
public:
	PosteRazorDragDropWidget(int x, int y, int w, int h, const char *label = 0);
	int handle(int event);
};

class PosteRazorDialog : public PosteRazorDialogUI
{
private:
	PosteRazor    *m_posteRazor;
	PosteRazorDragDropWidget *m_dragDropWidget;
	Fl_Menu_Item  *m_paperFormatMenuItems;
	Fl_Menu_Item  *m_distanceUnitMenuItems;

public:
	~PosteRazorDialog();
	PosteRazorDialog();

	int handle(int event);

	static void HandleDistanceUnitChoice_cb(Fl_Widget *widget, void *userData);
	void HandleDistanceUnitChangement(Fl_Widget *sourceWidget);
	void next(void);
	void prev(void);
	void UpdateNavigationButtons(void);
	void UpdatePreviewState(void);

	void LoadInputImage(const char *fileName);
	void UpdateImageInfoFields(void);

        void SetPaperSizeFields(void);
	static void HandlePaperFormatChoice_cb(Fl_Widget *widget, void *userData);
	void HandlePaperSizeChangement(Fl_Widget *sourceWidget);

	void SetOverlappingFields(void);
	void HandleOverlappingChangement(Fl_Widget *sourceWidget);

	void UpdatePosterSizeFields(Fl_Valuator *sourceWidget);
	void UpdatePosterSizeGroupsState(void);
	void SetPosterImageAlignmentButtons(void);
	void HandlePosterImageAlignment(void);

	void SavePoster(void);
	void SetLaunchPDFApplication(void);
};

#endif