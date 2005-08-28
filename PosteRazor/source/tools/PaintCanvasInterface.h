#ifndef PaintCanvasInterface_h
#define PaintCanvasInterface_h

class PaintCanvasInterface;

class PainterInterface
{
public:
	virtual void PaintOnCanvas(PaintCanvasInterface *paintCanvas, void* options = 0) = 0;
	virtual void GetImage(PaintCanvasInterface *paintCanvas) = 0;
};

class PaintCanvasInterface
{
protected:
	PainterInterface *m_painter;

public:
	PaintCanvasInterface()
	{
		m_painter = 0;
	}
	
	virtual ~PaintCanvasInterface() {}
	
	virtual void SetPainterInterface(PainterInterface *painter) {m_painter = painter;}
	virtual void DrawFilledRect(int x, int y, int width, int heigth, unsigned char red, unsigned char green, unsigned char blue) = 0;
	virtual void DrawLine(int x1, int y1, int x2, int y2, unsigned char red, unsigned char green, unsigned char blue) = 0;
	virtual void GetSize(int &width, int &height) = 0;
	virtual void SetImage(const unsigned char* rgbData, int width, int height) = 0;
	virtual void DrawImage(int x, int y, int width, int height) = 0;
};

#endif PaintCanvasInterface_h