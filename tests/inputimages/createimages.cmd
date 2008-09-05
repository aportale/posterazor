SET SOURCE=..\..\webpage\images\monalisa.png
SET EXTENSION=tif
SET PARAMETERS=-filter Gaussian -resize 250

for %%i in (png tif gif bmp    ) do convert %SOURCE% %PARAMETERS% -monochrome monochrome.%%i
for %%i in (png tif gif bmp    ) do convert %SOURCE% %PARAMETERS% -colors 2 palette1bpp.%%i
for %%i in (png tif            ) do convert %SOURCE% %PARAMETERS% -colors 4 palette2bpp.%%i
for %%i in (png tif gif bmp    ) do convert %SOURCE% %PARAMETERS% -colors 16 palette4bpp.%%i
for %%i in (png tif gif bmp    ) do convert %SOURCE% %PARAMETERS% -colors 256 palette8bpp.%%i
for %%i in (png tif     bmp jpg) do convert %SOURCE% %PARAMETERS% -depth 8 rgb24bpp.%%i
for %%i in (png tif            ) do convert %SOURCE% %PARAMETERS% -depth 16 rgb48bpp.%%i
for %%i in (png tif     bmp    ) do convert %SOURCE% %PARAMETERS% -depth 8 -matte -fill none -fuzz 20%% -draw "matte 5,5 floodfill" rgba32bpp.%%i
for %%i in (png tif            ) do convert %SOURCE% %PARAMETERS% -depth 16 -matte -fill none -fuzz 20%% -draw "matte 5,5 floodfill" rgba64bpp.%%i
for %%i in (png tif gif bmp jpg) do convert %SOURCE% %PARAMETERS% -depth 8 -colorspace Gray grayscale8bpp.%%i
for %%i in (png tif            ) do convert %SOURCE% %PARAMETERS% -depth 16 -colorspace Gray grayscale16bpp.%%i
for %%i in (    tif         jpg) do convert %SOURCE% %PARAMETERS% -depth 8 -profile sRGB.icc -profile CMYK.icc cmyk32bpp.%%i
for %%i in (    tif            ) do convert %SOURCE% %PARAMETERS% -depth 16 -profile sRGB.icc -profile CMYK.icc cmyk64bpp.%%i
