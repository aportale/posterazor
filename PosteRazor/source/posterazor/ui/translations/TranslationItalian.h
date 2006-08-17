/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2006 by Alessandro Portale
	http://posterazor.sourceforge.net/
	
	Italian translation by Stefano Nosei - kluster[at]imente[dot]org

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

#ifndef TranslationItalian_h
#define TranslationItalian_h

#include "TranslationInterface.h"
#include "TranslationConstants.h"

#define ITALIAN_POSTERAZORWEBSITEURL POSTERAZORWEBSITEDOMAIN

class TranslationItalian: public TranslationInterface
{
public:
	const char* LanguageName(void)                    {return "Italiano";}

	const char* AbsoluteSize(void)                    {return "Dimensioni assolute:";}
	const char* AllImageFormats(void)                 {return "Tutti i formati immagine";}
	const char* Back(void)                            {return "Indietro";}
	const char* Borders(void)                         {return "Bordi";}
	const char* Bottom(void)                          {return "Inferiore";}
	const char* BottomLeft(void)                      {return "Inferiore sinistro";}
	const char* BottomRight(void)                     {return "Inferiore destro";}
	const char* Cancel(void)                          {return "Cancella";}
	const char* ColorType(void)                       {return "Tipo di colore:";}
	const char* Custom(void)                          {return "Personalizzato";}
	const char* FileCouldNotBeLoaded(void)            {return "Il file \"%s\" non può essere caricato.";}
	const char* Format(void)                          {return "Formato:";}
	const char* Grayscale(void)                       {return "Scala di grigi";}
	const char* Height(void)                          {return "Altezza:";}
	const char* ImageAlignment(void)                  {return "Allineamento immagine";}
	const char* ImageInformations(void)               {return "Informazioni immagine";}
	const char* ImageSize(void)                       {return "Dimensione immagine";}
	const char* InputImage(void)                      {return "Immagine sorgente";}
	const char* Landscape(void)                       {return "Landscape";}
	const char* Language(void)                        {return "Linguaggio";}
	const char* LanguageExplanation(void)             {return "Selezione il tuo linguaggio";}
	const char* LaunchPDFApplication(void)            {return "Lancia l'applicazione PDF dopo che il poster è stato salvato";}
	const char* Left(void)                            {return "Sinistra";}
	const char* LoadAnInputImage(void)                {return StepTitle01();}
	const char* Monochrome(void)                      {return "Monocromatico";}
	const char* Next(void)                            {return "Successivo";}
	const char* Orientation(void)                     {return "Orientamento:";}
	const char* OverlappingPosition(void)             {return "Posizione del sovrapposizionamento";}
	const char* OverlappingSize(void)                 {return "Dimensione del sovrapposizionamento";}
	const char* OverwriteFile(void)                   {return "Il file '%s' esiste già.\nVuoi sovrascriverlo?";}
	const char* Pages(void)                           {return "pagine";}
	const char* PaperFormat(void)                     {return "Formato carta";}
	const char* Palette(void)                         {return "Paletta colori";}
	const char* Portrait(void)                        {return "Portrait";}
	const char* PosteRazorHelp(void)                  {return "Guida PosteRazor";}
	const char* PosteRazorSettings(void)              {return "Impostazioni PosteRazor";}
	const char* PosteRazorWebSiteURL(void)            {return ITALIAN_POSTERAZORWEBSITEURL;}
	const char* PosteRazorWebSite(void)               {return "Sito Web PosteRazor";}
	const char* PreviewWithOpenGL(void)               {return "Anteprima con OpenGL";}
	const char* PreviewWithOpenGLExplanation(void)    {return "OpenGL permette una più accurata anteprima sui sistemi moderni, sebbene possa risultare più lenta nei computer meno recenti";}
	const char* Resolution(void)                      {return "Risoluzione:";}
	const char* Right(void)                           {return "Destra";}
	const char* SaveThePoster(void)                   {return "Salva il poster";}
	const char* SaveThePosterAs(void)                 {return "Salva il poster come";}
	const char* Settings(void)                        {return "Impostazioni...";}
	const char* Size(void)                            {return "Dimensione:";}
	const char* SizeInPages(void)                     {return "Dimensione in pagine";}
	const char* SizeInPercent(void)                   {return "Dimensione in percentuale:";}
	const char* SizeInPixels(void)                    {return "Dimensione (in pixels):";}
	const char* SizeInUnitOfLength(void)              {return "Dimensione (in %s):";}
	const char* Standard(void)                        {return "Standard";}
	const char* StepXOfY(void)                        {return "Passaggio %d di %d";}
	const char* Top(void)                             {return "Superiore";}
	const char* TopLeft(void)                         {return "Superiore sinistro";}
	const char* TopRight(void)                        {return "Superiore destro";}
	const char* UnitOfLength(void)                    {return "Unità di misura";}
	const char* UnitOfLengthExplanation(void)         {return "Scegli l'unità di misura della distanza con cui intendi lavorare";}
	const char* Width(void)                           {return "Larghezza:";}


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
#define ITALIAN_POSTERAZORHELPWHYPDFOUTPUT            "Perchè un output in PDF?"
#define ITALIAN_POSTERAZORHELPCODEFROMTHIRDPARTIES    "Codice da Terze Parti"
#define ITALIAN_POSTERAZORHELPLICENSE                 "Licenza"

	const char* StepTitle01(void)                     {return ITALIAN_POSTERAZORHELPSTEPTITLE01;};
	const char* StepTitle02(void)                     {return ITALIAN_POSTERAZORHELPSTEPTITLE02;};
	const char* StepTitle03(void)                     {return ITALIAN_POSTERAZORHELPSTEPTITLE03;};
	const char* StepTitle04(void)                     {return ITALIAN_POSTERAZORHELPSTEPTITLE04;};
	const char* StepTitle05(void)                     {return ITALIAN_POSTERAZORHELPSTEPTITLE05;};
	const char* HelpHtml(void)
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
					"PosteRazor è un programma open source che dipende da <a href=\"#" POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES "\">altri progetti open source</a>. " POSTERAZORHELPENDLINE \
					"PosteRazor è ospitato su <b>posterazor.sourceforge.net</b>." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUAL, ITALIAN_POSTERAZORHELPMANUAL) \
					POSTERAZORHELPINDENTATION "PosteRazor ha la un interfaccia utente organizzata in facili procedure guidate (\"Wizard\"). Le procedure per creare il poster possono essere effettuate  in 5 passaggi. I tasti <b>Precedente</b> and <b>Successivo</b> permettono di navigare attraverso i passaggi.<br>" POSTERAZORHELPENDLINE \
					"Il tasto <b>?</b> apre una finestra di aiuto con una spiegazione sulle operazioni del passaggio corrente.<br>" POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "Tutte le impostazioni e le scelte effettuate dall'utente sono registrate dal programma e rimarranno tali nelle successive riaperture di PosteRazor." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORSETTINGS, ITALIAN_POSTERAZORHELPSETTINGS) \
					POSTERAZORHELPINDENTATION "Premendo il tasto <b>Impostazioni...</b> in basso a sinistra nella finestra principale,  si aprirà la finestra di configurazione di PosteRazor." POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>Unità di Misura:</b> scegli l'unità di misura che intendi utilizzare nel tuo lavoro. Quando un'unità viene cambiata, tutti i valori predefiniti e quelli precedentemente impostati vengono automaticamente ricalcolati nella nuova unità.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Linguaggio:</b> scegli il tuo linguaggio. PosteRazor non necessita di essere riavviato quando viene modificato il linguaggio.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Anteprima con OpenGL:</b> indica a PosteRazor di utilizzare OpenGL per l'anteprima dell'immagine. Di solito, su hardware recente, OpenGL dovrebbe visualizzare l'anteprima in maniera più veloce ed accurata rispetto al metodo non-OpenGL. In ogni caso se PosteRazor dovesse risultare più lento e/o instabile, è indicato disabilitare la modalità OpenGL.</LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP01, ITALIAN_POSTERAZORHELSTEP " 1: " ITALIAN_POSTERAZORHELPSTEPTITLE01) \
					POSTERAZORHELPINDENTATION "Carica l'immagine premendo il bottone con l'icona a forma di cartella e seleziona l'immagine di origine. L'immagine può essere anche trascinata all'interno della finestra tramite drag & drop. La procedura di drag & drop funziona anche nei successivi passaggi<br>" POSTERAZORHELPENDLINE \
					"Possono essere caricati svariati <a href=\"#" POSTERAZORHELPANCHORINPUTFILEFORMATS "\">formati di files e tipi di immagini</a> . Dopo il caricamento dell'immagine, le informazioni di dettaglio sono elencate nella casella <b>Informazioni immagine</b>." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP02, ITALIAN_POSTERAZORHELSTEP " 2: " ITALIAN_POSTERAZORHELPSTEPTITLE02) \
					POSTERAZORHELPINDENTATION "Definisce la dimensione del foglio di stampa che viene utilizzato dalla tua stampante. I principali formati standard per stampante possono essere selezionati dalla casella di scelta <b>Formato</b>, così come per l'<b>Orientamento</b>. In alternativa, può essere definito un foglio di stampa personalizzato selezionando la scheda <b>Personalizzato</b>. (Vi prego di comunicarmi via mail, se l'operazione vi facesse perdere il formato foglio standard nella casella di scelta). " POSTERAZORHELPENDLINE \
					"I bordi del foglio sono definiti nella casella <b>Bordi</b>. Sebbene la vostra stampante possa specificatamente stampare senza margini vi consigliamo di lasciare un piccolo bordo per facilitare la successiva incollatura dei pezzi per comporre il poster finale." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP03, ITALIAN_POSTERAZORHELSTEP " 3: " ITALIAN_POSTERAZORHELPSTEPTITLE03) \
					POSTERAZORHELPINDENTATION "La sovrapposizione delle sezioni dell'immagine è utile per avere un intervallo di tolleranza per tagliare i bordi non necessari sui lati. In aggiunta, come specificato per i bordi nel passo precedente, può permettere un'area più ampia per l'incollatura finale del poster. " POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "La <b>Posizione del Sovrapposizionamento</b> difinisce i bordi che saranno sovrapposti dalle singole sezioni contigue dell'immagine. I bordi sui lati opposti sono quelli che si intendono tagliare per l'incollatura (ad eccezione delle sezioni di margine esterno)." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP04, ITALIAN_POSTERAZORHELSTEP " 4: " ITALIAN_POSTERAZORHELPSTEPTITLE04) \
					POSTERAZORHELPINDENTATION "Definisci la dimensione finale del poster, in uno dei seguenti tre  metodi che possono essere selezionati marcando i corrispondenti tasti di scelta:<br>" POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>Dimensioni assolute</b> dell'immagine: imposta una dimensione specifica per il tuo poster.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Dimensioni in pagine</b>: imposta in quante pagine totali verrà ripartita l'immagine da stampare.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Dimensioni immagine in percentuale</b>: l'immagine sorgente selezionata avrà una specifica dimensione in pixel e in dpi (punti per pollice). Selezionando questa opzione l'immagine sarà ingrandita in base al fattore percentuale inserito.</LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "La proporzione tra la larghezza e l'altezza è sempre 1:1 ed è automaticamente ricalcolata. Nell'area di Anteprima, puoi vedere le aree di sovrapposizionamento che sono marcate da triangoli di color rosso chiaro. " POSTERAZORHELPENDLINE \
					"<b>Allineamento immagine</b> imposta l'allineamento dell'immagine nell'area totale di stampa del poster. Ciò è utile se vuoi mantenere parti di pagina non utilizzate." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP05, ITALIAN_POSTERAZORHELSTEP " 5: " ITALIAN_POSTERAZORHELPSTEPTITLE05) \
					POSTERAZORHELPINDENTATION "Salva il poster premendo il bottone con l'icona a forma di floppy e specifica un nome file di destinazione. Marca o smarca il segno di spunta <b>Lancia l'applicazione PDF dopo che il poster è stato salvato</b>, e l'applicazione impostata come predefinita per il formato PDF verrà avviata automaticamente dopo il salvataggio del file" POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORINPUTFILEFORMATS, ITALIAN_POSTERAZORHELPINPUTFILEFORMATS) \
					POSTERAZORHELPINDENTATION "La maggior parte delle immagini raster che sono supportate da FreeImage sono supportate anche da PosteRazor:<br>" POSTERAZORHELPENDLINE \
					"<b>BMP, file DDS , Dr. Halo, GIF, ICO, IFF, JBIG, JNG, JPEG/JIF, KOALA, LBM, Kodak PhotoCD, MNG, PCX, PBM, PGM, PNG, PPM, PhotoShop PSD, Sun RAS, TARGA, TIFF, WBMP, XBM, XPM.<br></b>" POSTERAZORHELPENDLINE \
					"PosteRazor distingue e supporta immagini monocromatiche, a scala di grigi, con palette a 4-bit ,8-bit, 24 bit RGB, e quadricromia CMYK (solo per il formato Tif). Le immagini RGB con un canale alpha sono automaticamente composte con sfondo bianco." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORWHYPDFOUTPUT, ITALIAN_POSTERAZORHELPWHYPDFOUTPUT) \
					POSTERAZORHELPINDENTATION "Perchè creare un PDF invece di stampare direttamente? Prima di tutto lo sviluppatore di questo programma non sa (ancora) il metodo per \"inviare immagini alla stampante\" sui differenti sistemi operativi per i quali PosteRazor è pensato . Inoltre, il formato PDF ha l'utilità della portabilità, quindi per esempio il poster può essere tagliato in casa con tutto il tempo necessario ed il giorno dopo può essere stampato con la stampante laser a colori in ufficio (dopo che tutti i colleghi se ne sono andati). " POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "Perchè PDF e non altri formati immagine raster? Perchè un PDF dà la possibilità di allegare l'intera immagine e di tagliarla virtualmente con suddivisioni ben più piccole rispetto ai pixel. In aggiunta, è molto più pratico stampare un singolo file multipagina PDF, che un file con immagini multiple." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES, ITALIAN_POSTERAZORHELPCODEFROMTHIRDPARTIES) \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>FLTK</b> è usato per l'interfaccia utente. E' un piccola (per dimensione), veloce e \"fun&easy\" UI Toolkit applicazione portabile. <a href=\"http://www.fltk.org/\">www.fltk.org</a></LI>" POSTERAZORHELPENDLINE \
					"<LI><b>FreeImage</b> è usato per il caricamento e la gestione delle immagini. Rende la gestione delle immagini veramente semplice, togliendo tanti grattacapi agli sviluppatori, ed oltretutto è portabile nei sistemi operativi per cui PosteRazor è pensato. <a href=\"http://freeimage.sourceforge.net/\">FreeImage website</a></LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Fl_Native_File_Chooser</b> è usato per l'apertura ed il salvataggio dei file nei nativi sistemi operativi utilizzati. <a href=\"http://seriss.com/people/erco/fltk/Fl_Native_File_Chooser/\">Fl_Native_File_Chooser website</a></LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORLICENSE, ITALIAN_POSTERAZORHELPLICENSE) \
					"PosteRazor - Crea il tuo poster!<br>" POSTERAZORHELPENDLINE \
					"<a href=\""ITALIAN_POSTERAZORWEBSITEURL"\">posterazor.sourceforge.net</a><br>" POSTERAZORHELPENDLINE \
					"Copyright (C) 2005-2006 by Alessandro Portale<br>&nbsp;<br>" POSTERAZORHELPENDLINE \

					"<b>Traduzione francese ad opera di Martin Loyer (traduction<b></b>@<b></b>loyer<b></b>.<b></b>name).</b><br>" POSTERAZORHELPENDLINE \
					"<b>Traduzione italiana ad opera di Stefano Nosei (kluster<b></b>@<b></b>imente<b></b>.<b></b>org).</b><br>" POSTERAZORHELPENDLINE \
					"<b>Traduzione polacca ad opera di Grzegorz Wacikowski.</b><br>&nbsp;<br>" POSTERAZORHELPENDLINE \

					"Questo programma è un software gratis; puoi redistribuirlo e/o modificarlo sotto i termini della <a href=\"http://www.gnu.org/licenses/gpl.txt\">GNU General Public License</a> come pubblicato dalla Free Software Foundation; compresa la versione 2 della Licenza, oppure (a tua scelta) qualsiasi successiva versione.<br>&nbsp;<br>" POSTERAZORHELPENDLINE \
					"Questo programma è distribuito nella speranza che sia per te utile, ma SENZA ALCUNA GARANZIA; senza persino la garanzia implicita di MERCHANTABILITY o di IDONEITÀ PER UNO SCOPO PRECISO. Per maggiori dettaglio visualizza la GNU General Public License.<br>&nbsp;<br>" POSTERAZORHELPENDLINE \
					"Dovresti aver ricevuto una copia della GNU General Public License insieme a questo programma; se non è così, ti prego di scrivere alla Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA." POSTERAZORHELPENDLINE \
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

static TranslationItalian italian;

#endif