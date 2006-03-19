<?
	define('EN', 'english');
	define('DE', 'german');

	$lang = $_GET['lang'] == DE?DE:EN;
	$page = isset($_GET['page'])?strtolower($_GET['page']):"about";
	
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
						<h3><? text('February 7th 2006', '7. Februar 2006'); ?>: Version 1.1</h3>
						<p><? text('A few bugfixes and improved usability, no significant new functional features.', 'Einige behobene Fehler und grö&szlig;ere Bedienerfreundlichkeit, keine relevanten neuen Funktionen.'); ?></p>
						<ul>
							<li><? text('The ".pdf" file extension is automatically appended when a poster is saved.', 'Die Datei-Endung ".pdf" wird bei der Speicherung eines Posters automatisch angeh&auml;ngt.'); ?></li>
							<li><? text('The user interface is multilingual. English and German are choosable at present.', 'Die Benutzeroberfl&auml;che ist mehrsprachig. Derzeit sind deutsch und englisch ausw&auml;hlbar.'); ?></li>
							<li><? text('The Poster preview is (optionally) done via OpenGL.', 'Die Vorschau des Posters wird (optional) per OpenGL dargestellt.'); ?></li>
						</ul>
						<p><a class="external" href="http://cvs.sourceforge.net/viewcvs.py/posterazor/PosteRazor/CHANGES?view=markup"><? text('Full list of changements', 'Vollst&auml;ndige Liste der &Auml;nderungen (auf englisch)'); ?></a></p>
					</li>
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
						<strong><? text('Input image formats', 'Ausgangs-Bildformate'); ?>.</strong> <? text('All image formats that', 'Alle Bildformate, die'); ?> <a class="external" href="http://freeimage.sourceforge.net/features.html">FreeImage</a> <? text('can read', 'lesen kann,'); ?> <i><? text('should', 'sollten'); ?></i> <? text('be usable as input for the PosteRazor', 'als Ausgangsmaterial f&uuml;r den PosteRazor geeignet sein'); ?>:
						<div class="fileformats">BMP, DDS, Dr. Halo, GIF, ICO, IFF, JBIG, JNG, JPEG/JIF, KOALA, LBM, Kodak PhotoCD, MNG, PCX, PBM, PGM, PNG, PPM, PhotoShop PSD, Sun RAS, TARGA, TIFF, WBMP, XBM, XPM</div>
					</li>
					<li>
						<strong><? text('Image types', 'Farbtypen'); ?>.</strong> <? text('PosteRazor can handle the following image color types', 'Die folgenden Bildfarbtypen werden unterst&uuml;tzt'); ?>:
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
				<div id="screenshotthumbs">
					<a href="screenshot_<?=$lang?>_step01.png"><img src="screenshotthumb_step01.png" width="120" height="92" alt="Step 1" /><br /><? text('Step', 'Schritt'); ?> 1</a>
					<a href="screenshot_<?=$lang?>_step02.png"><img src="screenshotthumb_step02.png" width="120" height="92" alt="Step 2" /><br /><? text('Step', 'Schritt'); ?> 2</a>
					<a href="screenshot_<?=$lang?>_step03.png"><img src="screenshotthumb_step03.png" width="120" height="92" alt="Step 3" /><br /><? text('Step', 'Schritt'); ?> 3</a>
					<a href="screenshot_<?=$lang?>_step04.png"><img src="screenshotthumb_step04.png" width="120" height="92" alt="Step 4" /><br /><? text('Step', 'Schritt'); ?> 4</a>
					<a href="screenshot_<?=$lang?>_step05.png"><img src="screenshotthumb_step05.png" width="120" height="92" alt="Step 5" /><br /><? text('Step', 'Schritt'); ?> 5</a>
					<a href="screenshot_<?=$lang?>_help_settings.png"><img src="screenshotthumb_help_settings.png" width="120" height="90" alt="Help" /><br /><? text('Help, settings', 'Hilfe, Einstellungen'); ?></a>
				</div>
<?
			break;
			case 'download':		
?>
				<h2><? text('Download', 'Herunterladen'); ?></h2>
				<p><? text('The following PosteRazor download links lead to sites with lists of download locations. There, please click on a "Download" link next to a location that is geographically next to Your place.', 'Die folgenden PosteRazor-Download-Verweise f&uuml;hren auf Seiten mit mehreren m&ouml;glichen Downloadservern. Bitte klicken Sie Dort auf einen "Download"-Verweis, der Ihnen geografisch am n&auml;chsten ist.'); ?></p>
				<p><? text('For <strong>direct linking to the downloads</strong> from another site, please use exactly the following links, only these are guaranteed to be valid in the future.', '<strong>Direktes Verlinken auf die Downloads</strong> von anderen Seiten aus bitte mit den unten aufgef&uuml;hrten Links. Nur diese werden mit gro&szlig;er Sicherheit auch in Zukunft g&uuml;ltig sein.'); ?></p>
				<ul>
					<li>
						<a class="external" href="http://prdownloads.sourceforge.net/posterazor/PosteRazor-1.1-Win32.zip?download"><strong><? text('Windows version', 'Windows-version'); ?></strong> (404 KB)</a><br />
						<? text('After downloading the ZIP archive, extract the contained PosteRazor.exe to a place of Your choice and start it. If You use a Windows version below XP, You probably need an installed <a class="external" href="http://www.7-zip.org/">Unzip tool</a>.', 'Nach dem Herunterladen des ZIP-Archivs, k&ouml;nnen Sie das enthaltene PosteRazor.exe in ein Verzeichnis Ihrer Wahl entpacken und starten. Falls sie eine Windows-version unterhalb von XP nutzen, ben&ouml;tigen Sie evenuell ein installiertes <a class="external" href="http://www.7-zip.org/">Unzip-Programm</a>.'); ?>
					</li>
					<li>
						<a class="external" href="http://prdownloads.sourceforge.net/posterazor/PosteRazor-1.1-OSX.dmg?download"><strong><? text('OSX version', 'OSX-version'); ?></strong> (668 KB)</a><br />
						<? text('After downloading the OSX disk image, double click to mount it if it doesn\'t mount automatically. You can start the contained PosteRazor application directly by double clicking it or drag it into a location of Your choice.', 'Nach dem Herunterladen des OSX-Diskimages k&ouml;nnen Sie es, falls dies nicht automatisch geschieht, per Doppelclick mounten. Danach kann die enthaltene PosteRazor-Applikation entweder direkt gestartet werden oder in einen Ordner Ihrer Wahl kopiert werden.'); ?><br />
					</li>
					<li>
						<a class="external" href="http://prdownloads.sourceforge.net/posterazor/PosteRazor-1.1-Source.zip?download"><strong><? text('Source', 'Quelltext'); ?></strong> (189 KB)</a><br />
						<? text('The source archive includes only project files for VC6, VS 2003 .Net, XCode 2.2 and an unfinished CMake file. FLTK and FreeImage are not included. In order to compile without OpenGL, the preprocessor symbol <em>NO_OPENGL_PREVIEW</em> can be defined.', 'Das Quelltext-archiv enth&auml;lt nur Projekte f&uuml;r VC6, VS 2003 .Net, XCode 2.2 und eine unvollst&auml;ndige CMake-Datei. FLTK und FreeImage sind nicht enthalten. Um ohne OpenGL zu kompilieren, kann das Pr&auml;prozessorsymbol <em>NO_OPENGL_PREVIEW</em> definiert werden.'); ?><br />
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
						<strong><? text('Image loading', 'Bilder laden'); ?>:</strong> <? text('The images are loaded by', 'Die Bilder werden mittels'); ?> <a class="external" href="http://freeimage.sourceforge.net/">FreeImage 3.8.0</a><? text('. This is a portable library that makes image loading, handling and saving a no-brainer.', ' geladen. Dies ist eine portierbare Bibliothek, die das Laden, Manipulieren und Speichern von Bildern zu einem Kinderspiel macht.'); ?>
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
				<br /><div style="text-align: center; margin: 10px;"><img src="workflow_<?=$lang?>.png" width="378" height="108" alt="PosteRazor workflow"/></div>
				<? text('As input, the PosteRazor takes a raster image. The resulting poster is saved as a multipage PDF document. An easy to use, wizard like user interface guides through 5 steps. PosteRazor is available as a Windows and as an OSX version (it should also be compilable on Linux).', 'Als Ausgangsmaterial nimmt der PosteRazor eine Rasterbild-datei. Das Endprodukt ist ein Poster in Form eines mehrseitigen PDF-Dokuments. Eine einfach zu bedienende Benutzerschnittstelle im Assistenten-Stil begleitet durch f&uuml;nf Schritte. Der PosteRazor ist als Windows- und als OSX-Version erh&auml;ltlich (er sollte auch f&uuml;r Linux kompilierbar sein).'); ?>
				<? text('It is an open source, ', 'Er ist ein quelloffenes, '); ?><a href="<?=linkParameters("license","")?>"><? text('GNU licensed', 'GNU-lizensiertes'); ?></a> <? text('project which is hosted on SourceForge.net.', 'Projekt, das auf SourceForge hinterlegt ist.'); ?>
				<? text('For feedback, bug reports or feature requests, please use the', 'F&uuml;r Feedback, Fehlerberichte oder Erweiterungsw&uuml;nsche nutzen Sie bitte die '); ?> <a class="external" href="http://sourceforge.net/projects/posterazor/"><? text('PosteRazor project page', 'PosteRazor-Projektseite'); ?></a>, <? text('write a mail to', 'schreiben Sie eine Mail an'); ?> <strong>Alessandro&nbsp;&auml;t&nbsp;casaportale&nbsp;d&ocirc;t de</strong> <? text('or contact the author via', 'oder kontaktieren Sie den Autor via'); ?> <a class="external" href="http://www.casaportale.de/html/index.php?page=contact&amp;lang=<? text('english', 'german'); ?>&amp;menu=on"><? text('mail form', 'Mail-Formular'); ?></a>.
				<div id="awards">
					<a href="http://freshmeat.net/projects/posterazor/"><img src="freshmeat.gif" width="88" height="31" alt="FreshMeat" /></a>
					<a href="http://mac.softpedia.com/get/DTP-Prepress/PosteRazor.shtml"><img src="softpedia_pick_award_s.gif" width="75" height="40" alt="Softpedia Pick" /></a>
					<a href="http://winload.de/download/50466/Grafik,Desktop/Bildbearbeitung/PosteRazor-1.1.html"><img src="http://winload.de/banner/80/winload_statisch_80x30_1_1.gif" width="88" height="30" alt="winload.de" /></a>
					<a href="http://www.foto-freeware.de/posterazor.php"><img src="http://www.foto-freeware.de/pic/button_88x31.gif" width="88" height="31" alt="foto-freeware.de" /></a>
					<a href="http://www.freeware.de/software/Programm_PosteRazor_23998.html"><img src="http://media.upload.de/27/46/47/149.gif" width="80" height="30" alt="freeware.de" /></a>
					<a href="http://www.shareware.de/software/Programm_PosteRazor_23998.html"><img src="http://media.upload.de/27/46/48/118.gif" width="80" height="30" alt="shareware.de" /></a>
					<a href="http://www.brothersoft.com/graphics_design/misc_graphics/posterazor_45842.html"><img src="http://www.brothersoft.com/images/LinktoUs/006.gif" width="88" height="31" alt="5/5 stars BrotherSoft" /></a>
					<a href="http://posterazor.uptodown.com/"><img src="http://imagenes.uptodown.com/imagenes/masvotado.gif" width="115" height="42" alt="uptodown mas votado" /></a>
					<a href="http://www.topshareware.com/PosteRazor-download-42692.htm"><img src="http://www.topshareware.com/images/logo/topshareware_8831.gif" width="88" height="31" alt="Free Downloads" /></a>
					<br/>
					<a href="http://www.wintotal.de/softw/?id=3107">[wintotal.de]</a>
					<a href="http://www.versiontracker.com/dyn/moreinfo/macosx/29212">[versiontracker.com]</a>
					<a href="http://www.digitazero.org/?p=29">[digitazero.org]</a>
					<a href="http://www.macupdate.com/info.php/id/20738">[macupdate.com]</a>
					<a href="http://www.macwelt.de/news/fav/336478/index.html">[macwelt.de]</a>
					<a href="http://www.freewarefiles.com/program_3_33_18358.html">[freewarefiles.com]</a>
					<a href="http://www.softforall.com/Multimedia/Illustration/PosteRazor07040048.htm">[softforall.com	]</a>
					<a href="http://www.freeware-guide.com/dir/mmedia/imagedit2.html">[freeware-guide.com]</a>
					<a href="http://www.infoweek.ch/downloads/dl_single.cfm?dl_id=1056&amp;sid=0">[infoweek.ch]</a>
					<a href="http://www.erfahrungswert.de/download/grafik1.htm#PosteRazor">[erfahrungswert.de]</a>
					<a href="http://downloads.tomorrow.msn.de/beschreibung.php?programm_id=50466">[tomorrow.msn.de]</a>
					<a href="http://www.heise.de/software/default.shtml?prg=32759&amp;T=posterazor">[heise.de]</a>
					<a href="http://www.download.bg/index.php?cls=program&amp;mtd=view&amp;id=33887">[download.bg]</a>
					<a href="http://descargas.terra.es/informacion_extendida.phtml?n_id=45043&amp;plat=1">[terra.es]</a>
					<a href="http://www.arcor.de/content/pcgames/downloads/grafik/34726539.html">[arcor.de]</a>
					<a href="http://www.sofotex.com/PosteRazor-download_L38851.html">[sofotex.com]</a>
					<a href="http://www.solofreeware.net/descargar-software-PosteRazor.html">[solofreeware.net]</a>
					<a href="http://www.files-library.com/files/PosteRazor-Make-your-own-poster.html">[files-library.com]</a>
					<a href="http://digg.com/software/PosteRazor,_A_better_Rasterbator_app">[digg.com]</a>
					<a href="http://os4depot.net/index.php?function=showfile&amp;file=utility/print/posterazor.lha">[os4depot.net]</a>
					<a href="http://www.genbeta.com/archivos/2005/10/12-generate-tu-poster-a-partir-de.php">[genbeta.com]</a>
					<a href="http://www.allapp.com/PosteRazor_softinfo_27697.html">[allapp.com]</a>
					<a href="http://www.programas-gratis.net/php/programa2.php?id_programa=4140">[programas-gratis.net]</a>
					<a href="http://alltompc.fpgroup.se/nyheter/?id=31781">[fpgroup.se]</a>
					<a href="http://download.excite.it/scheda.php?id=271282">[excite.it]</a>
					<a href="http://www.filehungry.com/english/product/windows_software/multimedia_&amp;_graphics/graphic_conversion_tools/posterazor">[filehungry.com]</a>
					<a href="http://www.foto-digital.com.mx/2005/10/20/posterazor/">[foto-digital.com.mx]</a>
					<a href="http://www.fltk.org/links.php?V272">[fltk.org]</a>
				</div>
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
				<a href="<?=linkParameters("","english")?>"><img src="flagEnglish<? text('_selected', ''); ?>.png" width="26" height="17" alt="English" /></a><a href="<?=linkParameters("","german")?>"><img src="flagGerman<? text('', '_selected'); ?>.png" width="26" height="17" alt="Deutsch" /></a>
			</div>
			<div id="navigation">
				<ul id="navigationlist"><li><a href="<?=linkParameters("news","")?>"<?=conditionalSelectedClass("news")?>><? text('News', 'Neuigkeiten'); ?></a></li><li><a href="<?=linkParameters("about","")?>"<?=conditionalSelectedClass("about")?>><? text('About', '&Uuml;ber'); ?></a></li><li><a href="<?=linkParameters("features","")?>"<?=conditionalSelectedClass("features")?>><? text('Features', 'Funktionen'); ?></a></li><li><a href="<?=linkParameters("screenshots","")?>"<?=conditionalSelectedClass("screenshots")?>><? text('Screenshots', 'Bildschirmfotos'); ?></a></li><li><a href="<?=linkParameters("download","")?>"<?=conditionalSelectedClass("download")?>><? text('Download', 'Herunterladen'); ?></a></li><li><a href="<?=linkParameters("thirdparty","")?>"<?=conditionalSelectedClass("thirdparty")?>><? text('Third&nbsp;party&nbsp;code', 'Code&nbsp;von&nbsp;Dritten'); ?></a></li><li><a href="<?=linkParameters("license","")?>"<?=conditionalSelectedClass("license")?>><? text('License', 'Lizenz'); ?></a></li></ul>
				<a class="external" href="http://sourceforge.net"><img src="http://sourceforge.net/sflogo.php?group_id=141842&amp;type=1" width="88" height="31" alt="SF.net Logo" /></a>
				<a class="external" href="http://sourceforge.net/projects/posterazor/"><? text('SF project page', 'SF Projekt-Seite'); ?></a>
			</div>
			<div id="content">
<?=writeContent();
?>
			</div>
			<div id="footer">
			</div>
		</div>
	</body>
</html>