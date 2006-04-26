/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2006 by Alessandro Portale
	http://posterazor.sourceforge.net/

	Polish translation by Grzegorz Wacikowski
	
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

#ifndef TranslationPolish_h
#define TranslationPolish_h

#include "TranslationInterface.h"

class TranslationPolish: public TranslationInterface
{
public:
	const char* LanguageName(void)                    {return "Polski";}

	const char* AbsoluteSize(void)                    {return "Rozmiar ca³kowity:";}
	const char* AllImageFormats(void)                 {return "Wszystkie formaty";}
	const char* Back(void)                            {return "Wróc";}
	const char* Borders(void)                         {return "Marginesy";}
	const char* Bottom(void)                          {return "Dó³";}
	const char* BottomLeft(void)                      {return "Dó³ z lewej";}
	const char* BottomRight(void)                     {return "Dó³ z prawej";}
	const char* Cancel(void)                          {return "Anuluj";}
	const char* ColorType(void)                       {return "Typ koloru:";}
	const char* Custom(void)                          {return "W³asny";}   
	const char* FileCouldNotBeLoaded(void)            {return "Nie mo¿na otworzyæ pliku \"%s\"";}
	const char* Format(void)                          {return "Format:";}
	const char* Grayscale(void)                       {return "Skala szaroœci";}
	const char* Height(void)                          {return "Wysokoœæ:";}
	const char* ImageAlignment(void)                  {return "Ustawienia obrazu";}
	const char* ImageInformations(void)               {return "Informacje o obrazie";}
	const char* ImageSize(void)                       {return "Rozmiar obrazu";}
	const char* InputImage(void)                      {return "Obraz wejœciowy";}
	const char* Landscape(void)                       {return "Poziomo";}
	const char* Language(void)                        {return "Jêzyk";}
	const char* LanguageExplanation(void)             {return "Wybierz jêzyk";}
	const char* LaunchPDFApplication(void)            {return "Uruchom przegladarkê PDF po zapisaniu plakatu";}
	const char* Left(void)                            {return "Lewa";}
	const char* LoadAnInputImage(void)                {return StepTitle01();}
	const char* Monochrome(void)                      {return "Monochromatyczny";}
	const char* Next(void)                            {return "Dalej";}
	const char* Orientation(void)                     {return "Po³o¿enie:";}
	const char* OverlappingPosition(void)             {return "Miejsce zazêbienia";}
	const char* OverlappingSize(void)                 {return "Szerokoœæ zazêbienia";}
	const char* OverwriteFile(void)                   {return "Plik '%s' ju¿ instnieje.\nCzy chcesz go nadpisaæ?";}
	const char* Pages(void)                           {return "strony";}
	const char* PaperFormat(void)                     {return "Rozmiar papieru";}
	const char* Palette(void)                         {return "Paleta";}
	const char* Portrait(void)                        {return "Pionowo";}
	const char* PosteRazorHelp(void)                  {return "PosteRazor pomoc";}
	const char* PosteRazorSettings(void)              {return "PosteRazor ustawienia";}
	const char* PosteRazorWebSite(void)               {return "PosteRazor strona www";}
	const char* PreviewWithOpenGL(void)               {return "Podgl¹d z OpenGL";}
	const char* PreviewWithOpenGLExplanation(void)    {return "OpenGL umo¿liwia p³ynny podgl¹d na nowoczesnych komputerach. Mo¿e wyd³u¿yæ proces podgl¹du na starszych maszynach.";}
	const char* Resolution(void)                      {return "Rozdzielczoœæ:";}
	const char* Right(void)                           {return "Prawa";}
	const char* SaveThePoster(void)                   {return "Zapisz plakat";}
	const char* SaveThePosterAs(void)                 {return "Zapisz plakat jako";}
	const char* Settings(void)                        {return "Ustawienia...";}
	const char* Size(void)                            {return "Rozmiar:";}
	const char* SizeInPages(void)                     {return "Rozmiar na stronie:";}
	const char* SizeInPercent(void)                   {return "Rozmiar w procentach:";}
	const char* SizeInPixels(void)                    {return "Rozmiar (w pikselach):";}
	const char* SizeInUnitOfLength(void)              {return "Rozmiar (w %s):";}
	const char* Standard(void)                        {return "Standard";}
	const char* StepXOfY(void)                        {return "Krok %d z %d";}
	const char* Top(void)                             {return "Góra";}
	const char* TopLeft(void)                         {return "Góra z lewej";}
	const char* TopRight(void)                        {return "Góra z prawej";}
	const char* UnitOfLength(void)                    {return "Jednostka d³ugoœci";}
	const char* UnitOfLengthExplanation(void)         {return "Wybierz miarê d³ugoœci, któej chcesz u¿ywaæ";}
	const char* Width(void)                           {return "Szerokoœæ:";}


#include "PosteRazorHelpConstants.h"

#define POLISH_POSTERAZORHELSTEP                     "Krok"

#define POLISH_POSTERAZORHELPABOUT                   "O programie PosteRazor"
#define POLISH_POSTERAZORHELPMANUAL                  "Manual"
#define POLISH_POSTERAZORHELPSETTINGS                "Ustawienia"
#define POLISH_POSTERAZORHELPSTEPTITLE01             "Za³aduj obraz"
#define POLISH_POSTERAZORHELPSTEPTITLE02             "Ustawienie formatu papieru drukarki"
#define POLISH_POSTERAZORHELPSTEPTITLE03             "Definiowanie zazêbiania siê"
#define POLISH_POSTERAZORHELPSTEPTITLE04             "Ustawienie koñcowego rozmiaru plakatu"
#define POLISH_POSTERAZORHELPSTEPTITLE05             "Zapisz plakat"
#define POLISH_POSTERAZORHELPINPUTFILEFORMATS        "Wspierane pliki wejœciowe"
#define POLISH_POSTERAZORHELPWHYPDFOUTPUT            "Dlaczego na wyjœciu plik PDF?"
#define POLISH_POSTERAZORHELPCODEFROMTHIRDPARTIES    "Dodatkowy kod"
#define POLISH_POSTERAZORHELPLICENSE                 "Licencja"

	const char* StepTitle01(void)                     {return POLISH_POSTERAZORHELPSTEPTITLE01;}
	const char* StepTitle02(void)                     {return POLISH_POSTERAZORHELPSTEPTITLE02;}
	const char* StepTitle03(void)                     {return POLISH_POSTERAZORHELPSTEPTITLE03;}
	const char* StepTitle04(void)                     {return POLISH_POSTERAZORHELPSTEPTITLE04;}
	const char* StepTitle05(void)                     {return POLISH_POSTERAZORHELPSTEPTITLE05;}
	const char* HelpHtml(void)
	{
		return	"<HTML>" POSTERAZORHELPENDLINE \
				"<BODY>" POSTERAZORHELPENDLINE \
					"<A name=\"" POSTERAZORHELPANCHORTOP "\"><CENTER><H1>PosteRazor 1.1 Krok</H1></CENTER></A>" POSTERAZORHELPENDLINE \

					"<H3>Contents</H3>" POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORABOUT "\">" POLISH_POSTERAZORHELPABOUT "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORMANUAL "\">" POLISH_POSTERAZORHELPMANUAL "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORSETTINGS "\">" POLISH_POSTERAZORHELPSETTINGS "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<UL>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP01 "\">" POLISH_POSTERAZORHELSTEP " 1: " POLISH_POSTERAZORHELPSTEPTITLE01 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP02 "\">" POLISH_POSTERAZORHELSTEP " 2: " POLISH_POSTERAZORHELPSTEPTITLE02 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP03 "\">" POLISH_POSTERAZORHELSTEP " 3: " POLISH_POSTERAZORHELPSTEPTITLE03 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP04 "\">" POLISH_POSTERAZORHELSTEP " 4: " POLISH_POSTERAZORHELPSTEPTITLE04 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP05 "\">" POLISH_POSTERAZORHELSTEP " 5: " POLISH_POSTERAZORHELPSTEPTITLE05 "</A></LI>" POSTERAZORHELPENDLINE \
						"</UL>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORINPUTFILEFORMATS "\">" POLISH_POSTERAZORHELPINPUTFILEFORMATS "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORWHYPDFOUTPUT "\">" POLISH_POSTERAZORHELPWHYPDFOUTPUT "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES "\">" POLISH_POSTERAZORHELPCODEFROMTHIRDPARTIES "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORLICENSE "\">" POLISH_POSTERAZORHELPLICENSE "</A></B></LI>" POSTERAZORHELPENDLINE \
					"</UL><HR>" POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORABOUT, POLISH_POSTERAZORHELPABOUT) \
					POSTERAZORHELPINDENTATION "The PosteRazor rozcina obraz rastrowy na kawa³ki, kt&oacute;re mog¹ zostaæ wydrukowane, a nastêpnie po³¹czone w plakat. Jako plik wejœciowy, plik rastrowy sposr&oacute;d <A href=\"#" POSTERAZORHELPANCHORMANUALSTEP01 "\">various</A> plik&oacute;w graficznych o wspieranych formatach. Zamiast bezpoœrednio drukowaæ plakat, the PosteRazor tworzy wielostronicowy plik PDF, kt&oacute;ry zawiera kawalki plakatu.<br>" POSTERAZORHELPENDLINE \
					"Jest to oprogramowanie typu Open Source i zalezy od <a href=\"#" POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES "\">innych projekt&oacute;w tego typu</a>. " POSTERAZORHELPENDLINE \
					"The PosteRazor mo¿na znaleŸæ na <b>posterazor.sourceforge.net</b>." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUAL, POLISH_POSTERAZORHELPMANUAL) \
					POSTERAZORHELPINDENTATION "PosteRazor posiada interfejs u¿ytkownika zbudowanu w oparciu o \"Wizard\". Wszelkie ustawienia plakatu tworzone s¹ w 5 krokach. Przyciski <b>Cofnij</b> i <b>Dalej</b> prowadz¹ przez wizarda.<br>" POSTERAZORHELPENDLINE \
					"Przycisk <b>?</b> otwiera okno pomocy z wyjaœnieniem danego kroku.<br>" POSTERAZORHELPENDLINE \
					"Wszystkie pola wejœciowe, np. rozmiar, itd mog¹ byæ, jak zwykle, modyfikowany przy pomocy klawiatury oraz klikaj¹c i przeci¹gaj¹c myszka w lewo lub w prawo. R&oacute;¿ne przyciski myszy powiêkszaj¹/pomniejszaj¹ wartoœæ w r&oacute;¿nych krokach.<br>" POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "Wszystkie wejœcia i wybory s¹ pamiêtane do nastêpnego u¿ycia PosteRazor." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORSETTINGS, POLISH_POSTERAZORHELPSETTINGS) \
					POSTERAZORHELPINDENTATION "Naciskaj¹c przycisk <b>Ustawienia...</b> po lewej z do³u w menu g³&oacute;wnym, otwierane s¹ ustawienia PosteRazor." POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>Jednostka miary:</b> wybierz jednostkê miary, kt&oacute;r¹ bêdzisz u¿ywaæ w czasie pracy. Gdy jednostka zostanie zmieniona, wszystkie wartoœci zostaj¹ przeliczone automatycznie.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Jêzyk:</b> wybierz sw&oacute;j jêzyk. PosteRazor nie wymaga restartowanie po zmianie jêzyka.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Podgl¹d z OpenGL:</b>Wybierz, Jeœli PosteRazor powinien u¿ywaæ OpenGL do podgl¹du obrazu. Zazwayczaj, w nowych komputerach OpenGL powinien byæ szybszy i dawaæ wiêksz¹ dok³adnoœæ podgl¹du ni¿ komputery nie obs³uguj¹ce OpenGL. Je¿eli PosteRazor wydajê siê pracowaæ wolno i nie reaguje, spr&oacute;buj czy nie bêdzie lepiej pracowa³ po wy³aczeniu OpenGL.</LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP01, POLISH_POSTERAZORHELSTEP " 1: " POLISH_POSTERAZORHELPSTEPTITLE01) \
					POSTERAZORHELPINDENTATION "Za³aduj obraz klikaj¹c na przycisk i wybieraj¹c plik graficzny lub chwytaj¹c i przeciagaj¹c obraz na PosteRazor. Chwyæ i przeci¹gij dzia³a tak¿e w pozosta³ych krokach.<br>" POSTERAZORHELPENDLINE \
					"Wiele <a href=\"#" POSTERAZORHELPANCHORINPUTFILEFORMATS "\">format&oacute;w plik&oacute;w i typ&oacute;w obraz&oacute;w </a> mo¿e zostaæ za³adowanych. Po za³adowaniu obrazu, najwa¿niejsze informacje s¹ wypisane w polu <b>Informacje o obrazie</b> ." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP02, POLISH_POSTERAZORHELSTEP " 2: " POLISH_POSTERAZORHELPSTEPTITLE02) \
					POSTERAZORHELPINDENTATION "Zdefiniuj rozmiar papieru, kt&oacute;rego u¿ywasz w swojej drukarce. Standardowy rozmiar papieru mo¿e byæ wybrany z opcji <b>Format</b> , wraz z po¿¹dan¹  <b>Orientacja</b> papieru. Mo¿na tak¿e zdefiniowaæ w³asny rozmiar papieru w zak³adce <b>W³asny</b> . (Proszê napisz do mnie email, jeœli nie ma jakiegoœ standardowego rozmiaru do wyboru). " POSTERAZORHELPENDLINE \
					"Marginesy s¹ definiowane w polu <b>Marginesy</b>. Nawet jeœli twoja drukarka nie wymaga (choæby ma³ych) margines&oacute;w, jakiœ margines mo¿e byæ konieczny by m&oacute;c skleiæ kawa³ki plakatu w ca³oœæ." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP03, POLISH_POSTERAZORHELSTEP " 3: " POLISH_POSTERAZORHELPSTEPTITLE03) \
					POSTERAZORHELPINDENTATION "Krawêdzie zachodz¹ce s¹ konieczne jako tolerancja w czasie odcianania niepotrzebnych margines&oacute;w. Dodatkowo, tak jak marginesy, daje to wieksz¹ powierzchnie klejenia kawa³k&oacute;w w ca³oœæ. " POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "<b>Miejsce zazêbiania</b> okreœla brzeg jaki bêdzie zachodziæ na siebie z s¹siednim kawa³kiem. Brzegi po drugiej stronie przenaczone do odciêcia (opr&oacute;cz zewnêtrznych kawa³k&oacute;w)." POSTERAZORHELPENDLINE \
					
					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP04, POLISH_POSTERAZORHELSTEP " 4: " POLISH_POSTERAZORHELPSTEPTITLE04) \
					POSTERAZORHELPINDENTATION "Okreœl koñcowy rozmiar plakatu, jako jeden z trzech nastêpuj¹cych tryb&oacute;w, wybranych przyciskiem:<br>" POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>Calkowity rozmiar obrazu</b>: Chcesz mieæ specyficzny rozmiar plakatu.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Rozmiar na stronach</b>: Chcesz u¿yc ca³e strony i okreœliæ ile chcesz ich u¿yæ.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Rozmiar obrazu w procentach</b>: Tw&oacute;j obraz wejœciowy ma okreœlony rozmiar kt&oacute;ry jestdefiniowany przez iloœæ pikseli oraz dpi (kropek na cal) i chcesz powiêkszyæ obraz.</LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "Ratio szerokoœci i wysokoœci jest zawsze 1:1 i jest automatycznie przeliczane. W obszarze podgl¹du, mo¿esz zobaczyæ zazêbiaj¹ce siê powierzchnie, kt&oacute;re s¹ otoczone czerwonymi prostok¹tami. " POSTERAZORHELPENDLINE \
					"<b>Po³o¿enie obrazu</b> ustawia po³o¿enie na kartce. Jest to przydatne jeœli chcesz wkorzystaæ niezu¿yty papier." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP05, POLISH_POSTERAZORHELSTEP " 5: " POLISH_POSTERAZORHELPSTEPTITLE05) \
					POSTERAZORHELPINDENTATION "Zapisz plakat klikaj¹c na przysisk zapisywania i okreœlaj¹c lokalizajcê nowego pliku. SprawdŸ lub nie <b>Uruchom aplikacjê PDF po zapisaniu plakatu</b>, czy standardowa aplikacja PDF zainstalowana w stoim systemie operacyjnym powinna sie urychamiaæ automatycznie po zapisaniu pliku PDF." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORINPUTFILEFORMATS, POLISH_POSTERAZORHELPINPUTFILEFORMATS) \
					POSTERAZORHELPINDENTATION "Wiêkszoœæ obraz&oacute;w rastrowych wspieranych przez FreeImage jest tak¿e wspierana przez PosteRazor:<br>" POSTERAZORHELPENDLINE \
					"<b>BMP, pliki DDS, Dr. Halo, GIF, ICO, IFF, JBIG, JNG, JPEG/JIF, KOALA, LBM, Kodak PhotoCD, MNG, PCX, PBM, PGM, PNG, PPM, PhotoShop PSD, Sun RAS, TARGA, TIFF, WBMP, XBM, XPM.<br></b>" POSTERAZORHELPENDLINE \
					"PosteRazor odr&oacute;¿nia obrazu czarno-bia³e, skalê szaroœci, 4-bitow¹ paletê, 8-bitow¹ paletê, 24 bitowe RGB oraz CMYK (tylko z TIF). Obrazy RGB z kana³em alfa s¹ automatycznie ustawiane na bia³ym tle." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORWHYPDFOUTPUT, POLISH_POSTERAZORHELPWHYPDFOUTPUT) \
					POSTERAZORHELPINDENTATION "Dlaczego wyjœciowe pliki PDF nie s¹ automatycznie drukowane? Po pierwsze tworca programu nie wie jeszcze jak \"wysy³aæ obraz do drukarki\", na r&oacute;znych systemach operacyjnych, gdzie dzia³a PosteRazor. Tak¿e, tworzenie PDF ma sens, jeœli plakat bêdzie wydrukowany i pociêty w domowych warunkach, a nastepnego dnia drukowany na kolorowej drukarce laserowej w pracy (gdy wszyscy inni pojd¹ ju¿ do domu). " POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "Dlaczego PDF a nie inny obraz rastrowy na wyjœciu? PDF dajê mo¿liwoœæ stworzenia the ca³ego obrazu i wirtualne jego pociêcie; nie tylko pomiêdzy pikselami, ale tak¿e w u³amkach pikseli." POSTERAZORHELPENDLINE \
					
					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES, POLISH_POSTERAZORHELPCODEFROMTHIRDPARTIES) \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>FLTK</b> jest u¿ywane do interfejsu urzytkownika. Jest to ma³y (jeœli chodzi o rozmiar), szybki, fun&easy do nauczenia oraz bardzo przenoœny zestaw narzêdzi UI. <a href=\"http://www.fltk.org/\">www.fltk.org</a></LI>" POSTERAZORHELPENDLINE \
					"<LI><b>FreeImage</b> jest u¿ywany do za³adowania i trzymania obrazu. <a href=\"http://freeimage.sourceforge.net/\">FreeImage website</a></LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Fl_Native_File_Chooser</b> jest u¿ywany do otwierania plik&oacute;w i zapisywania. <a href=\"http://seriss.com/people/erco/fltk/Fl_Native_File_Chooser/\">Fl_Native_File_Chooser website</a></LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \
					
					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORLICENSE, POLISH_POSTERAZORHELPLICENSE) \
					"PosteRazor - Stw&oacute;rz sw&oacute;j w³asny plakat!<br>" POSTERAZORHELPENDLINE \
					"<a href=\"http://posterazor.sourceforge.net/\">posterazor.sourceforge.net</a><br>" POSTERAZORHELPENDLINE \
					"Copyright (C) 2005-2006 by Alessandro Portale<br>&nbsp;<br>" POSTERAZORHELPENDLINE \
					"Ten program jest darmowy; mo¿esz go rozprowadzaæ i/lub modyfikowaæ go stosuj¹c siê do warunk&oacute;w na <a href=\"http://www.gnu.org/licenses/gpl.txt\">GNU General Public License</a> opublikowana przed Free Software Foundation; r&oacute;wniez wersja 2 licencji lub ka¿da nastêpna.<br>&nbsp;<br>" POSTERAZORHELPENDLINE \
					"Ten program jest rozprowadzany w nadziei, ¿e bêdzie przydatny,  jednak BEZ ¯ADNEJ GWARANCJI. Zobacz wiêcej detali GNU General Public License.<br>&nbsp;<br>" POSTERAZORHELPENDLINE \
					"Powinieneœ otrzymaæ kopie licencji GNU General Public License wraz z tym programem; jeœli nie, napisz do Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA." POSTERAZORHELPENDLINE \
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

static TranslationPolish polish;

#endif