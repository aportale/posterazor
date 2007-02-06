/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2007 by Alessandro Portale
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

#ifndef TranslationSpanish_h
#define TranslationSpanish_h

#include "TranslationInterface.h"
#include "TranslationConstants.h"

#define SPANISH_POSTERAZORWEBSITEURL POSTERAZORWEBSITEDOMAIN

class TranslationSpanish: public TranslationInterface
{
public:
	const char* languageName(void)                    {return "Español";}

	const char* absoluteSize(void)                    {return "Tamaño total:";}
	const char* allImageFormats(void)                 {return "Todos los formatos de imagen";}
	const char* back(void)                            {return "Atrás";}
	const char* borders(void)                         {return "Márgenes";}
	const char* bottom(void)                          {return "Inferior";}
	const char* bottomLeft(void)                      {return "Inferior izquierdo";}
	const char* bottomRight(void)                     {return "Inferior derecho";}
	const char* cancel(void)                          {return "Cancelar";}
	const char* colorType(void)                       {return "Tipo de color:";}
	const char* custom(void)                          {return "Personalizado";}
	const char* fileCouldNotBeLoaded(void)            {return "No se pudo cargar el archivo \"%s\".";}
	const char* fileCouldNotBeSaved(void)             {return "No se pudo guardar el archivo \"%s\".";}
	const char* format(void)                          {return "Formato:";}
	const char* grayscale(void)                       {return "Escala de grises";}
	const char* height(void)                          {return "Altura:";}
	const char* imageAlignment(void)                  {return "Alineación de imagen";}
	const char* imageInformations(void)               {return "Informaciones de imagen";}
	const char* imageSize(void)                       {return "Tamaño de imagen";}
	const char* inputImage(void)                      {return "Imagen de entrada";}
	const char* landscape(void)                       {return "Horizontal";}
	const char* language(void)                        {return "Idioma";}
	const char* languageExplanation(void)             {return "Escoja su idioma";}
	const char* launchPDFApplication(void)            {return "Ejecutar la aplicación PDF tras guardar el poster";}
	const char* left(void)                            {return "Izquierdo";}
	const char* loadAnInputImage(void)                {return stepTitle01();}
	const char* monochrome(void)                      {return "Monocromo";}
	const char* next(void)                            {return "Siguiente";}
	const char* orientation(void)                     {return "Orientación:";}
	const char* overlappingPosition(void)             {return "Posición de superposición";}
	const char* overlappingSize(void)                 {return "Tamaño de superposición";}
	const char* overwriteFile(void)                   {return "El archivo '%s' ya existe.\n¿Desea sobrescribirlo?";}
	const char* pages(void)                           {return "páginas";}
	const char* paperFormat(void)                     {return "Formato de papel";}
	const char* palette(void)                         {return "Paleta";}
	const char* portrait(void)                        {return "Vertical";}
	const char* posteRazorHelp(void)                  {return "Ayuda de PosteRazor";}
	const char* posteRazorSettings(void)              {return "Configuración de PosteRazor";}
	const char* posteRazorWebSiteURL(void)            {return SPANISH_POSTERAZORWEBSITEURL;}
	const char* posteRazorWebSite(void)               {return "Sitio web de PosteRazor";}
	const char* previewWithOpenGL(void)               {return "Previsualizar con OpenGL";}
	const char* previewWithOpenGLExplanation(void)    {return "OpenGL posibilita una previsualización fácil en los sistemas modernos. En sistemas antiguos puede ralentizar la previsualización.";}
	const char* resolution(void)                      {return "Resolución:";}
	const char* right(void)                           {return "Derecho";}
	const char* saveThePoster(void)                   {return "Guardar el póster";}
	const char* saveThePosterAs(void)                 {return "Guardar el póster como";}
	const char* settings(void)                        {return "Configuraciones...";}
	const char* Size(void)                            {return "Tamaño:";}
	const char* sizeInPages(void)                     {return "Tamaño en páginas:";}
	const char* sizeInPercent(void)                   {return "Tamaño en porcentaje:";}
	const char* sizeInPixels(void)                    {return "Tamaño (en píx.):";}
	const char* sizeInUnitOfLength(void)              {return "Tamaño (in %s):";}
	const char* standard(void)                        {return "Estándar";}
	const char* stepXOfY(void)                        {return "Paso %d de %d";}
	const char* top(void)                             {return "Superior";}
	const char* topLeft(void)                         {return "Superior izquierdo";}
	const char* topRight(void)                        {return "Superior derecho";}
	const char* unitOfLength(void)                    {return "Unidad de longitud";}
	const char* unitOfLengthExplanation(void)         {return "Escoja la unidad con la que desea trabajar";}
	const char* width(void)                           {return "Anchura:";}


#define SPANISH_POSTERAZORHELSTEP                         "Paso"

#define SPANISH_POSTERAZORHELPABOUT                       "Acerca de PosteRazor"
#define SPANISH_POSTERAZORHELPMANUAL                      "Manual"
#define SPANISH_POSTERAZORHELPSETTINGS                    "Configuraciones"
#define SPANISH_POSTERAZORHELPSTEPTITLE01                 "Cargar una imagen de entrada"
#define SPANISH_POSTERAZORHELPSTEPTITLE02                 "Definir el formato del papel de impresora"
#define SPANISH_POSTERAZORHELPSTEPTITLE03                 "Definir la superposición del mosaico de imagen"
#define SPANISH_POSTERAZORHELPSTEPTITLE04                 "Definir el tamaño final del póster"
#define SPANISH_POSTERAZORHELPSTEPTITLE05                 "Guardar el póster"
#define SPANISH_POSTERAZORHELPINPUTFILEFORMATS            "Archivos soportados para imagen de entrada"
#define SPANISH_POSTERAZORHELPWHYPDFOUTPUT                "¿Por qué un PDF de salida?"
#define SPANISH_POSTERAZORHELPCODEFROMTHIRDPARTIES        "Código de terceros"
#define SPANISH_POSTERAZORHELPLICENSE                     "Licencia"

	const char* stepTitle01(void)                     {return SPANISH_POSTERAZORHELPSTEPTITLE01;}
	const char* stepTitle02(void)                     {return SPANISH_POSTERAZORHELPSTEPTITLE02;}
	const char* stepTitle03(void)                     {return SPANISH_POSTERAZORHELPSTEPTITLE03;}
	const char* stepTitle04(void)                     {return SPANISH_POSTERAZORHELPSTEPTITLE04;}
	const char* stepTitle05(void)                     {return SPANISH_POSTERAZORHELPSTEPTITLE05;}
	const char* helpHtml(void)
	{
		return	"<HTML>" POSTERAZORHELPENDLINE \
				"<BODY>" POSTERAZORHELPENDLINE \
					"<A name=\"" POSTERAZORHELPANCHORTOP "\"><CENTER><H1>Ayuda de PosteRazor "POSTERAZORVERSION"</H1></CENTER></A>" POSTERAZORHELPENDLINE \

					"<H3>Contenidos</H3>" POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORABOUT "\">" SPANISH_POSTERAZORHELPABOUT "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORMANUAL "\">" SPANISH_POSTERAZORHELPMANUAL "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORSETTINGS "\">" SPANISH_POSTERAZORHELPSETTINGS "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<UL>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP01 "\">" SPANISH_POSTERAZORHELSTEP " 1: " SPANISH_POSTERAZORHELPSTEPTITLE01 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP02 "\">" SPANISH_POSTERAZORHELSTEP " 2: " SPANISH_POSTERAZORHELPSTEPTITLE02 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP03 "\">" SPANISH_POSTERAZORHELSTEP " 3: " SPANISH_POSTERAZORHELPSTEPTITLE03 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP04 "\">" SPANISH_POSTERAZORHELSTEP " 4: " SPANISH_POSTERAZORHELPSTEPTITLE04 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP05 "\">" SPANISH_POSTERAZORHELSTEP " 5: " SPANISH_POSTERAZORHELPSTEPTITLE05 "</A></LI>" POSTERAZORHELPENDLINE \
						"</UL>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORINPUTFILEFORMATS "\">" SPANISH_POSTERAZORHELPINPUTFILEFORMATS "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORWHYPDFOUTPUT "\">" SPANISH_POSTERAZORHELPWHYPDFOUTPUT "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES "\">" SPANISH_POSTERAZORHELPCODEFROMTHIRDPARTIES "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORLICENSE "\">" SPANISH_POSTERAZORHELPLICENSE "</A></B></LI>" POSTERAZORHELPENDLINE \
					"</UL><HR>" POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORABOUT, SPANISH_POSTERAZORHELPABOUT) \
					POSTERAZORHELPINDENTATION "PosteRazor corta una imagen ráster en partes que puedan ser impresas con una impresora y que se puedan unir para formar un póster. Se puede utilizar como imagen de entrada ficheros ráster de <A href=\"#" POSTERAZORHELPANCHORMANUALSTEP01 "\">varios</A> formatos de archivo de imagen. En lugar de imprimir directamente el póster, PosteRazor produce un archivo PDF de varias páginas que contiene el mosaico del póster.<br>" POSTERAZORHELPENDLINE \
					"Este es un programa de código abierto que depende de <a href=\"#" POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES "\">otros proyectos de código abierto</a>. " POSTERAZORHELPENDLINE \
					"PosteRazor está alojado en <b>posterazor.sourceforge.net</b>." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUAL, SPANISH_POSTERAZORHELPMANUAL) \
					POSTERAZORHELPINDENTATION "PosteRazor tiene una interfáz de usuario organizada en un estilo de \"Asistente\". Todos los ajustes para la creación del póster pueden ser realizados en 5 Pasos. Los botones <b>Atrás</b> y <b>Siguiente</b> sirven para navegar a través de estos pasos.<br>" POSTERAZORHELPENDLINE \
					"El botón <b>?</b> abre una ventana de ayuda con una explicación del paso actual.<br>" POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "Todas las entradas y elecciones son recordadas hasta el siguiente uso de PosteRazor." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORSETTINGS, SPANISH_POSTERAZORHELPSETTINGS) \
					POSTERAZORHELPINDENTATION "Al pulsar el botón <b>Configuraciones...</b> de la parte inferior izquierda del diálogo principal se abre el diálogo de opciones de PosteRazor." POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>Unidad de longitud:</b> selecciona la unidad de longitud con la que trabajar. Cuando se cambia de unidad todos los valores predefinidos, y los que usted ya ha definido, son transformados a la nueva unidad.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Idioma:</b> selecciona su idioma. PosteRazor no necesita ser reiniciado cuando se cambia el idioma.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Previsualizar con OpenGL:</b> selecciona si PosteRazor debe usar OpenGL para la previsualización de la imagen. Normalmente, en los sistemas modernos OpenGL debería ser más rápido y dar una previsualización más precisa que en la forma no-OpenGL. Si el programa parece ralentizarse y no responde, verifique si funciona mejor sin el OpenGL.</LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP01, SPANISH_POSTERAZORHELSTEP " 1: " SPANISH_POSTERAZORHELPSTEPTITLE01) \
					POSTERAZORHELPINDENTATION "Cargue una imagen haciendo clic sobre el botón del icono de Abrir y seleccione un archivo de imagen, o arrastre y suelte un archivo de imagen dentro de PosteRazor. La función arrastrar-y-soltar también opera en los demás pasos.<br>" POSTERAZORHELPENDLINE \
					"Se pueden cargar muchos <a href=\"#" POSTERAZORHELPANCHORINPUTFILEFORMATS "\">formatos de archivo y tipos de imagen</a>. Después de cargar la imagen se presentan las informaciones más relevantes en los campos de <b>Informaciones de imagen</b>." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP02, SPANISH_POSTERAZORHELSTEP " 2: " SPANISH_POSTERAZORHELPSTEPTITLE02) \
					POSTERAZORHELPINDENTATION "Defina el tamaño de la hoja de papel que usa su impresora. Puede seleccionar una hoja de papel de tamaño estándar desde el seleccionador <b>Formato</b>, así como también la <b>Orientación</b> de la hoja de papel. Alternativemente, puede definir un tamaño personalizado de papel en la pestaña <b>Personalizado</b>. (Por favor escríbame un email si echa de menos en el seleccionador su tamaño de papel estándar). " POSTERAZORHELPENDLINE \
					"Los márgenes del papel son definidos en los campos <b>Márgenes</b>. Aún si su impresora no necesita márgenes de papel, podría ser necesario algún margen para pegar conjuntamente las últimas piezas del póster." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP03, SPANISH_POSTERAZORHELSTEP " 3: " SPANISH_POSTERAZORHELPSTEPTITLE03) \
					POSTERAZORHELPINDENTATION "La superposición del mosaico es necesaria para tener alguna tolerancia para cortar totalmente los bordes innecesarios de un lado. Además, como en los márgenes del paso anterior, se da más área para pegar conjuntamente las piezas finales del póster. " POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "La <b>Posición de superposición</b> define los márgenes destinados a superponerse con las piezas de alrededor. Los márgenes de los lados opuestos son para ser cortados (excepto en las piezas más exteriores)." POSTERAZORHELPENDLINE \
					
					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP04, SPANISH_POSTERAZORHELSTEP " 4: " SPANISH_POSTERAZORHELPSTEPTITLE04) \
					POSTERAZORHELPINDENTATION "Define el tamaño final del póster en uno de los siguientes tres modos que pueden ser seleccionados con los correspondientes botones:<br>" POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>Tamaño total de la imagen</b>: usted desea tener un tamaño determinado de póster.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Tamaño en páginas</b>: usted quiere usar hojas de papel enteras y especificar cuántas de ellas desea usar.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Tamaño de imagen en porcentaje</b>: su imagen de entrada tiene un cierto tamaño que es definido por el número de píxeles y dpi (puntos por pulgada) y usted quiere aumentar la imagen por un cierto factor.</LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "La proporción dimensional de anchura y altura es siempre 1:1 y es automáticamente calculada de nuevo. En el área de previsualización se pueden ver las áreas de superposición en rectángulos de color rojo claro. " POSTERAZORHELPENDLINE \
					"La <b>Alineación de imagen</b> establece la alineación de la imagen en el total del papel del póster. Esto es útil si desea conservar el papel no usado." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP05, SPANISH_POSTERAZORHELSTEP " 5: " SPANISH_POSTERAZORHELPSTEPTITLE05) \
					POSTERAZORHELPINDENTATION "Guarde el póster pulsando el botón Guardar y especificando un nombre para el archivo resultante. Marque o desmaque la opción <b>Ejecutar la aplicación PDF tras guardar el poster</b> para, una vez guardado el archivo PDF resultante, iniciar automáticamente la aplicación predeterminada en su sistema para el manejo de archivos PDF ." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORINPUTFILEFORMATS, SPANISH_POSTERAZORHELPINPUTFILEFORMATS) \
					POSTERAZORHELPINDENTATION "La mayoría de los formatos de imagen ráster soportados por FreeImage también son soportados por PosteRazor:<br>" POSTERAZORHELPENDLINE \
					"<b>BMP, archivos DDS, Dr. Halo, GIF, ICO, IFF, JBIG, JNG, JPEG/JIF, KOALA, LBM, Kodak PhotoCD, MNG, PCX, PBM, PGM, PNG, PPM, PhotoShop PSD, Sun RAS, TARGA, TIFF, WBMP, XBM, XPM.<br></b>" POSTERAZORHELPENDLINE \
					"PosteRazor distingue y maneja imágenes monocromas, de escala de grises, de paleta de 4-bit, de paleta de 8-bit, de 24 bit RGB, y CMYK (sólo desde TIF). Las imágenes RGB con un canal alfa son compuestas automáticamente encima de un fondo blanco." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORWHYPDFOUTPUT, SPANISH_POSTERAZORHELPWHYPDFOUTPUT) \
					POSTERAZORHELPINDENTATION "¿Por qué un PDF resultante y no la impresión directa? Lo primero de todo es que el desarrollador de este programa no conoce (aún) como \"enviar imágenes a la impresora\", en los diferentes sistemas operativos, que es a lo que PosteRazor aspira. También el PDF tiene sentido si se hace un póster en casa con todo el tiempo necesario y al día siguiente se imprime en la impresora laser a color de la oficina (después de que todo el mundo se haya ido a casa). " POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "¿Por qué un PDF y no otros formatos ráster? El PDF da la posibilidad de implantar la imagen completa y cortarla virtualmente, y no sólo en píxeles, sino también con fracciones de píxeles. Además, parece más factible imprimir un archivo PDF de varias páginas en vez de múltiples archivos de imagen." POSTERAZORHELPENDLINE \
					
					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES, SPANISH_POSTERAZORHELPCODEFROMTHIRDPARTIES) \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>FLTK</b> es usado por la interfáz de usuario. Es pequeño (por tamaño), rápido, fácil y divertido de aprender y muy portable. <a href=\"http://www.fltk.org/\">www.fltk.org</a></LI>" POSTERAZORHELPENDLINE \
					"<LI><b>FreeImage</b> es usado para cargar y manejar la imagen. Hace que éstas operaciones sean sencillas de ejecutar y es portable a las platformas en las que PosteRazor funciona. <a href=\"http://freeimage.sourceforge.net/\">Sitio web de FreeImage</a></LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Fl_Native_File_Chooser</b> es usado para los diálogos de Abrir y Guardar en la apariencia y percepción del sistema nativo. <a href=\"http://seriss.com/people/erco/fltk/Fl_Native_File_Chooser/\">Sitio web de Fl_Native_File_Chooser</a></LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \
					
					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORLICENSE, SPANISH_POSTERAZORHELPLICENSE) \
					"PosteRazor - ¡Haz tu propio póster!<br>" POSTERAZORHELPENDLINE \
					"<a href=\""SPANISH_POSTERAZORWEBSITEURL"\">posterazor.sourceforge.net</a><br>" POSTERAZORHELPENDLINE \
					"Copyright (C) 2005-2007 por Alessandro Portale<br>&nbsp;<br>" POSTERAZORHELPENDLINE \

					"<b>Traducción al Español por <a href=\"http://hispanicoweb.net\">HispánicoWeb</a></b><br>" POSTERAZORHELPENDLINE \
					"<b>Traducción al Holandés/Belga por Erik Wijkamp - Lochem (Los Paises Bajos) (e_wijkamp<b></b>@<b></b>yahoo<b></b>.<b></b>com).</b><br>" POSTERAZORHELPENDLINE \
					"<b>Traducción al Francés por Martin Loyer (traduction<b></b>@<b></b>loyer<b></b>.<b></b>name).</b><br>" POSTERAZORHELPENDLINE \
					"<b>Traducción al Polaco por Grzegorz Wacikowski.</b><br>" POSTERAZORHELPENDLINE \
					"<b>Traducción al Italiano por Stefano Nosei (kluster<b></b>@<b></b>imente<b></b>.<b></b>org).</b><br>" POSTERAZORHELPENDLINE \

					"&nbsp;<br>" \

					"Este programa es software libre; puede usted redistribuirlo y/o modificarlo bajo los términos de la <a href=\"http://www.gnu.org/licenses/gpl.txt\">Licencia Pública General GNU</a> publicada por la Free Software Foundation; ya sea en la versión 2 de la Licencia, o (a su opción) en cualquier versión posterior.<br>&nbsp;<br>" POSTERAZORHELPENDLINE \
					"Este programa es distribuido con la esperanza de que será útil, pero SIN NINGUNA GARANTIA; incluso sin la garantía implícita de MERCANTIBILIDAD o APTITUD PARA UN PROPOSITO PARTICULAR. Vea la Licencia Pública General GNU para más información.<br>&nbsp;<br>" POSTERAZORHELPENDLINE \
					"Usted debería haber recibido una copia de la Licencia Pública General GNU junto con este programa; si no es así, escriba a la Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA." POSTERAZORHELPENDLINE \
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
			140,140,140,140,140,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,
			0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,
			247,0,0,140,140,140,140,140,140,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,
			247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,
			247,0,0,247,0,0,140,140,140,140,140,140,253,226,1,253,226,1,163,96,0,163,96,0,
			163,96,0,163,96,0,253,226,1,253,226,1,253,226,1,253,226,1,253,226,1,253,226,1,
			253,226,1,253,226,1,253,226,1,253,226,1,253,226,1,253,226,1,140,140,140,140,140,
			140,253,226,1,0,0,0,253,226,1,117,104,0,117,104,0,253,226,1,0,0,0,253,226,1,253,
			226,1,253,226,1,253,226,1,253,226,1,253,226,1,253,226,1,253,226,1,253,226,1,253,
			226,1,253,226,1,140,140,140,140,140,140,253,226,1,254,96,96,174,14,14,174,14,14,
			254,96,96,254,96,96,254,96,96,253,226,1,253,226,1,253,226,1,253,226,1,253,226,1,
			253,226,1,253,226,1,253,226,1,253,226,1,253,226,1,253,226,1,140,140,140,140,140,
			140,253,226,1,254,96,96,174,14,14,174,14,14,174,14,14,174,14,14,254,96,96,253,
			226,1,253,226,1,253,226,1,253,226,1,253,226,1,253,226,1,253,226,1,253,226,1,253,
			226,1,253,226,1,253,226,1,140,140,140,140,140,140,253,226,1,0,53,225,253,226,1,
			174,14,14,174,14,14,253,226,1,0,53,225,253,226,1,253,226,1,253,226,1,253,226,1,
			253,226,1,253,226,1,253,226,1,253,226,1,253,226,1,253,226,1,254,227,1,140,140,
			140,140,140,140,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,
			247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,
			140,140,140,140,140,140,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,
			247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,247,0,0,
			247,0,0,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140
		};

		return flagRGBData;
	}
};

static TranslationSpanish spanish;

#endif
