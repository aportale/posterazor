SET SOURCE=..\..\webpage\images\monalisa.png
SET EXTENSION=tif
SET PARAMETERS=-resize 64x64

for %%i in (png tif gif bmp    ) do convert %SOURCE% %PARAMETERS% -monochrome monochrome_1bpp.%%i
for %%i in (png tif gif bmp    ) do convert %SOURCE% %PARAMETERS% -colors 2 palette_1bpp.%%i
for %%i in (png tif            ) do convert %SOURCE% %PARAMETERS% -colors 4 palette_2bpp.%%i
for %%i in (png tif gif bmp    ) do convert %SOURCE% %PARAMETERS% -colors 16 palette_4bpp.%%i
for %%i in (png tif gif bmp    ) do convert %SOURCE% %PARAMETERS% -colors 256 palette_8bpp.%%i
for %%i in (png tif     bmp jpg) do convert %SOURCE% %PARAMETERS% -depth 8 rgb_24bpp.%%i
for %%i in (png tif            ) do convert %SOURCE% %PARAMETERS% -depth 16 rgb_48bpp.%%i
for %%i in (png tif     bmp    ) do convert %SOURCE% %PARAMETERS% -depth 8 -matte -fill none -fuzz 20%% -draw "matte 5,5 floodfill" rgba_32bpp.%%i
for %%i in (png tif            ) do convert %SOURCE% %PARAMETERS% -depth 16 -matte -fill none -fuzz 20%% -draw "matte 5,5 floodfill" rgba_64bpp.%%i
for %%i in (png tif gif bmp jpg) do convert %SOURCE% %PARAMETERS% -depth 8 -colorspace Gray grayscale_8bpp.%%i
for %%i in (png tif            ) do convert %SOURCE% %PARAMETERS% -depth 16 -colorspace Gray grayscale_16bpp.%%i
for %%i in (    tif         jpg) do convert %SOURCE% %PARAMETERS% -depth 8 -profile sRGB.icc -profile CMYK.icc -strip cmyk_32bpp.%%i
for %%i in (    tif            ) do convert %SOURCE% %PARAMETERS% -depth 16 -profile sRGB.icc -profile CMYK.icc -strip cmyk_64bpp.%%i
