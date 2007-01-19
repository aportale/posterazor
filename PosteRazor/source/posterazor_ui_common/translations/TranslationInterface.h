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
	virtual const char* languageName(void) = 0;

	virtual const char* absoluteSize(void) = 0;
	virtual const char* allImageFormats(void) = 0;
	virtual const char* back(void) = 0;
	virtual const char* borders(void) = 0;
	virtual const char* bottom(void) = 0;
	virtual const char* bottomLeft(void) = 0;
	virtual const char* bottomRight(void) = 0;
	virtual const char* cancel(void) = 0;
	virtual const char* colorType(void) = 0;
	virtual const char* custom(void) = 0;
	virtual const char* fileCouldNotBeLoaded(void) = 0;
	virtual const char* fileCouldNotBeSaved(void) = 0;
	virtual const char* format(void) = 0;
	virtual const char* grayscale(void) = 0;
	virtual const char* height(void) = 0;
	virtual const char* imageAlignment(void) = 0;
	virtual const char* imageInformations(void) = 0;
	virtual const char* imageSize(void) = 0;
	virtual const char* inputImage(void) = 0;
	virtual const char* landscape(void) = 0;
	virtual const char* language(void) = 0;
	virtual const char* languageExplanation(void) = 0;
	virtual const char* launchPDFApplication(void) = 0;
	virtual const char* left(void) = 0;
	virtual const char* loadAnInputImage(void) = 0;
	virtual const char* monochrome(void) = 0;
	virtual const char* next(void) = 0;
	virtual const char* orientation(void) = 0;
	virtual const char* overlappingSize(void) = 0;
	virtual const char* overlappingPosition(void) = 0;
	virtual const char* overwriteFile(void) = 0;
	virtual const char* pages(void) = 0;
	virtual const char* palette(void) = 0;
	virtual const char* paperFormat(void) = 0;
	virtual const char* portrait(void) = 0;
	virtual const char* posteRazorHelp(void) = 0;
	virtual const char* posteRazorSettings(void) = 0;
	virtual const char* posteRazorWebSiteURL(void) = 0;
	virtual const char* posteRazorWebSite(void) = 0;
	virtual const char* previewWithOpenGL(void) = 0;
	virtual const char* previewWithOpenGLExplanation(void) = 0;
	virtual const char* resolution(void) = 0;
	virtual const char* right(void) = 0;
	virtual const char* saveThePoster(void) = 0;
	virtual const char* saveThePosterAs(void) = 0;
	virtual const char* settings(void) = 0;
	virtual const char* Size(void) = 0;
	virtual const char* sizeInPages(void) = 0;
	virtual const char* sizeInPercent(void) = 0;
	virtual const char* sizeInPixels(void) = 0;
	virtual const char* sizeInUnitOfLength(void) = 0;
	virtual const char* standard(void) = 0;
	virtual const char* stepXOfY(void) = 0;
	virtual const char* top(void) = 0;
	virtual const char* topLeft(void) = 0;
	virtual const char* topRight(void) = 0;
	virtual const char* unitOfLength(void) = 0;
	virtual const char* unitOfLengthExplanation(void) = 0;
	virtual const char* width(void) = 0;

	virtual const char* stepTitle01(void) = 0;
	virtual const char* stepTitle02(void) = 0;
	virtual const char* stepTitle03(void) = 0;
	virtual const char* stepTitle04(void) = 0;
	virtual const char* stepTitle05(void) = 0;
	virtual const char* helpHtml(void) = 0;

	virtual const int flagImageWidth(void) = 0;
	virtual const int flagImageHeight(void) = 0;
	virtual const unsigned char* flagImageRGBData(void) = 0;
};

#endif
