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

#ifndef TranslationGerman_h
#define TranslationGerman_h

#include "TranslationInterface.h"

class TranslationGerman: public TranslationInterface
{
public:
	const char* LanguageName(void)                    {return "Deutsch";}

	const char* AbsoluteSize(void)                    {return "Absolute Maße:";}
	const char* Back(void)                            {return "Zurück";}
	const char* Borders(void)                         {return "Ränder";}
	const char* Bottom(void)                          {return "Unten";}
	const char* BottomLeft(void)                      {return "Unten links";}
	const char* BottomRight(void)                     {return "Unten rechts";}
	const char* Cancel(void)                          {return "Abbruch";}
	const char* ColorType(void)                       {return "Farbtyp:";}
	const char* Custom(void)                          {return "Eigenes";}
	const char* FileCouldNotBeLoaded(void)            {return "Die Datei \"%s\" konnte nicht geladen werden.";}
	const char* Format(void)                          {return "Format:";}
	const char* Grayscale(void)                       {return "Graustufen";}
	const char* Height(void)                          {return "Höhe:";}
	const char* ImageAlignment(void)                  {return "Ausrichtung des Bildes";}
	const char* ImageInformations(void)               {return "Bildinformationen";}
	const char* ImageSize(void)                       {return "Bildgröße";}
	const char* InputImage(void)                      {return "Ausgangsbild";}
	const char* Landscape(void)                       {return "Querformat";}
	const char* Language(void)                        {return "Sprache";}
	const char* LanguageExplanation(void)             {return "Wählen Sie ihre Sprache";}
	const char* LaunchPDFApplication(void)            {return "PDF-Applikation nach Speicherung des Posters starten";}
	const char* Left(void)                            {return "Links";}
	const char* LoadAnInputImage(void)                {return StepTitle01();}
	const char* Monochrome(void)                      {return "Monochrom";}
	const char* Next(void)                            {return "Weiter";}
	const char* Orientation(void)                     {return "Ausrichtung:";}
	const char* OverlappingPosition(void)             {return "Überlappende Seiten";}
	const char* OverlappingSize(void)                 {return "Maße der Überlappung";}
	const char* OverwriteFile(void)                   {return "Die Datei '%s' extistiert bereits.\nSoll sie überschrieben werden?";}
	const char* Pages(void)                           {return "Seiten";}
	const char* Palette(void)                         {return "Palette";}
	const char* PaperFormat(void)                     {return "Papierformat";}
	const char* Portrait(void)                        {return "Hochformat";}
	const char* PosteRazorHelp(void)                  {return "PosteRazor Hilfe";}
	const char* PosteRazorSettings(void)              {return "PosteRazor Einstellungen";}
	const char* PosteRazorWebSite(void)               {return "PosteRazor-Internetseite";}
	const char* PreviewWithOpenGL(void)               {return "Vorschau mit OpenGL";}
	const char* PreviewWithOpenGLExplanation(void)    {return "OpenGL ermöglicht eine bessere Vorschau. Auf alter Hardware könnte OpenGL jedoch langsamer sein.";}
	const char* Resolution(void)                      {return "Auflösung:";}
	const char* Right(void)                           {return "Rechts";}
	const char* SaveThePoster(void)                   {return "Das Poster speichern";}
	const char* SaveThePosterAs(void)                 {return "Das Poster speichern unter";}
	const char* Settings(void)                        {return "Einstellungen...";}
	const char* Size(void)                            {return "Größe:";}
	const char* SizeInPages(void)                     {return "Größe in Seiten:";}
	const char* SizeInPercent(void)                   {return "Prozentuelle Größe:";}
	const char* SizeInPixels(void)                    {return "Größe (in Pixeln):";}
	const char* SizeInUnitOfLength(void)              {return "Größe (in %s):";}
	const char* Standard(void)                        {return "Standard";}
	const char* StepXOfY(void)                        {return "Schritt %d von %d";}
	const char* Top(void)                             {return "Oben";}
	const char* TopLeft(void)                         {return "Oben links";}
	const char* TopRight(void)                        {return "Oben rechts";}
	const char* UnitOfLength(void)                    {return "Längeneinheit";}
	const char* UnitOfLengthExplanation(void)         {return "Wählen Sie die Längeneinheit, mit der Sie arbeiten möchten";}
	const char* Width(void)                           {return "Breite:";}


#include "PosteRazorHelpConstants.h"

#define GERMAN_POSTERAZORHELSTEP                      "Schritt"

#define GERMAN_POSTERAZORHELPABOUT                    "&Uuml;ber den PosteRazor"
#define GERMAN_POSTERAZORHELPABOUTNOHTML              "Über"
#define GERMAN_POSTERAZORHELPMANUAL                   "Bedienungsanleitung"
#define GERMAN_POSTERAZORHELPSETTINGS                 "Einstellungen"
#define GERMAN_POSTERAZORHELPSTEPTITLE01			  "Ein Ausgangsbild laden"
#define GERMAN_POSTERAZORHELPSTEPTITLENOHTML02        "Druckerpapier-Maße definieren"
#define GERMAN_POSTERAZORHELPSTEPTITLE02              "Druckerpapier-Ma&szlig;e definieren"
#define GERMAN_POSTERAZORHELPSTEPTITLENOHTML03        "Überlappung der Bildabschnitte definieren"
#define GERMAN_POSTERAZORHELPSTEPTITLE03              "&Uuml;berlappung der Bildabschnitte definieren"
#define GERMAN_POSTERAZORHELPSTEPTITLENOHTML04        "Die finale Postergröße definieren"
#define GERMAN_POSTERAZORHELPSTEPTITLE04              "Die finale Postergr&ouml;&szlig;e definieren"
#define GERMAN_POSTERAZORHELPSTEPTITLE05              "Das Poster speichern"
#define GERMAN_POSTERAZORHELPINPUTFILEFORMATS         "Unterst&uuml;tzte Ausgangs-Bildformate"
#define GERMAN_POSTERAZORHELPINPUTFILEFORMATSNOHTML   "Unterstützte Ausgangs-Bildformate"
#define GERMAN_POSTERAZORHELPWHYPDFOUTPUT             "Warum PDF als Ausgabeformat?"
#define GERMAN_POSTERAZORHELPCODEFROMTHIRDPARTIES     "Code von Drittanbietern"
#define GERMAN_POSTERAZORHELPLICENSE                  "Lizenz"

	const char* StepTitle01(void)                     {return GERMAN_POSTERAZORHELPSTEPTITLE01;};
	const char* StepTitle02(void)                     {return GERMAN_POSTERAZORHELPSTEPTITLENOHTML02;};
	const char* StepTitle03(void)                     {return GERMAN_POSTERAZORHELPSTEPTITLENOHTML03;};
	const char* StepTitle04(void)                     {return GERMAN_POSTERAZORHELPSTEPTITLENOHTML04;};
	const char* StepTitle05(void)                     {return GERMAN_POSTERAZORHELPSTEPTITLE05;};
	const char* HelpHtml(void)
	{
		return	"<HTML>" POSTERAZORHELPENDLINE \
				"<BODY>" POSTERAZORHELPENDLINE \
					"<A name=\"" POSTERAZORHELPANCHORTOP "\"><CENTER><H1>PosteRazor Help</H1></CENTER></A>" POSTERAZORHELPENDLINE \

					"<H3>Contents</H3>" POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORABOUT "\">" GERMAN_POSTERAZORHELPABOUT "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORMANUAL "\">" GERMAN_POSTERAZORHELPMANUAL "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORSETTINGS "\">" GERMAN_POSTERAZORHELPSETTINGS "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<UL>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP01 "\">" GERMAN_POSTERAZORHELSTEP " 1: " GERMAN_POSTERAZORHELPSTEPTITLE01 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP02 "\">" GERMAN_POSTERAZORHELSTEP " 2: " GERMAN_POSTERAZORHELPSTEPTITLE02 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP03 "\">" GERMAN_POSTERAZORHELSTEP " 3: " GERMAN_POSTERAZORHELPSTEPTITLE03 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP04 "\">" GERMAN_POSTERAZORHELSTEP " 4: " GERMAN_POSTERAZORHELPSTEPTITLE04 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP05 "\">" GERMAN_POSTERAZORHELSTEP " 5: " GERMAN_POSTERAZORHELPSTEPTITLE05 "</A></LI>" POSTERAZORHELPENDLINE \
						"</UL>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORINPUTFILEFORMATS "\">" GERMAN_POSTERAZORHELPINPUTFILEFORMATS "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORWHYPDFOUTPUT "\">" GERMAN_POSTERAZORHELPWHYPDFOUTPUT "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES "\">" GERMAN_POSTERAZORHELPCODEFROMTHIRDPARTIES "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORLICENSE "\">" GERMAN_POSTERAZORHELPLICENSE "</A></B></LI>" POSTERAZORHELPENDLINE \
					"</UL><HR>" POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORABOUT, GERMAN_POSTERAZORHELPABOUT) \
					POSTERAZORHELPINDENTATION "Der PosteRazor schneidet ein Rasterbild in St&uuml;cke, die auf einem Drucker ausgedruckt und zu einem Poster zusammengef&uuml;gt werden k&ouml;nnen. Als Ausgangsbilder werden Dateien in <A href=\"#" POSTERAZORHELPANCHORMANUALSTEP01 "\">vielen</A> Formaten unterst&uuml;tzt. Anstatt das Bild direkt zu drucken, generiert der PosteRazor ein mehrseitiges PDF-Dokument welches die Bildteile enth&auml;lt.<br>" POSTERAZORHELPENDLINE \
					"Es ist ein Open-Source-Programm, das von <a href=\"#" POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES "\">Open-Source-Projekten</a> abh&auml;ngt." POSTERAZORHELPENDLINE \
					"Der PosteRazor ist unter <b>posterazor.sourceforge.net</b> zu finden." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUAL, GERMAN_POSTERAZORHELPMANUAL) \
					POSTERAZORHELPINDENTATION "Der PosteRazor hat eine Benutzerf&uuml;hrung im \"Assistenten\"-Stil. Alle Einstellungen f&uuml;r die Postererstellung werden in f&uuml;nf Schritten erledigt. Die <b>Weiter</b> und <b>Zur&uuml;ck</b>-Kn&ouml;pfe bl&auml;ttern durch diese Schritte.<br>" POSTERAZORHELPENDLINE \
					"Der <b>?</b>-Knopf &ouml;ffnet ein Hilfefenster mit der Beschreibung des aktuellen Schrittes.<br>" POSTERAZORHELPENDLINE \
					"Jedes Eingabefeld f&uuml;r z.B. eine Ma&szlig;angabe, kann wie &uuml;blich mit der Tastatur bearbeitet werden. Die Werte k&ouml;nnen aber auch mit der Maus modifiziert werden, indem auf ein Feld geklickt und die Maus hin &amp; her bewegt wird. Die verschiedenen Mauskn&ouml;pfe ver&auml;ndern die Werte in unterschiedlich gro&zslig;en Schritten.<br>" POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "Der PosteRazor merkt sich jede Eingabe und Auswahl bis zur n&auml;chsten Benutzung des Programms." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORSETTINGS, GERMAN_POSTERAZORHELPSETTINGS) \
					POSTERAZORHELPINDENTATION "Durch klicken des <b>Einstellungen...</b>-Knopfes auf der unteren linken Seite des Hauptdialogs wird der Einstellungs-Dialog des PosteRazors ge&ouml;ffnet." POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>L&auml;ngeneinheit:</b> w&auml;hlen Sie die Einheit. mit der Sie Arbeiten werden. Wird die Einheit ver&auml;ndert, werden alle vorgegeben und die bereits selbst eingegeben Werte im Dialog in die neue Einheit umgerechnet.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Sprache:</b> w&auml;hlen Sie Ihre Sprache. Der PosteRazor braucht f&uuml;r die &Auml;nderung der Sprache nicht neu gestartet zu werden.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Vorschau mit OpenGL:</b> bestimmen Sie, ob der PosteRazor OpenGL f&uuml;r die Bild-Vorschau nutzen soll. &Uuml;blicherweise bietet der OpenGL-Modus auf moderner Hardware mehr Geschwindigkeit und ein saubereres als der Modus ohne OpenGL. Aber falls der PosteRazor langsam und ruckelig wirkt, versuchen Sie bitte, ob das Ausschalten von OpenGL Besserung bringt.</LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP01, GERMAN_POSTERAZORHELSTEP " 1: " GERMAN_POSTERAZORHELPSTEPTITLE01) \
					POSTERAZORHELPINDENTATION "Load an image by clicking the button with the open icon and selecting an image file, or by drag & dropping an image file on the PosteRazor. The drag & drop also works in the other steps.<br>" POSTERAZORHELPENDLINE \
					"Many <a href=\"#" POSTERAZORHELPANCHORINPUTFILEFORMATS "\">file formats and image types</a> can be loaded. After loading the image, the most important informations are listed in the <b>Image informations</b> fields." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP02, GERMAN_POSTERAZORHELSTEP " 2: " GERMAN_POSTERAZORHELPSTEPTITLE02) \
					POSTERAZORHELPINDENTATION "Define the paper sheet size that you use in your printer. A standard paper sheet size can be selected from the <b>Format</b> chooser, along with the desired paper sheet <b>Orientation</b>. Alternatively, a custom paper sheet size can be define in the <b>Custom</b> tab. (Please write me an email, if you miss your standard paper size in the chooser)." POSTERAZORHELPENDLINE \
					"Paper borders are defined in the <b>Borders</b> fileds. Even if your printer does need no (or small) paper borders, some border might be needed to have enough area for gluing the final poster tiles together." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP03, GERMAN_POSTERAZORHELSTEP " 3: " GERMAN_POSTERAZORHELPSTEPTITLE03) \
					POSTERAZORHELPINDENTATION "Image tile overlapping is needed to have some tolerance for cutting off the unneded borders from one side. Additionally, like the borders from the previous step, if gives more area for gluing together the final poster tiles." POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "The <b>Overlapping position</b> defines the borders that are intended to be overlapped by the neighbour tiles. The borders on the opposite sides are intended to be cut (except on the outermost tiles)." POSTERAZORHELPENDLINE \
					
					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP04, GERMAN_POSTERAZORHELSTEP " 4: " GERMAN_POSTERAZORHELPSTEPTITLE04) \
					POSTERAZORHELPINDENTATION "Define the final poster size, in one of the following three modes which can be selected by the corresponding radio buttons:<br>" POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>Absolute image size</b>: You want to have a specific size of your poster.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Size in Pages</b>: you want to use whole paper sheets and specify how many of them of them you want to use.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Image Size in percent</b>: your input image has a certain size which is defined by the number of pixels and dpi (dots per Inch) and your want to enlage the image by a certain factor.</LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "The aspect ratio of width and height is always 1:1 and is automatically recalculated. In the preview area, you can see the overlapping areas which are surrounded by light red rectangles." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP05, GERMAN_POSTERAZORHELSTEP " 5: " GERMAN_POSTERAZORHELPSTEPTITLE05) \
					POSTERAZORHELPINDENTATION "Save the poster by clicking the save button and specifying a destination file name. Check or uncheck the <b>PDF application after saving</b>, if the standard PDF handling application that is set in your operating system should be automatically started after the PDF file is saved." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORINPUTFILEFORMATS, GERMAN_POSTERAZORHELPINPUTFILEFORMATS) \
					POSTERAZORHELPINDENTATION "Most of the raster image formats which are supported by FreeImage are also supported by the PosteRazor:<br>" POSTERAZORHELPENDLINE \
					"<b>BMP, DDS files, Dr. Halo, GIF, ICO, IFF, JBIG, JNG, JPEG/JIF, KOALA, LBM, Kodak PhotoCD, MNG, PCX, PBM, PGM, PNG, PPM, PhotoShop PSD, Sun RAS, TARGA, TIFF, WBMP, XBM, XPM.<br></b>" POSTERAZORHELPENDLINE \
					"PosteRazor distinguishes and handles monochrome, greyscale, 4-bit palette, 8-bit palette, 24 bit RGB, and CMYK (only from TIF) images. RGB images with an alpha channel are automatically composed onto a white background." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORWHYPDFOUTPUT, GERMAN_POSTERAZORHELPWHYPDFOUTPUT) \
					POSTERAZORHELPINDENTATION "Why a PDF output and not direct printing? First of all the developer of this program does not know (yet) how to \"send images to the printer\", on the different operating systems, which PosteRazor is aimed for. Also, PDF makes sense, if a poster is razored at home with all the needed time and the day after it is printed on the color laser printer in the office (after everyone else went home)." POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "Why a PDF and not other raster formats as output? PDF gives the possibility to embed the whole image and virtually cut it, and not only between pixels but also with pixel fractions. Aditionally, it seems more practicable to print a multi page PDF file instead of multiple image files." POSTERAZORHELPENDLINE \
					
					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES, GERMAN_POSTERAZORHELPCODEFROMTHIRDPARTIES) \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>FLTK</b> was used for the user interface. It is a small (by size), fast, fun&easy to learn and very portable UI Toolkit. <a href=\"http://www.fltk.org/\">www.fltk.org</a></LI>" POSTERAZORHELPENDLINE \
					"<LI><b>FreeImage</b> was used for the image loading and handling. It makes image loading and handling really a no-brainer and is portable to the platforms, where the PosteRazor runs. <a href=\"http://freeimage.sourceforge.net/\">FreeImage website</a></LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Fl_Native_File_Chooser</b> was used for the file open and save dialog in the native system look and feel. <a href=\"http://seriss.com/people/erco/fltk/Fl_Native_File_Chooser/\">Fl_Native_File_Chooser website</a></LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \
					
					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORLICENSE, GERMAN_POSTERAZORHELPLICENSE) \
					"PosteRazor - Make your own poster!<br>" POSTERAZORHELPENDLINE \
					"<a href=\"http://posterazor.sourceforge.net/\">posterazor.sourceforge.net</a><br>" POSTERAZORHELPENDLINE \
					"Copyright (C) 2005 by Alessandro Portale<br>&nbsp;<br>" POSTERAZORHELPENDLINE \
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
			140,140,140,140,140,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,140,140,140,140,140,140,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,140,140,140,140,140,140,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			140,140,140,140,140,140,247,0,0,243,0,0,243,0,0,243,0,0,243,0,0,243,0,0,243,0,0,
			243,0,0,243,0,0,243,0,0,243,0,0,243,0,0,243,0,0,243,0,0,243,0,0,243,0,0,243,0,0,
			247,0,0,140,140,140,140,140,140,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,
			247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,
			247,0,0,247,0,0,140,140,140,140,140,140,247,0,0,250,0,0,250,0,0,250,0,0,250,0,0,
			250,0,0,250,0,0,250,0,0,250,0,0,250,0,0,250,0,0,250,0,0,250,0,0,250,0,0,250,0,0,
			250,0,0,250,0,0,247,0,0,140,140,140,140,140,140,254,227,1,253,226,1,253,226,1,
			253,226,1,253,226,1,253,226,1,253,226,1,253,226,1,253,226,1,253,226,1,253,226,1,
			253,226,1,253,226,1,253,226,1,253,226,1,253,226,1,253,226,1,254,227,1,140,140,
			140,140,140,140,254,227,1,254,227,1,254,227,1,254,227,1,254,227,1,254,227,1,254,
			227,1,254,227,1,254,227,1,254,227,1,254,227,1,254,227,1,254,227,1,254,227,1,254,
			227,1,254,227,1,254,227,1,254,227,1,140,140,140,140,140,140,254,227,1,254,227,1,
			254,227,1,254,227,1,254,227,1,254,227,1,254,227,1,254,227,1,254,227,1,254,227,1,
			254,227,1,254,227,1,254,227,1,254,227,1,254,227,1,254,227,1,254,227,1,254,227,1,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140
		};

		return flagRGBData;
	}
};

static TranslationGerman german;

#endif