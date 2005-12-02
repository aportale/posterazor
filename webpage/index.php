<?
	define('EN', 'english');
	define('DE', 'german');

	$lang = $_GET['lang'] == DE?DE:EN;

	function text($englishString, $germanString)
	{
		global $lang;
		echo $lang == EN?$englishString:$germanString;
	}

?><!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<?
	$textColor = "#330000";
	$contentBackgroundColor = "#ffffee";
?><html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />
		<meta name="author" content="Alessandro Portale" />
		<meta name="description" content="PosteRazor - Make your own poster!" />
		<meta name="keywords" content="Poster, PosteRazor, Print, Fltk, Freeimage, PDF" />
		<title>PosteRazor - <? text('Make your own poster', 'Mach\' Dein eigenes Poster'); ?>!</title>
		<style type="text/css">
		/*<![CDATA[*/
			h1
			{
				text-align : center;
				font-size : 3em;
			}

			h2
			{
				font-size : 2em;
			}

			h3
			{
				font-size : 1.1em;
				margin-bottom: 0px;
				padding-bottom: 0px;
			}

			hr
			{
				border : 0;
				color : <? echo $textColor; ?>;
				background-color : <? echo $textColor; ?>;
				height : 3px;
			}
			
			A	
			{
				color : <? echo $textColor; ?>;
				background-color : <? echo $contentBackgroundColor; ?>;
			}			

			A:Visited
			{
				color : <? echo $textColor; ?>;
				background-color : <? echo $contentBackgroundColor; ?>;
			}			

			A:Hover
			{
				color : #cc0000;
				background-color : <? echo $contentBackgroundColor; ?>;
			}			

			A.external
			{
				background: url(external.png) center right no-repeat;
				padding-right: 13px;
			}
			
			img
			{
				border : 0;
			}
			
			body
			{
				font-family : Verdana,sans-serif;
				font-size : 10pt;
				background-color : #eeeeff;
				margin : 10px;
			}

			td
			{
				text-align : center;
			}
			
			table.center
			{
				margin-left : auto;
				margin-right : auto;
			}

			li
			{
				margin-top: 5px;
				margin-bottom: 10px;
			}
			
			.mainpage
			{
				padding : 0px 15px;
				margin : 0 15%;
				border : 1px solid <? echo $textColor; ?>;
				background : <? echo $contentBackgroundColor; ?> url(images/logo.png) no-repeat; 
				color : <? echo $textColor; ?>;
			}
			
			.links
			{
				text-align: center;
			}

			.fileformats
			{
				margin-top: 3px;
				margin-bottom: 3px;
				padding: 5px 10px;
				border: 1px solid <? echo $textColor; ?>;
				background-color: #ffffff;
			}
		/*]]>*/
		</style>
	</head>
	<body>
		<div style="float:left;" >
			<p><a href="http://sourceforge.net"><img src="http://sourceforge.net/sflogo.php?group_id=141842&amp;type=1" width="88" height="31" alt="SourceForge.net Logo" /></a></p>
			<p><a href="http://validator.w3.org/check?uri=referer"><img src="http://www.w3.org/Icons/valid-xhtml10" alt="Valid XHTML 1.0 Strict" height="31" width="88" /></a></p>
			<p><a href="http://posterazor.uptodown.com/"><img src="http://www.uptodown.com/imagenes/publicado.gif" alt="Programa Recomendado en UpToDown.com" height="42" width="115" /></a></p>
		</div>
		
		<div class="mainpage">
			<h1>PosteRazor<br /><sup><? text('Make your own poster!', 'Mach\' Dein eigenes Poster!'); ?></sup></h1>
			<hr />
			<div class="links">
				<a href="#news"><? text('News', 'Neuigkeiten'); ?></a>
				- <a href="#about"><? text('About', '&Uuml;ber'); ?></a>
				- <a href="#features"><? text('Features', 'Funktionen'); ?></a>
				- <a href="#screenshots"><? text('Screenshots', 'Bildschirmfotos'); ?></a>
				- <a class="external" href="http://sourceforge.net/project/showfiles.php?group_id=141842"><? text('Download', 'Herunterladen'); ?></a>
				- <a href="#thirdparty"><? text('Third&nbsp;party&nbsp;code', 'Code&nbsp;von&nbsp;Drittanbietern'); ?></a>
				- <a href="#license"><? text('License', 'Lizenz'); ?></a>
			</div>

			<hr />
			<h2><a name="news"></a><? text('News', 'Neuigkeiten'); ?></h2>
			<ul>
				<li>
					<h3><? text('October 3rd 2005', '3. Oktober 2005'); ?>: Version 1.0</h3>
					<p><? text('The first release of PosteRazor. Windows and OSX version.', 'Die Erstausgabe des PosteRazors. Windows- und OSX-version.'); ?></p>
				</li>
			</ul>

			<hr />
			<h2><a name="about"></a><? text('About', '&Uuml;ber'); ?></h2>
			<? text('The PosteRazor cuts a raster image into pieces which can afterwards be printed out and assembled to a poster.', 'Der PosteRazor schneidet eine Rasterbild-datei in St&uuml;cke, die anschlie&szlig;end ausgedruckt und zu einem Poster zusammengef&uuml;gt werden k&ouml;nnen.'); ?>
			<br /><div style="text-align: center; margin: 10px;"><img src="images/workflow.png" width="400" height="114" alt="PosteRazor workflow"/></div>
			<? text('As input, the PosteRazor takes a raster image. The resulting poster is saved as a multipage PDF document. An easy to use, wizard like user interface guides through 5 steps. PosteRazor is available as a Windows and as an OSX version (it should also be compilable on Linux).', 'Als Ausgangsmaterial nimmt der PosteRazor eine Rasterbild-datei. Das Endprodukt ist ein Poster in Form eines mehrseitigen PDF-Dokuments. Eine einfach zu bedienende Benutzerschnittstelle im Assistenten-Stil begleitet durch f&uuml;nf Schritte. Der PosteRazor ist als Windows- und als OSX-Version erh&auml;ltlich (er sollte auch f&uuml;r Linux kompilierbar sein).'); ?>
			<? text('It is an open source, ', 'Er ist ein quelloffenes, '); ?><a href="#license"><? text('GNU licensed', 'GNU-lizensiertes'); ?></a> <? text('project which is hosted on SourceForge.net.', 'Projekt, das auf SourceForge hinterlegt ist.'); ?>
			<? text('For feedback, bug reports or feature requests, please use the', 'F&uuml;r Feedback, Fehlerberichte oder Erweiterungsw&uuml;nsche nutzen Sie bitte die '); ?> <a class="external" href="http://sourceforge.net/projects/posterazor/"><? text('PosteRazor project page', 'PosteRazor-Projektseite'); ?></a>, <? text('write a mail to', 'schreiben Sie eine Mail an'); ?> <strong>Alessandro&nbsp;&auml;t&nbsp;casaportale&nbsp;d&ocirc;t de</strong> <? text('or contact the author via', 'oder kontaktieren Sie den Autor via'); ?> <a class="external" href="http://www.casaportale.de/html/index.php?page=contact&amp;lang=<? text('english', 'german'); ?>&amp;menu=on"><? text('mail form', 'Mail-Formular'); ?></a>.

			<hr />
			<h2><a name="features"></a><? text('Features', 'Funktionen'); ?></h2>
			<ul>
				<li>
					<strong><? text('Input image formats', 'Ausgangs-Bildformate'); ?>.</strong> <? text('All image formats that', 'Alle Bildformate, die'); ?> <a class="external" href="http://freeimage.sourceforge.net/features.html">FreeImage</a> <? text('can read', 'lesen kann,'); ?> <i><? text('should', 'sollten'); ?></i> <? text('be usabe as input for the PosteRazor', 'als Ausgangsmaterial f&uuml;r den PosteRazor geeignet sein'); ?>:
					<div class="fileformats">BMP, DDS, Dr. Halo, GIF, ICO, IFF, JBIG, JNG, JPEG/JIF, KOALA, LBM, Kodak PhotoCD, MNG, PCX, PBM, PGM, PNG, PPM, PhotoShop PSD, Sun RAS, TARGA, TIFF, WBMP, XBM, XPM</div>
				</li>
				<li>
					<strong><? text('Image types', 'Farbtypen'); ?>.</strong> <? text('The following image color types are handable', 'Die folgenden Bildfarbtypen werden unterst&uuml;tzt'); ?>:
					<div class="fileformats"><? text('Monochrome, Grayscale, 4 Bit palette, 8 Bit palette, 24 Bit RGB, 48 Bit RGB ', 'Monochrom, Graustufen, 4-Bit Palette, 8-Bit Palette, 24-Bit RGB, 48-Bit RGB '); ?><small>(<? text('only via TIFF and PNG', 'nur bei TIFF und PNG'); ?>)</small>, <? text('32 Bit CMYK', '32-Bit CMYK'); ?> <small>(<? text('only via', 'nur bei'); ?> TIFF)</small></div>
					<? text('32 Bit RGBA images can be loaded, but are transformed to 24 Bit RGB by "merging" them with a white background.', '32-Bit RGBA-Bilder sind lesbar, werden allerdings nach 24-Bit RGB transformiert, indem sie auf einen wei&szlig;en Hintergrund "flachgerechnet" werden.'); ?>
				</li>
				<li>
					<strong><? text('Dimension Units', 'L&auml;ngeneinheiten'); ?>.</strong> <? text('Because people around the world invented so many different dimension units, PosteRazor supports quite a few', 'Weil die Menschen rund um den Erdball so viele verschiedene L&auml;ngeneinheiten erdacht haben, unterst&uuml;tzt der PosteRazor einige von ihnen'); ?>:
					<div class="fileformats">m, mm, cm, inch, ft, pt<small>(72<? text('th', '-tel'); ?> inch)</small></div>
				</li>
				<li>
					<strong><? text('Printer page layout', 'Druckerpapier-Ma&szlig;e'); ?>.</strong> <? text('The page size and orientation of the printer where the poster will be printed can be set manually or selected one from the following list of predefined formats', 'Die Seitengr&uuml;&szlig;e und -ausrichtung des Druckers, auf dem das Bild gedruckt werden soll, kann manuell eingestellt werden oder aus der folgenden Liste gewählt werden'); ?>:
					<div class="fileformats">DIN A4, DIN A3, Legal, Letter, Tabloid</div>
					<? text('The size limit for one page is 5 meters (16.4 feet), which is the maximum that PDF allows.', 'Die Gr&ouml;&szlig;enbegrezung einer einzelnen Seite liegt bei f&uuml;nf Metern. Dies ist die maximale von PDF unterstützte Gr&ouml;&szlig;e.'); ?>
				</li>
				<li>
					<strong><? text('Poster size', 'Gr&ouml;&szlig;e des Posters'); ?>.</strong> <? text('The size of the final poster can be set one of these three ways', 'Die Gr&ouml;&szlig;e des finalen Posters kann auf eine dieser drei Weisen definiert werden'); ?>:
					<ul>
						<li><strong><? text('Absolute image size', 'Absolute Bildma&szlig;e'); ?></strong>: <? text('You want to have a specific size of your poster', 'Genaue, spezifische Bildma&szlig;e werden angegeben'); ?>.</li>
						<li><strong><? text('Size in Pages', 'Gr&ouml;&szlig;e in Seiten'); ?></strong>: <? text('You want to use whole paper sheets and specify how many of them of them you want to use', 'Die Druckb&oegen sollen komplett genutzt werden, und es wird angegeben, wieviele von ihnen f&uuml;r den Druck genutzt werden'); ?>.</li>
						<li><strong><? text('Image Size in percent', 'Prozentuee Bildma&szlig;e'); ?></strong>: <? text('Your input image has a certain size which is defined by the number of pixels and dpi (dots per Inch) and your want to scale the image by a certain factor', 'Das Ausgangsbild hat bestimmte ma&szlig;e, die durch die Anzahl der Pixel und der Aufl&ouml;sung in dpi (\"dots per inch\") bestimmt sind. Das billd soll um einen bestimmten Faktor skaliert werden.'); ?>.</li>
					</ul>
					<? text('The final size of the poster is theoretically unlimited. Let\'s say it this way: it is less limited that the ink of your printer', 'Die finale Gr&ouml;&szlig;e des Posters ist theoretisch unbegrenzt. Anders gesagt: sie ist weniger begrenzt als die Druckertinte, die man zur Verf&uuml;gung hat'); ?> ;)<br />
					<? text('It is possible to select the alignment of the image on the total paper. This is useful if you want to keep the unused paper.', 'Es ist m&ouml;glich, die Ausrichtung des Bildes auf dem gesamten Papier zu definieren. Dies ist n&uuml;tzlich, wenn die &auml;u&szlig;eren unbedruckten Papierr&auml;nder nach dem Zusammenkleben nicht abgeschnitten werden sollen.'); ?>
				</li>
				<li>
					<strong><? text('Image tile overlapping', '&Uuml;berlappung der Bildabschnitte'); ?>.</strong> <? text('For a bigger tolerance when cutting spare paper borders and for easier pasting, an overlapping width and height of an image tile over the next can be set', 'Um eine gewisse Fehlertoleranz beim Schneiden und Zusammenf&uuml;gen der Bildabschnitte zu haben, kann die H&ouml;he und Breite einer &Uuml;berlappung eines Bildabschnitt &uuml;ber den n&auml;chsten definiert werden.'); ?>.
				</li>
				<li>
					<strong><? text('PDF output', 'PDF-erstellung'); ?>.</strong>
					<? text('The PDF output is implemented with the maximum image quality and a good compression in mind. A source image is embedded once in the PDF document and referenced from every tile page. Image color types remain unchanged. As compression method, the PDF "FlateDecode filter" (zip) is used. If a Jpeg image is used as input it gets directly embedded into the document without recompression. The PDF version is 1.4, so any Acrobat Reader version 4 and higher should be able to read the resulting document.',
					'Der PosteRazor wurde so konzipiert, dass die resultierende PDF-Datei die bestm&ouml;gliche Bildqualit&auml;t bei m&ouml;glichst kleiner Dateigr&ouml;ße hat. Das Bild wird nur einmal in das PDF-Dokument eingebettet und auf den verscheidenen Seiten jeweils referenziert. Als kompressionsmethode wird der PDF-&uuml;bliche "FlateDecode-filter" (zip) benutzt. Wenn das Ausgangsformat ein Jpeg-Bild ist, wird es ohne erneute Komprimierung direkt eingebettet. Die PDF-version ist 1.4, sodass jeder Acrobat Reader ab Version 4 in der Lage sein sollte, das Dokument zu &ouml;ffnen.'); ?>
				</li>
			</ul>
			<strong><? text('Missing features', 'Fehlende Funktionen'); ?>:</strong> <? text('Cut lines/aids; Support of Jpeg-CMYK images; Support of 16 Bit Grayscale images; Embedding an ICC profile into the PDF if there is one embedded in the input image', 'Schnittlinen -hilfen; Unterst&uuml;tzung von CMYK-Jpeg; Unterst&uuml;tzung von 16-Bit-Graustufen-Bildern; ICC-Profile, die in einem Ausgangsbild eingebettet sein können im PDF einbetten.'); ?>

			<hr />
			<h2><a name="screenshots"></a><? text('Screenshots', 'Bildschirmfotos'); ?></h2>
			<div style="align: center; " >
			<table border="0" class="center" cellpadding="5">
				<tr><td colspan="3"><? text('Click to enlarge', 'Auf das zu vergr&ouml;&szlig;ernde Bild klicken'); ?>:</td></tr>
				<tr>
					<td><a href="images/screenshots/step01.png"><img src="images/screenshots/thumbnails/step01.png" width="100" height="76" alt="Step 1" /><br /><? text('Step', 'Schritt'); ?> 1</a></td>
					<td><a href="images/screenshots/step02.png"><img src="images/screenshots/thumbnails/step02.png" width="100" height="76" alt="Step 2" /><br /><? text('Step', 'Schritt'); ?> 2</a></td>
					<td><a href="images/screenshots/step03.png"><img src="images/screenshots/thumbnails/step03.png" width="100" height="76" alt="Step 3" /><br /><? text('Step', 'Schritt'); ?> 3</a></td>
				</tr>
				<tr>
					<td><a href="images/screenshots/step04.png"><img src="images/screenshots/thumbnails/step04.png" width="100" height="76" alt="Step 4" /><br /><? text('Step', 'Schritt'); ?> 4</a></td>
					<td><a href="images/screenshots/step05.png"><img src="images/screenshots/thumbnails/step05.png" width="100" height="76" alt="Step 5" /><br /><? text('Step', 'Schritt'); ?> 5</a></td>
					<td><a href="images/screenshots/help.png"><img src="images/screenshots/thumbnails/help.png" width="100" height="72" alt="Help" /><br /><? text('Help', 'Hilfe'); ?></a></td>
				</tr>
			</table>
			</div>

			<hr />
			<h2><a name="thirdparty"></a><? text('Third party code', 'Code von Drittanbietern'); ?></h2>
			<? text('PosteRazor uses third party Open Source libraries. Without those, it would have been painful and unmotivating to create the PosteRazor, and the feature set and portability would have been much smaller. The libraries are statically linked into the PosteRazor.',
			'Der PosteRazor nutzt quelloffene Programmbibliotheken von Dritten. Ohne diese w&auml;re es schmerzvoll und unmotivierend gewesen, den PosteRazor zu erstellen. Au&szlig;erdem w&auml;ren Funktionsumfang und Portabilit&auml;t kleiner gewesen. Die Bibliotheken sind statisch in den PosteRazor eingebunden.'); ?>
			<ul>
				<li>
					<strong><? text('User interface', 'Benutzeroberfl&auml;che'); ?>:</strong> <? text('For the user graphical user interface,', 'F&uuml;r die grafische Benutzeroberfl&auml;che wird'); ?> <a class="external" href="http://fltk.org/">FLTK 1.1</a> <? text('is used', 'eingesetzt'); ?>. <? text('It is a ', 'Es ist ein "schnelles, leichtes UI Toolkit" ('); ?><strong>f</strong>ast, <strong>l</strong>ight UI <strong>t</strong>ool<strong>k</strong>it<? text('. Highly portable, flexible, easy and fun to learn&amp;use.', '). Sehr portierbar, flexibel, einfach, und es macht Spass, es zu lernen und zu benutzen.'); ?>
				</li>
				<li>
					<strong><? text('Image loading', 'Bilder laden'); ?>:</strong> <? text('The images are loaded by', 'Die Bilder werden mittels'); ?> <a class="external" href="http://freeimage.sourceforge.net/">FreeImage 3.8.0</a><? text('. This is a portable library that makes image loading, handling and saving a no-brainer.', ' geladen. Dies ist eine portierbare Bibliothek, das das Laden, Manipulieren und Speichern von Bildern zu einem Kinderspiel macht.'); ?>
				</li>
				<li>
					<strong><? text('File chooser dilaog', 'Dateiauswahl-dialog'); ?>:</strong> The file chooser of the PosteRazor have the platform specific look&amp;feel. Thanks to Fl_Native_File_Chooser: <a class="external" href="http://seriss.com/people/erco/fltk/Fl_Native_File_Chooser/">Fl_Native_File_Chooser</a>.
				</li>
			</ul>

			<hr />
			<h2><a name="license"></a>License</h2>
			PosteRazor - Make your own poster!<br />
			Copyright (C) 2005 by Alessandro Portale<br />
			<a class="external" href="http://posterazor.sourceforge.net/">http://posterazor.sourceforge.net/</a><br />
			<br />
			PosteRazor is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by	the Free Software Foundation; either version 2 of the License, or (at your option) any later version.<br />
			<br />
			PosteRazor is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the <a class="external" href="http://www.gnu.org/copyleft/gpl.html">GNU General Public License</a> for more details.<br />
			<br />
		</div>
	</body>
</html>