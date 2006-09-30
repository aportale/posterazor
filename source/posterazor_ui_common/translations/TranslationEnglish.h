/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2006 by Alessandro Portale
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

#ifndef TranslationEnglish_h
#define TranslationEnglish_h

#include "TranslationInterface.h"
#include "TranslationConstants.h"

#define ENGLISH_POSTERAZORWEBSITEURL POSTERAZORWEBSITEDOMAIN

class TranslationEnglish: public TranslationInterface
{
public:
	const char* LanguageName(void)                    {return "English";}

	const char* AbsoluteSize(void)                    {return "Absolute size:";}
	const char* AllImageFormats(void)                 {return "All image formats";}
	const char* Back(void)                            {return "Back";}
	const char* Borders(void)                         {return "Borders";}
	const char* Bottom(void)                          {return "Bottom";}
	const char* BottomLeft(void)                      {return "Bottom left";}
	const char* BottomRight(void)                     {return "Bottom right";}
	const char* Cancel(void)                          {return "Cancel";}
	const char* ColorType(void)                       {return "Color type:";}
	const char* Custom(void)                          {return "Custom";}
	const char* FileCouldNotBeLoaded(void)            {return "The File \"%s\" could not be loaded.";}
	const char* Format(void)                          {return "Format:";}
	const char* Grayscale(void)                       {return "Grayscale";}
	const char* Height(void)                          {return "Height:";}
	const char* ImageAlignment(void)                  {return "Image alignment";}
	const char* ImageInformations(void)               {return "Image informations";}
	const char* ImageSize(void)                       {return "Image size";}
	const char* InputImage(void)                      {return "Input image";}
	const char* Landscape(void)                       {return "Landscape";}
	const char* Language(void)                        {return "Language";}
	const char* LanguageExplanation(void)             {return "Choose your language";}
	const char* LaunchPDFApplication(void)            {return "Launch PDF application after the poster is saved";}
	const char* Left(void)                            {return "Left";}
	const char* LoadAnInputImage(void)                {return StepTitle01();}
	const char* Monochrome(void)                      {return "Monochrome";}
	const char* Next(void)                            {return "Next";}
	const char* Orientation(void)                     {return "Orientation:";}
	const char* OverlappingPosition(void)             {return "Overlapping position";}
	const char* OverlappingSize(void)                 {return "Overlapping size";}
	const char* OverwriteFile(void)                   {return "The file '%s' already exists.\nDo you want to overwrite it?";}
	const char* Pages(void)                           {return "pages";}
	const char* PaperFormat(void)                     {return "Paper format";}
	const char* Palette(void)                         {return "Palette";}
	const char* Portrait(void)                        {return "Portrait";}
	const char* PosteRazorHelp(void)                  {return "PosteRazor help";}
	const char* PosteRazorSettings(void)              {return "PosteRazor settings";}
	const char* PosteRazorWebSiteURL(void)            {return ENGLISH_POSTERAZORWEBSITEURL;}
	const char* PosteRazorWebSite(void)               {return "PosteRazor website";}
	const char* PreviewWithOpenGL(void)               {return "Preview with OpenGL";}
	const char* PreviewWithOpenGLExplanation(void)    {return "OpenGL enables a smooth preview on modern systems. It could slow the preview down on old systems, though.";}
	const char* Resolution(void)                      {return "Resolution:";}
	const char* Right(void)                           {return "Right";}
	const char* SaveThePoster(void)                   {return "Save the poster";}
	const char* SaveThePosterAs(void)                 {return "Save the poster as";}
	const char* Settings(void)                        {return "Settings...";}
	const char* Size(void)                            {return "Size:";}
	const char* SizeInPages(void)                     {return "Size in pages:";}
	const char* SizeInPercent(void)                   {return "Size in percent:";}
	const char* SizeInPixels(void)                    {return "Size (in pixels):";}
	const char* SizeInUnitOfLength(void)              {return "Size (in %s):";}
	const char* Standard(void)                        {return "Standard";}
	const char* StepXOfY(void)                        {return "Step %d of %d";}
	const char* Top(void)                             {return "Top";}
	const char* TopLeft(void)                         {return "Top left";}
	const char* TopRight(void)                        {return "Top right";}
	const char* UnitOfLength(void)                    {return "Unit of Length";}
	const char* UnitOfLengthExplanation(void)         {return "Choose the distance unit you want to work with";}
	const char* Width(void)                           {return "Width:";}


#define ENGLISH_POSTERAZORHELSTEP                     "Step"

#define ENGLISH_POSTERAZORHELPABOUT                   "About the PosteRazor"
#define ENGLISH_POSTERAZORHELPMANUAL                  "Manual"
#define ENGLISH_POSTERAZORHELPSETTINGS                "Settings"
#define ENGLISH_POSTERAZORHELPSTEPTITLE01             "Load an input image"
#define ENGLISH_POSTERAZORHELPSTEPTITLE02             "Define the printer paper format"
#define ENGLISH_POSTERAZORHELPSTEPTITLE03             "Define the image tile overlapping"
#define ENGLISH_POSTERAZORHELPSTEPTITLE04             "Define the final poster size"
#define ENGLISH_POSTERAZORHELPSTEPTITLE05             "Save the Poster"
#define ENGLISH_POSTERAZORHELPINPUTFILEFORMATS        "Supported input image files"
#define ENGLISH_POSTERAZORHELPWHYPDFOUTPUT            "Why a PDF output?"
#define ENGLISH_POSTERAZORHELPCODEFROMTHIRDPARTIES    "Code from third parties"
#define ENGLISH_POSTERAZORHELPLICENSE                 "License"

	const char* StepTitle01(void)                     {return ENGLISH_POSTERAZORHELPSTEPTITLE01;};
	const char* StepTitle02(void)                     {return ENGLISH_POSTERAZORHELPSTEPTITLE02;};
	const char* StepTitle03(void)                     {return ENGLISH_POSTERAZORHELPSTEPTITLE03;};
	const char* StepTitle04(void)                     {return ENGLISH_POSTERAZORHELPSTEPTITLE04;};
	const char* StepTitle05(void)                     {return ENGLISH_POSTERAZORHELPSTEPTITLE05;};
	const char* HelpHtml(void)
	{
		return	"<HTML>" POSTERAZORHELPENDLINE \
				"<BODY>" POSTERAZORHELPENDLINE \
					"<A name=\"" POSTERAZORHELPANCHORTOP "\"><CENTER><H1>PosteRazor "POSTERAZORVERSION" Help</H1></CENTER></A>" POSTERAZORHELPENDLINE \

					"<H3>Contents</H3>" POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORABOUT "\">" ENGLISH_POSTERAZORHELPABOUT "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORMANUAL "\">" ENGLISH_POSTERAZORHELPMANUAL "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORSETTINGS "\">" ENGLISH_POSTERAZORHELPSETTINGS "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<UL>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP01 "\">" ENGLISH_POSTERAZORHELSTEP " 1: " ENGLISH_POSTERAZORHELPSTEPTITLE01 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP02 "\">" ENGLISH_POSTERAZORHELSTEP " 2: " ENGLISH_POSTERAZORHELPSTEPTITLE02 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP03 "\">" ENGLISH_POSTERAZORHELSTEP " 3: " ENGLISH_POSTERAZORHELPSTEPTITLE03 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP04 "\">" ENGLISH_POSTERAZORHELSTEP " 4: " ENGLISH_POSTERAZORHELPSTEPTITLE04 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP05 "\">" ENGLISH_POSTERAZORHELSTEP " 5: " ENGLISH_POSTERAZORHELPSTEPTITLE05 "</A></LI>" POSTERAZORHELPENDLINE \
						"</UL>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORINPUTFILEFORMATS "\">" ENGLISH_POSTERAZORHELPINPUTFILEFORMATS "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORWHYPDFOUTPUT "\">" ENGLISH_POSTERAZORHELPWHYPDFOUTPUT "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES "\">" ENGLISH_POSTERAZORHELPCODEFROMTHIRDPARTIES "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORLICENSE "\">" ENGLISH_POSTERAZORHELPLICENSE "</A></B></LI>" POSTERAZORHELPENDLINE \
					"</UL><HR>" POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORABOUT, ENGLISH_POSTERAZORHELPABOUT) \
					POSTERAZORHELPINDENTATION "The PosteRazor cuts a raster image into pieces which can be printed on a printer and be put together to a poster. As an input image, raster files of <A href=\"#" POSTERAZORHELPANCHORMANUALSTEP01 "\">various</A> image file formats are supported. Instead of directly printing the poster, the PosteRazor produces a multi page PDF files which contains the poster tiles.<br>" POSTERAZORHELPENDLINE \
					"It is an open source program which depends on <a href=\"#" POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES "\">other open source projects</a>. " POSTERAZORHELPENDLINE \
					"The PosteRazor is hostet on <b>posterazor.sourceforge.net</b>." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUAL, ENGLISH_POSTERAZORHELPMANUAL) \
					POSTERAZORHELPINDENTATION "PosteRazor has its user interface organized in a \"Wizard\" fashion. All settings for the poster creation can be done in 5 Steps. The <b>Back</b> and <b>Next</b> buttons navigate through these steps.<br>" POSTERAZORHELPENDLINE \
					"The <b>?</b> button opens a help window with an explanation of the current step.<br>" POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "All entries and choices are remembered until the next usage of the PosteRazor." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORSETTINGS, ENGLISH_POSTERAZORHELPSETTINGS) \
					POSTERAZORHELPINDENTATION "By pressing the <b>Settings...</b> button on the lower left of the main dialog, the PosteRazor settings dialog is opened." POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>Unit of Length:</b> choose the unit of length that you a re used to work with. When a unit is changed, all predefined values and the values which You already defined are transformed to the new unit.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Language:</b> choose your language. The PosteRazor does not need to be restarted when the language is changed.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Preview with OpenGL:</b> choose, if the PosteRazor should use OpenGL for the image preview. Usually, on modern hardware OpenGL should be faster and give a more precise preview than the non-OpenGL preview. But if the PosteRazor seems to be slow and unresponsive, plese try if it works better with OpenGL switched off.</LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP01, ENGLISH_POSTERAZORHELSTEP " 1: " ENGLISH_POSTERAZORHELPSTEPTITLE01) \
					POSTERAZORHELPINDENTATION "Load an image by clicking the button with the open icon and selecting an image file, or by drag & dropping an image file on the PosteRazor. The drag & drop also works in the other steps.<br>" POSTERAZORHELPENDLINE \
					"Many <a href=\"#" POSTERAZORHELPANCHORINPUTFILEFORMATS "\">file formats and image types</a> can be loaded. After loading the image, the most important informations are listed in the <b>Image informations</b> fields." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP02, ENGLISH_POSTERAZORHELSTEP " 2: " ENGLISH_POSTERAZORHELPSTEPTITLE02) \
					POSTERAZORHELPINDENTATION "Define the paper sheet size that you use in your printer. A standard paper sheet size can be selected from the <b>Format</b> chooser, along with the desired paper sheet <b>Orientation</b>. Alternatively, a custom paper sheet size can be define in the <b>Custom</b> tab. (Please write me an email, if you miss your standard paper size in the chooser). " POSTERAZORHELPENDLINE \
					"Paper borders are defined in the <b>Borders</b> fileds. Even if your printer does need no (or small) paper borders, some border might be needed to have enough area for gluing the final poster tiles together." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP03, ENGLISH_POSTERAZORHELSTEP " 3: " ENGLISH_POSTERAZORHELPSTEPTITLE03) \
					POSTERAZORHELPINDENTATION "Image tile overlapping is needed to have some tolerance for cutting off the unneded borders from one side. Additionally, like the borders from the previous step, it gives more area for gluing together the final poster tiles. " POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "The <b>Overlapping position</b> defines the borders that are intended to be overlapped by the neighbour tiles. The borders on the opposite sides are intended to be cut (except on the outermost tiles)." POSTERAZORHELPENDLINE \
					
					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP04, ENGLISH_POSTERAZORHELSTEP " 4: " ENGLISH_POSTERAZORHELPSTEPTITLE04) \
					POSTERAZORHELPINDENTATION "Define the final poster size, in one of the following three modes which can be selected by the corresponding radio buttons:<br>" POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>Absolute image size</b>: You want to have a specific size of your poster.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Size in Pages</b>: you want to use whole paper sheets and specify how many of them of them you want to use.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Image Size in percent</b>: your input image has a certain size which is defined by the number of pixels and dpi (dots per Inch) and your want to enlarge the image by a certain factor.</LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "The aspect ratio of width and height is always 1:1 and is automatically recalculated. In the preview area, you can see the overlapping areas which are surrounded by light red rectangles. " POSTERAZORHELPENDLINE \
					"<b>Image alignment</b> sets the alignment of the image on the total paper area of the poster. This is useful if you want to keep the unused paper." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP05, ENGLISH_POSTERAZORHELSTEP " 5: " ENGLISH_POSTERAZORHELPSTEPTITLE05) \
					POSTERAZORHELPINDENTATION "Save the poster by clicking the save button and specifying a destination file name. Check or uncheck the <b>Launch PDF application after the poster is saved</b>, if the standard PDF handling application that is set in your operating system should be automatically started after the PDF file is saved." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORINPUTFILEFORMATS, ENGLISH_POSTERAZORHELPINPUTFILEFORMATS) \
					POSTERAZORHELPINDENTATION "Most of the raster image formats which are supported by FreeImage are also supported by the PosteRazor:<br>" POSTERAZORHELPENDLINE \
					"<b>BMP, DDS files, Dr. Halo, GIF, ICO, IFF, JBIG, JNG, JPEG/JIF, KOALA, LBM, Kodak PhotoCD, MNG, PCX, PBM, PGM, PNG, PPM, PhotoShop PSD, Sun RAS, TARGA, TIFF, WBMP, XBM, XPM.<br></b>" POSTERAZORHELPENDLINE \
					"PosteRazor distinguishes and handles monochrome, greyscale, 4-bit palette, 8-bit palette, 24 bit RGB, and CMYK (only from TIF) images. RGB images with an alpha channel are automatically composed onto a white background." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORWHYPDFOUTPUT, ENGLISH_POSTERAZORHELPWHYPDFOUTPUT) \
					POSTERAZORHELPINDENTATION "Why a PDF output and not direct printing? First of all the developer of this program does not know (yet) how to \"send images to the printer\", on the different operating systems, which PosteRazor is aimed for. Also, PDF makes sense, if a poster is razored at home with all the needed time and the day after it is printed on the color laser printer in the office (after everyone else went home). " POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "Why a PDF and not other raster formats as output? PDF gives the possibility to embed the whole image and virtually cut it, and not only between pixels but also with pixel fractions. Additionally, it seems more practicable to print a multi page PDF file instead of multiple image files." POSTERAZORHELPENDLINE \
					
					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES, ENGLISH_POSTERAZORHELPCODEFROMTHIRDPARTIES) \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>FLTK</b> is used for the user interface. It is a small (by size), fast, fun&easy to learn and very portable UI Toolkit. <a href=\"http://www.fltk.org/\">www.fltk.org</a></LI>" POSTERAZORHELPENDLINE \
					"<LI><b>FreeImage</b> is used for the image loading and handling. It makes image loading and handling really a no-brainer and is portable to the platforms, where the PosteRazor runs. <a href=\"http://freeimage.sourceforge.net/\">FreeImage website</a></LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Fl_Native_File_Chooser</b> is used for the file open and save dialog in the native system look and feel. <a href=\"http://seriss.com/people/erco/fltk/Fl_Native_File_Chooser/\">Fl_Native_File_Chooser website</a></LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \
					
					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORLICENSE, ENGLISH_POSTERAZORHELPLICENSE) \
					"PosteRazor - Make your own poster!<br>" POSTERAZORHELPENDLINE \
					"<a href=\""ENGLISH_POSTERAZORWEBSITEURL"\">posterazor.sourceforge.net</a><br>" POSTERAZORHELPENDLINE \
					"Copyright (C) 2005-2006 by Alessandro Portale<br>&nbsp;<br>" POSTERAZORHELPENDLINE \

					"<b>French translation by Martin Loyer (traduction<b></b>@<b></b>loyer<b></b>.<b></b>name).</b><br>" POSTERAZORHELPENDLINE \
					"<b>Polish translation by Grzegorz Wacikowski.</b><br>&nbsp;<br>" POSTERAZORHELPENDLINE \

					"This program is free software; you can redistribute it and/or modify it under the terms of the <a href=\"http://www.gnu.org/licenses/gpl.txt\">GNU General Public License</a> as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.<br>&nbsp;<br>" POSTERAZORHELPENDLINE \
					"This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.<br>&nbsp;<br>" POSTERAZORHELPENDLINE \
					"You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA." POSTERAZORHELPENDLINE \
				"</BODY>" POSTERAZORHELPENDLINE \
			"</HTML>";
	}

	const int FlagImageWidth(void)                    {return 20;}
	const int FlagImageHeight(void)                   {return 11;}
	const unsigned char *FlagImageRGBData(void)
	{
		static const unsigned char flagRGBData[] =
		{
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,0,0,153,0,0,153,0,0,153,0,0,153,0,0,153,0,0,153,0,0,153,0,0,
			153,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,
			0,0,140,140,140,140,140,140,0,0,153,255,255,255,0,0,153,255,255,255,0,0,153,
			255,255,255,0,0,153,0,0,153,255,255,255,255,255,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,232,232,255,81,81,0,0,153,0,0,153,140,140,140,140,140,
			140,0,0,153,0,0,153,0,0,153,0,0,153,0,0,153,0,0,153,0,0,153,0,0,153,255,0,0,255,
			0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,255,255,255,255,255,255,255,255,255,
			255,255,140,140,140,140,140,140,0,0,153,0,0,153,255,255,255,0,0,153,255,255,255,
			0,0,153,255,255,255,0,0,153,255,255,255,255,255,255,255,232,232,255,81,81,255,
			0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,140,140,140,140,140,140,0,0,153,0,
			0,153,0,0,153,0,0,153,0,0,153,0,0,153,0,0,153,0,0,153,255,0,0,255,0,0,255,0,0,
			255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,140,140,140,140,140,140,
			255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,221,202,
			202,255,81,81,255,0,0,255,0,0,255,255,255,255,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,255,255,255,255,255,255,140,140,140,140,140,140,255,0,0,
			255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,255,255,255,0,0,255,0,0,255,
			255,255,255,255,255,255,0,0,255,0,0,255,0,0,0,0,153,0,0,153,0,0,153,140,140,140,
			140,140,140,255,255,255,255,255,255,255,255,255,253,151,152,255,0,0,0,0,153,0,0,
			153,255,255,255,255,0,0,255,0,0,255,255,255,0,0,153,255,255,255,255,255,255,255,
			0,0,255,0,0,255,0,0,0,0,153,140,140,140,140,140,140,255,0,0,255,0,0,255,0,0,0,
			0,153,0,0,153,0,0,153,0,0,153,255,255,255,255,0,0,255,0,0,255,255,255,0,0,153,
			0,0,153,0,0,153,255,255,255,255,255,255,255,0,0,255,0,0,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140
		};

		return flagRGBData;
	}
};

static TranslationEnglish english;

#endif
