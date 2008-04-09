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

#ifndef TranslationBrazilianPortuguese_h
#define TranslationBrazilianPortuguese_h

#include "TranslationInterface.h"
#include "TranslationConstants.h"

#define BRAZILIANPORTUGUESE_POSTERAZORWEBSITEURL POSTERAZORWEBSITEDOMAIN

class TranslationBrazilianPortuguese: public TranslationInterface
{
public:
	const char* languageName(void)                    {return "Português do Brasil";}

	const char* absoluteSize(void)                    {return "Tamanho total:";}
	const char* allImageFormats(void)                 {return "Todos os formatos de imagens";}
	const char* back(void)                            {return "Voltar";}
	const char* borders(void)                         {return "Margens";}
	const char* bottom(void)                          {return "Inferior";}
	const char* bottomLeft(void)                      {return "Inferior esquerdo";}
	const char* bottomRight(void)                     {return "Inferior direito";}
	const char* cancel(void)                          {return "Cancelar";}
	const char* colorType(void)                       {return "Tipo de cor:";}
	const char* custom(void)                          {return "Personalizado";}
	const char* fileCouldNotBeLoaded(void)            {return "O arquivo \"%s\" não pôde ser carregado.";}
	const char* fileCouldNotBeSaved(void)             {return "O Arquivo \"%s\" não pôde ser salvo.";}
	const char* format(void)                          {return "Formato:";}
	const char* grayscale(void)                       {return "Escala de cinza";}
	const char* height(void)                          {return "Altura:";}
	const char* imageAlignment(void)                  {return "Alinhamento da imagem";}
	const char* imageInformations(void)               {return "Informações da imagem";}
	const char* imageSize(void)                       {return "Tamanho da imagem";}
	const char* inputImage(void)                      {return "Imagem de entrada";}
	const char* landscape(void)                       {return "Paisagem";}
	const char* language(void)                        {return "Idioma";}
	const char* languageExplanation(void)             {return "Escolha seu idioma";}
	const char* launchPDFApplication(void)            {return "Execute o leitor PDF após salvar o poster";}
	const char* left(void)                            {return "Esquerda";}
	const char* loadAnInputImage(void)                {return stepTitle01();}
	const char* monochrome(void)                      {return "Monocromático";}
	const char* next(void)                            {return "Próximo";}
	const char* orientation(void)                     {return "Orientação:";}
	const char* overlappingPosition(void)             {return "Posição da Superposição";}
	const char* overlappingSize(void)                 {return "Tamanho da Superposição";}
	const char* overwriteFile(void)                   {return "O arquivo '%s' já existe.\nQuer sobrescrevê-lo?";}
	const char* pages(void)                           {return "Páginas";}
	const char* paperFormat(void)                     {return "Formato do papel";}
	const char* palette(void)                         {return "Paleta";}
	const char* portrait(void)                        {return "Retrato";}
	const char* posteRazorHelp(void)                  {return "Ajuda do PosteRazor";}
	const char* posteRazorSettings(void)              {return "Configurações do PosteRazor";}
	const char* posteRazorWebSiteURL(void)            {return BRAZILIANPORTUGUESE_POSTERAZORWEBSITEURL;}
	const char* posteRazorWebSite(void)               {return "Homepage do PosteRazor";}
	const char* previewWithOpenGL(void)               {return "Previsualizar com OpenGL";}
	const char* previewWithOpenGLExplanation(void)    {return "OpenGL possibilita uma previsualização fácil em sistemas modernos. Em sistemas mais antigos a previsualização fica mais lenta.";}
	const char* resolution(void)                      {return "Resolução:";}
	const char* right(void)                           {return "Direita";}
	const char* saveThePoster(void)                   {return "Salvar o poster";}
	const char* saveThePosterAs(void)                 {return "Salvar o poster como";}
	const char* settings(void)                        {return "Configurações...";}
	const char* Size(void)                            {return "Tamanho:";}
	const char* sizeInPages(void)                     {return "Tamanho em páginas:";}
	const char* sizeInPercent(void)                   {return "Tamanho em percentual:";}
	const char* sizeInPixels(void)                    {return "Tamanho (em pixels):";}
	const char* sizeInUnitOfLength(void)              {return "Tamanho (em %s):";}
	const char* standard(void)                        {return "Padrão";}
	const char* stepXOfY(void)                        {return "Passo %d de %d";}
	const char* top(void)                             {return "Superior";}
	const char* topLeft(void)                         {return "Superior esquerdo";}
	const char* topRight(void)                        {return "Superior direito";}
	const char* unitOfLength(void)                    {return "Unidade de Comprimento";}
	const char* unitOfLengthExplanation(void)         {return "Escolha a unidade com que deseja trabalhar";}
	const char* width(void)                           {return "Largura:";}


#define BRAZILIANPORTUGUESE_POSTERAZORHELSTEP                     "Passo"

#define BRAZILIANPORTUGUESE_POSTERAZORHELPABOUT                   "Sobre o PosteRazor"
#define BRAZILIANPORTUGUESE_POSTERAZORHELPMANUAL                  "Manual"
#define BRAZILIANPORTUGUESE_POSTERAZORHELPSETTINGS                "Configurações"
#define BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE01             "Carregar uma imagem de entrada"
#define BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE02             "Definie o formato do papel da impressora"
#define BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE03             "Definir a superposição do mosaico da imagem"
#define BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE04             "Definir o tamanho final do poster"
#define BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE05             "Salvar o Poster"
#define BRAZILIANPORTUGUESE_POSTERAZORHELPINPUTFILEFORMATS        "Arquivos de imagens de entrada suportados"
#define BRAZILIANPORTUGUESE_POSTERAZORHELPWHYPDFOUTPUT            "Porque a saída em PDF?"
#define BRAZILIANPORTUGUESE_POSTERAZORHELPCODEFROMTHIRDPARTIES    "Código de terceiros"
#define BRAZILIANPORTUGUESE_POSTERAZORHELPLICENSE                 "Licença"

	const char* stepTitle01(void)                     {return BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE01;};
	const char* stepTitle02(void)                     {return BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE02;};
	const char* stepTitle03(void)                     {return BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE03;};
	const char* stepTitle04(void)                     {return BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE04;};
	const char* stepTitle05(void)                     {return BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE05;};
	const char* helpHtml(void)
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
					POSTERAZORHELPINDENTATION "O PosteRazor corta uma imagem e redimensiona em pedaços que podem ser impressas e colocadas juntas formando um Poster (cartaz). Como uma imagem de entrada, uma varredura de arquivos <A href=\"#" POSTERAZORHELPANCHORMANUALSTEP01 "\">diversos</A> formatos de arquivos de imagem são suportados. Em evz de imprimir diretamente o poster (cartaz), o PosteRazor produz uma multi-página em arquivo PDF que contém o poster.<br>" POSTERAZORHELPENDLINE \
					"Este é um programa open source que depende de <a href=\"#" POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES "\">outros projetos open source</a>. " POSTERAZORHELPENDLINE \
					"O PosteRazor is hospedado em <b>posterazor.sourceforge.net</b>." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUAL, BRAZILIANPORTUGUESE_POSTERAZORHELPMANUAL) \
					POSTERAZORHELPINDENTATION "PosteRazor tem a interface do usuário organizada em um \"Assistente\". Todas as configurações para a criação do poster podem ser feitas em 5 passos. Os botões <b>Voltar</b> e <b>Próximo</b> navegam através desses passos.<br>" POSTERAZORHELPENDLINE \
					"O botão <b>?</b> abre uma janela de ajuda com a explicação do corrente passo.<br>" POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "Todas as entradas e escolhas são lembradas até o próximo uso do PosteRazor." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORSETTINGS, BRAZILIANPORTUGUESE_POSTERAZORHELPSETTINGS) \
					POSTERAZORHELPINDENTATION "Pressionando o botão <b>Configurações...</b> na parte inferior esquerda da janela de diálogo, a janela de diálogo configurações do PosteRazor é aberta." POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>Unidade de Comprimento:</b> escolha a unidade de comprimento que você está acostumado a trabalhar. Quando a unidade é modificada, todos os valores predefinidos e os valores que você já definiu são transformados para a nova unidade.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Linguagem:</b> escolha sua linguagem. O PosteRazor não precisa ser reiniciado quando uma linguagem é modificada.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Previsualização com OpenGL:</b> escolha, se o PosteRazor deveria usar OpenGL para previsualizar a imagem. Geralmente, em hardwares novos OpenGL deve deixar mais rápido e dar uma previsualização mais precisa que aquela que não usa o OpenGL. Mas se o PosteRazor parecer lento e sem resposta, por favor veja se ele trabalha menor com o OpenGL desabilitado.</LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP01, BRAZILIANPORTUGUESE_POSTERAZORHELSTEP " 1: " BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE01) \
					POSTERAZORHELPINDENTATION "carregue a imagem clicando no botão com o ícone de abrir e selecione o arquivo de imagem, ou  clique & arraste uma imagem para o PosteRazor. O clique & arraste também funciona nos outros passos.<br>" POSTERAZORHELPENDLINE \
					"Muitos <a href=\"#" POSTERAZORHELPANCHORINPUTFILEFORMATS "\">formatos de arquivos e tipos de imagens</a> podem ser usados. Após carregar uma imagem, a informações mais importantes são listadas nos campos <b>Informações da imagem</b>." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP02, BRAZILIANPORTUGUESE_POSTERAZORHELSTEP " 2: " BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE02) \
					POSTERAZORHELPINDENTATION "Defina o tamanho da folha de papel que usa em sua impressora. Um tamanho padrão de folhe pode ser selecionado através da escolha <b>Formato</b>, bem como a dsejada <b>Orientation</b> do papel. Alternativamente, pode definir um tamanho personalizado na aba <b>Personalizar</b>. (Favor me escrever um e-mail caso seu tamanho padrão escolhido seja perdido). " POSTERAZORHELPENDLINE \
					"As bordas do papel são definidas nos campos <b>Bordas</b>. Mesmo que sua impressora não precise (precise de pequenas) de bordas na folha, algumas bordas podem ser necessárias para ter área suficiente para colar as folhas do poster final." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP03, BRAZILIANPORTUGUESE_POSTERAZORHELSTEP " 3: " BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE03) \
					POSTERAZORHELPINDENTATION "A sobreposição do mosaico é necessária para ter alguma tolerância para cortar totalmente as bordas desnecessárias de um lado. Assim, como nas margens do passo anterior, dá uma área maior para colar juntas as páginas do poster final. " POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "The <b>Posição de sobreposição</b> define as margens destinadas a sobrepor cm as páginas vizinhas. As margens dos lados opostos devem ser cortadas (exceto as páginas ultraperiféricas)." POSTERAZORHELPENDLINE \
					
					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP04, BRAZILIANPORTUGUESE_POSTERAZORHELSTEP " 4: " BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE04) \
					POSTERAZORHELPINDENTATION "Define o tamanho final do poster, em um dos três modos seguintes que podem ser selecionados com os botões correspondentes:<br>" POSTERAZORHELPENDLINE \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>Tamanho total da imagem</b>: usado para determinar o tamanho do poster.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Tamanho em páginas</b>: usado para determinar quantas páginas inteiras serão usadas pelo poster.</LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Tamanho da imagem em porcentagem</b>: sua imagem de entrada tem o tamanho definido pelo número de pixels e dpi (pontos por polegadas) e você quer aumentar a imagem por um certo fator.</LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "O tamanho da largura e altura é sempre 1:1 e é automaticamente recalculado. Na área de previsualização, você pode ver as áreas de sobreposição que serão marcadas por retângulos vermelhos. " POSTERAZORHELPENDLINE \
					"<b>Alinhamento da imagem</b> estabelece o alinhamento da imagem na área total do papel do poster. Isto é util se você quer guardar o papel não utilizado." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORMANUALSTEP05, BRAZILIANPORTUGUESE_POSTERAZORHELSTEP " 5: " BRAZILIANPORTUGUESE_POSTERAZORHELPSTEPTITLE05) \
					POSTERAZORHELPINDENTATION "Salve o portsre clicando no botão Salvar e especificando o nome do arquivo destino. Marque ou desmarque o <b>Executar aplicação PDF após o porter ser salvo</b>, para, uma vez salvo o aqruivo PDF, abrir o aplicativo de PDF automaticamente." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORINPUTFILEFORMATS, BRAZILIANPORTUGUESE_POSTERAZORHELPINPUTFILEFORMATS) \
					POSTERAZORHELPINDENTATION "A maioria dos formatos de imagem são suportados pelo FreeImage também são suportadas pelo PosteRazor:<br>" POSTERAZORHELPENDLINE \
					"<b>BMP, arquivos DDS, Dr. Halo, GIF, ICO, IFF, JBIG, JNG, JPEG/JIF, KOALA, LBM, Kodak PhotoCD, MNG, PCX, PBM, PGM, PNG, PPM, PhotoShop PSD, Sun RAS, TARGA, TIFF, WBMP, XBM, XPM.<br></b>" POSTERAZORHELPENDLINE \
					"PosteRazor distingue e maneja imagens monocromáticas, escala de cinza, paleta de 4-bits, paleta de 8-bits, RGB 24 bits, e CMYK (apenas de TIF). Imagens RGB com um canal alfa são compostas automaticamente sobre um fundo branco." POSTERAZORHELPENDLINE \

					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORWHYPDFOUTPUT, BRAZILIANPORTUGUESE_POSTERAZORHELPWHYPDFOUTPUT) \
					POSTERAZORHELPINDENTATION "Porque o arquivo PDF não é automaticamente impresso? Primeiro que o desenvolvedor do software não sabe (ainda) como fazer isso, do tipo \"enviar imagens para a impressora\", em diferentes sistemas operacionais, os quais Posterrazor funciona. Também, PDF faz sentido, se o poster é criado em casa com toda a disponibilidade de tempo, no dia seguinte pode ser impresso numa impressora a laser colorida em outro local. " POSTERAZORHELPENDLINE \
					POSTERAZORHELPINDENTATION "Por que PDF e não outro formato de arquivo? PDF dá a possibilidade de juntar toda a imagem e cortá-la virtualmente, e não apenas em pixel mas também em suas frações. Além disso, parece ser mais prático imprimir um arquivo PDF multi-páginas que múltiplos arquivos de imagem." POSTERAZORHELPENDLINE \
					
					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES, BRAZILIANPORTUGUESE_POSTERAZORHELPCODEFROMTHIRDPARTIES) \
					"<UL>" POSTERAZORHELPENDLINE \
					"<LI><b>FLTK</b> é usado para a interface do usuário. É pequeno (pelo tamanho), rápido, divertido e fácil de aprender e uma UI muito portável. <a href=\"http://www.fltk.org/\">www.fltk.org</a></LI>" POSTERAZORHELPENDLINE \
					"<LI><b>FreeImage</b> é usado para carregar e manipular. Ele carregar e realmente manipula para várias plataformas, onde PosteRazor pode ser executado. <a href=\"http://freeimage.sourceforge.net/\">FreeImage website</a></LI>" POSTERAZORHELPENDLINE \
					"<LI><b>Fl_Native_File_Chooser</b> é usado nos diálogos abrir e salvar. <a href=\"http://seriss.com/people/erco/fltk/Fl_Native_File_Chooser/\">Fl_Native_File_Chooser website</a></LI>" POSTERAZORHELPENDLINE \
					"</UL>" POSTERAZORHELPENDLINE \
					
					POSTERAZORHELPSECTIONHEADER(POSTERAZORHELPANCHORLICENSE, BRAZILIANPORTUGUESE_POSTERAZORHELPLICENSE) \
					"PosteRazor - Faça seu próprio poster!<br>" POSTERAZORHELPENDLINE \
					"<a href=\""BRAZILIANPORTUGUESE_POSTERAZORWEBSITEURL"\">posterazor.sourceforge.net</a><br>" POSTERAZORHELPENDLINE \
					"Copyright (C) 2005-2007 by Alessandro Portale<br>&nbsp;<br>" POSTERAZORHELPENDLINE \

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

	const int flagImageWidth(void)                    {return 20;}
	const int flagImageHeight(void)                   {return 11;}
	const unsigned char *flagImageRGBData(void)
	{
		static const unsigned char flagRGBData[] =
		{
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,0,146,63,0,146,63,0,146,63,0,146,63,0,146,63,0,146,63,0,146,
			63,0,146,63,62,158,47,62,158,47,0,146,63,0,146,63,0,146,63,0,146,63,0,146,63,0,
			146,63,0,146,63,0,146,63,140,140,140,140,140,140,0,146,63,0,146,63,0,146,63,0,
			146,63,0,146,63,0,146,63,62,158,47,187,183,16,187,144,33,187,144,33,187,183,16,
			62,158,47,0,146,63,0,146,63,0,146,63,0,146,63,0,146,63,0,146,63,140,140,140,
			140,140,140,0,146,63,0,146,63,0,146,63,0,146,63,62,158,47,187,183,16,214,168,18,
			66,43,97,40,22,111,40,22,111,66,43,97,214,168,18,187,183,16,62,158,47,0,146,63,
			0,146,63,0,146,63,0,146,63,140,140,140,140,140,140,0,146,63,0,146,63,62,158,
			47,187,183,16,248,195,0,248,195,0,151,125,102,112,100,160,128,117,170,60,41,
			108,40,22,111,126,93,65,248,195,0,248,195,0,187,183,16,62,158,47,0,146,63,0,146,
			63,140,140,140,140,140,140,0,146,63,124,171,31,248,195,0,248,195,0,248,195,0,
			248,195,0,60,41,108,40,22,111,43,25,113,112,100,160,112,100,160,60,41,108,248,
			195,0,248,195,0,248,195,0,248,195,0,124,171,31,0,146,63,140,140,140,140,140,140,
			0,146,63,0,146,63,62,158,47,187,183,16,248,195,0,248,195,0,126,93,65,40,22,
			111,40,22,111,40,22,111,112,100,160,151,125,102,248,195,0,248,195,0,187,183,16,
			62,158,47,0,146,63,0,146,63,140,140,140,140,140,140,0,146,63,0,146,63,0,146,63,
			0,146,63,62,158,47,187,183,16,214,168,18,66,43,97,40,22,111,40,22,111,66,43,
			97,214,168,18,187,183,16,62,158,47,0,146,63,0,146,63,0,146,63,0,146,63,140,140,
			140,140,140,140,0,146,63,0,146,63,0,146,63,0,146,63,0,146,63,0,146,63,62,158,47,
			187,183,16,187,144,33,187,144,33,187,183,16,62,158,47,0,146,63,0,146,63,0,146,
			63,0,146,63,0,146,63,0,146,63,140,140,140,140,140,140,0,146,63,0,146,63,0,146,
			63,0,146,63,0,146,63,0,146,63,0,146,63,0,146,63,62,158,47,62,158,47,0,146,63,0,
			146,63,0,146,63,0,146,63,0,146,63,0,146,63,0,146,63,0,146,63,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,
			140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140,140
		};

		return flagRGBData;
	}
};

static TranslationBrazilianPortuguese brazilianPortuguese;

#endif
