<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
    "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<?
	$textColor = "#330000";
?><html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<title>PosteRazor - Make your own poster!</title>
		<style type="text/css">
		/*<![CDATA[*/
			h1
			{
				text-align: center;
				font-size: 2.6em;
			}

			h2
			{
				font-size: 1.6em;
			}

			hr
			{
				border: 0;
				color: <? echo $textColor; ?>;
				background-color: <? echo $textColor; ?>;
				height: 3px;
			}
			
			A:Visited
			{
				color: <? echo $textColor; ?>;
			}			

			img
			{
				border: 0;
			}
			
			body
			{
				font-family: Verdana,sans-serif;
				font-size: 10pt;
				background: #eeeeff none;
				margin: 10px;
			}

			td
			{
				text-align: center;
			}
			
			#mainpage
			{
				padding: 0px 15px;
				margin: 0 15%;
				border: 1px solid <? echo $textColor; ?>;
				background: #ffffee url(images/logo.png) no-repeat; 
				color: <? echo $textColor; ?>;
			}
			
			#links
			{
				text-align: center;
			}

			#fileformats
			{
				margin: 10px 5%;
				padding: 10px 15px;
				border: 1px solid <? echo $textColor; ?>;
				background: #ffffff none;
			}
		/*]]>*/
		</style>
	</head>
	<body>
		<div id="mainpage">
			<h1>PosteRazor<br /><sup>Make your own poster!</sup></h1>
			<hr />
			<div id="links">
				<a href="#about">About</a>
				- <a href="#about">Screenshots</a>
				- <a href="http://sourceforge.net/project/showfiles.php?group_id=141842">Download</a>
			</div>

			<hr />
			<a name="about" />
			<h2>About</h2>
			The PosteRazor cuts a raster image into pieces which can be printed on a printer and be put together to a poster.
			<br /><div style="text-align: center; margin: 10px;"><img src="images/workflow.png" width="500" height="143" /></div>
			As an input image, raster files of various image file formats are supported:
			Instead of directly printing the poster, the PosteRazor produces a multi page PDF files which contains the poster tiles.<br />
			<div id="fileformats">
				BMP, DDS files, Dr. Halo, GIF, ICO, IFF, JBIG, JNG, JPEG/JIF, KOALA, LBM, Kodak PhotoCD, MNG, PCX, PBM, PGM, PNG, PPM, PhotoShop PSD, Sun RAS, TARGA, TIFF, WBMP, XBM, XPM
			</div>
			It is an open source program which depends on <a href="#">other open source projects</a>.
				
			<hr />
			<a name="screenshots" />
			<h2>Screenshots</h2>
			<div style="text-align: center; " >
			<table border="0" align="center">
				<tr>
					<td><a href="images/screenshots/step01.png"><img src="images/screenshots/thumbnails/step01.png" width="100" height="76" /><br />Step 1</a></td>
					<td><a href="images/screenshots/step02.png"><img src="images/screenshots/thumbnails/step02.png" width="100" height="76" /><br />Step 2</a></td>
					<td><a href="images/screenshots/step03.png"><img src="images/screenshots/thumbnails/step03.png" width="100" height="76" /><br />Step 3</a></td>
					<td><a href="images/screenshots/step04.png"><img src="images/screenshots/thumbnails/step04.png" width="100" height="76" /><br />Step 4</a></td>
					<td><a href="images/screenshots/step05.png"><img src="images/screenshots/thumbnails/step05.png" width="100" height="76" /><br />Step 5</a></td>
					<td><a href="images/screenshots/help.png"><img src="images/screenshots/thumbnails/help.png" width="100" height="72" /><br />Help</a></td>
				</tr>
			</table>
			</div>
		</div>
	</body>
</html>