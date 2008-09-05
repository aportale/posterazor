SET SOURCE=..\..\webpage\images\monalisa.png
SET EXTENSION=tif
SET PARAMETERS=-filter Gaussian -resize 250

convert %SOURCE% %PARAMETERS% -monochrome monochrome.png
convert %SOURCE% %PARAMETERS% -colors 2 palette1bpp.png
convert %SOURCE% %PARAMETERS% -colors 4 palette2bpp.png
convert %SOURCE% %PARAMETERS% -colors 16 palette4bpp.png
convert %SOURCE% %PARAMETERS% -colors 256 palette8bpp.png
convert %SOURCE% %PARAMETERS% -depth 8 rgb24bpp.png
convert %SOURCE% %PARAMETERS% -depth 16 rgb48bpp.png
convert %SOURCE% %PARAMETERS% -depth 8 -matte -fill none -fuzz 50% -draw "matte 5,5 floodfill" rgba32bpp.png
convert %SOURCE% %PARAMETERS% -depth 16 -matte -fill none -fuzz 50% -draw "matte 5,5 floodfill" rgba64bpp.png
convert %SOURCE% %PARAMETERS% -depth 8 -colorspace Gray grayscale8bpp.tif
convert %SOURCE% %PARAMETERS% -depth 16 -colorspace Gray grayscale16bpp.tif
convert %SOURCE% %PARAMETERS% -depth 8 -profile sRGB.icc -profile CMYK.icc cmyk32bpp.tif
convert %SOURCE% %PARAMETERS% -depth 16 -profile sRGB.icc -profile CMYK.icc cmyk64bpp.tif
convert %SOURCE% %PARAMETERS% -colorspace Gray grayscale.jpg
convert %SOURCE% %PARAMETERS% rgb.jpg
convert %SOURCE% %PARAMETERS% -profile sRGB.icc -profile CMYK.icc cmyk.jpg
