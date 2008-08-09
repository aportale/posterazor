/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2008 by Alessandro Portale
	http://posterazor.sourceforge.net/

	This file is part of PosteRazor

	PosteRazor is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	
	PosteRazor is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with PosteRazor; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifndef PAINTCANVASBASE_H
#define PAINTCANVASBASE_H

#include "PaintCanvasInterface.h"
#include <QString>

class PaintCanvasBase: public PaintCanvasInterface
{
protected:
	QString m_stateString;
	unsigned char m_backgroundColor[3];
	double m_maxImageWidth;
	double m_maxImageHeight;
	const PainterInterface *m_painter;
	
public:
	PaintCanvasBase();

	virtual void setPainterInterface(const PainterInterface *painter);
	virtual void setState(const QString &state);
	virtual void setBackgroundColor(unsigned char red, unsigned char green, unsigned char blue);
	virtual void requestImage(void);

	virtual void disposeImage(void) = 0;
};

#endif // PAINTCANVASBASE_H
