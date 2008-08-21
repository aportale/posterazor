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

#ifndef TranslationEnglish_h
#define TranslationEnglish_h

#include "TranslationInterface.h"
#include "TranslationConstants.h"

#define ENGLISH_POSTERAZORWEBSITEURL POSTERAZORWEBSITEDOMAIN

class TranslationEnglish: public TranslationInterface
{
public:
	const char* languageName(void) const                    {return "Suomi";}

	const char* absoluteSize(void) const                    {return "Absoluuttinen koko:";}
	const char* allImageFormats(void) const                 {return "Kaikki kuvamuodot";}
	const char* back(void) const                            {return "Takaisin";}
	const char* borders(void) const                         {return "Reunukset";}
	const char* bottom(void) const                          {return "Ala";}
	const char* bottomLeft(void) const                      {return "Alavasen";}
	const char* bottomRight(void) const                     {return "Alaoikea";}
	const char* cancel(void) const                          {return "Peruuta";}
	const char* colorType(void) const                       {return "Värityyppi:";}
	const char* custom(void) const                          {return "Mukautettu";}
	const char* fileCouldNotBeLoaded(void) const            {return "Tiedostoa \"%s\" ei voida ladata.";}
	const char* fileCouldNotBeSaved(void) const             {return "Tiedostoa \"%s\" ei voida tallentaa.";}
	const char* format(void) const                          {return "Muoto:";}
	const char* grayscale(void) const                       {return "Harmaa";}
	const char* height(void) const                          {return "Korkeus:";}
	const char* imageAlignment(void) const                  {return "Kuvan tasaus";}
	const char* imageInformations(void) const               {return "Kuvan tiedot";}
	const char* imageSize(void) const                       {return "Kuvan koko";}
	const char* inputImage(void) const                      {return "Sisääntulokuva";}
	const char* landscape(void) const                       {return "Vaaka";}
	const char* language(void) const                        {return "Kieli";}
	const char* languageExplanation(void) const             {return "Valitse kielesi";}
	const char* launchPDFApplication(void) const            {return "Käynnistä PDF-ohjelma, kun juliste on tallennettu.";}
	const char* left(void) const                            {return "Vasen";}
	const char* loadAnInputImage(void) const                {return stepTitle01();}
	const char* monochrome(void) const                      {return "Yksivärinen";}
	const char* next(void) const                            {return "Seuraava";}
	const char* orientation(void) const                     {return "Sopeutuminen:";}
	const char* overlappingPosition(void) const             {return "Limityssijainti";}
	const char* overlappingSize(void) const                 {return "Limityskoko";}
	const char* overwriteFile(void) const                   {return "Tiedosto '%s' on jo olemassa.\nHaluatko päällekirjoittaa sen?";}
	const char* pages(void) const                           {return "sivua";}
	const char* paperFormat(void) const                     {return "Paperimuoto";}
	const char* palette(void) const                         {return "Paletti";}
	const char* portrait(void) const                        {return "Muotokuva";}
	const char* posteRazorHelp(void) const                  {return "PosteRazor -ohje";}
	const char* posteRazorSettings(void) const              {return "PosteRazor -asetukset";}
	const char* posteRazorWebSiteURL(void) const            {return ENGLISH_POSTERAZORWEBSITEURL;}
	const char* posteRazorWebSite(void) const               {return "PosteRazor -nettisivu";}
	const char* previewWithOpenGL(void) const               {return "Esikatsele OpenGL:llä";}
	const char* previewWithOpenGLExplanation(void) const    {return "OpenGL antaa tasaisen esikatselun moderneissa järjestelmissä. Se saattaa hidastaa esikatselua vanhoissa järjestelmissä.";}
	const char* resolution(void) const                      {return "Resoluutio:";}
	const char* right(void) const                           {return "Oikea";}
	const char* saveThePoster(void) const                   {return "Tallenna juliste";}
	const char* saveThePosterAs(void) const                 {return "Tallenna juliste nimellä";}
	const char* settings(void) const                        {return "Asetukset...";}
	const char* Size(void) const                            {return "Koko:";}
	const char* sizeInPages(void) const                     {return "Koko sivuina:";}
	const char* sizeInPercent(void) const                   {return "Koko prosentteina:";}
	const char* sizeInPixels(void) const                    {return "Koko (pikseleinä):";}
	const char* sizeInUnitOfLength(void) const              {return "Koko (yksikössä %s):";}
	const char* standard(void) const                        {return "Standardi";}
	const char* stepXOfY(void) const                        {return "Vaihe %d/%d";}
	const char* top(void) const                             {return "Ylä";}
	const char* topLeft(void) const                         {return "Ylävasen";}
	const char* topRight(void) const                        {return "Yläoikea";}
	const char* unitOfLength(void) const                    {return "Pituusyksikkö";}
	const char* unitOfLengthExplanation(void) const         {return "Valitse etäisyysyksikkö työskennelläksesi";}
	const char* width(void) const                           {return "Leveys:";}


#define ENGLISH_POSTERAZORHELSTEP                     "Vaihe"

#define ENGLISH_POSTERAZORHELPABOUT                   "Tietoja PosteRazorista"
#define ENGLISH_POSTERAZORHELPMANUAL                  "Manuaali"
#define ENGLISH_POSTERAZORHELPSETTINGS                "Asetukset"
#define ENGLISH_POSTERAZORHELPSTEPTITLE01             "Lataa sisääntulokuva"
#define ENGLISH_POSTERAZORHELPSTEPTITLE02             "Määritä tulostimen paperimuoto"
#define ENGLISH_POSTERAZORHELPSTEPTITLE03             "Määritä kuvan tiililimitys"
#define ENGLISH_POSTERAZORHELPSTEPTITLE04             "Määritä valmiin julisteen koko"
#define ENGLISH_POSTERAZORHELPSTEPTITLE05             "Tallenna juliste"
#define ENGLISH_POSTERAZORHELPINPUTFILEFORMATS        "Tuetut sisäätulokuvan muodot"
#define ENGLISH_POSTERAZORHELPWHYPDFOUTPUT            "Miksi PDF-ulostulo?"
#define ENGLISH_POSTERAZORHELPCODEFROMTHIRDPARTIES    "Koodi kolmansilta osapuolilta"
#define ENGLISH_POSTERAZORHELPLICENSE                 "Lisenssi"

	const char* stepTitle01(void) const                     {return ENGLISH_POSTERAZORHELPSTEPTITLE01;}
	const char* stepTitle02(void) const                     {return ENGLISH_POSTERAZORHELPSTEPTITLE02;}
	const char* stepTitle03(void) const                     {return ENGLISH_POSTERAZORHELPSTEPTITLE03;}
	const char* stepTitle04(void) const                     {return ENGLISH_POSTERAZORHELPSTEPTITLE04;}
	const char* stepTitle05(void) const                     {return ENGLISH_POSTERAZORHELPSTEPTITLE05;}
	const char* helpHtml(void) const
	{
		return	"<HTML>" POSTERAZORHELPENDLINE \
				"<BODY>" POSTERAZORHELPENDLINE \
					"<A name=\"" POSTERAZORHELPANCHORTOP "\"><CENTER><H1>PosteRazor "POSTERAZORVERSION" Ohje</H1></CENTER></A>" POSTERAZORHELPENDLINE \

					"<H3>Sisältö</H3>" POSTERAZORHELPENDLINE \
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
					POSTERAZORHELPINDENTATION "PosteRazor leikkaa rasterikuvan osiin jotka voidaan tulostaa tulostimella ja sijoittaa yhteen julisteessa. Ulostulokuvana, rasteritiedostot <A href=\"#" POSTERAZORHELPANCHORMANUALSTEP01 "\">monissa</A> eri kuvamuodoissa ovat tuettuja. Suoran tulostamisen sijaan, PosteRazor tuottaa monisivuisia PDF-tiedostoja, jotka sisältävät julisteiden osia.<br>" POSTERAZORHELPENDLINE \
					"Se on vapaan lähdekoodin ohjelma, joka riippuu <a href=\"#" POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES "\">muista vapaan lähdekoodin ohjelmista</a>. " POSTERAZORHELPENDLINE \
					"PosteRazor on hostattu osoitteeseen <b>posterazor.sourceforge.net</b>." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUAL, ENGLISH_POSTERAZORHELPMANUAL) \
					POSTERAZORHELPINDENTATION "PosteRazorissa on käyttöliittymä joka on järjestetty \"Velho\" -tyyppiin. Kaikki julisteenluontivaiheet suoritetaan 5 vaiheessa. Painikkeilla <b>Takaisin</b> ja <b>Seuraava</b>  voidaan navigoida näiden vaiheiden avulla.<br>" POSTERAZORHELPENDLINE \
					"<b>?</b> -painike avaa ohjeikkunan, joka näyttää lisätietoja nykyisestä vaiheesta.<br>" POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "Kaikki syötetyt ja valinnat muistetaan seuraavaan PosteRazorin käyttökertaan." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORSETTINGS, ENGLISH_POSTERAZORHELPSETTINGS) \
					POSTERAZORHELPINDENTATION "Painamalla <b>Asetukset...</b> -painiketta alavasemmalla pääikkunassa, PosteRazor -asetusikkuna avautuu." POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>Pituuden yksikkö:</b> valitse yksikkö jota haluat käyttää, kun työskentelet.
Kun yksikkö muuttuu, kaikki valmiit arvot ja omat arvosi muutetaan uuteen yksikköön.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Kieli:</b> valitse kielesi. PosteRazor ei vaadi uudelleenkäynnistystä, kun kieli muutetaan.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Esikatsele OpenGL:llä:</b> valitse, jos PosteRazor pitää käyttää OpenGL:ää kuvien esikatseluun. Yleensä, moderneilla laitteistoilla OpenGL pitäisi nopeuttaa ja antaa parempi kuva kuin ei-OpenGL -esikatselu. Mutta, jos PosteRazor hidastuu tai muuttuu vastaamattomaksi, kokeile, jos se toimisi paremmin, kun OpenGL onpoistettu.</LI>" POSTERAZORHELPENDLINE \
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
					"<LI><b>Size in pages</b>: you want to use whole paper sheets and specify how many of them of them you want to use.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Image size in percent</b>: your input image has a certain size which is defined by the number of pixels and dpi (dots per Inch) and your want to enlarge the image by a certain factor.</LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "The aspect ratio of width and height is always 1:1 and is automatically recalculated. In the preview area, you can see the overlapping areas which are surrounded by light red rectangles. " POSTERAZORHELPENDLINE \
					"<b>Image alignment</b> sets the alignment of the image on the total paper area of the poster. This is useful if you want to keep the unused paper." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP05, ENGLISH_POSTERAZORHELSTEP " 5: " ENGLISH_POSTERAZORHELPSTEPTITLE05) \
					POSTERAZORHELPINDENTATION "Save the poster by clicking the save button and specifying a destination file name. Check or uncheck the <b>Launch PDF application after the poster is saved</b>, if the standard PDF handling application that is set in your operating system should be automatically started after the PDF file is saved." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORINPUTFILEFORMATS, ENGLISH_POSTERAZORHELPINPUTFILEFORMATS) \
					POSTERAZORHELPINDENTATION "Most of the raster image formats which are supported by FreeImage are also supported by the PosteRazor:<br>" POSTERAZORHELPENDLINE \
					"<b>BMP, DDS files, Dr. Halo, GIF, ICO, IFF, JBIG, JPEG/JIF, KOALA, LBM, Kodak PhotoCD, PCX, PBM, PGM, PNG, PPM, PhotoShop PSD, Sun RAS, TARGA, TIFF, WBMP, XBM, XPM.<br></b>" POSTERAZORHELPENDLINE \
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
					"PosteRazor - Tee oma julisteesi!<br>" POSTERAZORHELPENDLINE \
					"<a href=\""ENGLISH_POSTERAZORWEBSITEURL"\">posterazor.sourceforge.net</a><br>" POSTERAZORHELPENDLINE \
					POSTERAZORCOPYRIGHT \

					POSTERAZORTRANSLATIONCREDITSSTART \
					POSTERAZORTRANSLATIONCREDITSFRENCH \
					POSTERAZORTRANSLATIONCREDITSPOLISH \
					POSTERAZORTRANSLATIONCREDITSDUTCH \
					POSTERAZORTRANSLATIONCREDITSITALIAN \
					POSTERAZORTRANSLATIONCREDITSSPANISH \
					POSTERAZORTRANSLATIONCREDITSBRAZILIANPORTUGUESE \
					POSTERAZORTRANSLATIONCREDITSEND \

					"&nbsp;<br>" \

					POSTERAZORLICENSE \

				"</BODY>" POSTERAZORHELPENDLINE \
			"</HTML>";
	}

	const int flagImageWidth(void) const                    {return 20;}
	const int flagImageHeight(void) const                   {return 11;}
	const unsigned char *flagImageRGBData(void) const
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

static const TranslationEnglish english;

#endif
