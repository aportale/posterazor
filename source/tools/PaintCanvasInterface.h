#ifndef PaintCanvasInterface_h
#define PaintCanvasInterface_h

class PaintCanvasInterface;

class PainterInterface
{
public:
	virtual void PaintOnCanvas(PaintCanvasInterface *paintCanvas, void* options = 0) const = 0;
	virtual void GetImage(PaintCanvasInterface *paintCanvas) const = 0;
};

class PaintCanvasInterface
{
protected:
	const PainterInterface *m_painter;

public:
	PaintCanvasInterface()
	{
		m_painter = 0;
	}
	
	virtual ~PaintCanvasInterface() {}
	
	virtual void SetPainterInterface(const PainterInterface *painter) {m_painter = painter;}
	virtual void DrawFilledRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue) = 0;
	virtual void DrawRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue) = 0;
	virtual void DrawLine(double x1, double y1, double x2, double y2, unsigned char red, unsigned char green, unsigned char blue) = 0;
	virtual void GetSize(double &width, double &height) const = 0;
	virtual void SetImage(const unsigned char* rgbData, double width, double height) = 0;
	virtual void DrawImage(double x, double y, double width, double height) = 0;
};

#endif PaintCanvasInterface_h