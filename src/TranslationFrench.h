/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2008 by Alessandro Portale
	http://posterazor.sourceforge.net/

	French translation by Martin Loyer - traduction et loyer dot name

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

#ifndef TranslationFrench_h
#define TranslationFrench_h

#include "TranslationInterface.h"
#include "TranslationConstants.h"

#define FRENCH_POSTERAZORWEBSITEURL POSTERAZORWEBSITEDOMAIN

class TranslationFrench: public TranslationInterface
{
public:
	const char* languageName(void) const                    {return "Français";}

	const char* absoluteSize(void) const                    {return "Taille réelle :";}
	const char* allImageFormats(void) const                 {return "Tous les formats d'images";}
	const char* back(void) const                            {return "Précédent";}
	const char* borders(void) const                         {return "Bordures";}
	const char* bottom(void) const                          {return "Bas";}
	const char* bottomLeft(void) const                      {return "En bas à gauche";}
	const char* bottomRight(void) const                     {return "En bas à droite";}
	const char* cancel(void) const                          {return "Annuler";}
	const char* colorType(void) const                       {return "Format :";}
	const char* custom(void) const                          {return "Personnalisé";}
	const char* fileCouldNotBeLoaded(void) const            {return "Le fichier \"%s\" ne peut pas être chargé.";}
	const char* fileCouldNotBeSaved(void) const             {return "Le fichier \"%s\" ne peut pas être enregistré.";}
	const char* format(void) const                          {return "Format :";}
	const char* grayscale(void) const                       {return "Niveau de gris";}
	const char* height(void) const                          {return "Hauteur :";}
	const char* imageAlignment(void) const                  {return "Position de l'image";}
	const char* imageInformations(void) const               {return "Informations :";}
	const char* imageSize(void) const                       {return "Taille de l'image";}
	const char* inputImage(void) const                      {return "Image à découper";}
	const char* landscape(void) const                       {return "Paysage";}
	const char* language(void) const                        {return "Langue";}
	const char* languageExplanation(void) const             {return "Choisissez votre langage";}
	const char* launchPDFApplication(void) const            {return "Ouvrir le PDF après avoir sauvé le poster";}
	const char* left(void) const                            {return "Gauche";}
	const char* loadAnInputImage(void) const                {return stepTitle01();}
	const char* monochrome(void) const                      {return "monochrome";}
	const char* next(void) const                            {return "Suivant";}
	const char* orientation(void) const                     {return "Orientation :";}
	const char* overlappingPosition(void) const             {return "Position du recouvrement";}
	const char* overlappingSize(void) const                 {return "Taille du recouvrement";}
	const char* overwriteFile(void) const                   {return "Le fichier '%s' existe déjà.\nVoulez-vous le remplacer ?";}
	const char* pages(void) const                           {return "pages";}
	const char* paperFormat(void) const                     {return "Format de papier";}
	const char* palette(void) const                         {return "Palette";}
	const char* portrait(void) const                        {return "Portrait";}
	const char* posteRazorHelp(void) const                  {return "Aide de PosteRazor";}
	const char* posteRazorSettings(void) const              {return 
#ifdef __APPLE__
// This seems to be the only problematic string on OSX. It is used for a window title.
														"R\x8Eglages de PosteRazor"
#else
														"Réglages de PosteRazor"
#endif
	                                                  ;}
	const char* posteRazorWebSiteURL(void) const            {return FRENCH_POSTERAZORWEBSITEURL;}
	const char* posteRazorWebSite(void) const               {return "Siteweb de PosteRazor";}
	const char* previewWithOpenGL(void) const               {return "Prévisualisation OpenGL";}
	const char* previewWithOpenGLExplanation(void) const    {return "OpenGL permet un rendu plus net. Mais il peut ralentir la prévisualisation sur les machines moins récente.";}
	const char* resolution(void) const                      {return "Résolution :";}
	const char* right(void) const                           {return "Droite";}
	const char* saveThePoster(void) const                   {return "Enregistrer le poster";}
	const char* saveThePosterAs(void) const                 {return "Enregistrer le poster sous";}
	const char* settings(void) const                        {return "Réglages...";}
	const char* Size(void) const                            {return "Taille :";}
	const char* sizeInPages(void) const                     {return "Taille en nombres de pages :";}
	const char* sizeInPercent(void) const                   {return "Taille en pourcentage :";}
	const char* sizeInPixels(void) const                    {return "Taille (en pixels) :";}
	const char* sizeInUnitOfLength(void) const              {return "Taille (en %s) :";}
	const char* standard(void) const                        {return "Standard";}
	const char* stepXOfY(void) const                        {return "Étape %d de %d";}
	const char* top(void) const                             {return "Haut ";}
	const char* topLeft(void) const                         {return "En haut à gauche";}
	const char* topRight(void) const                        {return "En haut à droite";}
	const char* unitOfLength(void) const                    {return "Unité de mesure";}
	const char* unitOfLengthExplanation(void) const         {return "Choisissez l'unité de mesure qui vous convient.";}
	const char* width(void) const                           {return "Largeur :";}


#define FRENCH_POSTERAZORHELSTEP                     "&Eacute;tape"

#define FRENCH_POSTERAZORHELPABOUT                   "&Agrave; propos de PosteRazor"
#define FRENCH_POSTERAZORHELPMANUAL                  "Manuel"
#define FRENCH_POSTERAZORHELPSETTINGS                "R&eacute;glages"
#define FRENCH_POSTERAZORHELPSTEPTITLE01             "Ouvrir une image"
#define FRENCH_POSTERAZORHELPSTEPTITLE02             "Format du papier"
#define FRENCH_POSTERAZORHELPSTEPTITLE03             "Recouvrements de l'image"
#define FRENCH_POSTERAZORHELPSTEPTITLE04             "Taille final du poster"
#define FRENCH_POSTERAZORHELPSTEPTITLE05             "Enregistrer le Poster"
#define FRENCH_POSTERAZORHELPINPUTFILEFORMATS        "Formats d'image support&eacute;s"
#define FRENCH_POSTERAZORHELPWHYPDFOUTPUT            "Pourquoi un poster en PDF ?"
#define FRENCH_POSTERAZORHELPCODEFROMTHIRDPARTIES    "Code source tiers"
#define FRENCH_POSTERAZORHELPLICENSE                 "License"

	const char* stepTitle01(void) const                     {return FRENCH_POSTERAZORHELPSTEPTITLE01;}
	const char* stepTitle02(void) const                     {return FRENCH_POSTERAZORHELPSTEPTITLE02;}
	const char* stepTitle03(void) const                     {return FRENCH_POSTERAZORHELPSTEPTITLE03;}
	const char* stepTitle04(void) const                     {return FRENCH_POSTERAZORHELPSTEPTITLE04;}
	const char* stepTitle05(void) const                     {return FRENCH_POSTERAZORHELPSTEPTITLE05;}
	const char* helpHtml(void) const
	{
		return	"<HTML>" POSTERAZORHELPENDLINE \
				"<BODY>" POSTERAZORHELPENDLINE \
					"<A name=\"" POSTERAZORHELPANCHORTOP "\"><CENTER><H1>Aide de PosteRazor "POSTERAZORVERSION"</H1></CENTER></A>" POSTERAZORHELPENDLINE \

					"<H3>Contents</H3>" POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORABOUT "\">" FRENCH_POSTERAZORHELPABOUT "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORMANUAL "\">" FRENCH_POSTERAZORHELPMANUAL "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORSETTINGS "\">" FRENCH_POSTERAZORHELPSETTINGS "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<UL>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP01 "\">" FRENCH_POSTERAZORHELSTEP " 1: " FRENCH_POSTERAZORHELPSTEPTITLE01 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP02 "\">" FRENCH_POSTERAZORHELSTEP " 2: " FRENCH_POSTERAZORHELPSTEPTITLE02 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP03 "\">" FRENCH_POSTERAZORHELSTEP " 3: " FRENCH_POSTERAZORHELPSTEPTITLE03 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP04 "\">" FRENCH_POSTERAZORHELSTEP " 4: " FRENCH_POSTERAZORHELPSTEPTITLE04 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP05 "\">" FRENCH_POSTERAZORHELSTEP " 5: " FRENCH_POSTERAZORHELPSTEPTITLE05 "</A></LI>" POSTERAZORHELPENDLINE \
						"</UL>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORINPUTFILEFORMATS "\">" FRENCH_POSTERAZORHELPINPUTFILEFORMATS "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORWHYPDFOUTPUT "\">" FRENCH_POSTERAZORHELPWHYPDFOUTPUT "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES "\">" FRENCH_POSTERAZORHELPCODEFROMTHIRDPARTIES "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORLICENSE "\">" FRENCH_POSTERAZORHELPLICENSE "</A></B></LI>" POSTERAZORHELPENDLINE \
					"</UL><HR>" POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORABOUT, FRENCH_POSTERAZORHELPABOUT) \
					POSTERAZORHELPINDENTATION "PosteRazor fractionne une grande image en plusieurs &eacute;l&eacute;ments qui peuvent &ecirc;tre imprim&eacute;s plus facilement. Ces morceaux sont ensuite assembl&eacute;s pour former un poster. Le format de l'image initiale doit &ecirc;tre compatible avec les <A href=\"#" POSTERAZORHELPANCHORMANUALSTEP01 "\">formats</A> suivants. Au lieu de directement imprimer le poster, PosteRazor cr&eacute;&eacute; un fichier PDF de plusieurs pages qui contient les morceaux &agrave; imprimer.<br>" POSTERAZORHELPENDLINE \
					"Ce programme est libre (licence GNU GPL). Il fonctionne avec des codes, libres, utilis&eacute;s dans d'<a href=\"#" POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES "\">autres projets</a>. " POSTERAZORHELPENDLINE \
					"Le site web de PosteRazor est <b>posterazor.sourceforge.net</b>." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUAL, FRENCH_POSTERAZORHELPMANUAL) \
					POSTERAZORHELPINDENTATION "PosteRazor est organis&eacute; &agrave; la mani&egrave;re d'un assistant. La cr&eacute;ation d'un poster se fait en cinq &eacute;tapes. Les boutons <b>Pr&eacute;c&eacute;dent</b> et <b>Suivant</b> permettent de naviguer facilement entre ces diff&eacute;rentes &eacute;tapes.<br>" POSTERAZORHELPENDLINE \
					"Le bouton <b>?</b> ouvre une fen&ecirc;tre d'aide, qui explique l'&eacute;tape en cours.<br>" POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "Toutes les valeurs et choix sont conserv&eacute;s au prochain lancement de l'application." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORSETTINGS, FRENCH_POSTERAZORHELPSETTINGS) \
					POSTERAZORHELPINDENTATION "En cliquant sur le bouton <b>R&eacute;glages</b>, situ&eacute; en bas &agrave; gauche de la fen&ecirc;tre principale, la boite de r&eacute;glages des pr&eacute;f&eacute;rences s'affiche. Les r&eacute;glages suivants sont possibles :" POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>Unit&eacute; de mesure :</b> permet de choisir l'unit&eacute; de mesure qui sera utilis&eacute;e dans PosteRazor. Quand l'unit&eacute; est chang&eacute;e, toutes les valeurs pr&eacute;enregistr&eacute;es sont automatiquement converties.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Langue :</b> choisissez votre langage. PosteRazor n'a pas besoin d'&ecirc;tre relanc&eacute;. Il affiche automatiquement la nouvelle langue.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Pr&eacute;visualisation OpenGL :</b> permet d'utiliser (ou non) OpenGL pour pr&eacute;visualiser le poster. Cela permet un affichage plus net. Cela peut ralentir l'affichage sur les machines plus anciennes. Si PosteRazor devient lent et ne r&eacute;pond plus, essayez de d&eacute;sactiver cette option.</LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP01, FRENCH_POSTERAZORHELSTEP " 1: " FRENCH_POSTERAZORHELPSTEPTITLE01) \
					POSTERAZORHELPINDENTATION "Chargez une image en cliquant sur l'ic&ocirc;ne en forme de dossier. Choisissez le fichier en naviguant dans vos dossiers ou glissez-d&eacute;posez l'image dans la fen&ecirc;tre. Le gliss&eacute;-d&eacute;pos&eacute; marche aussi dans les autres &eacute;tapes de l'assistant.<br>" POSTERAZORHELPENDLINE \
					"Plusieurs <a href=\"#" POSTERAZORHELPANCHORINPUTFILEFORMATS "\">formats d'images</a> sont compatibles. Apr&egrave;s avoir charg&eacute; l'image, les informations pratiques (taille, couleur, r&eacute;solution) sont affich&eacute;es dans la rubrique <b>Informations :</b>." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP02, FRENCH_POSTERAZORHELSTEP " 2: " FRENCH_POSTERAZORHELPSTEPTITLE02) \
					POSTERAZORHELPINDENTATION "Dans cette &eacute;tape, vous allez r&eacute;gler le type de papier que vous utiliserez pour imprimer. Les formats de papier courants ainsi que l'orientation (paysage/portrait) sont disponibles dans la cat&eacute;gorie <b>Standard</b>. Cependant, si vous souhaitez d&eacute;finir vous-m&ecirc;me la taille du papier, vous pouvez utiliser la cat&eacute;gorie <b>Personnalis&eacute;</b> (si une taille de papier standard n'appara&icirc;t pas, n'h&eacute;sitez pas &agrave; m'envoyer un e-mail)." POSTERAZORHELPENDLINE \
					"M&ecirc;me si votre imprimante n'impose pas de marges, il est toujours utile d'en mettre, afin de permettre de coller les diff&eacute;rents &eacute;l&eacute;ments du poster entre eux." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP03, FRENCH_POSTERAZORHELSTEP " 3: " FRENCH_POSTERAZORHELPSTEPTITLE03) \
					POSTERAZORHELPINDENTATION "Les recouvrements entre morceaux donnent une certaine tol&eacute;rance lors du d&eacute;coupage et du collage du poster." POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "La position de recouvrement d&eacute;termine les cot&eacute;s qui seront recouverts. " POSTERAZORHELPENDLINE \
					
					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP04, FRENCH_POSTERAZORHELSTEP " 4: " FRENCH_POSTERAZORHELPSTEPTITLE04) \
					POSTERAZORHELPINDENTATION "Pour d&eacute;terminer la taille finale du poster, il existe trois m&eacute;thodes :<br>" POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>Taille r&eacute;elle :</b> vous sp&eacute;cifiez une taille pr&eacute;cise pour votre poster.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Taille en pages :</b> la taille de votre poster d&eacute;pend du nombre de pages que vous utiliserez.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Taille en pourcentage :</b> vous choisissez un pourcentage de zoom en fonction de la r&eacute;solution d'origine de l'image. La r&eacute;solution d'origine est calcul&eacute;e en fonction de la taille (hauteur / largeur) et du nombre de pixels par centim&egrave;tres (ou DPI, nombre de pixels par pouces).</LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "Par d&eacute;faut, le poster est imm&eacute;diatement calcul&eacute; avec un rendu de 1 pour 1 (100%). Vous pouvez juger du rendu dans la fen&ecirc;tre de pr&eacute;visualisation. Les traits rouges figurent la coupure entre les pages." POSTERAZORHELPENDLINE \
					"Le bouton <b>Position de l'image</b> permet de r&eacute;gler la position de l'image par rapport au papier. L'image peut &ecirc;tre centr&eacute;e ou coll&eacute;e sur un des bords." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP05, FRENCH_POSTERAZORHELSTEP " 5: " FRENCH_POSTERAZORHELPSTEPTITLE05) \
					POSTERAZORHELPINDENTATION "Enregistrez votre poster en cliquant sur le bouton en forme de disquette. Ensuite, donnez un nom &agrave; votre &aelig;uvre, choisissez l'emplacement, puis cliquez sur <b>Enregistrer</b>. Si vous cochez l'option <b>Ouvrir le PDF apr&egrave;s avoir sauv&eacute; le poster</b>, le poster sera automatiquement ouvert dans votre application PDF apr&egrave;s l'enregistrement." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORINPUTFILEFORMATS, FRENCH_POSTERAZORHELPINPUTFILEFORMATS) \
					POSTERAZORHELPINDENTATION "La plupart des formats d'images support&eacute;s par FreeImage sont support&eacute;s par PosteRazor. Les formats suivants sont g&eacute;r&eacute;s :<br>" POSTERAZORHELPENDLINE \
					"<b>BMP, DDS files, Dr. Halo, GIF, ICO, IFF, JBIG, JNG, JPEG/JIF, KOALA, LBM, Kodak PhotoCD, MNG, PCX, PBM, PGM, PNG, PPM, PhotoShop PSD, Sun RAS, TARGA, TIFF, WBMP, XBM, XPM.<br></b>" POSTERAZORHELPENDLINE \
					"PosteRazor g&egrave;re les formats monochrome, niveaux de gris, RVB et CMJN (uniquement TIFF) au format 4, 8 et 24 bits. La couche alpha des images RVB est transform&eacute;e en fond blanc." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORWHYPDFOUTPUT, FRENCH_POSTERAZORHELPWHYPDFOUTPUT) \
					POSTERAZORHELPINDENTATION "Pourquoi utiliser le PDF, alors qu'il serait possible d'imprimer directement ?  Tout d'abord, PosteRazor a &eacute;t&eacute; cr&eacute;&eacute; pour fonctionner sur de multiples syst&egrave;mes, qui utilisent tous des moyens diff&eacute;rents pour imprimer. L'auteur de l'application ne les conna&icirc;t pas tous. Ensuite, le PDF est utile quand on souhaite composer soigneusement son poster, pour enfin l'imprimer sans risque ailleurs (chez l'imprimeur, au travail, chez un ami...)." POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "Pourquoi utiliser le format PDF et non pas un format d'image ? Le PDF permet d'int&eacute;grer directement toute l'image et de la couper virtuellement. Le PDF g&egrave;re aussi directement les recouvrements. Enfin, il est plus pratique d'imprimer un PDF, que d'imprimer s&eacute;par&eacute;ment les diff&eacute;rentes images !" POSTERAZORHELPENDLINE \
					
					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES, FRENCH_POSTERAZORHELPCODEFROMTHIRDPARTIES) \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>FLTK</b> est utilis&eacute; pour l'interface graphique, Il prend peu de place, il est portable et rapide. Enfin, il est facile &agrave; utiliser. <a href=\"http://www.fltk.org/\">www.fltk.org</a></LI>" POSTERAZORHELPENDLINE \
					"<LI><b>FreeImage</b> est utilis&eacute; pour g&eacute;rer les images. Il permet une gestion facile, tout en &eacute;tant multi plateforme. <a href=\"http://freeimage.sourceforge.net/\">Site web de FreeImage</a></LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Fl_Native_File_Chooser</b> est utilis&eacute; pour les fen&ecirc;tres d'ouverture et d'enregistrement. <a href=\"http://seriss.com/people/erco/fltk/Fl_Native_File_Chooser/\">Site web de Fl_Native_File_Chooser</a></LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \
					
					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORLICENSE, FRENCH_POSTERAZORHELPLICENSE) \
					"PosteRazor - Cr&eacute;ez vos propres posters !<br>" POSTERAZORHELPENDLINE \
					"<a href=\""FRENCH_POSTERAZORWEBSITEURL"\">posterazor.sourceforge.net</a><br>" POSTERAZORHELPENDLINE \
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

					"La licence GNU GPL est pour le moment en Anglais, tant que la Free Software Foundation n'aura pas valid&eacute; la licence en langue Fran&ccedil;aise.<br>&nbsp;<br>" POSTERAZORHELPENDLINE \
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
			140,140,140,140,140,28,82,255,28,82,255,28,82,255,28,82,255,28,82,255,28,82,255,
			255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0,0,
			255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,140,140,140,140,140,140,28,82,255,28,82,
			255,28,82,255,28,82,255,28,82,255,28,82,255,255,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,255,255,255,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,
			0,0,140,140,140,140,140,140,28,82,255,28,82,255,28,82,255,28,82,255,28,82,255,
			28,82,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
			255,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,140,140,140,140,140,140,28,
			82,255,28,82,255,28,82,255,28,82,255,28,82,255,28,82,255,255,255,255,255,255,
			255,255,255,255,255,255,255,255,255,255,255,255,255,255,0,0,255,0,0,255,0,0,255,
			0,0,255,0,0,255,0,0,140,140,140,140,140,140,28,82,255,28,82,255,28,82,255,28,
			82,255,28,82,255,28,82,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,140,140,140,
			140,140,140,28,82,255,28,82,255,28,82,255,28,82,255,28,82,255,28,82,255,255,255,
			255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0,0,255,0,0,
			255,0,0,255,0,0,255,0,0,255,0,0,140,140,140,140,140,140,28,82,255,28,82,255,28,
			82,255,28,82,255,28,82,255,28,82,255,255,255,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,255,255,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,
			140,140,140,140,140,140,28,82,255,28,82,255,28,82,255,28,82,255,28,82,255,28,82,
			255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,
			0,0,255,0,0,255,0,0,255,0,0,255,0,0,255,0,0,140,140,140,140,140,140,28,82,255,
			28,82,255,28,82,255,28,82,255,28,82,255,28,82,255,255,255,255,255,255,255,255,
			255,255,255,255,255,255,255,255,255,255,255,255,0,0,255,0,0,255,0,0,255,0,0,255,
			0,0,255,0,0,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140
		};

		return flagRGBData;
	}
};

static const TranslationFrench french;

#endif
