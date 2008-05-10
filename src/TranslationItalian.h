/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2007 by Alessandro Portale
	http://posterazor.sourceforge.net/
	
	Italian translation by Stefano Nosei - kluster[at]imente[dot]org

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

#ifndef TranslationItalian_h
#define TranslationItalian_h

#include "TranslationInterface.h"
#include "TranslationConstants.h"

#define ITALIAN_POSTERAZORWEBSITEURL POSTERAZORWEBSITEDOMAIN

class TranslationItalian: public TranslationInterface
{
public:
	const char* languageName(void) const                    {return "Italiano";}

	const char* absoluteSize(void) const                    {return "Dimensioni assolute:";}
	const char* allImageFormats(void) const                 {return "Tutti i formati immagine";}
	const char* back(void) const                            {return "Indietro";}
	const char* borders(void) const                         {return "Bordi";}
	const char* bottom(void) const                          {return "Inferiore";}
	const char* bottomLeft(void) const                      {return "Inferiore sinistro";}
	const char* bottomRight(void) const                     {return "Inferiore destro";}
	const char* cancel(void) const                          {return "Cancella";}
	const char* colorType(void) const                       {return "Tipo di colore:";}
	const char* custom(void) const                          {return "Personalizzato";}
	const char* fileCouldNotBeLoaded(void) const            {return "Il file \"%s\" non può essere caricato.";}
	const char* fileCouldNotBeSaved(void) const             {return "Il file \"%s\" non può essere salvato.";}
	const char* format(void) const                          {return "Formato:";}
	const char* grayscale(void) const                       {return "Scala di grigi";}
	const char* height(void) const                          {return "Altezza:";}
	const char* imageAlignment(void) const                  {return "Allineamento immagine";}
	const char* imageInformations(void) const               {return "Informazioni immagine";}
	const char* imageSize(void) const                       {return "Dimensione immagine";}
	const char* inputImage(void) const                      {return "Immagine sorgente";}
	const char* landscape(void) const                       {return "Landscape";}
	const char* language(void) const                        {return "Linguaggio";}
	const char* languageExplanation(void) const             {return "Selezione il tuo linguaggio";}
	const char* launchPDFApplication(void) const            {return "Lancia l'applicazione PDF dopo che il poster è stato salvato";}
	const char* left(void) const                            {return "Sinistra";}
	const char* loadAnInputImage(void) const                {return stepTitle01();}
	const char* monochrome(void) const                      {return "Monocromatico";}
	const char* next(void) const                            {return "Successivo";}
	const char* orientation(void) const                     {return "Orientamento:";}
	const char* overlappingPosition(void) const             {return "Posizione del sovrapposizionamento";}
	const char* overlappingSize(void) const                 {return "Dimensione del sovrapposizionamento";}
	const char* overwriteFile(void) const                   {return "Il file '%s' esiste già.\nVuoi sovrascriverlo?";}
	const char* pages(void) const                           {return "pagine";}
	const char* paperFormat(void) const                     {return "Formato carta";}
	const char* palette(void) const                         {return "Paletta colori";}
	const char* portrait(void) const                        {return "Portrait";}
	const char* posteRazorHelp(void) const                  {return "Guida PosteRazor";}
	const char* posteRazorSettings(void) const              {return "Impostazioni PosteRazor";}
	const char* posteRazorWebSiteURL(void) const            {return ITALIAN_POSTERAZORWEBSITEURL;}
	const char* posteRazorWebSite(void) const               {return "Sito Web PosteRazor";}
	const char* previewWithOpenGL(void) const               {return "Anteprima con OpenGL";}
	const char* previewWithOpenGLExplanation(void) const    {return "OpenGL permette una più accurata anteprima sui sistemi moderni, sebbene possa risultare più lenta nei computer meno recenti";}
	const char* resolution(void) const                      {return "Risoluzione:";}
	const char* right(void) const                           {return "Destra";}
	const char* saveThePoster(void) const                   {return "Salva il poster";}
	const char* saveThePosterAs(void) const                 {return "Salva il poster come";}
	const char* settings(void) const                        {return "Impostazioni...";}
	const char* Size(void) const                            {return "Dimensione:";}
	const char* sizeInPages(void) const                     {return "Dimensione in pagine";}
	const char* sizeInPercent(void) const                   {return "Dimensione in percentuale:";}
	const char* sizeInPixels(void) const                    {return "Dimens. (in pixels):";}
	const char* sizeInUnitOfLength(void) const              {return "Dimensione (in %s):";}
	const char* standard(void) const                        {return "Standard";}
	const char* stepXOfY(void) const                        {return "Passaggio %d di %d";}
	const char* top(void) const                             {return "Superiore";}
	const char* topLeft(void) const                         {return "Superiore sinistro";}
	const char* topRight(void) const                        {return "Superiore destro";}
	const char* unitOfLength(void) const                    {return "Unità di misura";}
	const char* unitOfLengthExplanation(void) const         {return "Scegli l'unità di misura della distanza con cui intendi lavorare";}
	const char* width(void) const                           {return "Larghezza:";}


#define ITALIAN_POSTERAZORHELSTEP                     "Passaggio"

#define ITALIAN_POSTERAZORHELPABOUT                   "Informazioni su PosteRazor"
#define ITALIAN_POSTERAZORHELPMANUAL                  "Manuale"
#define ITALIAN_POSTERAZORHELPSETTINGS                "Impostazioni"
#define ITALIAN_POSTERAZORHELPSTEPTITLE01             "Carica in immagine"
#define ITALIAN_POSTERAZORHELPSTEPTITLE02             "Definisci il formato pagina della stampante"
#define ITALIAN_POSTERAZORHELPSTEPTITLE03             "Definisci le suddivisioni dell'immagine"
#define ITALIAN_POSTERAZORHELPSTEPTITLE04             "Definisci le dimensioni finali del poster"
#define ITALIAN_POSTERAZORHELPSTEPTITLE05             "Salva il Poster"
#define ITALIAN_POSTERAZORHELPINPUTFILEFORMATS        "Immagine supportate"
#define ITALIAN_POSTERAZORHELPWHYPDFOUTPUT            "Perch&egrave; un output in PDF?"
#define ITALIAN_POSTERAZORHELPCODEFROMTHIRDPARTIES    "Codice da Terze Parti"
#define ITALIAN_POSTERAZORHELPLICENSE                 "Licenza"

	const char* stepTitle01(void) const                     {return ITALIAN_POSTERAZORHELPSTEPTITLE01;}
	const char* stepTitle02(void) const                     {return ITALIAN_POSTERAZORHELPSTEPTITLE02;}
	const char* stepTitle03(void) const                     {return ITALIAN_POSTERAZORHELPSTEPTITLE03;}
	const char* stepTitle04(void) const                     {return ITALIAN_POSTERAZORHELPSTEPTITLE04;}
	const char* stepTitle05(void) const                     {return ITALIAN_POSTERAZORHELPSTEPTITLE05;}
	const char* helpHtml(void) const
	{
		return	"<HTML>" POSTERAZORHELPENDLINE \
				"<BODY>" POSTERAZORHELPENDLINE \
					"<A name=\"" POSTERAZORHELPANCHORTOP "\"><CENTER><H1>PosteRazor "POSTERAZORVERSION" Aiuto</H1></CENTER></A>" POSTERAZORHELPENDLINE \

					"<H3>Contenuti</H3>" POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORABOUT "\">" ITALIAN_POSTERAZORHELPABOUT "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORMANUAL "\">" ITALIAN_POSTERAZORHELPMANUAL "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORSETTINGS "\">" ITALIAN_POSTERAZORHELPSETTINGS "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<UL>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP01 "\">" ITALIAN_POSTERAZORHELSTEP " 1: " ITALIAN_POSTERAZORHELPSTEPTITLE01 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP02 "\">" ITALIAN_POSTERAZORHELSTEP " 2: " ITALIAN_POSTERAZORHELPSTEPTITLE02 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP03 "\">" ITALIAN_POSTERAZORHELSTEP " 3: " ITALIAN_POSTERAZORHELPSTEPTITLE03 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP04 "\">" ITALIAN_POSTERAZORHELSTEP " 4: " ITALIAN_POSTERAZORHELPSTEPTITLE04 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP05 "\">" ITALIAN_POSTERAZORHELSTEP " 5: " ITALIAN_POSTERAZORHELPSTEPTITLE05 "</A></LI>" POSTERAZORHELPENDLINE \
						"</UL>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORINPUTFILEFORMATS "\">" ITALIAN_POSTERAZORHELPINPUTFILEFORMATS "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORWHYPDFOUTPUT "\">" ITALIAN_POSTERAZORHELPWHYPDFOUTPUT "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES "\">" ITALIAN_POSTERAZORHELPCODEFROMTHIRDPARTIES "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORLICENSE "\">" ITALIAN_POSTERAZORHELPLICENSE "</A></B></LI>" POSTERAZORHELPENDLINE \
					"</UL><HR>" POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORABOUT, ITALIAN_POSTERAZORHELPABOUT) \
					POSTERAZORHELPINDENTATION "PosteRazor permette di tagliare un immagine raster in vari pezzi che possono essere stampati e successivamente riuniti creando un poster. Come immagine di ingresso sono supportati <A href=\"#" POSTERAZORHELPANCHORMANUALSTEP01 "\">svariati</A> formati immagine. Invece di stampare direttamente il poster, PosteRazor produce un PDF multipagina che contiene le singole sezioni del poster.<br>" POSTERAZORHELPENDLINE \
					"PosteRazor &egrave; un programma open source che dipende da <a href=\"#" POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES "\">altri progetti open source</a>. " POSTERAZORHELPENDLINE \
					"PosteRazor &egrave; ospitato su <b>posterazor.sourceforge.net</b>." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUAL, ITALIAN_POSTERAZORHELPMANUAL) \
					POSTERAZORHELPINDENTATION "PosteRazor ha la un interfaccia utente organizzata in facili procedure guidate (\"Wizard\"). Le procedure per creare il poster possono essere effettuate  in 5 passaggi. I tasti <b>Precedente</b> and <b>Successivo</b> permettono di navigare attraverso i passaggi.<br>" POSTERAZORHELPENDLINE \
					"Il tasto <b>?</b> apre una finestra di aiuto con una spiegazione sulle operazioni del passaggio corrente.<br>" POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "Tutte le impostazioni e le scelte effettuate dall'utente sono registrate dal programma e rimarranno tali nelle successive riaperture di PosteRazor." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORSETTINGS, ITALIAN_POSTERAZORHELPSETTINGS) \
					POSTERAZORHELPINDENTATION "Premendo il tasto <b>Impostazioni...</b> in basso a sinistra nella finestra principale,  si aprir&agrave; la finestra di configurazione di PosteRazor." POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>Unit&agrave; di Misura:</b> scegli l'unit&agrave; di misura che intendi utilizzare nel tuo lavoro. Quando un'unit&agrave; viene cambiata, tutti i valori predefiniti e quelli precedentemente impostati vengono automaticamente ricalcolati nella nuova unit&agrave;.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Linguaggio:</b> scegli il tuo linguaggio. PosteRazor non necessita di essere riavviato quando viene modificato il linguaggio.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Anteprima con OpenGL:</b> indica a PosteRazor di utilizzare OpenGL per l'anteprima dell'immagine. Di solito, su hardware recente, OpenGL dovrebbe visualizzare l'anteprima in maniera pi&ugrave; veloce ed accurata rispetto al metodo non-OpenGL. In ogni caso se PosteRazor dovesse risultare pi&ugrave; lento e/o instabile, &egrave; indicato disabilitare la modalit&agrave; OpenGL.</LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP01, ITALIAN_POSTERAZORHELSTEP " 1: " ITALIAN_POSTERAZORHELPSTEPTITLE01) \
					POSTERAZORHELPINDENTATION "Carica l'immagine premendo il bottone con l'icona a forma di cartella e seleziona l'immagine di origine. L'immagine pu&ograve; essere anche trascinata all'interno della finestra tramite drag & drop. La procedura di drag & drop funziona anche nei successivi passaggi<br>" POSTERAZORHELPENDLINE \
					"Possono essere caricati svariati <a href=\"#" POSTERAZORHELPANCHORINPUTFILEFORMATS "\">formati di files e tipi di immagini</a> . Dopo il caricamento dell'immagine, le informazioni di dettaglio sono elencate nella casella <b>Informazioni immagine</b>." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP02, ITALIAN_POSTERAZORHELSTEP " 2: " ITALIAN_POSTERAZORHELPSTEPTITLE02) \
					POSTERAZORHELPINDENTATION "Definisce la dimensione del foglio di stampa che viene utilizzato dalla tua stampante. I principali formati standard per stampante possono essere selezionati dalla casella di scelta <b>Formato</b>, cos&igrave; come per l'<b>Orientamento</b>. In alternativa, pu&ograve; essere definito un foglio di stampa personalizzato selezionando la scheda <b>Personalizzato</b>. (Vi prego di comunicarmi via mail, se l'operazione vi facesse perdere il formato foglio standard nella casella di scelta). " POSTERAZORHELPENDLINE \
					"I bordi del foglio sono definiti nella casella <b>Bordi</b>. Sebbene la vostra stampante possa specificatamente stampare senza margini vi consigliamo di lasciare un piccolo bordo per facilitare la successiva incollatura dei pezzi per comporre il poster finale." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP03, ITALIAN_POSTERAZORHELSTEP " 3: " ITALIAN_POSTERAZORHELPSTEPTITLE03) \
					POSTERAZORHELPINDENTATION "La sovrapposizione delle sezioni dell'immagine &egrave; utile per avere un intervallo di tolleranza per tagliare i bordi non necessari sui lati. In aggiunta, come specificato per i bordi nel passo precedente, pu&ograve; permettere un'area pi&ugrave; ampia per l'incollatura finale del poster. " POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "La <b>Posizione del Sovrapposizionamento</b> difinisce i bordi che saranno sovrapposti dalle singole sezioni contigue dell'immagine. I bordi sui lati opposti sono quelli che si intendono tagliare per l'incollatura (ad eccezione delle sezioni di margine esterno)." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP04, ITALIAN_POSTERAZORHELSTEP " 4: " ITALIAN_POSTERAZORHELPSTEPTITLE04) \
					POSTERAZORHELPINDENTATION "Definisci la dimensione finale del poster, in uno dei seguenti tre  metodi che possono essere selezionati marcando i corrispondenti tasti di scelta:<br>" POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>Dimensioni assolute</b> dell'immagine: imposta una dimensione specifica per il tuo poster.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Dimensioni in pagine</b>: imposta in quante pagine totali verr&agrave; ripartita l'immagine da stampare.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Dimensioni immagine in percentuale</b>: l'immagine sorgente selezionata avr&agrave; una specifica dimensione in pixel e in dpi (punti per pollice). Selezionando questa opzione l'immagine sar&agrave; ingrandita in base al fattore percentuale inserito.</LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "La proporzione tra la larghezza e l'altezza &egrave; sempre 1:1 ed &egrave; automaticamente ricalcolata. Nell'area di Anteprima, puoi vedere le aree di sovrapposizionamento che sono marcate da triangoli di color rosso chiaro. " POSTERAZORHELPENDLINE \
					"<b>Allineamento immagine</b> imposta l'allineamento dell'immagine nell'area totale di stampa del poster. Ci&ograve; &egrave; utile se vuoi mantenere parti di pagina non utilizzate." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP05, ITALIAN_POSTERAZORHELSTEP " 5: " ITALIAN_POSTERAZORHELPSTEPTITLE05) \
					POSTERAZORHELPINDENTATION "Salva il poster premendo il bottone con l'icona a forma di floppy e specifica un nome file di destinazione. Marca o smarca il segno di spunta <b>Lancia l'applicazione PDF dopo che il poster &egrave; stato salvato</b>, e l'applicazione impostata come predefinita per il formato PDF verr&agrave; avviata automaticamente dopo il salvataggio del file" POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORINPUTFILEFORMATS, ITALIAN_POSTERAZORHELPINPUTFILEFORMATS) \
					POSTERAZORHELPINDENTATION "La maggior parte delle immagini raster che sono supportate da FreeImage sono supportate anche da PosteRazor:<br>" POSTERAZORHELPENDLINE \
					"<b>BMP, file DDS , Dr. Halo, GIF, ICO, IFF, JBIG, JNG, JPEG/JIF, KOALA, LBM, Kodak PhotoCD, MNG, PCX, PBM, PGM, PNG, PPM, PhotoShop PSD, Sun RAS, TARGA, TIFF, WBMP, XBM, XPM.<br></b>" POSTERAZORHELPENDLINE \
					"PosteRazor distingue e supporta immagini monocromatiche, a scala di grigi, con palette a 4-bit ,8-bit, 24 bit RGB, e quadricromia CMYK (solo per il formato Tif). Le immagini RGB con un canale alpha sono automaticamente composte con sfondo bianco." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORWHYPDFOUTPUT, ITALIAN_POSTERAZORHELPWHYPDFOUTPUT) \
					POSTERAZORHELPINDENTATION "Perch&egrave; creare un PDF invece di stampare direttamente? Prima di tutto lo sviluppatore di questo programma non sa (ancora) il metodo per \"inviare immagini alla stampante\" sui differenti sistemi operativi per i quali PosteRazor &egrave; pensato . Inoltre, il formato PDF ha l'utilit&agrave; della portabilit&agrave;, quindi per esempio il poster pu&ograve; essere tagliato in casa con tutto il tempo necessario ed il giorno dopo pu&ograve; essere stampato con la stampante laser a colori in ufficio (dopo che tutti i colleghi se ne sono andati). " POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "Perch&egrave; PDF e non altri formati immagine raster? Perch&egrave; un PDF d&agrave; la possibilit&agrave; di allegare l'intera immagine e di tagliarla virtualmente con suddivisioni ben pi&ugrave; piccole rispetto ai pixel. In aggiunta, &egrave; molto pi&ugrave; pratico stampare un singolo file multipagina PDF, che un file con immagini multiple." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES, ITALIAN_POSTERAZORHELPCODEFROMTHIRDPARTIES) \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>FLTK</b> &egrave; usato per l'interfaccia utente. E' un piccola (per dimensione), veloce e \"fun&easy\" UI Toolkit applicazione portabile. <a href=\"http://www.fltk.org/\">www.fltk.org</a></LI>" POSTERAZORHELPENDLINE \
					"<LI><b>FreeImage</b> &egrave; usato per il caricamento e la gestione delle immagini. Rende la gestione delle immagini veramente semplice, togliendo tanti grattacapi agli sviluppatori, ed oltretutto &egrave; portabile nei sistemi operativi per cui PosteRazor &egrave; pensato. <a href=\"http://freeimage.sourceforge.net/\">FreeImage website</a></LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Fl_Native_File_Chooser</b> &egrave; usato per l'apertura ed il salvataggio dei file nei nativi sistemi operativi utilizzati. <a href=\"http://seriss.com/people/erco/fltk/Fl_Native_File_Chooser/\">Fl_Native_File_Chooser website</a></LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORLICENSE, ITALIAN_POSTERAZORHELPLICENSE) \
					"PosteRazor - Crea il tuo poster!<br>" POSTERAZORHELPENDLINE \
					"<a href=\""ITALIAN_POSTERAZORWEBSITEURL"\">posterazor.sourceforge.net</a><br>" POSTERAZORHELPENDLINE \
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
			140,140,140,140,140,0,204,0,0,204,0,0,204,0,0,204,0,0,204,0,0,204,0,255,255,255,
			255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0,0,255,0,0,255,
			0,0,255,0,0,255,0,0,255,0,0,140,140,140,140,140,140,0,204,0,0,204,0,0,204,0,0,
			204,0,0,204,0,0,204,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
			255,255,255,255,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,140,140,140,140,
			140,140,0,204,0,0,204,0,0,204,0,0,204,0,0,204,0,0,204,0,255,255,255,255,255,255,
			255,255,255,255,255,255,255,255,255,255,255,255,255,0,0,255,0,0,255,0,0,255,0,0,
			255,0,0,255,0,0,140,140,140,140,140,140,0,204,0,0,204,0,0,204,0,0,204,0,0,204,0,
			0,204,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
			255,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,140,140,140,140,140,140,0,
			204,0,0,204,0,0,204,0,0,204,0,0,204,0,0,204,0,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,255,255,255,255,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,
			255,0,0,140,140,140,140,140,140,0,204,0,0,204,0,0,204,0,0,204,0,0,204,0,0,204,0,
			255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0,0,
			255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,140,140,140,140,140,140,0,204,0,0,204,0,
			0,204,0,0,204,0,0,204,0,0,204,0,255,255,255,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,255,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,140,
			140,140,140,140,140,0,204,0,0,204,0,0,204,0,0,204,0,0,204,0,0,204,0,255,255,255,
			255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0,0,255,0,0,255,
			0,0,255,0,0,255,0,0,255,0,0,140,140,140,140,140,140,0,204,0,0,204,0,0,204,0,0,
			204,0,0,204,0,0,204,0,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
			255,255,255,255,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140
		};

		return flagRGBData;
	}
};

static const TranslationItalian italian;

#endif
