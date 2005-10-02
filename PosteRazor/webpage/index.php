<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
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
		<title>PosteRazor - Make your own poster!</title>
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
			<a href="http://sourceforge.net"><img src="http://sourceforge.net/sflogo.php?group_id=141842&amp;type=1" width="88" height="31" alt="SourceForge.net Logo" /></a><br />
			<a href="http://validator.w3.org/check?uri=referer"><img src="http://www.w3.org/Icons/valid-xhtml10" alt="Valid XHTML 1.0 Strict" height="31" width="88" /></a>
		</div>
		
		<div class="mainpage">
			<h1>PosteRazor<br /><sup>Make your own poster!</sup></h1>
			<hr />
			<div class="links">
				<a href="#news">News</a>
				- <a href="#about">About</a>
				- <a href="#features">Features</a>
				- <a href="#screenshots">Screenshots</a>
				- <a href="http://sourceforge.net/project/showfiles.php?group_id=141842">Download</a>
				- <a href="#thirdparty">Third&nbsp;party&nbsp;code</a>
				- <a href="#license">License</a>
			</div>

			<hr />
			<h2><a name="news"></a>News</h2>
			<ul>
				<li>
					<b>October 3rd 2005:</b> Version 1.0
					<br/>The first release of PosteRazor. Windows and OSX version.
				</li>
			</ul>

			<hr />
			<h2><a name="about"></a>About</h2>
			The PosteRazor cuts a raster image into pieces which can afterwards be printed out and assembled to a poster.
			<br /><div style="text-align: center; margin: 10px;"><img src="images/workflow.png" width="400" height="114" alt="PosteRazor workflow"/></div>
			As input, the PosteRazor takes a raster image. The resulting poster is saved as a multipage PDF document. An easy to use, wizard like user interface guides through 5 steps. PosteRazor is available as a Windows and as an OSX version (it should also be compilable on Linux). It is an open source, GNU licensed project which is hosted on SourceForge.net. For feedback, bug reports feature requests, please use the <a href="http://sourceforge.net/projects/posterazor/">PosteRazor project page</a> or write a mail to <b>Alessandro&nbsp;&auml;t&nbsp;casaportale&nbsp;d&ocirc;t de</b>
			
			<hr />
			<h2><a name="features"></a>Features</h2>
			<ul>
				<li>
					<b>Input image formats.</b> All image formats that <a href="http://freeimage.sourceforge.net/features.html">FreeImage</a> can read <i>should</i> be usabe as input for the PosteRazor:
					<div class="fileformats">BMP, DDS files, Dr. Halo, GIF, ICO, IFF, JBIG, JNG, JPEG/JIF, KOALA, LBM, Kodak PhotoCD, MNG, PCX, PBM, PGM, PNG, PPM, PhotoShop PSD, Sun RAS, TARGA, TIFF, WBMP, XBM, XPM</div>
				</li>
				<li>
					<b>Image types.</b> The following image color types are handable:
					<div class="fileformats">Monochrome, Grayscale, 4 Bit palette, 8 Bit palette, 24 Bit RGB/A, 48 Bit RGB (only via TIFF), 32 Bit CMYK (only via TIFF)</div>
				</li>
				<li>
					<b>Dimension Units.</b> Because people around the world invented so many different dimension units, PosteRazor supports quite a few:
					<div class="fileformats">m, mm, cm, inch, feet, points(72th inch)</div>
				</li>
				<li>
					<b>Printer page layout.</b> The page size and orientation of the printer where the poster wil be printed can be set manually or selected one from the following list of predefined formats:
					<div class="fileformats">DIN A4, DIN A3, Legal, Letter, Tabloid</div>
					The size limit for one page is 5 meters (16.4 feet), which is the maximum that PDF allows.
				</li>
				<li>
					<b>Poster size.</b> The size of the final poster can be set one of these three ways:
					<ul>
						<li><b>Absolute image size</b>: You want to have a specific size of your poster.</li>
						<li><b>Size in Pages</b>: you want to use whole paper sheets and specify how many of them of them you want to use.</li>
						<li><b>Image Size in percent</b>: your input image has a certain size which is defined by the number of pixels and dpi (dots per Inch) and your want to enlage the image by a certain factor.</li>
					</ul>
					The final size of the poster is theoretically unlimited. Let's say it this way: it is less limited that the ink of your printer ;)<br />
					It is possible to select the alignment of the image on the total paper. This is useful if you want to keep the unused paper.
				</li>
				<li>
					<b>Image tile overlapping.</b> For a bigger tolerance when cutting spare paper borders and for easier pasting, an overlapping width and height of an image tile over the next can be set.
				</li>
				<li>
					<b>PDF output.</b> The PDF output is implemented with the maximum image quality and a good compression in mind. The source image is embedded once in the PDF document and referenced from every tile page. The image color types remain unchanged. As compression method, the PDF "FlateDecode filter" (zip) is used. If a Jpeg image is used as input it gets directly embedded into the document without recompression.
				</li>
			</ul>
			<b>Missing features:</b> Cut lines/aids; Support of Jpeg-CMYK images; Support of 16 Bit Grayscale images; Embedding an ICC profile into the PDF if there is one embedded in the input image

			<hr />
			<h2><a name="screenshots"></a>Screenshots</h2>
			<div style="align: center; " >
			<table border="0" class="center" cellpadding="5">
				<tr><td colspan="3">Click to enlarge:</td></tr>
				<tr>
					<td><a href="images/screenshots/step01.png"><img src="images/screenshots/thumbnails/step01.png" width="100" height="76" alt="Step 1" /><br />Step 1</a></td>
					<td><a href="images/screenshots/step02.png"><img src="images/screenshots/thumbnails/step02.png" width="100" height="76" alt="Step 2" /><br />Step 2</a></td>
					<td><a href="images/screenshots/step03.png"><img src="images/screenshots/thumbnails/step03.png" width="100" height="76" alt="Step 3" /><br />Step 3</a></td>
				</tr>
				<tr>
					<td><a href="images/screenshots/step04.png"><img src="images/screenshots/thumbnails/step04.png" width="100" height="76" alt="Step 4" /><br />Step 4</a></td>
					<td><a href="images/screenshots/step05.png"><img src="images/screenshots/thumbnails/step05.png" width="100" height="76" alt="Step 5" /><br />Step 5</a></td>
					<td><a href="images/screenshots/help.png"><img src="images/screenshots/thumbnails/help.png" width="100" height="72" alt="Help" /><br />Help</a></td>
				</tr>
			</table>
			</div>
			
			<hr />
			<h2><a name="thirdparty"></a>Third party code</h2>
			PosteRazor uses third party Open Source libraries. Without those, it would have been painful and unmotivating to create the PosteRazor, and the feature set and portability would have been much smaller. The libraries are statically linked into the PosteRazor.
			<ul>
				<li>
					<b>User interface:</b> For the user interface, <a href="http://fltk.org/">FLTK 1.1</a> is used. It is a <b>f</b>ast, <b>l</b>ight UI <b>t</b>ool<b>k</b>it. Highly portable, flexible, easy and fun to learn&amp;use.
				</li>
				<li>
					<b>Image loading:</b> The images are loaded by <a href="http://freeimage.sourceforge.net/">FreeImage 3.8.0</a>. This is a portable library that makes image loading, handling and saving a no-brainer.
				</li>
				<li>
					<b>File chooser:</b> The file chooser of the PosteRazor have the platform specific look&amp;feel. Thanks to Fl_Native_File_Chooser: <a href="http://seriss.com/people/erco/fltk/Fl_Native_File_Chooser/">Variant 1</a> and <a href="http://homepages.dordt.edu/~nthnlvnd/soft/Fl_Native_File_Chooser.html">Variant 2</a>.
				</li>
			</ul>
			
			<hr />
			<h2><a name="license"></a>License</h2>
			PosteRazor - Make your own poster!<br />
			Copyright (C) 2005 by Alessandro Portale<br />
			<a href="http://posterazor.sourceforge.net/">http://posterazor.sourceforge.net/</a><br />
			<br />
			PosteRazor is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by	the Free Software Foundation; either version 2 of the License, or (at your option) any later version.<br />
			<br />
			PosteRazor is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the <a href="http://www.gnu.org/copyleft/gpl.html">GNU General Public License</a> for more details.<br />
			<br />
		</div>
	</body>
</html>