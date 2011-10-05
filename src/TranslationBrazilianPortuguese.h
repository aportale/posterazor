/*
	PosteRazor - Make your own poster!
	Copyright (C) 2005-2011 by Alessandro Portale
	http://posterazor.sourceforge.net/

	Brazilian Portuguese translation by Ederson Gomes dos Santos

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

#ifndef TranslationBrazilianPortuguese_h
#define TranslationBrazilianPortuguese_h

#include "TranslationInterface.h"
#include "TranslationConstants.h"

#define BRAZILIANPORTUGUESE_POSTERAZORWEBSITEURL POSTERAZORWEBSITEDOMAIN

class TranslationBrazilianPortuguese: public TranslationInterface
{
public:
	TranslationBrazilianPortuguese() {}

	const char* languageName(void) const                    {return "Português do Brasil";}

	const char* absoluteSize(void) const                    {return "Tamanho total:";}
	const char* allImageFormats(void) const                 {return "Todos os formatos de imagens";}
	const char* back(void) const                            {return "Voltar";}
	const char* borders(void) const                         {return "Margens";}
	const char* bottom(void) const                          {return "Inferior";}
	const char* bottomLeft(void) const                      {return "Inferior esquerdo";}
	const char* bottomRight(void) const                     {return "Inferior direito";}
	const char* cancel(void) const                          {return "Cancelar";}
	const char* colorType(void) const                       {return "Tipo de cor:";}
	const char* custom(void) const                          {return "Personalizado";}
	const char* fileCouldNotBeLoaded(void) const            {return "O arquivo \"%s\" não pôde ser carregado.";}
	const char* fileCouldNotBeSaved(void) const             {return "O arquivo \"%s\" não pôde ser salvo.";}
	const char* format(void) const                          {return "Formato:";}
	const char* grayscale(void) const                       {return "Escala de cinza";}
	const char* height(void) const                          {return "Altura:";}
	const char* imageAlignment(void) const                  {return "Alinhamento da imagem";}
	const char* imageInformations(void) const               {return "Informações da imagem";}
	const char* imageSize(void) const                       {return "Tamanho da imagem";}
	const char* inputImage(void) const                      {return "Imagem de entrada";}
	const char* landscape(void) const                       {return "Paisagem";}
	const char* language(void) const                        {return "Idioma";}
	const char* languageExplanation(void) const             {return "Escolha seu idioma";}
	const char* launchPDFApplication(void) const            {return "Execute o leitor PDF após salvar o poster";}
	const char* left(void) const                            {return "Esquerda";}
	const char* loadAnInputImage(void) const                {return stepTitle01();}
	const char* monochrome(void) const                      {return "Monocromático";}
	const char* next(void) const                            {return "Próximo";}
	const char* orientation(void) const                     {return "Orientação:";}
	const char* overlappingPosition(void) const             {return "Posição da Superposição";}
	const char* overlappingSize(void) const                 {return "Tamanho da Superposição";}
	const char* overwriteFile(void) const                   {return "O arquivo '%s' já existe.\nQuer sobrescrevê-lo?";}
	const char* pages(void) const                           {return "Páginas";}
	const char* paperFormat(void) const                     {return "Formato do papel";}
	const char* palette(void) const                         {return "Paleta";}
	const char* portrait(void) const                        {return "Retrato";}
	const char* posteRazorHelp(void) const                  {return "Ajuda do PosteRazor";}
	const char* posteRazorSettings(void) const              {return "Configurações do PosteRazor";}
	const char* posteRazorWebSiteURL(void) const            {return BRAZILIANPORTUGUESE_POSTERAZORWEBSITEURL;}
	const char* posteRazorWebSite(void) const               {return "Homepage do PosteRazor";}
	const char* previewWithOpenGL(void) const               {return "Previsualizar com OpenGL";}
	const char* previewWithOpenGLExplanation(void) const    {return "OpenGL possibilita uma previsualização fácil em sistemas modernos. Em sistemas mais antigos a previsualização fica mais lenta.";}
	const char* resolution(void) const                      {return "Resolução:";}
	const char* right(void) const                           {return "Direita";}
	const char* saveThePoster(void) const                   {return "Salvar o poster";}
	const char* saveThePosterAs(void) const                 {return "Salvar o poster como";}
	const char* settings(void) const                        {return "Configurações...";}
	const char* Size(void) const                            {return "Tamanho:";}
	const char* sizeInPages(void) const                     {return "Tamanho em páginas:";}
	const char* sizeInPercent(void) const                   {return "Tamanho em percentual:";}
	const char* sizeInPixels(void) const                    {return "Tamanho (pixels):";}
	const char* sizeInUnitOfLength(void) const              {return "Tamanho (%s):";}
	const char* standard(void) const                        {return "Padrão";}
	const char* stepXOfY(void) const                        {return "Passo %d de %d";}
	const char* top(void) const                             {return "Superior";}
	const char* topLeft(void) const                         {return "Superior esquerdo";}
	const char* topRight(void) const                        {return "Superior direito";}
	const char* unitOfLength(void) const                    {return "Unidade de Comprimento";}
	const char* unitOfLengthExplanation(void) const         {return "Escolha a unidade com que deseja trabalhar";}
	const char* width(void) const                           {return "Largura:";}


#define BRAZILIANPORTUGUESE_POSTERAZORHELSTEP                     "Passo"

#define BRAZILIANPORTUGUESE_POSTERAZORHELPABOUT                   "Sobre o PosteRazor"
#define BRAZILIANPORTUGUESE_POSTERAZORHELPMANUAL                  "Manual"
#define BRAZILIANPORTUGUESE_POSTERAZORHELPSETTINGS                "Configura&ccedil;&otilde;es"
#define BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE01             "Carregar uma imagem de entrada"
#define BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE02             "Definie o formato do papel da impressora"
#define BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLENOHTML03       "Definir a superposição do mosaico da imagem"
#define BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE03             "Definir a superposi&ccedil;&atilde;o do mosaico da imagem"
#define BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE04             "Definir o tamanho final do poster"
#define BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE05             "Salvar o Poster"
#define BRAZILIANPORTUGUESE_POSTERAZORHELPINPUTFILEFORMATS        "Arquivos de imagens de entrada suportados"
#define BRAZILIANPORTUGUESE_POSTERAZORHELPWHYPDFOUTPUT            "Porque a sa&iacute;da em PDF?"
#define BRAZILIANPORTUGUESE_POSTERAZORHELPCODEFROMTHIRDPARTIES    "C&oacute;digo de terceiros"
#define BRAZILIANPORTUGUESE_POSTERAZORHELPLICENSE                 "Licen&ccedil;a"

	const char* stepTitle01(void) const                     {return BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE01;}
	const char* stepTitle02(void) const                     {return BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE02;}
	const char* stepTitle03(void) const                     {return BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLENOHTML03;}
	const char* stepTitle04(void) const                     {return BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE04;}
	const char* stepTitle05(void) const                     {return BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE05;}
	const char* helpHtml(void) const
	{
		return	"<HTML>" POSTERAZORHELPENDLINE \
				"<BODY>" POSTERAZORHELPENDLINE \
					"<A name=\"" POSTERAZORHELPANCHORTOP "\"><CENTER><H1>PosteRazor "POSTERAZORVERSION" Help</H1></CENTER></A>" POSTERAZORHELPENDLINE \

					"<H3>Contents</H3>" POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORABOUT "\">" BRAZILIANPORTUGUESE_POSTERAZORHELPABOUT "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORMANUAL "\">" BRAZILIANPORTUGUESE_POSTERAZORHELPMANUAL "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORSETTINGS "\">" BRAZILIANPORTUGUESE_POSTERAZORHELPSETTINGS "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<UL>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP01 "\">" BRAZILIANPORTUGUESE_POSTERAZORHELSTEP " 1: " BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE01 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP02 "\">" BRAZILIANPORTUGUESE_POSTERAZORHELSTEP " 2: " BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE02 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP03 "\">" BRAZILIANPORTUGUESE_POSTERAZORHELSTEP " 3: " BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE03 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP04 "\">" BRAZILIANPORTUGUESE_POSTERAZORHELSTEP " 4: " BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE04 "</A></LI>" POSTERAZORHELPENDLINE \
							"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP05 "\">" BRAZILIANPORTUGUESE_POSTERAZORHELSTEP " 5: " BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE05 "</A></LI>" POSTERAZORHELPENDLINE \
						"</UL>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORINPUTFILEFORMATS "\">" BRAZILIANPORTUGUESE_POSTERAZORHELPINPUTFILEFORMATS "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORWHYPDFOUTPUT "\">" BRAZILIANPORTUGUESE_POSTERAZORHELPWHYPDFOUTPUT "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES "\">" BRAZILIANPORTUGUESE_POSTERAZORHELPCODEFROMTHIRDPARTIES "</A></B></LI>" POSTERAZORHELPENDLINE \
						"<LI><B><A href=\"#" POSTERAZORHELPANCHORLICENSE "\">" BRAZILIANPORTUGUESE_POSTERAZORHELPLICENSE "</A></B></LI>" POSTERAZORHELPENDLINE \
					"</UL><HR>" POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORABOUT, BRAZILIANPORTUGUESE_POSTERAZORHELPABOUT) \
					POSTERAZORHELPINDENTATION "O PosteRazor corta uma imagem e redimensiona em peda&ccedil;os que podem ser impressas e colocadas juntas formando um Poster (cartaz). Como uma imagem de entrada, uma varredura de arquivos <A href=\"#" POSTERAZORHELPANCHORMANUALSTEP01 "\">diversos</A> formatos de arquivos de imagem s&atilde;o suportados. Em evz de imprimir diretamente o poster (cartaz), o PosteRazor produz uma multi-p&aacute;gina em arquivo PDF que cont&eacute;m o poster.<br>" POSTERAZORHELPENDLINE \
					"Este &eacute; um programa open source que depende de <a href=\"#" POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES "\">outros projetos open source</a>. " POSTERAZORHELPENDLINE \
					"O PosteRazor is hospedado em <b>posterazor.sourceforge.net</b>." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUAL, BRAZILIANPORTUGUESE_POSTERAZORHELPMANUAL) \
					POSTERAZORHELPINDENTATION "PosteRazor tem a interface do usu&aacute;rio organizada em um \"Assistente\". Todas as configura&ccedil;&otilde;es para a cria&ccedil;&atilde;o do poster podem ser feitas em 5 passos. Os bot&otilde;es <b>Voltar</b> e <b>Pr&oacute;ximo</b> navegam atrav&eacute;s desses passos.<br>" POSTERAZORHELPENDLINE \
					"O bot&atilde;o <b>?</b> abre uma janela de ajuda com a explica&ccedil;&atilde;o do corrente passo.<br>" POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "Todas as entradas e escolhas s&atilde;o lembradas at&eacute; o pr&oacute;ximo uso do PosteRazor." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORSETTINGS, BRAZILIANPORTUGUESE_POSTERAZORHELPSETTINGS) \
					POSTERAZORHELPINDENTATION "Pressionando o bot&atilde;o <b>Configura&ccedil;&otilde;es...</b> na parte inferior esquerda da janela de di&aacute;logo, a janela de di&aacute;logo configura&ccedil;&otilde;es do PosteRazor &eacute; aberta." POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>Unidade de Comprimento:</b> escolha a unidade de comprimento que voc&ecirc; est&aacute; acostumado a trabalhar. Quando a unidade &eacute; modificada, todos os valores predefinidos e os valores que voc&ecirc; j&aacute; definiu s&atilde;o transformados para a nova unidade.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Linguagem:</b> escolha sua linguagem. O PosteRazor n&atilde;o precisa ser reiniciado quando uma linguagem &eacute; modificada.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Previsualiza&ccedil;&atilde;o com OpenGL:</b> escolha, se o PosteRazor deveria usar OpenGL para previsualizar a imagem. Geralmente, em hardwares novos OpenGL deve deixar mais r&aacute;pido e dar uma previsualiza&ccedil;&atilde;o mais precisa que aquela que n&atilde;o usa o OpenGL. Mas se o PosteRazor parecer lento e sem resposta, por favor veja se ele trabalha menor com o OpenGL desabilitado.</LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP01, BRAZILIANPORTUGUESE_POSTERAZORHELSTEP " 1: " BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE01) \
					POSTERAZORHELPINDENTATION "carregue a imagem clicando no bot&atilde;o com o &iacute;cone de abrir e selecione o arquivo de imagem, ou  clique & arraste uma imagem para o PosteRazor. O clique & arraste tamb&eacute;m funciona nos outros passos.<br>" POSTERAZORHELPENDLINE \
					"Muitos <a href=\"#" POSTERAZORHELPANCHORINPUTFILEFORMATS "\">formatos de arquivos e tipos de imagens</a> podem ser usados. Ap&oacute;s carregar uma imagem, a informa&ccedil;&otilde;es mais importantes s&atilde;o listadas nos campos <b>Informa&ccedil;&otilde;es da imagem</b>." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP02, BRAZILIANPORTUGUESE_POSTERAZORHELSTEP " 2: " BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE02) \
					POSTERAZORHELPINDENTATION "Defina o tamanho da folha de papel que usa em sua impressora. Um tamanho padr&atilde;o de folhe pode ser selecionado atrav&eacute;s da escolha <b>Formato</b>, bem como a dsejada <b>Orientation</b> do papel. Alternativamente, pode definir um tamanho personalizado na aba <b>Personalizar</b>. (Favor me escrever um e-mail caso seu tamanho padr&atilde;o escolhido seja perdido). " POSTERAZORHELPENDLINE \
					"As bordas do papel s&atilde;o definidas nos campos <b>Bordas</b>. Mesmo que sua impressora n&atilde;o precise (precise de pequenas) de bordas na folha, algumas bordas podem ser necess&aacute;rias para ter &aacute;rea suficiente para colar as folhas do poster final." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP03, BRAZILIANPORTUGUESE_POSTERAZORHELSTEP " 3: " BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE03) \
					POSTERAZORHELPINDENTATION "A sobreposi&ccedil;&atilde;o do mosaico &eacute; necess&aacute;ria para ter alguma toler&acirc;ncia para cortar totalmente as bordas desnecess&aacute;rias de um lado. Assim, como nas margens do passo anterior, d&aacute; uma &aacute;rea maior para colar juntas as p&aacute;ginas do poster final. " POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "The <b>Posi&ccedil;&atilde;o de sobreposi&ccedil;&atilde;o</b> define as margens destinadas a sobrepor cm as p&aacute;ginas vizinhas. As margens dos lados opostos devem ser cortadas (exceto as p&aacute;ginas ultraperif&eacute;ricas)." POSTERAZORHELPENDLINE \
					
					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP04, BRAZILIANPORTUGUESE_POSTERAZORHELSTEP " 4: " BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE04) \
					POSTERAZORHELPINDENTATION "Define o tamanho final do poster, em um dos tr&ecirc;s modos seguintes que podem ser selecionados com os bot&otilde;es correspondentes:<br>" POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>Tamanho total da imagem</b>: usado para determinar o tamanho do poster.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Tamanho em p&aacute;ginas</b>: usado para determinar quantas p&aacute;ginas inteiras ser&atilde;o usadas pelo poster.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Tamanho da imagem em porcentagem</b>: sua imagem de entrada tem o tamanho definido pelo n&uacute;mero de pixels e dpi (pontos por polegadas) e voc&ecirc; quer aumentar a imagem por um certo fator.</LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "O tamanho da largura e altura &eacute; sempre 1:1 e &eacute; automaticamente recalculado. Na &aacute;rea de previsualiza&ccedil;&atilde;o, voc&ecirc; pode ver as &aacute;reas de sobreposi&ccedil;&atilde;o que ser&atilde;o marcadas por ret&acirc;ngulos vermelhos. " POSTERAZORHELPENDLINE \
					"<b>Alinhamento da imagem</b> estabelece o alinhamento da imagem na &aacute;rea total do papel do poster. Isto &eacute; util se voc&ecirc; quer guardar o papel n&atilde;o utilizado." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP05, BRAZILIANPORTUGUESE_POSTERAZORHELSTEP " 5: " BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE05) \
					POSTERAZORHELPINDENTATION "Salve o portsre clicando no bot&atilde;o Salvar e especificando o nome do arquivo destino. Marque ou desmarque o <b>Executar aplica&ccedil;&atilde;o PDF ap&oacute;s o porter ser salvo</b>, para, uma vez salvo o aqruivo PDF, abrir o aplicativo de PDF automaticamente." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORINPUTFILEFORMATS, BRAZILIANPORTUGUESE_POSTERAZORHELPINPUTFILEFORMATS) \
					POSTERAZORHELPINDENTATION "A maioria dos formatos de imagem s&atilde;o suportados pelo FreeImage tamb&eacute;m s&atilde;o suportadas pelo PosteRazor:<br>" POSTERAZORHELPENDLINE \
					"<b>BMP, arquivos DDS, Dr. Halo, GIF, ICO, IFF, JBIG, JPEG/JIF, KOALA, LBM, Kodak PhotoCD, PCX, PBM, PGM, PNG, PPM, PhotoShop PSD, Sun RAS, TARGA, TIFF, WBMP, XBM, XPM.<br></b>" POSTERAZORHELPENDLINE \
					"PosteRazor distingue e maneja imagens monocrom&aacute;ticas, escala de cinza, paleta de 4-bits, paleta de 8-bits, RGB 24 bits, e CMYK (apenas de TIF). Imagens RGB com um canal alfa s&atilde;o compostas automaticamente sobre um fundo branco." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORWHYPDFOUTPUT, BRAZILIANPORTUGUESE_POSTERAZORHELPWHYPDFOUTPUT) \
					POSTERAZORHELPINDENTATION "Porque o arquivo PDF n&atilde;o &eacute; automaticamente impresso? Primeiro que o desenvolvedor do software n&atilde;o sabe (ainda) como fazer isso, do tipo \"enviar imagens para a impressora\", em diferentes sistemas operacionais, os quais Posterrazor funciona. Tamb&eacute;m, PDF faz sentido, se o poster &eacute; criado em casa com toda a disponibilidade de tempo, no dia seguinte pode ser impresso numa impressora a laser colorida em outro local. " POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "Por que PDF e n&atilde;o outro formato de arquivo? PDF d&aacute; a possibilidade de juntar toda a imagem e cort&aacute;-la virtualmente, e n&atilde;o apenas em pixel mas tamb&eacute;m em suas fra&ccedil;&otilde;es. Al&eacute;m disso, parece ser mais pr&aacute;tico imprimir um arquivo PDF multi-p&aacute;ginas que m&uacute;ltiplos arquivos de imagem." POSTERAZORHELPENDLINE \
					
					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES, BRAZILIANPORTUGUESE_POSTERAZORHELPCODEFROMTHIRDPARTIES) \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>FLTK</b> &eacute; usado para a interface do usu&aacute;rio. &Eacute; pequeno (pelo tamanho), r&aacute;pido, divertido e f&aacute;cil de aprender e uma UI muito port&aacute;vel. <a href=\"http://www.fltk.org/\">www.fltk.org</a></LI>" POSTERAZORHELPENDLINE \
					"<LI><b>FreeImage</b> &eacute; usado para carregar e manipular. Ele carregar e realmente manipula para v&aacute;rias plataformas, onde PosteRazor pode ser executado. <a href=\"http://freeimage.sourceforge.net/\">FreeImage website</a></LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Fl_Native_File_Chooser</b> &eacute; usado nos di&aacute;logos abrir e salvar. <a href=\"http://seriss.com/people/erco/fltk/Fl_Native_File_Chooser/\">Fl_Native_File_Chooser website</a></LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \
					
					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORLICENSE, BRAZILIANPORTUGUESE_POSTERAZORHELPLICENSE) \
					"PosteRazor - Fa&ccedil;a seu pr&oacute;prio poster!<br>" POSTERAZORHELPENDLINE \
					"<a href=\""BRAZILIANPORTUGUESE_POSTERAZORWEBSITEURL"\">posterazor.sourceforge.net</a><br>" POSTERAZORHELPENDLINE \
					POSTERAZORCOPYRIGHT \

					POSTERAZORTRANSLATIONCREDITSSTART \
					POSTERAZORTRANSLATIONCREDITSBRAZILIANPORTUGUESE \
					POSTERAZORTRANSLATIONCREDITSFRENCH \
					POSTERAZORTRANSLATIONCREDITSPOLISH \
					POSTERAZORTRANSLATIONCREDITSDUTCH \
					POSTERAZORTRANSLATIONCREDITSITALIAN \
					POSTERAZORTRANSLATIONCREDITSSPANISH \
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
			140,140,140,140,140,0,175,75,0,175,75,0,175,75,0,175,75,0,175,75,0,175,75,0,175,
			75,0,175,75,62,192,56,62,192,56,0,175,75,0,175,75,0,175,75,0,175,75,0,175,75,0,
			175,75,0,175,75,0,175,75,140,140,140,140,140,140,0,175,75,0,175,75,0,175,75,0,
			175,75,0,175,75,0,175,75,62,192,56,187,226,19,248,243,0,248,243,0,187,226,19,62,
			192,56,0,175,75,0,175,75,0,175,75,0,175,75,0,175,75,0,175,75,140,140,140,140,
			140,140,0,175,75,0,175,75,0,175,75,0,175,75,62,192,56,187,226,19,236,233,8,139,
			150,75,67,88,126,67,88,126,139,150,75,236,233,8,187,226,19,62,192,56,0,175,75,0,
			175,75,0,175,75,0,175,75,140,140,140,140,140,140,0,175,75,0,175,75,62,192,56,
			187,226,19,248,243,0,248,243,0,160,168,111,121,137,193,121,137,193,53,78,142,30,
			57,151,139,150,75,248,243,0,248,243,0,187,226,19,62,192,56,0,175,75,0,175,75,
			140,140,140,140,140,140,0,175,75,124,209,37,248,243,0,248,243,0,248,243,0,248,
			243,0,53,78,142,30,57,151,33,59,152,113,130,189,94,113,181,53,78,142,248,243,0,
			248,243,0,248,243,0,248,243,0,124,209,37,0,175,75,140,140,140,140,140,140,0,175,
			75,0,175,75,62,192,56,187,226,19,248,243,0,248,243,0,139,150,75,30,57,151,30,
			57,151,30,57,151,94,113,181,160,168,111,248,243,0,248,243,0,187,226,19,62,192,
			56,0,175,75,0,175,75,140,140,140,140,140,140,0,175,75,0,175,75,0,175,75,0,175,
			75,62,192,56,187,226,19,236,233,8,139,150,75,67,88,126,67,88,126,139,150,75,
			236,233,8,187,226,19,62,192,56,0,175,75,0,175,75,0,175,75,0,175,75,140,140,140,
			140,140,140,0,175,75,0,175,75,0,175,75,0,175,75,0,175,75,0,175,75,62,192,56,187,
			226,19,248,243,0,248,243,0,187,226,19,62,192,56,0,175,75,0,175,75,0,175,75,0,
			175,75,0,175,75,0,175,75,140,140,140,140,140,140,0,175,75,0,175,75,0,175,75,0,
			175,75,0,175,75,0,175,75,0,175,75,0,175,75,62,192,56,62,192,56,0,175,75,0,175,
			75,0,175,75,0,175,75,0,175,75,0,175,75,0,175,75,0,175,75,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140
		};

		return flagRGBData;
	}
};

static const TranslationBrazilianPortuguese brazilianPortuguese;

#endif
