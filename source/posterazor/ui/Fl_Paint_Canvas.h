#ifndef Fl_Paint_Canvas_h
#define Fl_Paint_Canvas_h

#include <FL/Fl_Box.H>
#include <FL/Fl_Image.H>
#include "../../tools/PaintCanvasInterface.h"

class Fl_Paint_Canvas: public Fl_Box, public PaintCanvasInterface
{
private:
	char m_stateString[1024];
	Fl_RGB_Image *m_image;
	Fl_Image *m_scaledImage;
	
public:
	Fl_Paint_Canvas(int width, int height, int x, int y);
	~Fl_Paint_Canvas();

	virtual void SetState(const char *state);
		
	virtual void draw();
	virtual void DrawFilledRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue);
	virtual void DrawRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue);
	virtual void DrawLine(double x1, double y1, double x2, double y2, unsigned char red, unsigned char green, unsigned char blue);
	virtual void GetSize(double &width, double &height) const;

	virtual void RequestImage(void);
	virtual void SetImage(const unsigned char* rgbData, double width, double height);
	virtual void DisposeImage(void);
	virtual void DrawImage(double x, double y, double width, double height);
};

#endif Fl_Paint_Canvas_h