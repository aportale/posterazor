/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2007 by Alessandro Portale
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

#include "Fl_Gl_Paint_Canvas.h"
#include <string.h>

#define BORDER 9.0
#define MIN(a, b) ((a)<=(b)?(a):(b))

Fl_Gl_Paint_Canvas::Fl_Gl_Paint_Canvas(int x, int y, int width, int height, Fl_Widget *parentWidget)
	:Fl_Gl_Window(x, y, width, height)
	, PaintCanvasBase()
	, m_texturesNames(NULL)
	, m_imageWidth(0)
	, m_imageHeight(0)
	, m_texturesSize(64)
	, m_parentWidget(parentWidget)
{
}

Fl_Gl_Paint_Canvas::~Fl_Gl_Paint_Canvas()
{
	disposeImage();
}

void Fl_Gl_Paint_Canvas::draw()
{
	if (!valid())
	{
		valid(1);
		glLoadIdentity();
		glViewport(0, 0, w(), h());
		glOrtho(0, w(), h(), 0, -1, 1);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &m_texturesSize);
		m_texturesSize = MIN(m_texturesSize, 256);
	}
	glClear(GL_COLOR_BUFFER_BIT);

	drawFilledRect(-BORDER, -BORDER, w(), h(), m_backgroundColor[0], m_backgroundColor[1], m_backgroundColor[2], 255);

	m_painter->paintOnCanvas(this, m_stateString);
}

int Fl_Gl_Paint_Canvas::handle(int event)
{
	if (m_parentWidget)
	{
		switch (event)
		{
		case FL_DND_ENTER:
		case FL_DND_DRAG:
		case FL_DND_LEAVE:
		case FL_DND_RELEASE:
			return 1;
		case FL_PASTE:
			return m_parentWidget->parent()->handle(event);
		default:
			return Fl_Gl_Window::handle(event);
		};
	}
	else
		return Fl_Gl_Window::handle(event);
}

void Fl_Gl_Paint_Canvas::drawFilledRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	if (height > 0 && height < 1)
	{
		drawLine(x, y, x+width, y, red, green, blue, alpha);
	}
	else if (width > 0 && width < 1)
	{
		drawLine(x, y, x, y+height, red, green, blue, alpha);
	}
	else
	{
		glColor4d(red/255.0, green/255.0, blue/255.0, alpha/255.0);
		glRectd(x + BORDER, y + BORDER, width + x + BORDER, height + y + BORDER);
	}
}

void Fl_Gl_Paint_Canvas::drawRect(double x, double y, double width, double height, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	if (height > 0 && height < 1)
	{
		drawLine(x, y, x+width, y, red, green, blue, alpha);
	}
	else if (width > 0 && width < 1)
	{
		drawLine(x, y, x, y+height, red, green, blue, alpha);
	}
	else
	{
		glColor4d(red/255.0, green/255.0, blue/255.0, alpha/255.0);
		glBegin(GL_LINE_LOOP);
		double x1 = x + BORDER;
		double x2 = width + x + BORDER;
		double y1 = y + BORDER;
		double y2 = height + y + BORDER;
		glVertex2d(x1, y1);
		glVertex2d(x2, y1);
		glVertex2d(x2, y2);
		glVertex2d(x1, y2);
		glEnd();
	}
}

void Fl_Gl_Paint_Canvas::drawLine(double x1, double y1, double x2, double y2, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
	glColor4d(red/255.0, green/255.0, blue/255.0, alpha/255.0);
	glBegin(GL_LINES);
	glVertex2d(x1 + BORDER, y1 + BORDER);
	glVertex2d(x2 + BORDER, y2 + BORDER);
	glEnd();
}

void Fl_Gl_Paint_Canvas::getSize(double &width, double &height) const
{
	width = w() - BORDER - BORDER;
	height = h() - BORDER - BORDER;
}

void Fl_Gl_Paint_Canvas::setImage(const unsigned char *rgbData, double width, double height)
{
	disposeImage();

	m_imageHeight = (unsigned int)height;
	m_imageWidth = (unsigned int)width;
	m_texturesNames = new GLuint[getTexturesCount()];
	glGenTextures(getTexturesCount(), m_texturesNames);
	unsigned long bytesPerImageRowCount = m_imageWidth * 3;
	unsigned long bytesPerTextureRowCount = m_texturesSize * 3;
	unsigned long textureRgbDataBytesCount = m_texturesSize * bytesPerTextureRowCount;
	unsigned char *textureRgbData = new unsigned char[textureRgbDataBytesCount];
	for (unsigned int texturesRow = 0; texturesRow < getTexturesRowsCount(); texturesRow++)
	{
		for (unsigned int texturesColumn = 0; texturesColumn < getTexturesColumnsCount(); texturesColumn++)
		{
			unsigned int currentTexture = texturesRow * getTexturesColumnsCount() + texturesColumn;
			unsigned int currentTexturePixelsColumns = getTexturesColumnPixelColumns(texturesColumn);
			unsigned int currentTexturePixelsRows = getTexturesRowPixelRows(texturesRow);
			memset(textureRgbData, 255, textureRgbDataBytesCount);

			for (unsigned int texturePixelRow = 0; texturePixelRow < currentTexturePixelsRows; texturePixelRow++)
			{
				memcpy
				(
					textureRgbData + texturePixelRow*bytesPerTextureRowCount,
					rgbData + ((texturesRow*m_texturesSize+texturePixelRow)*bytesPerImageRowCount) + (texturesColumn*bytesPerTextureRowCount),
					currentTexturePixelsColumns * 3
				);
			}

			glBindTexture(GL_TEXTURE_2D, m_texturesNames[currentTexture]);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
			GLfloat color[4];
			color[0] = color[1] = color[2] = 1; color[3] = 0;
			glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_texturesSize, m_texturesSize, 0, GL_RGB, GL_UNSIGNED_BYTE, textureRgbData);
		}
	}
	delete[] textureRgbData;
	redraw();
}

void Fl_Gl_Paint_Canvas::disposeImage(void)
{
	if (m_texturesNames)
	{
		glDeleteTextures(getTexturesCount(), m_texturesNames);
		delete[] m_texturesNames;
		m_texturesNames = NULL;
		m_imageWidth = 0;
		m_imageHeight = 0;
	}
}

void Fl_Gl_Paint_Canvas::drawImage(double x, double y, double width, double height)
{
	if (m_texturesNames)
	{
		glColor4d(1, 1, 1, 1);
		glEnable(GL_TEXTURE_2D);
		unsigned int texturesRowsCount = getTexturesRowsCount();
		unsigned int texturesColumnsCount = getTexturesColumnsCount();
		double widthResizeFactor = width/(double)m_imageWidth;
		double heightResizeFactor = height/(double)m_imageHeight;
		double defaultTextureWidth = m_texturesSize * widthResizeFactor;
		double defaultTextureHeight = m_texturesSize * heightResizeFactor;
		GLint textureMagFilter = widthResizeFactor >= 2.75?GL_NEAREST:GL_LINEAR;
		for (unsigned int texturesRow = 0; texturesRow < texturesRowsCount; texturesRow++)
		{
			double currentTextureYOffset = texturesRow * defaultTextureHeight;
			for (unsigned int texturesColumn = 0; texturesColumn < texturesColumnsCount; texturesColumn++)
			{
				unsigned int currentTexture = texturesRow * texturesColumnsCount + texturesColumn;
				unsigned int currentTexturePixelsColumns = getTexturesColumnPixelColumns(texturesColumn);
				double currentTextureWidth = (double)currentTexturePixelsColumns * widthResizeFactor;
				unsigned int currentTexturePixelsRows = getTexturesRowPixelRows(texturesRow);
				double currentTextureHeight = (double)currentTexturePixelsRows * heightResizeFactor;
				double currentTextureXOffset = texturesColumn * defaultTextureWidth;
				double currentTexCoordMaxX = (GLdouble)currentTexturePixelsColumns / m_texturesSize;
				double currentTexCoordMaxY = (GLdouble)currentTexturePixelsRows / m_texturesSize;

				glBindTexture(GL_TEXTURE_2D, m_texturesNames[currentTexture]);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureMagFilter);
				glBegin(GL_QUADS);
				glTexCoord2d (0, 0);
				glVertex2d(x + currentTextureXOffset + BORDER, y + currentTextureYOffset + BORDER);
				glTexCoord2d (currentTexCoordMaxX, 0);
				glVertex2d(x + currentTextureXOffset + BORDER + currentTextureWidth, y + currentTextureYOffset + BORDER);
				glTexCoord2d (currentTexCoordMaxX, currentTexCoordMaxY);
				glVertex2d(x + currentTextureXOffset + BORDER + currentTextureWidth, y + currentTextureYOffset + BORDER + currentTextureHeight);
				glTexCoord2d (0, currentTexCoordMaxY);
				glVertex2d(x + currentTextureXOffset + BORDER, y + currentTextureYOffset + BORDER + currentTextureHeight);
				glEnd();
			}
		}
		glDisable(GL_TEXTURE_2D);
	}
}

unsigned int Fl_Gl_Paint_Canvas::getTexturesColumnsCount(void) const
{
	return (int)ceil((double)m_imageWidth / (double)m_texturesSize);
}

unsigned int Fl_Gl_Paint_Canvas::getTexturesRowsCount(void) const
{
	return (int)ceil((double)m_imageHeight / (double)m_texturesSize);
}

unsigned int Fl_Gl_Paint_Canvas::getTexturesCount(void) const
{
	return getTexturesColumnsCount() * getTexturesRowsCount();
}

unsigned int Fl_Gl_Paint_Canvas::getLastTexturesColumnPixelsColumns(void) const
{
	return m_imageWidth - (getTexturesColumnsCount()-1)*m_texturesSize;
}

unsigned int Fl_Gl_Paint_Canvas::getLastTexturesRowPixelsRows(void) const
{
	return m_imageHeight - (getTexturesRowsCount()-1)*m_texturesSize;
}

unsigned int Fl_Gl_Paint_Canvas::getTexturesColumnPixelColumns(unsigned int column) const
{
	return column < getTexturesColumnsCount()-1?m_texturesSize:getLastTexturesColumnPixelsColumns();
}

unsigned int Fl_Gl_Paint_Canvas::getTexturesRowPixelRows(unsigned int row) const
{
	return row < getTexturesRowsCount()-1?m_texturesSize:getLastTexturesRowPixelsRows();
}
