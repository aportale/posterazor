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

#ifndef TranslationDutch_h
#define TranslationDutch_h

#include "TranslationInterface.h"
#include "TranslationConstants.h"

#define DUTCH_POSTERAZORWEBSITEURL POSTERAZORWEBSITEDOMAIN"?lang=dutch"

class TranslationDutch: public TranslationInterface
{
public:
	const char* languageName(void)                    {return "Nederlands";}

	const char* absoluteSize(void)                    {return "Absolute grootte:";}
	const char* allImageFormats(void)                 {return "Alle beeldformaten";}
	const char* back(void)                            {return "Terug";}
	const char* borders(void)                         {return "Marges";}
	const char* bottom(void)                          {return "Onder";}
	const char* bottomLeft(void)                      {return "Linksonder";}
	const char* bottomRight(void)                     {return "Rechtsonder";}
	const char* cancel(void)                          {return "Afbreken";}
	const char* colorType(void)                       {return "Kleurinformatie:";}
	const char* custom(void)                          {return "Op maat";}
	const char* fileCouldNotBeLoaded(void)            {return "Het bestand \"%s\" kan niet geopend worden.";}
	const char* fileCouldNotBeSaved(void)             {return "The File \"%s\" could not be saved.";}
	const char* format(void)                          {return "Formaat:";}
	const char* grayscale(void)                       {return "Grijstinten";}
	const char* height(void)                          {return "Hoogte:";}
	const char* imageAlignment(void)                  {return "Afbeelding uitlijnen";}
	const char* imageInformations(void)               {return "Afbeeldinginformatie";}
	const char* imageSize(void)                       {return "Afbeeldinggrootte";}
	const char* inputImage(void)                      {return "Afbeelding";}
	const char* landscape(void)                       {return "Landschap";}
	const char* language(void)                        {return "Taal";}
	const char* languageExplanation(void)             {return "kies uw taal";}
	const char* launchPDFApplication(void)            {return "De PDF-applicatie opstarten nadat de poster is opgeslagen";}
	const char* left(void)                            {return "Links";}
	const char* loadAnInputImage(void)                {return stepTitle01();}
	const char* monochrome(void)                      {return "Monochroom";}
	const char* next(void)                            {return "Volgende";}
	const char* orientation(void)                     {return "Oriëntatie:";}
	const char* overlappingPosition(void)             {return "Overlappende zijden";}
	const char* overlappingSize(void)                 {return "Overlapping";}
	const char* overwriteFile(void)                   {return "Het bestand '%s' bestaat reeds.\nMoet dit worden overschreven?";}
	const char* pages(void)                           {return "Pagina's";}
	const char* palette(void)                         {return "Palet";}
	const char* paperFormat(void)                     {return "Papierformaat";}
	const char* portrait(void)                        {return "Portret";}
	const char* posteRazorHelp(void)                  {return "PosteRazor Help";}
	const char* posteRazorSettings(void)              {return "PosteRazor instellingen";}
	const char* posteRazorWebSiteURL(void)            {return DUTCH_POSTERAZORWEBSITEURL;}
	const char* posteRazorWebSite(void)               {return "PosteRazor website";}
	const char* previewWithOpenGL(void)               {return "Schermvoorbeeld met OpenGL";}
	const char* previewWithOpenGLExplanation(void)    {return "OpenGL zorgt voor een beter schermvoorbeeld. Bij oude hardware vertraagt OpenGL deze werking.";}
	const char* resolution(void)                      {return "Resolutie:";}
	const char* right(void)                           {return "Rechts";}
	const char* saveThePoster(void)                   {return "De poster opslaan";}
	const char* saveThePosterAs(void)                 {return "De poster opslaan als";}
	const char* settings(void)                        {return "Instellingen...";}
	const char* Size(void)                            {return "Grootte:";}
	const char* sizeInPages(void)                     {return "Grootte in pagina's:";}
	const char* sizeInPercent(void)                   {return "Grootte in percentage:";}
	const char* sizeInPixels(void)                    {return "Formaat (in pixels):";}
	const char* sizeInUnitOfLength(void)              {return "Formaat (in %s):";}
	const char* standard(void)                        {return "Standaard";}
	const char* stepXOfY(void)                        {return "Stap %d van %d";}
	const char* top(void)                             {return "Boven";}
	const char* topLeft(void)                         {return "Linksboven";}
	const char* topRight(void)                        {return "Rechtsboven";}
	const char* unitOfLength(void)                    {return "Lengtemaat";}
	const char* unitOfLengthExplanation(void)         {return "Kies de lengtemaat waarmee gewerkt moet worden";}
	const char* width(void)                           {return "Breedte:";}


#define DUTCH_POSTERAZORHELSTEP                       "Stap"

#define DUTCH_POSTERAZORHELPABOUT                     "Over PosteRazor"
#define DUTCH_POSTERAZORHELPMANUAL                    "Gebruiksaanwijzing"
#define DUTCH_POSTERAZORHELPSETTINGS                  "Instellingen"
#define DUTCH_POSTERAZORHELPSTEPTITLE01               "Kies een afbeelding"
#define DUTCH_POSTERAZORHELPSTEPTITLENOHTML02         "Papierafmeting definiëren"
#define DUTCH_POSTERAZORHELPSTEPTITLE02               "Papierafmeting defini&euml;ren"
#define DUTCH_POSTERAZORHELPSTEPTITLENOHTML03         "Overlapping definiëren"
#define DUTCH_POSTERAZORHELPSTEPTITLE03               "Overlapping defini&euml;ren"
#define DUTCH_POSTERAZORHELPSTEPTITLENOHTML04         "Postergrootte definiëren"
#define DUTCH_POSTERAZORHELPSTEPTITLE04               "Postergrootte defini&euml;ren"
#define DUTCH_POSTERAZORHELPSTEPTITLE05               "Poster opslaan"
#define DUTCH_POSTERAZORHELPINPUTFILEFORMATS          "Ondersteunde bestandsformaten"
#define DUTCH_POSTERAZORHELPWHYPDFOUTPUT              "Waarom PDF als eindbestand?"
#define DUTCH_POSTERAZORHELPCODEFROMTHIRDPARTIES      "Code van derden"
#define DUTCH_POSTERAZORHELPLICENSE                   "Licentie"

	const char* stepTitle01(void)                     {return DUTCH_POSTERAZORHELPSTEPTITLE01;};
	const char* stepTitle02(void)                     {return DUTCH_POSTERAZORHELPSTEPTITLENOHTML02;};
	const char* stepTitle03(void)                     {return DUTCH_POSTERAZORHELPSTEPTITLENOHTML03;};
	const char* stepTitle04(void)                     {return DUTCH_POSTERAZORHELPSTEPTITLENOHTML04;};
	const char* stepTitle05(void)                     {return DUTCH_POSTERAZORHELPSTEPTITLE05;};
	const char* helpHtml(void)
	{
		return	"<HTML>" POSTERAZORHELPENDLINE \
				"<BODY>" POSTERAZORHELPENDLINE \
					"<A name=\"" POSTERAZORHELPANCHORTOP "\"><CENTER><H1>PosteRazor "POSTERAZORVERSION" Help</H1></CENTER></A>" POSTERAZORHELPENDLINE \

					"<H3>Inhoud</H3>" POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORABOUT "\">" DUTCH_POSTERAZORHELPABOUT "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORMANUAL "\">" DUTCH_POSTERAZORHELPMANUAL "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORSETTINGS "\">" DUTCH_POSTERAZORHELPSETTINGS "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<UL>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP01 "\">" DUTCH_POSTERAZORHELSTEP " 1: " DUTCH_POSTERAZORHELPSTEPTITLE01 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP02 "\">" DUTCH_POSTERAZORHELSTEP " 2: " DUTCH_POSTERAZORHELPSTEPTITLE02 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP03 "\">" DUTCH_POSTERAZORHELSTEP " 3: " DUTCH_POSTERAZORHELPSTEPTITLE03 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP04 "\">" DUTCH_POSTERAZORHELSTEP " 4: " DUTCH_POSTERAZORHELPSTEPTITLE04 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP05 "\">" DUTCH_POSTERAZORHELSTEP " 5: " DUTCH_POSTERAZORHELPSTEPTITLE05 "</A></LI>" POSTERAZORHELPENDLINE \
						"</UL>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORINPUTFILEFORMATS "\">" DUTCH_POSTERAZORHELPINPUTFILEFORMATS "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORWHYPDFOUTPUT "\">" DUTCH_POSTERAZORHELPWHYPDFOUTPUT "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES "\">" DUTCH_POSTERAZORHELPCODEFROMTHIRDPARTIES "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORLICENSE "\">" DUTCH_POSTERAZORHELPLICENSE "</A></B></LI>" POSTERAZORHELPENDLINE \
					"</UL><HR>" POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORABOUT, DUTCH_POSTERAZORHELPABOUT) \
					POSTERAZORHELPINDENTATION "PosteRazor deelt gerasterde afbeeldingen op in stukken die, na op een printer te zijn afgedrukt, tot een poster samengevoegd kunnen worden. Als afbeeldingbestand worden <A href=\"#" POSTERAZORHELPANCHORMANUALSTEP01 "\">verschillende</A> bestandsformaten geaccepteerd. In plaats van een directe afdruk maakt PosteRazor eerst een uit meerdere bladzijden bestaand document waarin alle pagina's zijn opgeslagen.<br>" POSTERAZORHELPENDLINE \
					"Het is een Open-Source-Programma, dat op zijn beurt weer van <a href=\"#" POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES "\">Open-Source-Projecten</a> afhankelijk is. " POSTERAZORHELPENDLINE \
					"PosteRazor is onder <b>posterazor.sourceforge.net</b> op internet terug te vinden." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUAL, DUTCH_POSTERAZORHELPMANUAL) \
					POSTERAZORHELPINDENTATION "PosteRazor heeft een gebruikersinterface in de \"Wizard\"-stijl. Alle instellingen voor een poster worden in 5 stappen uitgevoerd. De <b>Volgende</b> en <b>Terug</b> knoppen leiden de gebruiker door het programma.<br>" POSTERAZORHELPENDLINE \
					"De <b>?</b>-knop opent het helpvenster met een omschrijving van de op dat moment gebruikte functie.<br>" POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "PosteRazor houdt elke instelling en selectie vast en onthoudt ze tot een volgend gebruik van het programma." POSTERAZORHELPENDLINE \
					
					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORSETTINGS, DUTCH_POSTERAZORHELPSETTINGS) \
					POSTERAZORHELPINDENTATION "Door te klikken op de <b>Instellingen...</b>-knop, linksonder in het hoofdvenster, wordt het PosteRazor Instellingenmenu geopend." POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>Lengte-eenheid:</b> kies de lengte-eenheid waarmee gewerkt moet worden. Als deze wordt veranderd dan worden alle reeds ingestelde maten omgerekend naar de nieuwe maatvoering.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Taal:</b> kies de taal van de gebruikersinterface. Na het wijzigen van de taal hoeft er niet opnieuw te worden opgestart.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Schermvoorbeeld met OpenGL:</b> kies of OpenGL voor het schermvoorbeeld gebruikt moet worden. Bij gebruik van recente hardware wordt het beeld beter weergegeven. Verschijnt het beeld echter haperend dan moet er niet voor OpenGL gekozen worden. Het beeld mag dan kwalitatief wat minder zijn, de werking van de hardware is beter betrouwbaar.</LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP01, DUTCH_POSTERAZORHELSTEP " 1: " DUTCH_POSTERAZORHELPSTEPTITLE01) \
					POSTERAZORHELPINDENTATION "Kies een afbeelding door op het icoon van de open map te klikken en te zoeken naar de plaats van de afbeelding, of maak gebruik van \"Drag and Drop\". Sleep dan het afbeeldingbestand naar de PosteRazor. Dit \"Drag and Drop\" principe werkt ook bij de andere functies binnen PosteRazor.<br>" POSTERAZORHELPENDLINE \
					"Veel <a href=\"#" POSTERAZORHELPANCHORINPUTFILEFORMATS "\">bestands- en grafische formaten</a> kunnen worden gebruikt. Na het kiezen van het invoerbestand worden de belangrijkste gegevens getoond in het <b> Afbeeldinginformatie</b> venster." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP02, DUTCH_POSTERAZORHELSTEP " 2: " DUTCH_POSTERAZORHELPSTEPTITLE02) \
					POSTERAZORHELPINDENTATION "Kies het papierformaat dat gebruikt wordt in de printer. Standaardafmetingen kunnen bij voorbaat al aangeklikt worden in het <b>Formaat</b> venster, evenals de <b>Ori&euml;ntatie</b> in de lengte of breedte. Eventueel kan een afwijkend formaat gebruikt worden bij de keuze <b>Op maat</b>. (Stuur anders even een email als een bepaalde standaardmaat hier niet bij staat)." POSTERAZORHELPENDLINE \
					"Papiermarges worden vastgelegd in de optie <b>Marges</b>. Ook al heeft een printer geen -of een heel kleine- papiermarge, een redelijke ruimte is toch altijd nog nodig om de vellen aan elkaar te lijmen." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP03, DUTCH_POSTERAZORHELSTEP " 3: " DUTCH_POSTERAZORHELPSTEPTITLE03) \
					POSTERAZORHELPINDENTATION "Gedeeltelijke overlapping is nodig om ruimte te krijgen aan een papierkanzijde. Dit geeft ruimte om de verschillende vellen te verlijmen. " POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "De <b>Overlappende zijden</b> geven de hoeken aan die door het naastliggende vel papier bedekt worden. De tegenoverliggende randen van de opvolgende vellen dienen te worden afgesneden of -geknipt (zonder de buitenmarge dus)." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP04, DUTCH_POSTERAZORHELSTEP " 4: " DUTCH_POSTERAZORHELPSTEPTITLE04) \
					POSTERAZORHELPINDENTATION "Bepaal de uiteindelijke grootte van de poster met gebruikmaking van de volgende instellingen, die via de knoppen gekozen kunnen worden:<br>" POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>Absolute grootte</b>: bepaal de maximale grootte van de poster.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b> Grootte in pagina's</b>: maak gebruik van hele vellen papier en bepaal hoeveel er gebruikt moeten worden.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Grootte in percentage</b>: een afbeelding heeft een zekere grootte, afhankelijk van de hoeveelheid pixels en DPI (dots per Inch). Dit kan vergroot worden met een zekere factor.</LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "De breedte-hoogte verhouding is altijd 1:1 en wordt automatisch herberekend. In het schermvoorbeeld venster worden de overlappende zijden helderrood gemarkeerd. "  POSTERAZORHELPENDLINE \
					"<b>Afbeelding uitlijnen</b> bepaalt de positie van de poster ten opzichte van het totale oppervlak van alle vellen.  Dit kan handig zijn voor papierbesparing van het overgebleven papier." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP05, ENGLISH_POSTERAZORHELSTEP " 5: " DUTCH_POSTERAZORHELPSTEPTITLE05) \
					POSTERAZORHELPINDENTATION "Sla de poster op door te klikken op de brede knop en het ingeven van een nieuwe, voor opslag geschikte bestandsnaam. Vink <b>De PDF-applicatie opstarten.. </b> aan als de opgeslagen poster in de voor het besturingssysteem tot standaard gemaakte PDF-applicatie moet worden opgestart." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORINPUTFILEFORMATS, ENGLISH_POSTERAZORHELPINPUTFILEFORMATS) \
					POSTERAZORHELPINDENTATION "De meeste bestandsformaten die ondersteund worden bij FreeImage, worden ook ondersteund in PosteRazor:<br>" POSTERAZORHELPENDLINE \
					"<b>BMP, DDS files, Dr. Halo, GIF, ICO, IFF, JBIG, JNG, JPEG/JIF, KOALA, LBM, Kodak PhotoCD, MNG, PCX, PBM, PGM, PNG, PPM, PhotoShop PSD, Sun RAS, TARGA, TIFF, WBMP, XBM, XPM.<br></b>" POSTERAZORHELPENDLINE \
					"PosteRazor herkent ook de volgende bestandsformaten en kan ze gebruiken: monochroom, grijstinten, 4-bit palet, 8-bit palet, 24 bit RGB, en CMYK (alleen bij TIF) afbeeldingen. RGB afbeeldingen met een alpha kanaal worden automatisch geconverteerd en getoond op een witte achtergrond." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORWHYPDFOUTPUT, DUTCH_POSTERAZORHELPWHYPDFOUTPUT) \
					POSTERAZORHELPINDENTATION "Waarom een  PDF bestand en niet direct printen? Allereerst weet de ontwerper van dit programma nog niet hoe dit \"send images to the printer\" werkt op verschillende platformen en besturingssystemen waar PosteRazor voor is bedoeld. Echter, het PDF formaat geeft ook een uitstekend resultaat als de poster thuis \"gerazored\" is en als PDF bestand meegenomen wordt naar het werk, om daar op de kleuren laserprinter te worden uitgedraaid (en natuurlijk iedereen al naar huis is...)." POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "Waarom PDF en geen ander bestandsformaat als eindresultaat? PDF geeft de mogelijkheid om meer dan de benodigde gegevens in één bestand op te slaan. PDF geeft ook nog eens de mogelijkheid om hele bestanden in één totaalbestand op te nemen en virtueel te delen, niet alleen in pixels maar ook in fracties van pixels. Ook is het printen van één -uit meerdere pagina’s bestaand- PDF bestand handiger dan meerdere losse afbeeldingen in meerdere bestanden." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES, ENGLISH_POSTERAZORHELPCODEFROMTHIRDPARTIES) \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>FLTK</b> wordt gebruikt in de gebruikersinterface. Het is een klein (in opslag), snel, leuk, eenvoudig te leren en bijzonder uitwisselbare UI Toolkit. Het is te vinden op de <a href=\"http://www.fltk.org/\">www.fltk.org</a> website.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>FreeImage</b> wordt gebruikt voor de grafische afhandeling. Dat maakt het  tonen van bestanden en een grafische weergave simpel en is uitwisselbaar op meerdere platformen waar PosteRazor ook op werkt. Het is te vinden op de <a href=\"http://freeimage.sourceforge.net/\">FreeImage</a> website.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Fl_Native_File_Chooser</b> wordt gebruikt voor het openen en opslaan van bestanden in de vertrouwde \"look and feel\" stijl. Het is te vinden op: <a href=\"http://seriss.com/people/erco/fltk/Fl_Native_File_Chooser/\">Fl Native File Chooser</a> website.</LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORLICENSE, ENGLISH_POSTERAZORHELPLICENSE) \
					"PosteRazor - Make your own poster!<br>" POSTERAZORHELPENDLINE \
					"<a href=\""ENGLISH_POSTERAZORWEBSITEURL"\">posterazor.sourceforge.net</a><br>" POSTERAZORHELPENDLINE \
					"Copyright (C) 2005-2007 by Alessandro Portale<br>&nbsp;<br>" POSTERAZORHELPENDLINE \

					"<b>Dutch/Belgian translation <br>by Erik Wijkamp - Lochem (The Netherlands) (e_wijkamp<b></b>@<b></b>yahoo<b></b>.<b></b>com).</b><br>" POSTERAZORHELPENDLINE \
					"<b>French translation <br>by Martin Loyer (traduction<b></b>@<b></b>loyer<b></b>.<b></b>name).</b><br>" POSTERAZORHELPENDLINE \
					"<b>Polish translation <br>by Grzegorz Wacikowski.</b><br>" POSTERAZORHELPENDLINE \
					"<b>Italian translation <br>by Stefano Nosei (kluster<b></b>@<b></b>imente<b></b>.<b></b>org).</b><br>" POSTERAZORHELPENDLINE \

					"&nbsp;<br>" \

					"This program is free software; you can redistribute it and/or modify it under the terms of the <a href=\"http://www.gnu.org/licenses/gpl.txt\">GNU General Public License</a> as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.<br>&nbsp;<br>" POSTERAZORHELPENDLINE \
					"This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.<br>&nbsp;<br>" POSTERAZORHELPENDLINE \
					"You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA." POSTERAZORHELPENDLINE \

				"</BODY>" POSTERAZORHELPENDLINE \
			"</HTML>";
	}

	const int flagImageWidth(void)                    {return 20;}
	const int flagImageHeight(void)                   {return 11;}
	const unsigned char *flagImageRGBData(void)
	{
		static const unsigned char flagRGBData[] =
		{
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,
			0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,
			255,0,0,140,140,140,140,140,140,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,
			255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,
			255,0,0,255,0,0,140,140,140,140,140,140,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,
			255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,
			255,0,0,255,0,0,255,0,0,140,140,140,140,140,140,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,140,140,140,140,140,140,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,140,140,140,140,140,140,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,140,140,140,140,140,140,28,82,255,28,82,255,28,82,255,
			28,82,255,28,82,255,28,82,255,28,82,255,28,82,255,28,82,255,28,82,255,28,82,
			255,28,82,255,28,82,255,28,82,255,28,82,255,28,82,255,28,82,255,28,82,255,140,
			140,140,140,140,140,28,82,255,28,82,255,28,82,255,28,82,255,28,82,255,28,82,255,
			28,82,255,28,82,255,28,82,255,28,82,255,28,82,255,28,82,255,28,82,255,28,82,
			255,28,82,255,28,82,255,28,82,255,28,82,255,140,140,140,140,140,140,28,82,255,
			28,82,255,28,82,255,28,82,255,28,82,255,28,82,255,28,82,255,28,82,255,28,82,
			255,28,82,255,28,82,255,28,82,255,28,82,255,28,82,255,28,82,255,28,82,255,28,82,
			255,28,82,255,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140
		};

		return flagRGBData;
	}
};

static TranslationDutch dutch;

#endif
