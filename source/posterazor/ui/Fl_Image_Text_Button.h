#ifndef Fl_Image_Text_Button_h
#define Fl_Image_Text_Button_h

#include <Fl/Fl_Image.h>
#include <Fl/Fl_Button.h>

class Fl_Image_Text_Button: public Fl_Button
{
public:
	Fl_Image_Text_Button(int x, int y, int w, int h, const char* label = 0);
	void label_image(Fl_Image *image);

private:
	Fl_Image *m_label_image;

	virtual void draw();
};

#endif