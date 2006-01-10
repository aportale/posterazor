#include "Fl_Image_Text_Button.h"

#include <FL/fl_draw.H>
#include <FL/Fl.H>

Fl_Image_Text_Button::Fl_Image_Text_Button(int x, int y, int w, int h, const char* label)
	:Fl_Button(x, y, w, h, label)
{
	m_label_image = 0;
}

void Fl_Image_Text_Button::label_image(Fl_Image *image)
{
	m_label_image = image;
}

void Fl_Image_Text_Button::draw()
{
	Fl_Button::draw();

	if (m_label_image)
		m_label_image->draw(x() + 6, y() + (h()-m_label_image->h()) / 2);
}