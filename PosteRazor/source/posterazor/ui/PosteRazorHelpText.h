#ifndef PosteRazorHelpText_h
#define PosteRazorHelpText_h

#define POSTERAZORHELPSTEPTITLE01 "Load an input image"
#define POSTERAZORHELPSTEPTITLE02 "Define the printer paper size"
#define POSTERAZORHELPSTEPTITLE03 "Define the image tile overlapping"
#define POSTERAZORHELPSTEPTITLE04 "Define the final poster size"
#define POSTERAZORHELPSTEPTITLE05 "Save the Poster"

#define POSTERAZORHELPANCHORTOP "top"
#define POSTERAZORHELPANCHORABOUT "about"
#define POSTERAZORHELPANCHORMANUAL "manual"
#define POSTERAZORHELPANCHORMANUALSTEP "manualstep"
#define POSTERAZORHELPANCHORMANUALSTEP01 "manualstep01"
#define POSTERAZORHELPANCHORMANUALSTEP02 "manualstep02"
#define POSTERAZORHELPANCHORMANUALSTEP03 "manualstep03"
#define POSTERAZORHELPANCHORMANUALSTEP04 "manualstep04"
#define POSTERAZORHELPANCHORMANUALSTEP05 "manualstep05"
#define POSTERAZORHELPANCHORINPUTFILEFORMATS "inputfileformats"
#define POSTERAZORHELPANCHORABOUTPDFOUTPUT "aboutpdfoutput"
#define POSTERAZORHELPANCHORWHYPDFOUTPUT "whypdfoutput"
#define POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES "codefromthirdparties"


#define POSTERAZORHELPINDENTATION "<br>&nbsp;&nbsp;&nbsp;&nbsp;"
#define POSTERAZORHELPENDLINE ""

const static const char *posteRazorHelpText =
"<HTML>" POSTERAZORHELPENDLINE \
	"<BODY>" POSTERAZORHELPENDLINE \
		"<A name=\"" POSTERAZORHELPANCHORTOP "\"><CENTER><H1>PosteRazor Help</H1></CENTER></A>" POSTERAZORHELPENDLINE \

		"<H3>Contents</H3>" POSTERAZORHELPENDLINE \
		"<UL>" POSTERAZORHELPENDLINE \
			"<LI><B><A href=\"#" POSTERAZORHELPANCHORABOUT "\">About</A></B></LI>" POSTERAZORHELPENDLINE \
			"<LI><B><A href=\"#" POSTERAZORHELPANCHORMANUAL "\">Manual</A></B></LI>" POSTERAZORHELPENDLINE \
			"<UL>" POSTERAZORHELPENDLINE \
				"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP01 "\">Step 1: " POSTERAZORHELPSTEPTITLE01 "</A></LI>" POSTERAZORHELPENDLINE \
				"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP02 "\">Step 2: " POSTERAZORHELPSTEPTITLE02 "</A></LI>" POSTERAZORHELPENDLINE \
				"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP03 "\">Step 3: " POSTERAZORHELPSTEPTITLE03 "</A></LI>" POSTERAZORHELPENDLINE \
				"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP04 "\">Step 4: " POSTERAZORHELPSTEPTITLE04 "</A></LI>" POSTERAZORHELPENDLINE \
				"<LI><A href=\"#" POSTERAZORHELPANCHORMANUALSTEP05 "\">Step 5: " POSTERAZORHELPSTEPTITLE05 "</A></LI>" POSTERAZORHELPENDLINE \
			"</UL>" POSTERAZORHELPENDLINE \
			"<LI><B><A href=\"#" POSTERAZORHELPANCHORINPUTFILEFORMATS "\">Supported input image files</A></B></LI>" POSTERAZORHELPENDLINE \
			"<LI><B><A href=\"#" POSTERAZORHELPANCHORABOUTPDFOUTPUT "\">About the PDF output</A></B></LI>" POSTERAZORHELPENDLINE \
			"<LI><B><A href=\"#" POSTERAZORHELPANCHORWHYPDFOUTPUT "\">Why a PDF output?</A></B></LI>" POSTERAZORHELPENDLINE \
			"<LI><B><A href=\"#" POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES "\">Code from third parties</A></B></LI>" POSTERAZORHELPENDLINE \
		"</UL><HR>" POSTERAZORHELPENDLINE \

		"<A name=\"" POSTERAZORHELPANCHORABOUT "\"><H3>About</H3></A>" POSTERAZORHELPENDLINE \
		POSTERAZORHELPINDENTATION "The PosteRazor cuts a raster image into pieces which can be printed on a printer and be put together to a poster. As an input image, raster files of <A href=\"#" POSTERAZORHELPANCHORMANUALSTEP01 "\">various</A> image file formats are supported. Instead of directly printing the poster, the PosteRazor produces a multi page PDF files which contains the poster tiles.<br>" POSTERAZORHELPENDLINE \
		"It is an open source program which depends on <a href=\"#" POSTERAZORHELPANCHORINPUTFILEFORMATS "\">other open source projects</a>." POSTERAZORHELPENDLINE \
		"The PosteRazor is hostet on <b>posterazor.sourceforge.net</b>." POSTERAZORHELPENDLINE \

		"<A name=\"" POSTERAZORHELPANCHORMANUAL "\"><H3>Manual</H3></A>" POSTERAZORHELPENDLINE \
		POSTERAZORHELPINDENTATION "PosteRazor has its user interface organized in a \"Wizard\" fashion. All settings for the poster creation can be done in 5 Steps. The <b>Back</b> and <b>Next</b> buttons navigate through these steps.<br>" POSTERAZORHELPENDLINE \
		"The <b>?</b> Button opens a help window with an explanation of the current step. Before working for the first time with the PosteRazor, please choose your the dimension which you intend to work with in the <b>Units</b> chooser on the lower left of the dialog.<br>" POSTERAZORHELPENDLINE \
		"Every input field for a dimension, etc. can as usual be modified with the keyboard but also by clicking on it and dragging the mouse to the left and right. The different mouse buttons in-/de-crease the values in different steps.<br>" POSTERAZORHELPENDLINE \
		POSTERAZORHELPINDENTATION "All entries and choices are remembered until the next usage of the PosteRazor." POSTERAZORHELPENDLINE \

		"<A name=\"" POSTERAZORHELPANCHORMANUALSTEP01 "\"><H3>Step 1: " POSTERAZORHELPSTEPTITLE01 "</H3></A>" POSTERAZORHELPENDLINE \
		POSTERAZORHELPINDENTATION "Load an image by clicking the button with the open icon and selecting an image file, or by drag & dropping an image file on the PosteRazor. The drag & drop also works in the other steps.<br>" POSTERAZORHELPENDLINE \
		"Many <a href=\"#" POSTERAZORHELPANCHORINPUTFILEFORMATS "\">file formats and image types</a> can be loaded. After loading the image, the most important informations are listed in the <b>Image informations field</b>." POSTERAZORHELPENDLINE \

		"<A name=\"" POSTERAZORHELPANCHORMANUALSTEP02 "\"><H3>Step 2: " POSTERAZORHELPSTEPTITLE02 "</H3></A>" POSTERAZORHELPENDLINE \
		POSTERAZORHELPINDENTATION "Define the paper sheet size that you use in your printer. A standard paper sheet size can be selected from the <b>Format</b> chooser, along with the desired paper sheet <b>Orientation</b>. Alternatively, a custom paper sheet size can be define in the <b>Custom</b> tab. (Please write me an email, if you miss your standard paper size in the chooser)." POSTERAZORHELPENDLINE \
		"Paper borders are defined in the <b>Borders</b> fileds. Even if your printer does need no (or small) paper borders, some border might be needed to have enough area for gluing the final poster tiles together." POSTERAZORHELPENDLINE \

		"<A name=\"" POSTERAZORHELPANCHORMANUALSTEP03 "\"><H3>Step 3: " POSTERAZORHELPSTEPTITLE03 "</H3></A>" POSTERAZORHELPENDLINE \
		POSTERAZORHELPINDENTATION "Image tile overlapping is needed to have some tolerance for cutting off the unneded borders from one side. Additionally, like the borders from the previous step, if gives more area for gluing together the final poster tiles." POSTERAZORHELPENDLINE \
		POSTERAZORHELPINDENTATION "The <b>Overlapping position</b> defines the borders that are intended to be overlapped by the neighbour tiles. The borders on the opposite sides are intended to be cut (except on the outermost tiles)." POSTERAZORHELPENDLINE \
		
		"<A name=\"" POSTERAZORHELPANCHORMANUALSTEP04 "\"><H3>Step 4: " POSTERAZORHELPSTEPTITLE04 "</H3></A>" POSTERAZORHELPENDLINE \
		POSTERAZORHELPINDENTATION "Define the final poster size, in one of the following three modes which can be selected by the corresponding radio buttons:<br>" POSTERAZORHELPENDLINE \
		"<b>Absolute image size</b>: You want to have a specific size of your poster.<br>" POSTERAZORHELPENDLINE \
		"<b>Size in Pages</b>: you want to use whole paper sheets and specify how many of them of them you want to use.<br>" POSTERAZORHELPENDLINE \
		"<b>Image Size in percent</b>: your input image has a certain size which is defined by the number of pixels and dpi (dots per Inch) and your want to enlage the image by a certain factor.<br>" POSTERAZORHELPENDLINE \
		POSTERAZORHELPINDENTATION "The aspect ratio of width and height is always 1:1 and is automatically recalculated. In the preview area, you can see the overlapping areas which are surrounded by light red rectangles." POSTERAZORHELPENDLINE \

		"<A name=\"" POSTERAZORHELPANCHORMANUALSTEP05 "\"><H3>Step 5: " POSTERAZORHELPSTEPTITLE05 "</H3></A>" POSTERAZORHELPENDLINE \
		POSTERAZORHELPINDENTATION "Save the poster by clicking the save button and specifying a destination file name. Check or uncheck the <b>PDF application after saving</b>, if the standard PDF handling application that is set in your operating system should be automatically started after the PDF file is saved." POSTERAZORHELPENDLINE \

		"<A name=\"" POSTERAZORHELPANCHORINPUTFILEFORMATS "\"><H3>Supported input image files</H3></A>" POSTERAZORHELPENDLINE \
		POSTERAZORHELPINDENTATION "Most of the raster image formats which are supported by FreeImage are also supported by the PosteRazor:<br>" POSTERAZORHELPENDLINE \
		"<b>BMP, DDS files, Dr. Halo, GIF, ICO, IFF, JBIG, JNG, JPEG/JIF, KOALA, LBM, Kodak PhotoCD, MNG, PCX, PBM, PGM, PNG, PPM, PhotoShop PSD, Sun RAS, TARGA, TIFF, WBMP, XBM, XPM.<br></b>" POSTERAZORHELPENDLINE \
		"PosteRazor distinguishes and handles monochrome, greyscale, 4-bit palette, 8-bit palette, 24 bit RGB, and CMYK (only from TIF) images. RGB images with an alpha channel are automatically composed onto a white background." POSTERAZORHELPENDLINE \

		"<A name=\"" POSTERAZORHELPANCHORWHYPDFOUTPUT "\"><H3>Why a PDF output</H3></A>" POSTERAZORHELPENDLINE \
		POSTERAZORHELPINDENTATION "Why a PDF output and not direct printing? First of all the developer of this program does not know (yet) how to \"send images to the printer\", on the different operating systems, which PosteRazor is aimed for. Also, PDF makes sense, if a poster is razored at home with all the needed time and the day after it is printed on the color laser printer in the office (after everyone else went home)." POSTERAZORHELPENDLINE \
		POSTERAZORHELPINDENTATION "Why a PDF and not other raster formats as output? PDF gives the possibility to embed the whole image and virtually cut it, and not only between pixels but also with pixel fractions. Aditionally, it seems more practicable to print a multi page PDF file instead of multiple image files." POSTERAZORHELPENDLINE \
		
		"<A name=\"" POSTERAZORHELPANCHORCODEFROMTHIRDPARTIES "\"><H3>Code from third parties</H3></A>" POSTERAZORHELPENDLINE \
		POSTERAZORHELPINDENTATION "<b>FLTK</b> was used for the user interface. It is a small (by size), fast, fun&easy to learn and very portable UI Toolkit. <b>www.fltk.org</b>" POSTERAZORHELPENDLINE \
		POSTERAZORHELPINDENTATION "<b>FreeImage</b> was used for the image loading and handling. It makes image loading and handling really a no-brainer and is portable to the platforms, where the PosteRazor runs. <b>freeimage.sourceforge.net</b>" POSTERAZORHELPENDLINE \
		POSTERAZORHELPINDENTATION "<b>Fl_Native_File_Chooser</b> was used for the file open and save dialog in the native system look and feel. <b>seriss.com/people/erco/fltk/Fl_Native_File_Chooser/</b> and <b>http://homepages.dordt.edu/~nthnlvnd/soft/Fl_Native_File_Chooser.html</b>" POSTERAZORHELPENDLINE \
		
	"</BODY>" POSTERAZORHELPENDLINE \
"</HTML>";

#endif

//		POSTERAZORHELPINDENTATION "" POSTERAZORHELPENDLINE \
