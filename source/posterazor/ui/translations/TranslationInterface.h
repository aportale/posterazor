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

#ifndef TranslationInterface_h
#define TranslationInterface_h

class TranslationInterface
{
public:
	virtual const char* LanguageName(void) = 0;

	virtual const char* AbsoluteSize(void) = 0;
	virtual const char* Back(void) = 0;
	virtual const char* Borders(void) = 0;
	virtual const char* Bottom(void) = 0;
	virtual const char* BottomLeft(void) = 0;
	virtual const char* BottomRight(void) = 0;
	virtual const char* Cancel(void) = 0;
	virtual const char* ColorType(void) = 0;
	virtual const char* Custom(void) = 0;
	virtual const char* FileCouldNotBeLoaded(void) = 0;
	virtual const char* Format(void) = 0;
	virtual const char* Grayscale(void) = 0;
	virtual const char* Height(void) = 0;
	virtual const char* ImageAlignment(void) = 0;
	virtual const char* ImageInformations(void) = 0;
	virtual const char* ImageSize(void) = 0;
	virtual const char* InputImage(void) = 0;
	virtual const char* Landscape(void) = 0;
	virtual const char* Language(void) = 0;
	virtual const char* LanguageExplanation(void) = 0;
	virtual const char* LaunchPDFApplication(void) = 0;
	virtual const char* Left(void) = 0;
	virtual const char* LoadAnInputImage(void) = 0;
	virtual const char* Monochrome(void) = 0;
	virtual const char* Next(void) = 0;
	virtual const char* Orientation(void) = 0;
	virtual const char* OverlappingSize(void) = 0;
	virtual const char* OverlappingPosition(void) = 0;
	virtual const char* OverwriteFile(void) = 0;
	virtual const char* Pages(void) = 0;
	virtual const char* Palette(void) = 0;
	virtual const char* PaperFormat(void) = 0;
	virtual const char* Portrait(void) = 0;
	virtual const char* PosteRazorHelp(void) = 0;
	virtual const char* PosteRazorSettings(void) = 0;
	virtual const char* PosteRazorWebSite(void) = 0;
	virtual const char* PreviewWithOpenGL(void) = 0;
	virtual const char* PreviewWithOpenGLExplanation(void) = 0;
	virtual const char* Resolution(void) = 0;
	virtual const char* Right(void) = 0;
	virtual const char* SaveThePoster(void) = 0;
	virtual const char* Settings(void) = 0;
	virtual const char* Size(void) = 0;
	virtual const char* SizeInPages(void) = 0;
	virtual const char* SizeInPercent(void) = 0;
	virtual const char* SizeInPixels(void) = 0;
	virtual const char* SizeInUnitOfLength(void) = 0;
	virtual const char* Standard(void) = 0;
	virtual const char* StepXOfY(void) = 0;
	virtual const char* Top(void) = 0;
	virtual const char* TopLeft(void) = 0;
	virtual const char* TopRight(void) = 0;
	virtual const char* UnitOfLength(void) = 0;
	virtual const char* UnitOfLengthExplanation(void) = 0;
	virtual const char* Width(void) = 0;

	virtual const char* StepTitle01(void) = 0;
	virtual const char* StepTitle02(void) = 0;
	virtual const char* StepTitle03(void) = 0;
	virtual const char* StepTitle04(void) = 0;
	virtual const char* StepTitle05(void) = 0;
	virtual const char* HelpHtml(void) = 0;

	virtual const int FlagImageWidth(void) = 0;
	virtual const int FlagImageHeight(void) = 0;
	virtual const unsigned char* FlagImageRGBData(void) = 0;
};

#endif