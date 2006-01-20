<?
	define('EN', 'english');
	define('DE', 'german');

	$lang = $_GET['lang'] == DE?DE:EN;
	$page = strtolower($_GET['page']);	

	function text($englishString, $germanString)
	{
		global $lang;
		echo $lang == EN?$englishString:$germanString;
	}

	function linkParameters($pageParameter, $langParameter)
	{
		global $lang;
		global $page;
		return $_SERVER["SCRIPT_NAME"]
			."?page=".($pageParameter!=""?$pageParameter:$page)
			."&amp;lang=".($langParameter!=""?$langParameter:$lang);
	}
	
	function conditionalSelectedClass($pageLink)
	{
		global $page;
		return $page == $pageLink?" class=\"selected\"":"";
	}
	
	function writeContent()
	{
		global $page;
		global $lang;

		switch ($page)
		{
			case 'news':
?>
				<h2><? text('News', 'Neuigkeiten'); ?></h2>
				<ul>
					<li>
						<h3><? text('October 3rd 2005', '3. Oktober 2005'); ?>: Version 1.0</h3>
						<p><? text('The first release of PosteRazor. Windows and OSX version.', 'Die Erstausgabe des PosteRazors. Windows- und OSX-version.'); ?></p>
					</li>
				</ul>
<?
			break;
			case 'features':		
?>
				<h2><? text('Features', 'Funktionen'); ?></h2>
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
							<li><strong><? text('Size in Pages', 'Gr&ouml;&szlig;e in Seiten'); ?></strong>: <? text('You want to use whole paper sheets and specify how many of them of them you want to use', 'Die Druckb&ouml;gen sollen komplett genutzt werden, und es wird angegeben, wieviele von ihnen f&uuml;r den Druck genutzt werden'); ?>.</li>
							<li><strong><? text('Image Size in percent', 'Prozentuee Bildma&szlig;e'); ?></strong>: <? text('Your input image has a certain size which is defined by the number of pixels and dpi (dots per Inch) and your want to scale the image by a certain factor', 'Das Ausgangsbild hat bestimmte ma&szlig;e, die durch die Anzahl der Pixel und der Aufl&ouml;sung in dpi ("dots per inch") bestimmt sind. Das billd soll um einen bestimmten Faktor skaliert werden.'); ?>.</li>
						</ul>
						<p><? text('The final size of the poster is theoretically unlimited. Let\'s say it this way: it is less limited that the ink of your printer', 'Die finale Gr&ouml;&szlig;e des Posters ist theoretisch unbegrenzt. Anders gesagt: sie ist weniger begrenzt als die Druckertinte, die man zur Verf&uuml;gung hat'); ?> ;)</p>
						<p><? text('It is possible to select the alignment of the image on the total paper. This is useful if you want to keep the unused paper.', 'Es ist m&ouml;glich, die Ausrichtung des Bildes auf dem gesamten Papier zu definieren. Dies ist n&uuml;tzlich, wenn die &auml;u&szlig;eren unbedruckten Papierr&auml;nder nach dem Zusammenkleben nicht abgeschnitten werden sollen.'); ?></p>
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
				<p><strong><? text('Missing features', 'Fehlende Funktionen'); ?>:</strong> <? text('Cut lines/aids; Support of Jpeg-CMYK images; Support of 16 Bit Grayscale images; Embedding an ICC profile into the PDF if there is one embedded in the input image', 'Schnittlinen -hilfen; Unterst&uuml;tzung von CMYK-Jpeg; Unterst&uuml;tzung von 16-Bit-Graustufen-Bildern; ICC-Profile, die in einem Ausgangsbild eingebettet sein können im PDF einbetten.'); ?></p>
<?
			break;
			case 'screenshots':		
?>
				<h2><? text('Screenshots', 'Bildschirmfotos'); ?></h2>
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
<?
			break;
			case 'download':		
?>
				<h2><? text('Download', 'Herunterladen'); ?></h2>
				<p><? text('The following PosteRazor download links lead to sites with lists of download locations. There, please click on a "Download" link next to a location that is geographically next to Your place.', 'Die folgenden PosteRazor-Download-Verweise f&uuml;hren auf Seiten mit mehreren m&ouml;glichen Downloadservern. Bitte klicken Sie Dort auf einen "Download"-Verweis, der Ihnen geographisch am n&auml;chsten ist.'); ?></p>
				<ul>
					<li>
						<a class="external" href="http://prdownloads.sourceforge.net/posterazor/PosteRazor-1.0-Win32.zip?download"><strong><? text('Windows version', 'Windows-version'); ?></strong> (385 KB)</a><br />
						<? text('After downloading the ZIP archive, extract the contained PosteRazor.exe to a place of Your choice and start it. If You use a Windows version below XP, You probably need an installed <a class="external" href="http://www.7-zip.org/">Unzip tool</a>.', 'Nach dem Herunterladen des ZIP-Archivs, k&ouml;nnen Sie das enthaltene PosteRazor.exe in ein Verzeichnis Ihrer Wahl entpacken und starten. Falls sie eine Windows-version unterhalb von XP nutzen, ben&ouml;tigen Sie evenuell ein installiertes <a class="external" href="http://www.7-zip.org/">Unzip-Programm</a>.'); ?>
					</li>
					<li>
						<a class="external" href="http://prdownloads.sourceforge.net/posterazor/PosteRazor-1.0-OSX.dmg?download"><strong><? text('OSX version', 'OSX-version'); ?></strong> (485 KB)</a><br />
						<? text('After downloading the OSX disk image, double click to mount it if it doesn\'t mount automatically. You can start the contained PosteRazor application directly by double clicking it or drag it into a location of Your choice.', 'Nach dem Herunterladen des OSX-Diskimages k&ouml;nnen Sie es, falls dies nicht automatisch geschieht, per Doppelclick mounten. Danach kann die enthaltene PosteRazor-Applikation entweder direkt gestartet werden oder in einen Ordner Ihrer Wahl kopiert werden.'); ?><br />
					</li>
				</ul>
<?
			break;
			case 'thirdparty':		
?>
				<h2><? text('Third party code', 'Code von Drittanbietern'); ?></h2>
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
						<strong><? text('File chooser dilaog', 'Dateiauswahl-dialog'); ?>:</strong> <? text('The file chooser of the PosteRazor have the platform specific look&amp;feel. Thanks to Fl_Native_File_Chooser:', 'Die Dateiauswahl-dialoge des PosteRazors verdanken ihr systemspezifisches "Look and Feel" dem'); ?> <a class="external" href="http://seriss.com/people/erco/fltk/Fl_Native_File_Chooser/">Fl_Native_File_Chooser</a>.
					</li>
				</ul>
<?
			break;
			case 'license':		
?>
				<h2><? text('License', 'Lizenz'); ?></h2>
				<p>
					PosteRazor - <? text('Make your own poster', 'Mach\' Dein eigenes Poster'); ?>!<br />
					Copyright (C) 2005 by Alessandro Portale<br />
					<a class="external" href="http://posterazor.sourceforge.net/<? text('', '?lang=german'); ?>">http://posterazor.sourceforge.net/</a>
				</p>
				<? text('', '<p><em>Der folgende Lizenztext ist in seiner englischen Originalfassung aufgef&uuml;hrt, da die <a class="external" href="http://www.gnu.de/gpl-ger.html">deutsche &Uuml;bersetzung</a> nicht offiziell oder im rechtlichen Sinne anerkannt ist.</em></p>'); ?>
				<p>PosteRazor is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by	the Free Software Foundation; either version 2 of the License, or (at your option) any later version.</p>
				<p>PosteRazor is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the <a class="external" href="http://www.gnu.org/copyleft/gpl.html">GNU General Public License</a> for more details.</p>
<?
			break;
			default:		
?>
				<h2><? text('About', '&Uuml;ber'); ?></h2>
				<? text('The PosteRazor cuts a raster image into pieces which can afterwards be printed out and assembled to a poster.', 'Der PosteRazor schneidet eine Rasterbild-datei in St&uuml;cke, die anschlie&szlig;end ausgedruckt und zu einem Poster zusammengef&uuml;gt werden k&ouml;nnen.'); ?>
				<br /><div style="text-align: center; margin: 10px;"><img src="images/workflow.png" width="400" height="114" alt="PosteRazor workflow"/></div>
				<? text('As input, the PosteRazor takes a raster image. The resulting poster is saved as a multipage PDF document. An easy to use, wizard like user interface guides through 5 steps. PosteRazor is available as a Windows and as an OSX version (it should also be compilable on Linux).', 'Als Ausgangsmaterial nimmt der PosteRazor eine Rasterbild-datei. Das Endprodukt ist ein Poster in Form eines mehrseitigen PDF-Dokuments. Eine einfach zu bedienende Benutzerschnittstelle im Assistenten-Stil begleitet durch f&uuml;nf Schritte. Der PosteRazor ist als Windows- und als OSX-Version erh&auml;ltlich (er sollte auch f&uuml;r Linux kompilierbar sein).'); ?>
				<? text('It is an open source, ', 'Er ist ein quelloffenes, '); ?><a href="#license"><? text('GNU licensed', 'GNU-lizensiertes'); ?></a> <? text('project which is hosted on SourceForge.net.', 'Projekt, das auf SourceForge hinterlegt ist.'); ?>
				<? text('For feedback, bug reports or feature requests, please use the', 'F&uuml;r Feedback, Fehlerberichte oder Erweiterungsw&uuml;nsche nutzen Sie bitte die '); ?> <a class="external" href="http://sourceforge.net/projects/posterazor/"><? text('PosteRazor project page', 'PosteRazor-Projektseite'); ?></a>, <? text('write a mail to', 'schreiben Sie eine Mail an'); ?> <strong>Alessandro&nbsp;&auml;t&nbsp;casaportale&nbsp;d&ocirc;t de</strong> <? text('or contact the author via', 'oder kontaktieren Sie den Autor via'); ?> <a class="external" href="http://www.casaportale.de/html/index.php?page=contact&amp;lang=<? text('english', 'german'); ?>&amp;menu=on"><? text('mail form', 'Mail-Formular'); ?></a>.
<?
		};		
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
		<meta name="description" content="PosteRazor - <? text('Make your own poster', 'Mach\' Dein eigenes Poster'); ?>!" />
		<meta name="keywords" content="poster, posterazor, print, fltk, freeimage, pdf, application, tool, app" />
		<title>PosteRazor - <? text('Make your own poster', 'Mach\' Dein eigenes Poster'); ?>!</title>
		<style type="text/css" media="all">
			@import "style.css";
		</style>
	</head>
	<body>
		<div id="page">
			<div id="header">
				<div id="title">PosteRazor</div><div id="tagline"><? text('Make your own poster!', 'Mach\' Dein eigenes Poster!'); ?></div>
			</div>
			<div id="navigation">
				<ul id="navigationlist"><li><a href="<?=linkParameters("news","")?>"<?=conditionalSelectedClass("news")?>><? text('News', 'Neuigkeiten'); ?></a></li><li><a href="<?=linkParameters("about","")?>"<?=conditionalSelectedClass("about")?>><? text('About', '&Uuml;ber'); ?></a></li><li><a href="<?=linkParameters("features","")?>"<?=conditionalSelectedClass("features")?>><? text('Features', 'Funktionen'); ?></a></li><li><a href="<?=linkParameters("screenshots","")?>"<?=conditionalSelectedClass("screenshots")?>><? text('Screenshots', 'Bildschirmfotos'); ?></a></li><li><a href="<?=linkParameters("download","")?>"<?=conditionalSelectedClass("download")?>><? text('Download', 'Herunterladen'); ?></a></li><li><a href="<?=linkParameters("thirdparty","")?>"<?=conditionalSelectedClass("thirdparty")?>><? text('Third&nbsp;party&nbsp;code', 'Code&nbsp;von&nbsp;Dritten'); ?></a></li><li><a href="<?=linkParameters("license","")?>"<?=conditionalSelectedClass("license")?>><? text('License', 'Lizenz'); ?></a></li></ul>
				<ul><li><a href="http://sourceforge.net"><img src="_http://sourceforge.net/sflogo.php?group_id=141842&amp;type=1" width="88" height="31" alt="SF.net Logo" /></a></li><li><a href="http://validator.w3.org/check?uri=referer"><img src="_http://www.w3.org/Icons/valid-xhtml11" alt="Valid XHTML" height="31" width="88" /></a></li></ul>
			</div>
			<div id="content">
<?=writeContent();
?>
			</div><!-- end "content"-->
			<div id="footer">
			</div><!-- end "footer"-->
		</div>
	</body>
</html>