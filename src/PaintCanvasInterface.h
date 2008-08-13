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

#ifndef PAINTCANVASINTERFACE_H
#define PAINTCANVASINTERFACE_H

#include <QVariant>

class PaintCanvasInterface;

class PainterInterface
{
public:
    virtual ~PainterInterface() {}

    virtual void paintOnCanvas(PaintCanvasInterface *paintCanvas, const QVariant &options) const = 0;
};

class PaintCanvasInterface
{
public:
    virtual ~PaintCanvasInterface() {}
    
    virtual void drawFilledRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) = 0;
    virtual void drawRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) = 0;
    virtual void drawLine(double x1, double y1, double x2, double y2, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) = 0;
    virtual void getSize(double &width, double &height) const = 0;
    virtual void drawImage(double x, double y, double width, double height) = 0;
};

#endif // PAINTCANVASINTERFACE_H
