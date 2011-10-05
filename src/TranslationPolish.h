/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2008 by Alessandro Portale
	http://posterazor.sourceforge.net/

	Polish translation by Grzegorz Wacikowski
	
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

#ifndef TranslationPolish_h
#define TranslationPolish_h

#include "TranslationInterface.h"
#include "TranslationConstants.h"

#define CHAR_Acedilla       "•"
#define CHAR_HTML_Acedilla  "&#165;"
#define CHAR_acedilla       "π"
#define CHAR_HTML_acedilla  "&#185;"

#define CHAR_Cacute         "∆"
#define CHAR_HTML_Cacute    "&#198;"
#define CHAR_cacute         "Ê"
#define CHAR_HTML_cacute    "&#230;"

#define CHAR_Ecedilla       " "
#define CHAR_HTML_Ecedilla  "&#202;"
#define CHAR_ecedilla       "Í"
#define CHAR_HTML_ecedilla  "&#234;"

#define CHAR_Laccent        "£"
#define CHAR_HTML_Laccent   "&#163;"
#define CHAR_laccent        "≥"
#define CHAR_HTML_laccent   "&#179;"

#define CHAR_Nacute         "—"
#define CHAR_HTML_Nacute    "&#209;"
#define CHAR_nacute         "Ò"
#define CHAR_HTML_nacute    "&#241;"

#define CHAR_Oacute         "”"
#define CHAR_HTML_Oacute    "&Oacute;"
#define CHAR_oacute         "Û"
#define CHAR_HTML_oacute    "&oacute;"

#define CHAR_Sacute         "å"
#define CHAR_HTML_Sacute    "&#140;"
#define CHAR_sacute         "ú"
#define CHAR_HTML_sacute    "&#156;"

#define CHAR_Zacute         "è"
#define CHAR_HTML_Zacute    "&#143;"
#define CHAR_zacute         "ü"
#define CHAR_HTML_zacute    "&#159;"

#define CHAR_Zdot           "Ø"
#define CHAR_HTML_Zdot      "&#175;"
#define CHAR_zdot           "ø"
#define CHAR_HTML_zdot      "&#191;"

#define POLISH_POSTERAZORWEBSITEURL POSTERAZORWEBSITEDOMAIN

class TranslationPolish: public TranslationInterface
{
public:
	TranslationPolish() {}

	const char* languageName(void) const                    {return "Polski";}

	const char* absoluteSize(void) const                    {return "Rozmiar ca"CHAR_laccent"kowity:";}
	const char* allImageFormats(void) const                 {return "Wszystkie formaty";}
	const char* back(void) const                            {return "Wr"CHAR_oacute"c";}
	const char* borders(void) const                         {return "Marginesy";}
	const char* bottom(void) const                          {return "D"CHAR_oacute""CHAR_laccent;}
	const char* bottomLeft(void) const                      {return "D"CHAR_oacute""CHAR_laccent" z lewej";}
	const char* bottomRight(void) const                     {return "D"CHAR_oacute""CHAR_laccent" z prawej";}
	const char* cancel(void) const                          {return "Anuluj";}
	const char* colorType(void) const                       {return "Typ koloru:";}
	const char* custom(void) const                          {return "W"CHAR_laccent"asny";}   
	const char* fileCouldNotBeLoaded(void) const            {return "Nie mo"CHAR_zdot"na otworzy"CHAR_cacute" pliku \"%s\"";}
	const char* fileCouldNotBeSaved(void) const             {return "The File \"%s\" could not be saved.";}
	const char* format(void) const                          {return "Format:";}
	const char* grayscale(void) const                       {return "Skala szaro"CHAR_sacute"ci";}
	const char* height(void) const                          {return "Wysoko"CHAR_sacute""CHAR_cacute":";}
	const char* imageAlignment(void) const                  {return "Ustawienia obrazu";}
	const char* imageInformations(void) const               {return "Informacje o obrazie";}
	const char* imageSize(void) const                       {return "Rozmiar obrazu";}
	const char* inputImage(void) const                      {return "Obraz wej"CHAR_sacute"ciowy";}
	const char* landscape(void) const                       {return "Poziomo";}
	const char* language(void) const                        {return "J"CHAR_ecedilla"zyk";}
	const char* languageExplanation(void) const             {return "Wybierz j"CHAR_ecedilla"zyk";}
	const char* launchPDFApplication(void) const            {return "Uruchom przegladark"CHAR_ecedilla" PDF po zapisaniu plakatu";}
	const char* left(void) const                            {return "Lewa";}
	const char* loadAnInputImage(void) const                {return stepTitle01();}
	const char* monochrome(void) const                      {return "Monochromatyczny";}
	const char* next(void) const                            {return "Dalej";}
	const char* orientation(void) const                     {return "Po"CHAR_laccent"o"CHAR_zdot"enie:";}
	const char* overlappingPosition(void) const             {return "Miejsce zaz"CHAR_ecedilla"bienia";}
	const char* overlappingSize(void) const                 {return "Szeroko"CHAR_sacute""CHAR_cacute" zaz"CHAR_ecedilla"bienia";}
	const char* overwriteFile(void) const                   {return "Plik '%s' ju"CHAR_zdot" instnieje.\nCzy chcesz go nadpisa"CHAR_cacute"?";}
	const char* pages(void) const                           {return "strony";}
	const char* paperFormat(void) const                     {return "Rozmiar papieru";}
	const char* palette(void) const                         {return "Paleta";}
	const char* portrait(void) const                        {return "Pionowo";}
	const char* posteRazorHelp(void) const                  {return "PosteRazor pomoc";}
	const char* posteRazorSettings(void) const              {return "PosteRazor ustawienia";}
	const char* posteRazorWebSiteURL(void) const            {return POLISH_POSTERAZORWEBSITEURL;}
	const char* posteRazorWebSite(void) const               {return "PosteRazor strona www";}
	const char* previewWithOpenGL(void) const               {return "Podgl"CHAR_acedilla"d z OpenGL";}
	const char* previewWithOpenGLExplanation(void) const    {return "OpenGL umo"CHAR_zdot"liwia p"CHAR_laccent"ynny podgl"CHAR_acedilla"d na nowoczesnych komputerach. Mo"CHAR_zdot"e wyd"CHAR_laccent"u"CHAR_zdot"y"CHAR_cacute" proces podgl"CHAR_acedilla"du na starszych maszynach.";}
	const char* resolution(void) const                      {return "Rozdzielczo"CHAR_sacute""CHAR_cacute":";}
	const char* right(void) const                           {return "Prawa";}
	const char* saveThePoster(void) const                   {return "Zapisz plakat";}
	const char* saveThePosterAs(void) const                 {return "Zapisz plakat jako";}
	const char* settings(void) const                        {return "Ustawienia...";}
	const char* Size(void) const                            {return "Rozmiar:";}
	const char* sizeInPages(void) const                     {return "Rozmiar na stronie:";}
	const char* sizeInPercent(void) const                   {return "Rozmiar w procentach:";}
	const char* sizeInPixels(void) const                    {return "Rozmiar:";} // (w pikselach)
	const char* sizeInUnitOfLength(void) const              {return "Rozmiar (w %s):";}
	const char* standard(void) const                        {return "Standard";}
	const char* stepXOfY(void) const                        {return "Krok %d z %d";}
	const char* top(void) const                             {return "G"CHAR_oacute"ra";}
	const char* topLeft(void) const                         {return "G"CHAR_oacute"ra z lewej";}
	const char* topRight(void) const                        {return "G"CHAR_oacute"ra z prawej";}
	const char* unitOfLength(void) const                    {return "Jednostka d"CHAR_laccent"ugo"CHAR_sacute"ci";}
	const char* unitOfLengthExplanation(void) const         {return "Wybierz miar"CHAR_ecedilla" d"CHAR_laccent"ugo"CHAR_sacute"ci, kt"CHAR_oacute"ej chcesz u"CHAR_zdot"ywa"CHAR_cacute"";}
	const char* width(void) const                           {return "Szeroko"CHAR_sacute""CHAR_cacute":";}


#define POLISH_POSTERAZORHELSTEP                     "Krok"

#define POLISH_POSTERAZORHELPABOUT                   "O programie PosteRazor"
#define POLISH_POSTERAZORHELPMANUAL                  "Manual"
#define POLISH_POSTERAZORHELPSETTINGS                "Ustawienia"
#define POLISH_POSTERAZORHELPSTEPTITLE01             "Za"CHAR_HTML_laccent"aduj obraz"
#define POLISH_POSTERAZORHELPSTEPTITLENOHTML01       "Za"CHAR_laccent"aduj obraz"
#define POLISH_POSTERAZORHELPSTEPTITLE02             "Ustawienie formatu papieru drukarki"
#define POLISH_POSTERAZORHELPSTEPTITLE03             "Definiowanie zaz"CHAR_HTML_ecedilla"biania si"CHAR_HTML_ecedilla""
#define POLISH_POSTERAZORHELPSTEPTITLENOHTML03       "Definiowanie zaz"CHAR_ecedilla"biania si"CHAR_ecedilla""
#define POLISH_POSTERAZORHELPSTEPTITLE04             "Ustawienie ko"CHAR_HTML_nacute"cowego rozmiaru plakatu"
#define POLISH_POSTERAZORHELPSTEPTITLENOHTML04       "Ustawienie ko"CHAR_nacute"cowego rozmiaru plakatu"
#define POLISH_POSTERAZORHELPSTEPTITLE05             "Zapisz plakat"
#define POLISH_POSTERAZORHELPINPUTFILEFORMATS        "Wspierane pliki wej"CHAR_HTML_sacute"ciowe"
#define POLISH_POSTERAZORHELPWHYPDFOUTPUT            "Dlaczego na wyj"CHAR_HTML_sacute"ciu plik PDF?"
#define POLISH_POSTERAZORHELPCODEFROMTHIRDPARTIES    "Dodatkowy kod"
#define POLISH_POSTERAZORHELPLICENSE                 "Licencja"

	const char* stepTitle01(void) const                     {return POLISH_POSTERAZORHELPSTEPTITLENOHTML01;}
	const char* stepTitle02(void) const                     {return POLISH_POSTERAZORHELPSTEPTITLE02;}
	const char* stepTitle03(void) const                     {return POLISH_POSTERAZORHELPSTEPTITLENOHTML03;}
	const char* stepTitle04(void) const                     {return POLISH_POSTERAZORHELPSTEPTITLENOHTML04;}
	const char* stepTitle05(void) const                     {return POLISH_POSTERAZORHELPSTEPTITLE05;}
	const char* helpHtml(void) const
	{
		return	"<HTML>" POSTERAZORHELPENDLINE \
				"<BODY>" POSTERAZORHELPENDLINE \
					"<A name=\"" POSTERAZORHELPANCHORTOP "\"><CENTER><H1>PosteRazor "POSTERAZORVERSION" Krok</H1></CENTER></A>" POSTERAZORHELPENDLINE \

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
					POSTERAZORHELPINDENTATION "The PosteRazor rozcina obraz rastrowy na kawa"CHAR_HTML_laccent"ki, kt"CHAR_HTML_oacute"re mog"CHAR_HTML_acedilla" zosta"CHAR_HTML_cacute" wydrukowane, a nast"CHAR_HTML_ecedilla"pnie po"CHAR_HTML_laccent""CHAR_HTML_acedilla"czone w plakat. Jako plik wej"CHAR_HTML_sacute"ciowy, plik rastrowy sposr"CHAR_HTML_oacute"d <A href=\"#" POSTERAZORHELPANCHORMANUALSTEP01 "\">various</A> plik"CHAR_HTML_oacute"w graficznych o wspieranych formatach. Zamiast bezpo"CHAR_HTML_sacute"rednio drukowa"CHAR_HTML_cacute" plakat, the PosteRazor tworzy wielostronicowy plik PDF, kt"CHAR_HTML_oacute"ry zawiera kawalki plakatu.<br>" POSTERAZORHELPENDLINE \
					"Jest to oprogramowanie typu Open Source i zalezy od <a href=\"#" POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES "\">innych projekt"CHAR_HTML_oacute"w tego typu</a>. " POSTERAZORHELPENDLINE \
					"The PosteRazor mo"CHAR_HTML_zdot"na znale"CHAR_HTML_zacute""CHAR_HTML_cacute" na <b>posterazor.sourceforge.net</b>." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUAL, POLISH_POSTERAZORHELPMANUAL) \
					POSTERAZORHELPINDENTATION "PosteRazor posiada interfejs u"CHAR_HTML_zdot"ytkownika zbudowanu w oparciu o \"Wizard\". Wszelkie ustawienia plakatu tworzone s"CHAR_HTML_acedilla" w 5 krokach. Przyciski <b>Wr"CHAR_HTML_oacute"c</b> i <b>Dalej</b> prowadz"CHAR_HTML_acedilla" przez wizarda.<br>" POSTERAZORHELPENDLINE \
					"Przycisk <b>?</b> otwiera okno pomocy z wyja"CHAR_HTML_sacute"nieniem danego kroku.<br>" POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "Wszystkie wej"CHAR_HTML_sacute"cia i wybory s"CHAR_HTML_acedilla" pami"CHAR_HTML_ecedilla"tane do nast"CHAR_HTML_ecedilla"pnego u"CHAR_HTML_zdot"ycia PosteRazor." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORSETTINGS, POLISH_POSTERAZORHELPSETTINGS) \
					POSTERAZORHELPINDENTATION "Naciskaj"CHAR_HTML_acedilla"c przycisk <b>Ustawienia...</b> po lewej z do"CHAR_HTML_laccent"u w menu g"CHAR_HTML_laccent""CHAR_HTML_oacute"wnym, otwierane s"CHAR_HTML_acedilla" ustawienia PosteRazor." POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>Jednostka miary:</b> wybierz jednostk"CHAR_HTML_ecedilla" miary, kt"CHAR_HTML_oacute"r"CHAR_HTML_acedilla" b"CHAR_HTML_ecedilla"dzisz u"CHAR_HTML_zdot"ywa"CHAR_HTML_cacute" w czasie pracy. Gdy jednostka zostanie zmieniona, wszystkie warto"CHAR_HTML_sacute"ci zostaj"CHAR_HTML_acedilla" przeliczone automatycznie.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>J"CHAR_HTML_ecedilla"zyk:</b> wybierz sw"CHAR_HTML_oacute"j j"CHAR_HTML_ecedilla"zyk. PosteRazor nie wymaga restartowanie po zmianie j"CHAR_HTML_ecedilla"zyka.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Podgl"CHAR_HTML_acedilla"d z OpenGL:</b> Wybierz, Je"CHAR_HTML_sacute"li PosteRazor powinien u"CHAR_HTML_zdot"ywa"CHAR_HTML_cacute" OpenGL do podgl"CHAR_HTML_acedilla"du obrazu. Zazwayczaj, w nowych komputerach OpenGL powinien by"CHAR_HTML_cacute" szybszy i dawa"CHAR_HTML_cacute" wi"CHAR_HTML_ecedilla"ksz"CHAR_HTML_acedilla" dok"CHAR_HTML_laccent"adno"CHAR_HTML_sacute""CHAR_HTML_cacute" podgl"CHAR_HTML_acedilla"du ni"CHAR_HTML_zdot" komputery nie obs"CHAR_HTML_laccent"uguj"CHAR_HTML_acedilla"ce OpenGL. Je"CHAR_HTML_zdot"eli PosteRazor wydaj"CHAR_HTML_ecedilla" si"CHAR_HTML_ecedilla" pracowa"CHAR_HTML_cacute" wolno i nie reaguje, spr"CHAR_HTML_oacute"buj czy nie b"CHAR_HTML_ecedilla"dzie lepiej pracowa"CHAR_HTML_laccent" po wy"CHAR_HTML_laccent"aczeniu OpenGL.</LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP01, POLISH_POSTERAZORHELSTEP " 1: " POLISH_POSTERAZORHELPSTEPTITLE01) \
/* polish html character test line		POSTERAZORHELPINDENTATION CHAR_HTML_Acedilla""CHAR_HTML_acedilla""CHAR_HTML_Cacute""CHAR_HTML_cacute""CHAR_HTML_Ecedilla""CHAR_HTML_ecedilla""CHAR_HTML_Laccent""CHAR_HTML_laccent""CHAR_HTML_Nacute""CHAR_HTML_nacute""CHAR_HTML_Oacute""CHAR_HTML_oacute""CHAR_HTML_Sacute""CHAR_HTML_sacute""CHAR_HTML_Zacute""CHAR_HTML_zacute""CHAR_HTML_Zdot""CHAR_HTML_zdot"<br>" POSTERAZORHELPENDLINE \ */
					POSTERAZORHELPINDENTATION "Za"CHAR_HTML_laccent"aduj obraz klikaj"CHAR_HTML_acedilla"c na przycisk i wybieraj"CHAR_HTML_acedilla"c plik graficzny lub chwytaj"CHAR_HTML_acedilla"c i przeciagaj"CHAR_HTML_acedilla"c obraz na PosteRazor. Chwy"CHAR_HTML_cacute" i przeci"CHAR_HTML_acedilla"gij dzia"CHAR_HTML_laccent"a tak"CHAR_HTML_zdot"e w pozosta"CHAR_HTML_laccent"ych krokach.<br>" POSTERAZORHELPENDLINE \
					"Wiele <a href=\"#" POSTERAZORHELPANCHORINPUTFILEFORMATS "\">format"CHAR_HTML_oacute"w plik"CHAR_HTML_oacute"w i typ"CHAR_HTML_oacute"w obraz"CHAR_HTML_oacute"w </a> mo"CHAR_HTML_zdot"e zosta"CHAR_HTML_cacute" za"CHAR_HTML_laccent"adowanych. Po za"CHAR_HTML_laccent"adowaniu obrazu, najwa"CHAR_HTML_zdot"niejsze informacje s"CHAR_HTML_acedilla" wypisane w polu <b>Informacje o obrazie</b>." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP02, POLISH_POSTERAZORHELSTEP " 2: " POLISH_POSTERAZORHELPSTEPTITLE02) \
					POSTERAZORHELPINDENTATION "Zdefiniuj rozmiar papieru, kt"CHAR_HTML_oacute"rego u"CHAR_HTML_zdot"ywasz w swojej drukarce. Standardowy rozmiar papieru mo"CHAR_HTML_zdot"e by"CHAR_HTML_cacute" wybrany z opcji <b>Format</b>, wraz z po"CHAR_HTML_zdot""CHAR_HTML_acedilla"dan"CHAR_HTML_acedilla"  <b>Orientacja</b> papieru. Mo"CHAR_HTML_zdot"na tak"CHAR_HTML_zdot"e zdefiniowa"CHAR_HTML_cacute" w"CHAR_HTML_laccent"asny rozmiar papieru w zak"CHAR_HTML_laccent"adce <b>W"CHAR_HTML_laccent"asny</b>. (Prosz"CHAR_HTML_ecedilla" napisz do mnie email, je"CHAR_HTML_sacute"li nie ma jakiego"CHAR_HTML_sacute" standardowego rozmiaru do wyboru). " POSTERAZORHELPENDLINE \
					"Marginesy s"CHAR_HTML_acedilla" definiowane w polu <b>Marginesy</b>. Nawet je"CHAR_HTML_sacute"li twoja drukarka nie wymaga (cho"CHAR_HTML_cacute"by ma"CHAR_HTML_laccent"ych) margines"CHAR_HTML_oacute"w, jaki"CHAR_HTML_sacute" margines mo"CHAR_HTML_zdot"e by"CHAR_HTML_cacute" konieczny by m"CHAR_HTML_oacute"c sklei"CHAR_HTML_cacute" kawa"CHAR_HTML_laccent"ki plakatu w ca"CHAR_HTML_laccent"o"CHAR_HTML_sacute""CHAR_HTML_cacute"." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP03, POLISH_POSTERAZORHELSTEP " 3: " POLISH_POSTERAZORHELPSTEPTITLE03) \
					POSTERAZORHELPINDENTATION "Kraw"CHAR_HTML_ecedilla"dzie zachodz"CHAR_HTML_acedilla"ce s"CHAR_HTML_acedilla" konieczne jako tolerancja w czasie odcianania niepotrzebnych margines"CHAR_HTML_oacute"w. Dodatkowo, tak jak marginesy, daje to wieksz"CHAR_HTML_acedilla" powierzchnie klejenia kawa"CHAR_HTML_laccent"k"CHAR_HTML_oacute"w w ca"CHAR_HTML_laccent"o"CHAR_HTML_sacute""CHAR_HTML_cacute". " POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "<b>Miejsce zaz"CHAR_HTML_ecedilla"biania</b> okre"CHAR_HTML_sacute"la brzeg jaki b"CHAR_HTML_ecedilla"dzie zachodzi"CHAR_HTML_cacute" na siebie z s"CHAR_HTML_acedilla"siednim kawa"CHAR_HTML_laccent"kiem. Brzegi po drugiej stronie przenaczone do odci"CHAR_HTML_ecedilla"cia (opr"CHAR_HTML_oacute"cz zewn"CHAR_HTML_ecedilla"trznych kawa"CHAR_HTML_laccent"k"CHAR_HTML_oacute"w)." POSTERAZORHELPENDLINE \
					
					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP04, POLISH_POSTERAZORHELSTEP " 4: " POLISH_POSTERAZORHELPSTEPTITLE04) \
					POSTERAZORHELPINDENTATION "Okre"CHAR_HTML_sacute"l ko"CHAR_HTML_nacute"cowy rozmiar plakatu, jako jeden z trzech nast"CHAR_HTML_ecedilla"puj"CHAR_HTML_acedilla"cych tryb"CHAR_HTML_oacute"w, wybranych przyciskiem:<br>" POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>Calkowity rozmiar obrazu</b>: Chcesz mie"CHAR_HTML_cacute" specyficzny rozmiar plakatu.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Rozmiar na stronach</b>: Chcesz u"CHAR_HTML_zdot"yc ca"CHAR_HTML_laccent"e strony i okre"CHAR_HTML_sacute"li"CHAR_HTML_cacute" ile chcesz ich u"CHAR_HTML_zdot"y"CHAR_HTML_cacute".</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Rozmiar obrazu w procentach</b>: Tw"CHAR_HTML_oacute"j obraz wej"CHAR_HTML_sacute"ciowy ma okre"CHAR_HTML_sacute"lony rozmiar kt"CHAR_HTML_oacute"ry jestdefiniowany przez ilo"CHAR_HTML_sacute""CHAR_HTML_cacute" pikseli oraz dpi (kropek na cal) i chcesz powi"CHAR_HTML_ecedilla"kszy"CHAR_HTML_cacute" obraz.</LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "Ratio szeroko"CHAR_HTML_sacute"ci i wysoko"CHAR_HTML_sacute"ci jest zawsze 1:1 i jest automatycznie przeliczane. W obszarze podgl"CHAR_HTML_acedilla"du, mo"CHAR_HTML_zdot"esz zobaczy"CHAR_HTML_cacute" zaz"CHAR_HTML_ecedilla"biaj"CHAR_HTML_acedilla"ce si"CHAR_HTML_ecedilla" powierzchnie, kt"CHAR_HTML_oacute"re s"CHAR_HTML_acedilla" otoczone czerwonymi prostok"CHAR_HTML_acedilla"tami. " POSTERAZORHELPENDLINE \
					"<b>Po"CHAR_HTML_laccent"o"CHAR_HTML_zdot"enie obrazu</b> ustawia po"CHAR_HTML_laccent"o"CHAR_HTML_zdot"enie na kartce. Jest to przydatne je"CHAR_HTML_sacute"li chcesz wkorzysta"CHAR_HTML_cacute" niezu"CHAR_HTML_zdot"yty papier." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP05, POLISH_POSTERAZORHELSTEP " 5: " POLISH_POSTERAZORHELPSTEPTITLE05) \
					POSTERAZORHELPINDENTATION "Zapisz plakat klikaj"CHAR_HTML_acedilla"c na przysisk zapisywania i okre"CHAR_HTML_sacute"laj"CHAR_HTML_acedilla"c lokalizajc"CHAR_HTML_ecedilla" nowego pliku. Sprawd"CHAR_HTML_zacute" lub nie <b>Uruchom aplikacj"CHAR_HTML_ecedilla" PDF po zapisaniu plakatu</b>, czy standardowa aplikacja PDF zainstalowana w stoim systemie operacyjnym powinna sie urychamia"CHAR_HTML_cacute" automatycznie po zapisaniu pliku PDF." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORINPUTFILEFORMATS, POLISH_POSTERAZORHELPINPUTFILEFORMATS) \
					POSTERAZORHELPINDENTATION "Wi"CHAR_HTML_ecedilla"kszo"CHAR_HTML_sacute""CHAR_HTML_cacute" obraz"CHAR_HTML_oacute"w rastrowych wspieranych przez FreeImage jest tak"CHAR_HTML_zdot"e wspierana przez PosteRazor:<br>" POSTERAZORHELPENDLINE \
					"<b>BMP, pliki DDS, Dr. Halo, GIF, ICO, IFF, JBIG, JPEG/JIF, KOALA, LBM, Kodak PhotoCD, PCX, PBM, PGM, PNG, PPM, PhotoShop PSD, Sun RAS, TARGA, TIFF, WBMP, XBM, XPM.<br></b>" POSTERAZORHELPENDLINE \
					"PosteRazor odr"CHAR_HTML_oacute""CHAR_HTML_zdot"nia obrazu czarno-bia"CHAR_HTML_laccent"e, skal"CHAR_HTML_ecedilla" szaro"CHAR_HTML_sacute"ci, 4-bitow"CHAR_HTML_acedilla" palet"CHAR_HTML_ecedilla", 8-bitow"CHAR_HTML_acedilla" palet"CHAR_HTML_ecedilla", 24 bitowe RGB oraz CMYK (tylko z TIF). Obrazy RGB z kana"CHAR_HTML_laccent"em alfa s"CHAR_HTML_acedilla" automatycznie ustawiane na bia"CHAR_HTML_laccent"ym tle." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORWHYPDFOUTPUT, POLISH_POSTERAZORHELPWHYPDFOUTPUT) \
					POSTERAZORHELPINDENTATION "Dlaczego wyj"CHAR_HTML_sacute"ciowe pliki PDF nie s"CHAR_HTML_acedilla" automatycznie drukowane? Po pierwsze tworca programu nie wie jeszcze jak \"wysy"CHAR_HTML_laccent"a"CHAR_HTML_cacute" obraz do drukarki\", na r"CHAR_HTML_oacute"znych systemach operacyjnych, gdzie dzia"CHAR_HTML_laccent"a PosteRazor. Tak"CHAR_HTML_zdot"e, tworzenie PDF ma sens, je"CHAR_HTML_sacute"li plakat b"CHAR_HTML_ecedilla"dzie wydrukowany i poci"CHAR_HTML_ecedilla"ty w domowych warunkach, a nastepnego dnia drukowany na kolorowej drukarce laserowej w pracy (gdy wszyscy inni pojd"CHAR_HTML_acedilla" ju"CHAR_HTML_zdot" do domu). " POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "Dlaczego PDF a nie inny obraz rastrowy na wyj"CHAR_HTML_sacute"ciu? PDF daj"CHAR_HTML_ecedilla" mo"CHAR_HTML_zdot"liwo"CHAR_HTML_sacute""CHAR_HTML_cacute" stworzenia the ca"CHAR_HTML_laccent"ego obrazu i wirtualne jego poci"CHAR_HTML_ecedilla"cie; nie tylko pomi"CHAR_HTML_ecedilla"dzy pikselami, ale tak"CHAR_HTML_zdot"e w u"CHAR_HTML_laccent"amkach pikseli." POSTERAZORHELPENDLINE \
					
					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES, POLISH_POSTERAZORHELPCODEFROMTHIRDPARTIES) \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>FLTK</b> jest u"CHAR_HTML_zdot"ywane do interfejsu urzytkownika. Jest to ma"CHAR_HTML_laccent"y (je"CHAR_HTML_sacute"li chodzi o rozmiar), szybki, fun&easy do nauczenia oraz bardzo przeno"CHAR_HTML_sacute"ny zestaw narz"CHAR_HTML_ecedilla"dzi UI. <a href=\"http://www.fltk.org/\">www.fltk.org</a></LI>" POSTERAZORHELPENDLINE \
					"<LI><b>FreeImage</b> jest u"CHAR_HTML_zdot"ywany do za"CHAR_HTML_laccent"adowania i trzymania obrazu. <a href=\"http://freeimage.sourceforge.net/\">FreeImage website</a></LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Fl_Native_File_Chooser</b> jest u"CHAR_HTML_zdot"ywany do otwierania plik"CHAR_HTML_oacute"w i zapisywania. <a href=\"http://seriss.com/people/erco/fltk/Fl_Native_File_Chooser/\">Fl_Native_File_Chooser website</a></LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \
					
					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORLICENSE, POLISH_POSTERAZORHELPLICENSE) \
					"PosteRazor - Stw"CHAR_HTML_oacute"rz sw"CHAR_HTML_oacute"j w"CHAR_HTML_laccent"asny plakat!<br>" POSTERAZORHELPENDLINE \
					"<a href=\""POLISH_POSTERAZORWEBSITEURL"\">posterazor.sourceforge.net</a><br>" POSTERAZORHELPENDLINE \
					POSTERAZORCOPYRIGHT \

					POSTERAZORTRANSLATIONCREDITSSTART \
					POSTERAZORTRANSLATIONCREDITSPOLISH \
					POSTERAZORTRANSLATIONCREDITSFRENCH \
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
	const int flagImageHeight(void) const                   {return 12;}
	const unsigned char *flagImageRGBData(void) const
	{
		static const unsigned char flagRGBData[] =
		{
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,140,
			140,140,140,140,140,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,140,
			140,140,140,140,140,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,140,
			140,140,140,140,140,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,140,
			140,140,140,140,140,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,140,
			140,140,140,140,140,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,
			0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,
			255,0,0,140,140,140,140,140,140,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,
			255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,
			255,0,0,255,0,0,140,140,140,140,140,140,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,
			255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,
			255,0,0,255,0,0,255,0,0,140,140,140,140,140,140,255,0,0,255,0,0,255,0,0,255,0,0,
			255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,
			255,0,0,255,0,0,255,0,0,255,0,0,140,140,140,140,140,140,255,0,0,255,0,0,255,0,0,
			255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,
			255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140
		};

		return flagRGBData;
	}
};

static const TranslationPolish polish;

#endif
