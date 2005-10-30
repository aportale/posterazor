/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005 by Alessandro Portale
	http://posterazor.sourceforge.net/

	This file is part of PosteRazor

	PosteRazor is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.
	
	PosteRazor is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with PosteRazor; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

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
	virtual void SetBackgroundColor(unsigned char red, unsigned char green, unsigned char blue) = 0;
	virtual void DrawFilledRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) = 0;
	virtual void DrawRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) = 0;
	virtual void DrawLine(double x1, double y1, double x2, double y2, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) = 0;
	virtual void GetSize(double &width, double &height) const = 0;
	virtual void SetImage(const unsigned char* rgbData, double width, double height) = 0;
	virtual void DrawImage(double x, double y, double width, double height) = 0;
};

#endif PaintCanvasInterface_h