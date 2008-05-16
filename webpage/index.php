<?
	define('EN', 'english');
	define('DE', 'german');

	$lang = $_GET['lang'] == DE?DE:EN;
	$page = isset($_GET['page'])?strtolower($_GET['page']):"about";

	function text($englishString, $germanString)
	{
		global $lang;
		return $lang == EN?$englishString:$germanString;
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

	function screenShot($imageBaseName, $imageCaption)
	{
		global $lang;
		return "<a href=\"screenshot_".$lang."_$imageBaseName.png\" rel=\"lightbox[screenshot]\" title=\"$imageCaption\"><img src=\"screenshot_".$imageBaseName."_thumb.png\" width=\"130\" height=\"102\" alt=\"$imageCaption\" /><br />$imageCaption</a>\n";
	}

	function writeContent()
	{
		global $page;
		global $lang;

		switch ($page)
		{
			case 'news':
?>
				<h2><?= text('News', 'Neuigkeiten') ?></h2>
				<ul>
					<li>
						<h3><?= text('May 15th 2008', '15. Mai 2007') ?>: Version 1.5</h3>
						<p><?= text('A new language, better packages.', 'Eine weitere Sprache, bessere Pakete.') ?></p>
						<ul>
							<li><?= text('Brazilian Portuguese translation by', 'Brasilianisch-portugisische &Uuml;bersetzung von') ?> &Eacute;derson Gomes dos Santos</li>
							<li><?= text('An installer for Windows', 'Ein Installationsprogramm f&uuml;r Windows') ?></li>
							<li><?= text('Universal Binary for OSX', 'Universal Binary f&uuml;r OSX') ?></li>
							<li><?= text('A program startup crash on Windows was fixed', 'Ein Absturz beim Programmstart unter Windows wurde behoben') ?></li>
						</ul>
						<p><a href="http://posterazor.svn.sourceforge.net/viewvc/*checkout*/posterazor/tags/PosteRazor_1_5_0/CHANGES"><?= text('Full list of changements', 'Vollst&auml;ndige Liste der &Auml;nderungen (auf englisch)') ?></a></p>
					</li>
					<li>
						<h3><?= text('July 12th 2007', '12. Juli 2007') ?>: Version 1.4</h3>
						<p><?= text('Three more languages and a Linux port.', 'Drei weitere Sprachen und eine Linux-Portierung.') ?></p>
						<ul>
							<li><?= text('PosteRazor builds on Linux!', 'PosteRazor kompiliert unter Linux!') ?></li>
							<li><?= text('Italian translation by Stefano Nosei', 'Italienische &Uuml;bersetzung von Stefano Nosei') ?></li>
							<li><?= text('Dutch translation by Erik Wijkamp', 'Holl&auml;ndische &Uuml;bersetzung von Erik Wijkamp') ?></li>
							<li><?= text('Spanish translation by Cristobal from Hispanicoweb.net', 'Spanische &Uuml;bersetzung von Cristobal (Hispanicoweb.net)') ?></li>
						</ul>
					</li>
					<li>
						<h3><?= text('June 18th 2006', '18. Juni 2006') ?>: Version 1.2</h3>
						<p><?= text('Two more languages, improved usability.', 'Zwei weitere Sprachen und grö&szlig;ere Bedienerfreundlichkeit.') ?></p>
						<ul>
							<li><?= text('Polish translation by Grzegorz Wacikowski. <em>Windows version, only</em>.', 'Polnische &Uuml;bersetzung von Grzegorz Wacikowski. <em>Nur in der Windows-version</em>.') ?></li>
							<li><?= text('French translation by Martin Loyer.', 'Franz&ouml;sische &Uuml;bersetzung von Martin Loyer.') ?></li>
							<li><?= text('Added +/- buttons to poster "Size in pages" input fields.', 'Den Poster-"Gr&ouml;&szlig;e in Seiten"-eingabefeldern wurden die Kn&ouml;pfe +/- hinzugefügt.') ?></li>
						</ul>
					</li>
					<li>
						<h3><?= text('February 7th 2006', '7. Februar 2006') ?>: Version 1.1</h3>
						<p><?= text('A few bugfixes and improved usability, no significant new functional features.', 'Einige behobene Fehler und grö&szlig;ere Bedienerfreundlichkeit, keine relevanten neuen Funktionen.') ?></p>
						<ul>
							<li><?= text('The ".pdf" file extension is automatically appended when a poster is saved.', 'Die Datei-Endung ".pdf" wird bei der Speicherung eines Posters automatisch angeh&auml;ngt.') ?></li>
							<li><?= text('The user interface is multilingual. English and German are choosable at present.', 'Die Benutzeroberfl&auml;che ist mehrsprachig. Derzeit sind deutsch und englisch ausw&auml;hlbar.') ?></li>
							<li><?= text('The Poster preview is (optionally) done via OpenGL.', 'Die Vorschau des Posters wird (optional) per OpenGL dargestellt.') ?></li>
						</ul>
					</li>
					<li>
						<h3><?= text('October 3rd 2005', '3. Oktober 2005') ?>: Version 1.0</h3>
						<p><?= text('The first release of PosteRazor. Windows and OSX version.', 'Die Erstausgabe des PosteRazors. Windows- und OSX-version.') ?></p>
					</li>
				</ul>
<?
			break;
			case 'features':
?>
				<h2><?= text('Features', 'Funktionen') ?></h2>
				<ul>
					<li>
						<strong><?= text('Input image formats', 'Ausgangs-Bildformate') ?>.</strong> <?= text('All image formats that', 'Alle Bildformate, die') ?> <a href="http://freeimage.sourceforge.net/features.html">FreeImage</a> <?= text('can read', 'lesen kann,') ?> <i><?= text('should', 'sollten') ?></i> <?= text('be usable as input for the PosteRazor', 'als Ausgangsmaterial f&uuml;r den PosteRazor geeignet sein') ?>:
						<div class="fileformats">BMP, DDS, Dr. Halo, GIF, ICO, IFF, JBIG, JPEG/JIF, KOALA, LBM, Kodak PhotoCD, PCX, PBM, PGM, PNG, PPM, PhotoShop PSD, Sun RAS, TARGA, TIFF, WBMP, XBM, XPM</div>
					</li>
					<li>
						<strong><?= text('Image types', 'Farbtypen') ?>.</strong> <?= text('PosteRazor can handle the following image color types', 'Die folgenden Bildfarbtypen werden unterst&uuml;tzt') ?>:
						<div class="fileformats"><?= text('Monochrome, Grayscale, 4 Bit palette, 8 Bit palette, 24 Bit RGB, 48 Bit RGB ', 'Monochrom, Graustufen, 4-Bit Palette, 8-Bit Palette, 24-Bit RGB, 48-Bit RGB ') ?><small>(<?= text('only via TIFF and PNG', 'nur bei TIFF und PNG') ?>)</small>, <?= text('32 Bit CMYK', '32-Bit CMYK') ?> <small>(<?= text('only via', 'nur bei') ?> TIFF)</small></div>
						<?= text('32 Bit RGBA images can be loaded, but are transformed to 24 Bit RGB by "merging" them with a white background.', '32-Bit RGBA-Bilder sind lesbar, werden allerdings nach 24-Bit RGB transformiert, indem sie auf einen wei&szlig;en Hintergrund "flachgerechnet" werden.') ?>
					</li>
					<li>
						<strong><?= text('Dimension Units', 'L&auml;ngeneinheiten') ?>.</strong> <?= text('Because people around the world invented so many different dimension units, PosteRazor supports quite a few', 'Weil die Menschen rund um den Erdball so viele verschiedene L&auml;ngeneinheiten erdacht haben, unterst&uuml;tzt der PosteRazor einige von ihnen') ?>:
						<div class="fileformats">m, mm, cm, inch, ft, pt<small>(72<?= text('th', '-tel') ?> inch)</small></div>
					</li>
					<li>
						<strong><?= text('Printer page layout', 'Druckerpapier-Ma&szlig;e') ?>.</strong> <?= text('The page size and orientation of the printer where the poster will be printed can be set manually or selected one from the following list of predefined formats', 'Die Seitengr&uuml;&szlig;e und -ausrichtung des Druckers, auf dem das Bild gedruckt werden soll, kann manuell eingestellt werden oder aus der folgenden Liste gewählt werden') ?>:
						<div class="fileformats">DIN A4, DIN A3, Legal, Letter, Tabloid</div>
						<?= text('The size limit for one page is 5 meters (16.4 feet), which is the maximum that PDF allows.', 'Die Gr&ouml;&szlig;enbegrezung einer einzelnen Seite liegt bei f&uuml;nf Metern. Dies ist die maximale von PDF unterstützte Gr&ouml;&szlig;e.') ?>
					</li>
					<li>
						<strong><?= text('Poster size', 'Gr&ouml;&szlig;e des Posters') ?>.</strong> <?= text('The size of the final poster can be set one of these three ways', 'Die Gr&ouml;&szlig;e des finalen Posters kann auf eine dieser drei Weisen definiert werden') ?>:
						<ul>
							<li><strong><?= text('Absolute image size', 'Absolute Bildma&szlig;e') ?></strong>: <?= text('You want to have a specific size of your poster', 'Genaue, spezifische Bildma&szlig;e werden angegeben') ?>.</li>
							<li><strong><?= text('Size in Pages', 'Gr&ouml;&szlig;e in Seiten') ?></strong>: <?= text('You want to use whole paper sheets and specify how many of them of them you want to use', 'Die Druckb&ouml;gen sollen komplett genutzt werden, und es wird angegeben, wieviele von ihnen f&uuml;r den Druck genutzt werden') ?>.</li>
							<li><strong><?= text('Image Size in percent', 'Prozentuee Bildma&szlig;e') ?></strong>: <?= text('Your input image has a certain size which is defined by the number of pixels and dpi (dots per Inch) and your want to scale the image by a certain factor', 'Das Ausgangsbild hat bestimmte ma&szlig;e, die durch die Anzahl der Pixel und der Aufl&ouml;sung in dpi ("dots per inch") bestimmt sind. Das billd soll um einen bestimmten Faktor skaliert werden.') ?>.</li>
						</ul>
						<p><?= text('The final size of the poster is theoretically unlimited. Let\'s say it this way: it is less limited that the ink of your printer', 'Die finale Gr&ouml;&szlig;e des Posters ist theoretisch unbegrenzt. Anders gesagt: sie ist weniger begrenzt als die Druckertinte, die man zur Verf&uuml;gung hat') ?> ;)</p>
						<p><?= text('It is possible to select the alignment of the image on the total paper. This is useful if you want to keep the unused paper.', 'Es ist m&ouml;glich, die Ausrichtung des Bildes auf dem gesamten Papier zu definieren. Dies ist n&uuml;tzlich, wenn die &auml;u&szlig;eren unbedruckten Papierr&auml;nder nach dem Zusammenkleben nicht abgeschnitten werden sollen.') ?></p>
					</li>
					<li>
						<strong><?= text('Image tile overlapping', '&Uuml;berlappung der Bildabschnitte') ?>.</strong> <?= text('For a bigger tolerance when cutting spare paper borders and for easier pasting, an overlapping width and height of an image tile over the next can be set', 'Um eine gewisse Fehlertoleranz beim Schneiden und Zusammenf&uuml;gen der Bildabschnitte zu haben, kann die H&ouml;he und Breite einer &Uuml;berlappung eines Bildabschnitt &uuml;ber den n&auml;chsten definiert werden.') ?>.
					</li>
					<li>
						<strong><?= text('PDF output', 'PDF-erstellung') ?>.</strong>
						<?= text('The PDF output is implemented with the maximum image quality and a good compression in mind. A source image is embedded once in the PDF document and referenced from every tile page. Image color types remain unchanged. As compression method, the PDF "FlateDecode filter" (zip) is used. If a Jpeg image is used as input it gets directly embedded into the document without recompression. The PDF version is 1.4, so any Acrobat Reader version 4 and higher should be able to read the resulting document.',
						'Der PosteRazor wurde so konzipiert, dass die resultierende PDF-Datei die bestm&ouml;gliche Bildqualit&auml;t bei m&ouml;glichst kleiner Dateigr&ouml;ße hat. Das Bild wird nur einmal in das PDF-Dokument eingebettet und auf den verscheidenen Seiten jeweils referenziert. Als kompressionsmethode wird der PDF-&uuml;bliche "FlateDecode-filter" (zip) benutzt. Wenn das Ausgangsformat ein Jpeg-Bild ist, wird es ohne erneute Komprimierung direkt eingebettet. Die PDF-version ist 1.4, sodass jeder Acrobat Reader ab Version 4 in der Lage sein sollte, das Dokument zu &ouml;ffnen.') ?>
					</li>
				</ul>
				<p><strong><?= text('Missing features', 'Fehlende Funktionen') ?>:</strong> <?= text('Cut lines/aids; Support of Jpeg-CMYK images; Support of 16 Bit Grayscale images; Embedding an ICC profile into the PDF if there is one embedded in the input image', 'Schnittlinen -hilfen; Unterst&uuml;tzung von CMYK-Jpeg; Unterst&uuml;tzung von 16-Bit-Graustufen-Bildern; ICC-Profile, die in einem Ausgangsbild eingebettet sein können im PDF einbetten.') ?></p>
<?
			break;
			case 'screenshots':
?>
				<h2><?= text('Screenshots', 'Bildschirmfotos') ?></h2>
				<div id="screenshotthumbs">
					<?= screenShot("step01", text("Step 1", "Schritt 1")) ?>
					<?= screenShot("step02", text("Step 2", "Schritt 2")) ?>
					<?= screenShot("step03", text("Step 3", "Schritt 3")) ?>
					<?= screenShot("step04", text("Step 4", "Schritt 4")) ?>
					<?= screenShot("step05", text("Step 5", "Schritt 5")) ?>
					<?= screenShot("help_settings", text('Help, settings', 'Hilfe, Einstellungen')) ?>
				</div>
<?
			break;
			case 'download':
?>
				<h2><?= text('Download', 'Herunterladen') ?></h2>
				<p><?= text('The following PosteRazor download links lead to sites with lists of download locations. There, please click on a "Download" link next to a location that is geographically next to Your place.', 'Die folgenden PosteRazor-Download-Verweise f&uuml;hren auf Seiten mit mehreren m&ouml;glichen Downloadservern. Bitte klicken Sie Dort auf einen "Download"-Verweis, der Ihnen geografisch am n&auml;chsten ist.') ?></p>
				<p><?= text('For <strong>direct linking to the downloads</strong> from another site, please use exactly the following links, only these are guaranteed to be valid in the future.', '<strong>Direktes Verlinken auf die Downloads</strong> von anderen Seiten aus bitte mit den unten aufgef&uuml;hrten Links. Nur diese werden mit gro&szlig;er Sicherheit auch in Zukunft g&uuml;ltig sein.') ?></p>
				<ul>
					<li>
						<a href="http://prdownloads.sourceforge.net/posterazor/PosteRazor-1.5-Win32-Installer.exe?download"><strong><?= text('Windows version (Installer)', 'Windows-version (Installationsprogramm)') ?></strong> (346 KB)</a><br />
						<?= text('Download and execute the installer. An uninstaller is integrated.', 'Laden Sie das Installationsprogramm aus, und f&uuml;hren Sie es aus. Ein Deinstallationsprogramm ist enthalten.') ?>
					</li>
					<li>
						<a href="http://prdownloads.sourceforge.net/posterazor/PosteRazor-1.5-Win32.zip?download"><strong><?= text('Windows version (zipped)', 'Windows-version (gezippt)') ?></strong> (346 KB)</a><br />
						<?= text('After downloading the ZIP archive, extract the contained PosteRazor.exe to a place of Your choice and start it. If You use a Windows version below XP, You probably need an installed <a href="http://www.7-zip.org/">Unzip tool</a>.', 'Nach dem Herunterladen des ZIP-Archivs, k&ouml;nnen Sie das enthaltene PosteRazor.exe in ein Verzeichnis Ihrer Wahl entpacken und starten. Falls sie eine Windows-version unterhalb von XP nutzen, ben&ouml;tigen Sie evenuell ein installiertes <a href="http://www.7-zip.org/">Unzip-Programm</a>.') ?>
					</li>
					<li>
						<a href="http://prdownloads.sourceforge.net/posterazor/PosteRazor-1.5-OSX.dmg?download"><strong><?= text('OSX version', 'OSX-version') ?> (Universal Binary)</strong> (610 KB)</a><br />
						<?= text('After downloading the OSX disk image, double click to mount it if it doesn\'t mount automatically. You can start the contained PosteRazor application directly by double clicking it or drag it into a location of Your choice.', 'Nach dem Herunterladen des OSX-Diskimages k&ouml;nnen Sie es, falls dies nicht automatisch geschieht, per Doppelclick mounten. Danach kann die enthaltene PosteRazor-Applikation entweder direkt gestartet werden oder in einen Ordner Ihrer Wahl kopiert werden.') ?><br />
					</li>
					<li>
						<a href="http://prdownloads.sourceforge.net/posterazor/PosteRazor-1.5-Linux-x86.tgz?download"><strong><?= text('Linux version', 'Linux-version') ?></strong> (768 KB)</a><br />
						<?= text('After downloading, untar it. This binary was statically linked against Fltk and FreeImage. It runs on (K)Ubuntu 6.06, 7.04, 7.10 and 8.04 from boot CD. Howerver, it will probably not run on a non-(K)Ubuntu system.', 'Nach dem Herunterladen ent-TAR-en. Dieses Binärpaket wurde statisch gegen Fltk und FreeImage gelinkt. Es l&auml;uft auf (K)Ubuntu 6.06, 7.04, 7.10 und 8.04 von Boot-CD. Aber es wird eventuell nicht auf einem nicht-(K)Ubuntu-System laufen.') ?><br />
					</li>
					<li>
						<a href="http://prdownloads.sourceforge.net/posterazor/PosteRazor-1.5-Source.zip?download"><strong><?= text('Source', 'Quelltext') ?></strong> (226 KB)</a><br />
						<?= text('The source archive includes project files for <a href="http://www.cmake.org">CMake</a> and XCode 2.2. Depends on the not included FLTK and FreeImage (and libXpm-dev on Linux). In order to compile without OpenGL, the preprocessor symbol <em>NO_OPENGL_PREVIEW</em> can be defined.', 'Das Quelltext-archiv enth&auml;lt Projekte f&uuml;r <a href="http://www.cmake.org">CMake</a> und XCode 2.2. Linkt gegen die nicht enthaltenen FLTK und FreeImage (und libXpm-dev unter Linux). Um ohne OpenGL zu kompilieren, kann das Pr&auml;prozessorsymbol <em>NO_OPENGL_PREVIEW</em> definiert werden.') ?><br />
					</li>
				</ul>
<?
			break;
			case 'thirdparty':
?>
				<h2><?= text('Third party code', 'Code von Drittanbietern') ?></h2>
				<?= text('PosteRazor uses third party Open Source libraries. Without those, it would have been painful and unmotivating to create the PosteRazor, and the feature set and portability would have been much smaller. The libraries are statically linked into the PosteRazor.',
				'Der PosteRazor nutzt quelloffene Programmbibliotheken von Dritten. Ohne diese w&auml;re es schmerzvoll und unmotivierend gewesen, den PosteRazor zu erstellen. Au&szlig;erdem w&auml;ren Funktionsumfang und Portabilit&auml;t kleiner gewesen. Die Bibliotheken sind statisch in den PosteRazor eingebunden.') ?>
				<ul>
					<li>
						<strong><?= text('User interface', 'Benutzeroberfl&auml;che') ?>:</strong> <?= text('For the user graphical user interface,', 'F&uuml;r die grafische Benutzeroberfl&auml;che wird') ?> <a href="http://fltk.org/">FLTK 1.1</a> <?= text('is used', 'eingesetzt') ?>. <?= text('It is a ', 'Es ist ein "schnelles, leichtes UI Toolkit" (') ?><strong>f</strong>ast, <strong>l</strong>ight UI <strong>t</strong>ool<strong>k</strong>it<?= text('. Highly portable, flexible, easy and fun to learn&amp;use.', '). Sehr portierbar, flexibel, einfach, und es macht Spass, es zu lernen und zu benutzen.') ?>
					</li>
					<li>
						<strong><?= text('Image loading', 'Bilder laden') ?>:</strong> <?= text('The images are loaded by', 'Die Bilder werden mittels') ?> <a href="http://freeimage.sourceforge.net/">FreeImage 3.10</a><?= text('. This is a portable library that makes image loading, handling and saving a no-brainer.', ' geladen. Dies ist eine portierbare Bibliothek, die das Laden, Manipulieren und Speichern von Bildern zu einem Kinderspiel macht.') ?>
					</li>
					<li>
						<strong><?= text('File chooser dilaog', 'Dateiauswahl-dialog') ?>:</strong> <?= text('The file chooser of the PosteRazor have the platform specific look&amp;feel. Thanks to Fl_Native_File_Chooser:', 'Die Dateiauswahl-dialoge des PosteRazors verdanken ihr systemspezifisches "Look and Feel" dem') ?> <a href="http://seriss.com/people/erco/fltk/Fl_Native_File_Chooser/">Fl_Native_File_Chooser</a>.
					</li>
				</ul>
<?
			break;
			case 'license':
?>
				<h2><?= text('License', 'Lizenz') ?></h2>
				<p>
					PosteRazor - <?= text('Make your own poster', 'Mach\' Dein eigenes Poster') ?>!<br />
					Copyright (C) 2005-2008 by Alessandro Portale<br />
					<a href="http://posterazor.sourceforge.net/<?= text('', '?lang=german') ?>">http://posterazor.sourceforge.net/</a>
				</p>
				<?= text('', '<p><em>Der folgende Lizenztext ist in seiner englischen Originalfassung aufgef&uuml;hrt, da die <a href="http://www.gnu.de/gpl-ger.html">deutsche &Uuml;bersetzung</a> nicht offiziell oder im rechtlichen Sinne anerkannt ist.</em></p>') ?>
				<p>PosteRazor is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.</p>
				<p>PosteRazor is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public License</a> for more details.</p>
<?
			break;
			case 'marketing':
?>
				<h2><?= text('Marketing', 'Marketing') ?></h2>
				<ul>
					<li>
						<strong><?= text('PosteRazor on the Internet', 'PosteRazor im Internet') ?></strong>
						<p>
							<a href="http://freshmeat.net/projects/posterazor/"><img src="marketing_freshmeat.gif" width="88" height="31" alt="FreshMeat" /></a>
							<a href="http://mac.softpedia.com/get/DTP-Prepress/PosteRazor.shtml"><img src="marketing_softpedia.gif" width="75" height="40" alt="Softpedia Pick" /></a>
							<a href="http://winload.de/download/50466/Grafik,Desktop/Bildbearbeitung/PosteRazor-1.1.html"><img src="http://winload.de/banner/80/winload_statisch_80x30_1_1.gif" width="88" height="30" alt="winload.de" /></a>
							<a href="http://www.foto-freeware.de/posterazor.php"><img src="http://www.foto-freeware.de/pic/button_88x31.gif" width="88" height="31" alt="foto-freeware.de" /></a>
							<a href="http://www.freeware.de/software/Programm_PosteRazor_23998.html"><img src="http://media.upload.de/27/46/47/149.gif" width="80" height="30" alt="freeware.de" /></a>
							<a href="http://www.shareware.de/software/Programm_PosteRazor_23998.html"><img src="http://media.upload.de/27/46/48/118.gif" width="80" height="30" alt="shareware.de" /></a>
							<a href="http://www.brothersoft.com/graphics_design/misc_graphics/posterazor_45842.html"><img src="http://www.brothersoft.com/images/LinktoUs/006.gif" width="88" height="31" alt="5/5 stars BrotherSoft" /></a>
							<a href="http://www.topshareware.com/PosteRazor-download-42692.htm"><img src="http://www.topshareware.com/images/logo/topshareware_8831.gif" width="88" height="31" alt="Free Downloads" /></a>
							<a href="http://www.winsoftware.de/posterazor,69,27769.htm"><img src="http://www.winsoftware.de/winsoftwarebutton.jpg" width="88" height="31" alt="Eingetragen bei Winsoftware.de" /></a>
							<a href="http://www.freewarefiles.com/program_3_33_18358.html"><img src="marketing_freewarefiles.gif" width="88" height="31" alt="freewarefiles.com" /></a>
							<a href="http://www.shareware4u.de/detail_templ.php?ProgrammID=13609"><img src="http://www.shareware4u.de/grafik/small01.gif" width="88" height="31" alt="Shareware 4U" /></a>
							<a href="http://www.loady.de/download-information/15682-PosteRazor.html"><img src="http://www.loady.de/banner/banner_88_ani.gif" width="88" height="31" alt="Loady" /></a>
							<a href="http://www.top-download.de/index.php?content=files&amp;fid=4992"><img src="http://www.top-download.de/grafik/2/button_neu_ani.gif" width="88" height="31" alt="top-download.de" /></a>
							<a href="http://www.softforall.com/Multimedia/Illustration/PosteRazor07040048.htm"><img src="marketing_softforall.jpg" width="100" height="40" alt="softforall.com" /></a>
							<a href="http://posterazor.uptodown.com/"><img src="http://imagenes.uptodown.com/imagenes/masvotado.gif" width="115" height="42" alt="uptodown mas votado" /></a>
						</p>
						<p>
							<a href="http://www.opensource-cd.de/grafik3.htm#posterazor">[opensource-cd.de]</a>
							<a href="http://www.wintotal.de/softw/?id=3107">[wintotal.de]</a>
							<a href="http://www.versiontracker.com/dyn/moreinfo/macosx/29212">[versiontracker.com]</a>
							<a href="http://www.aspo-marketingportal.de/cc_seite.php?id=850">[aspo-marketingportal.de]</a>
							<a href="http://www.digitazero.org/?p=29">[digitazero.org]</a>
							<a href="http://www.macupdate.com/info.php/id/20738">[macupdate.com]</a>
							<a href="http://www.macwelt.de/news/fav/336478/index.html">[macwelt.de]</a>
							<a href="http://www.freeware-guide.com/dir/mmedia/imagedit2.html">[freeware-guide.com]</a>
							<a href="http://www.infoweek.ch/downloads/dl_single.cfm?dl_id=1056&amp;sid=0">[infoweek.ch]</a>
							<a href="http://www.clubic.com/telecharger-fiche19446-posterazor.html">[clubic.com]</a>
							<a href="http://www.infos-du-net.com/telecharger/PosteRazor,0301-5121.html">[infos-du-net.com]</a>
							<a href="http://www.freewareplanet.net/imagetool2.php#posterazor">[freewareplanet.net]</a>
							<a href="http://www.heise.de/software/default.shtml?prg=32759&amp;T=posterazor">[heise.de]</a>
							<a href="http://www.addict3d.org/index.php?page=downloadfile&amp;ID=4714">[addict3d.org]</a>
							<a href="http://www.download.bg/index.php?cls=program&amp;mtd=view&amp;id=33887">[download.bg]</a>
							<a href="http://descargas.terra.es/informacion_extendida.phtml?n_id=45043&amp;plat=1">[terra.es]</a>
							<a href="http://www.download3000.com/download_13707.html">[download3000.com]</a>
							<a href="http://www.sofotex.com/PosteRazor-download_L38851.html">[sofotex.com]</a>
							<a href="http://www.solofreeware.net/PosteRazor">[solofreeware.net]</a>
							<a href="http://mac.egoism.jp/nu/item/2901/catid/1">[egoism.jp]</a>
							<a href="http://www.files-library.com/files/PosteRazor-Make-your-own-poster.html">[files-library.com]</a>
							<a href="http://digg.com/software/PosteRazor,_A_better_Rasterbator_app">[digg.com]</a>
							<a href="http://os4depot.net/index.php?function=showfile&amp;file=utility/print/posterazor.lha">[os4depot.net]</a>
							<a href="http://www.genbeta.com/archivos/2005/10/12-generate-tu-poster-a-partir-de.php">[genbeta.com]</a>
							<a href="http://www.allapp.com/PosteRazor_softinfo_27697.html">[allapp.com]</a>
							<a href="http://www.softsland.com/PosteRazor.html">[softsland.com]</a>
							<a href="http://www.shareware-list.com/download-584-34337.html">[shareware-list.com]</a>
							<a href="http://www.programas-gratis.net/php/programa2.php?id_programa=4140">[programas-gratis.net]</a>
							<a href="http://download.excite.it/scheda.php?id=271282">[excite.it]</a>
							<a href="http://www.filehungry.com/english/product/windows_software/multimedia_&amp;_graphics/graphic_conversion_tools/posterazor">[filehungry.com]</a>
							<a href="http://www.foto-digital.com.mx/2005/10/20/posterazor/">[foto-digital.com.mx]</a>
							<a href="http://download.bestweb.ro/GraphicsDesign/BannersPosters/2-29-0-33-0-0.html">[bestweb.ro]</a>
							<a href="http://www.fltk.org/links.php?V272">[fltk.org]</a>
							<a href="http://simplex.blogtotal.es/post/542/2270">[blogtotal.es]</a>
							<a href="http://www.libellules.ch/dotclear/index.php?2006/03/18/864-posterazor">[libellules.ch]</a>
						</p>
					</li>
					<li>
						<strong><?= text('Similar programs', '&Auml;hnliche Programme') ?></strong>
						<p>
							<?= text('Do You miss a feature in the PosteRazor? Try out the programs from this alphabetically sorted list:', 'Vermissen Sie eine Funktion beim PosteRazor? Testen Sie die Programme in dieser alphabetisch sortierten Liste:') ?>
						</p>
						<p>
							<a href="http://www.intemove.com/">[Ace Poster]</a>
							<a href="http://www.waltereckel.de/">[BookPrint]</a>
							<a href="http://www.srs1software.com/">[Digital Camera Poster Creator]</a>
							<a href="http://www.grafik-software.de/">[PicMaster]</a>
							<a href="http://www.postersw.com/">[Poster]</a>
							<a href="http://www.posterbuddy.com/">[Poster Buddy]</a>
							<a href="http://www.luxordevelopment.ch/posterprint/">[Poster Print]</a>
							<a href="http://www.cadkas.de/downengprint1.php">[Poster Printery]</a>
							<a href="http://www.posteriza.com/">[Posteriza]</a>
							<a href="http://grandutils.com/PosterPrint/">[PosterPrint]</a>
							<a href="http://www.bear.co.jp/en/PrintExpander.htm">[PrintExpander]</a>
							<a href="http://usefulsoft.com/printghost/">[PrintGhost]</a>
							<a href="http://www.ronyasoft.com/products/proposter/">[ProPoster]</a>
							<a href="http://arje.net/rasterbator">[Rasterbator Desktop]</a>
							<a href="http://homokaasu.org/rasterbator/">[Rasterbator Web]</a>
							<a href="http://www.keseling.de/pdr.htm">[SKS Poster-Drucker]</a>
							<a href="http://www.mindcad.com/tiler.php">[Tiler]</a>
							<a href="http://www.oreware.com/viewprogram.php?prog=9">[Wall Photo Maker]</a>
						</p>
					</li>
				</ul>
<?
			break;
			default:
?>
				<h2><?= text('About', '&Uuml;ber') ?></h2>
				<?= text('The PosteRazor cuts a raster image into pieces which can afterwards be printed out and assembled to a poster.', 'Der PosteRazor schneidet eine Rasterbild-datei in St&uuml;cke, die anschlie&szlig;end ausgedruckt und zu einem Poster zusammengef&uuml;gt werden k&ouml;nnen.') ?>
				<br /><div style="text-align: center; margin: 10px;"><img src="workflow.png" width="376" height="107" alt="PosteRazor workflow"/></div>
				<?= text('As input, the PosteRazor takes a raster image. The resulting poster is saved as a multipage PDF document. An easy to use, wizard like user interface guides through 5 steps. PosteRazor is available as a Windows, an OSX and a Linux version.', 'Als Ausgangsmaterial nimmt der PosteRazor eine Rasterbild-datei. Das Endprodukt ist ein Poster in Form eines mehrseitigen PDF-Dokuments. Eine einfach zu bedienende Benutzerschnittstelle im Assistenten-Stil begleitet durch f&uuml;nf Schritte. Der PosteRazor ist als Windows-, als OSX- und als Linux-Version erh&auml;ltlich.') ?>
				<?= text('It is an open source, ', 'Er ist ein quelloffenes, ') ?><a href="<?=linkParameters("license","")?>"><?= text('GNU licensed', 'GNU-lizensiertes') ?></a> <?= text('project which is hosted on SourceForge.net.', 'Projekt, das auf SourceForge hinterlegt ist.') ?>
				<?= text('For feedback, bug reports or feature requests, please use the', 'F&uuml;r Feedback, Fehlerberichte oder Erweiterungsw&uuml;nsche nutzen Sie bitte die ') ?> <a href="http://sourceforge.net/projects/posterazor/"><?= text('PosteRazor project page', 'PosteRazor-Projektseite') ?></a>, <?= text('write a mail to', 'schreiben Sie eine Mail an') ?> <strong>Alessandro&nbsp;&auml;t&nbsp;casaportale&nbsp;d&ocirc;t de</strong> <?= text('or contact the author via', 'oder kontaktieren Sie den Autor via') ?> <a href="http://www.casaportale.de/html/index.php?page=contact&amp;lang=<?= text('english', 'german') ?>&amp;menu=on"><?= text('mail form', 'Mail-Formular') ?></a>.
				<h3><?= text('Contributors', 'Mitwirkende') ?>:</h3>
				<ul>
					<li><?= text('Polish translation:', 'Polnische &Uuml;bersetzung:') ?> Grzegorz Wacikowski</li>
					<li><?= text('French translation:', 'Franz&ouml;sische &Uuml;bersetzung:') ?> Martin Loyer</li>
					<li><?= text('Italian translation:', 'Italienische &Uuml;bersetzung:') ?> Stefano Nosei</li>
					<li><?= text('Dutch/Belgian translation:', 'Holl&auml;ndische/Belgische &Uuml;bersetzung:') ?> Erik Wijkamp</li>
					<li><?= text('Spanish translation:', 'Spanische &Uuml;bersetzung:') ?> <a href="http://hispanicoweb.net/">Hisp&aacute;nico Web</a></li>
					<li><?= text('Brazilian Portuguese translation:', 'Brasilianisch-portugisische &Uuml;bersetzung:') ?> &Eacute;derson Gomes dos Santos</li>
				</ul>
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
		<meta name="description" content="PosteRazor - <?= text('Make your own poster', 'Mach\' Dein eigenes Poster') ?>!" />
		<meta name="keywords" content="poster, posterazor, print, fltk, freeimage, pdf, application, tool, app, free, create, freeware" />
		<title>PosteRazor - <?= text('Make your own poster', 'Mach\' Dein eigenes Poster') ?>!</title>
		<style type="text/css" media="all">
			@import "style.css";
		</style>
<?	if ($page == "screenshots"){ ?>
		<style type="text/css" media="screen">
			@import "jquery.lightbox-0.5.css";
		</style>
		<script type="text/javascript" src="jquery-1.2.3.min.js"></script>
		<script type="text/javascript" src="jquery.lightbox-0.5.min.js"></script>
		<script type="text/javascript">
			$(function() {
				$('#screenshotthumbs a').lightBox();
			});
		</script>
<?	}?>
	</head>
	<body>
		<div id="page">
			<div id="header">
				<div id="title">PosteRazor</div><div id="tagline"><?= text('Make your own poster!', 'Mach\' Dein eigenes Poster!') ?></div>
				<a href="<?=linkParameters("","english")?>"><img src="flagEnglish<?= text('_selected', '') ?>.png" width="26" height="17" alt="English" /></a><a href="<?=linkParameters("","german")?>"><img src="flagGerman<?= text('', '_selected') ?>.png" width="26" height="17" alt="Deutsch" /></a>
			</div>
			<div id="navigation">
				<ul id="navigationlist"><li><a href="<?=linkParameters("news","")?>"<?=conditionalSelectedClass("news")?>><?= text('News', 'Neuigkeiten') ?></a></li><li><a href="<?=linkParameters("about","")?>"<?=conditionalSelectedClass("about")?>><?= text('About', '&Uuml;ber') ?></a></li><li><a href="<?=linkParameters("features","")?>"<?=conditionalSelectedClass("features")?>><?= text('Features', 'Funktionen') ?></a></li><li><a href="<?=linkParameters("screenshots","")?>"<?=conditionalSelectedClass("screenshots")?>><?= text('Screenshots', 'Bildschirmfotos') ?></a></li><li><a href="<?=linkParameters("download","")?>"<?=conditionalSelectedClass("download")?>><?= text('Download', 'Herunterladen') ?></a></li><li><a href="<?=linkParameters("thirdparty","")?>"<?=conditionalSelectedClass("thirdparty")?>><?= text('Third&nbsp;party&nbsp;code', 'Code&nbsp;von&nbsp;Dritten') ?></a></li><li><a href="<?=linkParameters("license","")?>"<?=conditionalSelectedClass("license")?>><?= text('License', 'Lizenz') ?></a></li><li><a href="<?=linkParameters("marketing","")?>"<?=conditionalSelectedClass("marketing")?>><?= text('Marketing', 'Marketing') ?></a></li></ul>
				<a href="http://sourceforge.net"><img src="http://sourceforge.net/sflogo.php?group_id=141842&amp;type=1" width="88" height="31" alt="SF.net Logo" /></a>
				<a href="http://sourceforge.net/projects/posterazor/"><?= text('SF project page', 'SF Projekt-Seite') ?></a>
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