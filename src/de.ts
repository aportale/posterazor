<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS><TS version="1.1" language="de_DE">
<context>
    <name>Help</name>
    <message>
        <location filename="wizardcontroller.cpp" line="121"/>
        <source>Step %1 of %2:</source>
        <translation type="unfinished">Schritt %1 von %2:</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="90"/>
        <source>&amp;Manual</source>
        <translation type="unfinished">&amp;Bedienungsanleitung</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="92"/>
        <source>&amp;About PosteRazor</source>
        <translation type="unfinished">&amp;Über den PosteRazor</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="91"/>
        <source>PosteRazor &amp;website</source>
        <translation type="unfinished">PosteRazor-&amp;Internetseite</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="93"/>
        <source>About &amp;Qt</source>
        <translation type="unfinished">Über &amp;Qt</translation>
    </message>
    <message>
        <location filename="controller.cpp" line="458"/>
        <source>http://posterazor.sourceforge.net/</source>
        <comment>Only translate, if the website has this language.</comment>
        <translation type="unfinished">http://posterazor.sourceforge.net/?lang=german</translation>
    </message>
    <message>
        <location filename="wizardcontroller.cpp" line="130"/>
        <source>Load an input image</source>
        <translation type="unfinished">Ein Ausgangsbild laden</translation>
    </message>
    <message>
        <location filename="wizardcontroller.cpp" line="131"/>
        <source>Printer paper format</source>
        <translation type="unfinished">Druckerpapier-Maße</translation>
    </message>
    <message>
        <location filename="wizardcontroller.cpp" line="132"/>
        <source>Image tile overlapping</source>
        <translation type="unfinished">Überlappung der Bildabschnitte</translation>
    </message>
    <message>
        <location filename="wizardcontroller.cpp" line="133"/>
        <source>Final poster size</source>
        <translation type="unfinished">Die finale Postergröße</translation>
    </message>
    <message>
        <location filename="wizardcontroller.cpp" line="133"/>
        <source>Save the Poster</source>
        <translation type="unfinished">Das Poster speichern</translation>
    </message>
    <message>
        <location filename="wizardcontroller.cpp" line="143"/>
        <source>Load an image by clicking the button with the open icon and selecting an image file, or by drag &amp; dropping an image file on the PosteRazor. The drag &amp; drop also works during the other steps.
After loading the image, the most important informations are listed in the &apos;%1&apos; fields.</source>
        <comment>Wizard step 1. Place holders: %1 = &apos;Image informations&apos; (will be automatically inserted)</comment>
        <translation type="unfinished">Laden Sie ein Ausgangsbild, indem sie auf das &apos;öffnen&apos;-Symbol klicken und eine Datei wählen, oder indem Sie eine Datei auf den PosteRazor fallen lassen (Drag &amp; Drop). Die Drag &amp; Drop-Funktion des Ausgangsbildes ist in allen Assistenten-Schritten vorhanden.
Nach dem Laden eines Bildes werden in dem Feld &apos;%1&apos; die wichtigsten Angaben aufgelistet.</translation>
    </message>
    <message>
        <location filename="wizardcontroller.cpp" line="150"/>
        <source>Define the paper sheet size that you use in your printer.
A standard paper sheet size can be selected from the &apos;%1&apos; chooser, along with the desired paper sheet orientation.
Alternatively, a custom paper sheet size can be defined in the &apos;%2&apos; tab.
Paper borders are defined in the &apos;%3&apos; fields. Even if your printer does need no (or small) paper borders, some border might be needed to have enough area for gluing the final poster tiles together.</source>
        <comment>Wizard step 2. Place holders: %1 = &apos;Format:&apos;, %2 = &apos;Custom&apos;, %3 = &apos;Borders (%1)&apos; (will be automatically inserted)</comment>
        <translation type="unfinished">Definieren Sie, welches Papiermaß Ihr Drucker unterstützt.
Ein Standard-Papierbogenformat kann in der &apos;%1&apos;-Auswahl selektiert werden und ebenso die gewünschte Ausrichtung der Bögen.
Alternativ können in dem &apos;%2&apos;-Reiter selbstdefinierte Bogenmaße angegeben werden.
Papierränder können in den &apos;%3&apos;-Feldern angegeben werden. Auch wenn Ihr Drucker randlos druckt, wird später gegebenfalls etwas Rand als Klebefläche benötigt.</translation>
    </message>
    <message>
        <location filename="wizardcontroller.cpp" line="157"/>
        <source>Image tile overlapping is needed to have some tolerance for cutting off the unneeded borders from one side. Additionally, like the borders from the previous step, it gives more area for gluing together the final poster tiles.
The &apos;%1&apos; defines the borders that are intended to be overlapped by the neighbor tiles. The borders on the opposite sides are intended to be cut (except on the outermost tiles).</source>
        <comment>Wizard step 3. Place holders: %1 = &apos;Overlapping position&apos; (will be automatically inserted)</comment>
        <translation type="unfinished">Eine Überlappung der Bildabschnitte ist sehr hilfreich, da sie beim Schneiden der überfälligen Ränder und Zusammenkleben der Teile eine gewisse Fehlertoleranz ins Spiel bringt. Zusätzlich bietet sie (ebenso wie die Ränder des vorangegangenen Schrittes) mehr Klebefläche für die Bildteile.
Die Angabe &apos;%1&apos; beschreibt, welche Seitenränder von den anliegneden Bildabschnitten überlagert werden sollen. Die Ränder auf den gegenüberliegenden Seiten sind zum Abschneiden gedacht (ausgenommen jene auf den äußeren Bildabschnitten).</translation>
    </message>
    <message>
        <location filename="wizardcontroller.cpp" line="166"/>
        <source>Define the final poster size, in one of the following three modes which can be selected by the corresponding radio buttons:
&apos;%1&apos; You want to have a specific size of your poster.
&apos;%2&apos; You want to use whole paper sheets and specify how many of them of them you want to use.
&apos;%3&apos; Your input image has a certain size which is defined by the number of pixels and dpi (dots per Inch) and your want to enlarge the image by a certain factor.
The aspect ratio of width and height is always 1:1 and is automatically recalculated. In the preview area, you can see the overlapping areas which are surrounded by light red rectangles.
&apos;%4&apos; sets the alignment of the image on the total paper area of the poster. This is useful if you want to keep the unused paper.</source>
        <comment>Wizard step 4. Place holders: %1 = &apos;Absolute size:&apos;, %2 = &apos;Size in pages:&apos;, %3 = &apos;Size in percent:&apos;, %4 = &apos;Image alignment&apos; (will be automatically inserted)</comment>
        <translation type="unfinished">Beschreiben Sie auf eine der drei folgenden Weisen die Maße des finalen Posters: Die entsprechende Eingabeweise muss per Radio-Button aktiviert sein.
&apos;%1&apos; Sie wollen, dass das Poster ganz bestimmte Maße hat.
&apos;%2&apos; Sie wollen die Druckbögen komplett nutzen und spezifizieren die Anzahl der Bögen.
&apos;%3&apos; Ihr Ausgangsbild hat bestimmte Maße, die sich aus seiner Anzahl an Pixeln und der Auflösung (dpi, dots per Inch) ergeben. Sie wollen das Bild auf einen bestimmten Prozentsatz vergrößern.
Das Seitenverhältnis ist immer 1:1, bei der Editierung z.B. der Breite wird die Höhe automatisch errechnet. In dem Vorschaubereich können Sie die Überlappungen der Bildabschnitte als rötlich markierte Balken sehen.
&apos;%4&apos; beschreibt die Ausrichtung des Bildes auf der gesamten Papierfläche des Posters. Diese Einstellung ist nur dann sinnvoll, wenn das überstehende Papier am Ende nicht abgeschnitten werden soll.</translation>
    </message>
    <message>
        <location filename="wizardcontroller.cpp" line="174"/>
        <source>Save the poster by clicking the save button and specifying a destination file name.
Check or uncheck the &apos;%1&apos;, if the standard PDF handling application that is set in your operating system should be automatically started after the PDF file is saved.</source>
        <comment>Wizard step 5. Place holders: %1 = &apos;Open PDF after saving&apos; (will be automatically inserted)</comment>
        <translation type="unfinished">Speichern Sie das Poster, indem Sie auf den &apos;speichern&apos;-Knopf klicken und einen Dateinamen definieren.
Aktivieren oder deaktivieren Sie &apos;%1&apos;, je nach dem, ob das Poster nach dem Speichern automatisch mit dem Standard-PDF-Programm gestartet werden soll.</translation>
    </message>
</context>
<context>
    <name>Main window</name>
    <message>
        <location filename="mainwindow.cpp" line="95"/>
        <source>Image Informations</source>
        <translation type="unfinished">Bildinformationen</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="96"/>
        <source>Color type:</source>
        <translation type="unfinished">Farbtyp:</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="97"/>
        <source>Resolution:</source>
        <translation type="unfinished">Auflösung:</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="98"/>
        <source>Size (in pixels):</source>
        <translation type="unfinished">Größe (in Pixeln):</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="99"/>
        <source>Input Image</source>
        <translation type="unfinished">Ausgangsbild</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="100"/>
        <source>Open PDF after saving</source>
        <translation type="unfinished">PDF nach Speicherung öffnen</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="101"/>
        <source>&amp;File</source>
        <translation type="unfinished">&amp;Datei</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="102"/>
        <source>&amp;Settings</source>
        <translation type="unfinished">&amp;Einstellungen</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="103"/>
        <source>Next</source>
        <translation type="unfinished">Weiter</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="131"/>
        <source>Height:</source>
        <translation type="unfinished">Höhe:</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="105"/>
        <source>Bottom left</source>
        <translation type="unfinished">Unten links</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="106"/>
        <source>Bottom right</source>
        <translation type="unfinished">Unten rechts</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="107"/>
        <source>Overlapping position</source>
        <translation type="unfinished">Überlappende Seiten</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="108"/>
        <source>Top left</source>
        <translation type="unfinished">Oben links</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="109"/>
        <source>Top right</source>
        <translation type="unfinished">Oben rechts</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="110"/>
        <source>Overlapping size</source>
        <translation type="unfinished">Maße der Überlappung</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="133"/>
        <source>Width:</source>
        <translation type="unfinished">Breite:</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="112"/>
        <source>Bottom</source>
        <translation type="unfinished">Unten</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="147"/>
        <source>Size (in %1):</source>
        <translation type="unfinished">Größe (in %1):</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="148"/>
        <source>Borders (%1)</source>
        <translation type="unfinished">Ränder (%1)</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="113"/>
        <source>Left</source>
        <translation type="unfinished">Links</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="114"/>
        <source>Right</source>
        <translation type="unfinished">Rechts</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="115"/>
        <source>Top</source>
        <translation type="unfinished">Oben</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="118"/>
        <source>Format:</source>
        <translation type="unfinished">Format:</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="120"/>
        <source>Custom</source>
        <translation type="unfinished">Eigenes</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="122"/>
        <source>Standard</source>
        <translation type="unfinished">Standard</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="123"/>
        <source>Orientation:</source>
        <translation type="unfinished">Ausrichtung:</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="124"/>
        <source>Landscape</source>
        <translation type="unfinished">Querformat</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="125"/>
        <source>Portrait</source>
        <translation type="unfinished">Hochformat</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="126"/>
        <source>Paper size</source>
        <translation type="unfinished">Papierformat</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="129"/>
        <source>Image alignment</source>
        <translation type="unfinished">Ausrichtung des Bildes</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="132"/>
        <source>pages</source>
        <translation type="unfinished">Seiten</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="134"/>
        <source>Size:</source>
        <translation type="unfinished">Größe:</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="135"/>
        <source>Absolute size:</source>
        <translation type="unfinished">Absolute Maße:</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="136"/>
        <source>Image size</source>
        <translation type="unfinished">Größe</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="137"/>
        <source>Size in pages:</source>
        <translation type="unfinished">Größe in Seiten:</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="138"/>
        <source>Size in percent:</source>
        <translation type="unfinished">Prozentuelle Größe:</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="139"/>
        <source>Back</source>
        <translation type="unfinished">Zurück</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="141"/>
        <source>Save the poster</source>
        <translation type="unfinished">Das Poster speichern</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="276"/>
        <source>Monochrome</source>
        <translation type="unfinished">Monochrom</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="277"/>
        <source>Gray scale</source>
        <translation type="unfinished">Graustufen</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="278"/>
        <source>Palette</source>
        <translation type="unfinished">Palette</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="279"/>
        <source>RGB</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="280"/>
        <source>RGBA</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="282"/>
        <source>CMYK</source>
        <translation type="unfinished"></translation>
    </message>
    <message>
        <location filename="controller.cpp" line="349"/>
        <source>All image formats</source>
        <translation type="unfinished">Alle Bildformate</translation>
    </message>
    <message>
        <location filename="controller.cpp" line="356"/>
        <source>Load an input image</source>
        <translation type="unfinished">Ein Ausgangsbild laden</translation>
    </message>
    <message>
        <location filename="controller.cpp" line="374"/>
        <source>The Image &apos;%1&apos; could not be loaded.</source>
        <translation type="unfinished">Die Datei &apos;%1&apos; konnte nicht geladen werden.
</translation>
    </message>
    <message>
        <location filename="controller.cpp" line="421"/>
        <source>The file &apos;%1&apos; already exists.
Do you want to overwrite it?</source>
        <translation type="unfinished">Die Datei &apos;%1&apos; extistiert bereits.
Soll sie überschrieben werden?</translation>
    </message>
    <message>
        <location filename="controller.cpp" line="425"/>
        <source>The File &quot;%1&quot; could not be saved.</source>
        <translation type="unfinished">Die Datei &apos;%1&apos; konnte nicht gespeichert werden.</translation>
    </message>
    <message>
        <location filename="mainwindow.cpp" line="443"/>
        <source>Language name</source>
        <translation type="unfinished">Deutsch</translation>
    </message>
</context>
</TS>
