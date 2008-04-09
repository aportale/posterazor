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

#ifndef TranslationInterface_h
#define TranslationInterface_h

class TranslationInterface
{
public:
	virtual ~TranslationInterface() {}

	virtual const char* languageName(void) const = 0;

	virtual const char* absoluteSize(void) const = 0;
	virtual const char* allImageFormats(void) const = 0;
	virtual const char* back(void) const = 0;
	virtual const char* borders(void) const = 0;
	virtual const char* bottom(void) const = 0;
	virtual const char* bottomLeft(void) const = 0;
	virtual const char* bottomRight(void) const = 0;
	virtual const char* cancel(void) const = 0;
	virtual const char* colorType(void) const = 0;
	virtual const char* custom(void) const = 0;
	virtual const char* fileCouldNotBeLoaded(void) const = 0;
	virtual const char* fileCouldNotBeSaved(void) const = 0;
	virtual const char* format(void) const = 0;
	virtual const char* grayscale(void) const = 0;
	virtual const char* height(void) const = 0;
	virtual const char* imageAlignment(void) const = 0;
	virtual const char* imageInformations(void) const = 0;
	virtual const char* imageSize(void) const = 0;
	virtual const char* inputImage(void) const = 0;
	virtual const char* landscape(void) const = 0;
	virtual const char* language(void) const = 0;
	virtual const char* languageExplanation(void) const = 0;
	virtual const char* launchPDFApplication(void) const = 0;
	virtual const char* left(void) const = 0;
	virtual const char* loadAnInputImage(void) const = 0;
	virtual const char* monochrome(void) const = 0;
	virtual const char* next(void) const = 0;
	virtual const char* orientation(void) const = 0;
	virtual const char* overlappingSize(void) const = 0;
	virtual const char* overlappingPosition(void) const = 0;
	virtual const char* overwriteFile(void) const = 0;
	virtual const char* pages(void) const = 0;
	virtual const char* palette(void) const = 0;
	virtual const char* paperFormat(void) const = 0;
	virtual const char* portrait(void) const = 0;
	virtual const char* posteRazorHelp(void) const = 0;
	virtual const char* posteRazorSettings(void) const = 0;
	virtual const char* posteRazorWebSiteURL(void) const = 0;
	virtual const char* posteRazorWebSite(void) const = 0;
	virtual const char* previewWithOpenGL(void) const = 0;
	virtual const char* previewWithOpenGLExplanation(void) const = 0;
	virtual const char* resolution(void) const = 0;
	virtual const char* right(void) const = 0;
	virtual const char* saveThePoster(void) const = 0;
	virtual const char* saveThePosterAs(void) const = 0;
	virtual const char* settings(void) const = 0;
	virtual const char* Size(void) const = 0;
	virtual const char* sizeInPages(void) const = 0;
	virtual const char* sizeInPercent(void) const = 0;
	virtual const char* sizeInPixels(void) const = 0;
	virtual const char* sizeInUnitOfLength(void) const = 0;
	virtual const char* standard(void) const = 0;
	virtual const char* stepXOfY(void) const = 0;
	virtual const char* top(void) const = 0;
	virtual const char* topLeft(void) const = 0;
	virtual const char* topRight(void) const = 0;
	virtual const char* unitOfLength(void) const = 0;
	virtual const char* unitOfLengthExplanation(void) const = 0;
	virtual const char* width(void) const = 0;

	virtual const char* stepTitle01(void) const = 0;
	virtual const char* stepTitle02(void) const = 0;
	virtual const char* stepTitle03(void) const = 0;
	virtual const char* stepTitle04(void) const = 0;
	virtual const char* stepTitle05(void) const = 0;
	virtual const char* helpHtml(void) const = 0;

	virtual const int flagImageWidth(void) const = 0;
	virtual const int flagImageHeight(void) const = 0;
	virtual const unsigned char* flagImageRGBData(void) const = 0;
};

#endif
