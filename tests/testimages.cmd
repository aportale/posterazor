convert -size 3x1 xc:white -depth 16 ^
    -fill "#df1234" -draw "point 0,0" ^
    -fill "#12df34" -draw "point 1,0" ^
    -fill "#1234df" -draw "point 2,0" ^
    rgb_48bpp.png

convert -size 1x1 xc:white -depth 16 ^
    -fill "#AABBCCDDEEFF" -draw "point 0,0" ^
    rgb_48bpp_failing.png

convert rgb_48bpp.png -depth 8 rgb_24bpp.png
convert rgb_48bpp.png -colors 255 -depth 8 palette_8bpp.png

convert -size 2x1  xc:none -depth 16 -colorspace Gray ^
    -fill "#012301230123" -draw "point 0,0" ^
    -fill "#ABCDABCDABCD" -draw "point 1,0" ^
    grayscale_16bpp.png

convert -size 3x2 xc:none -depth 16 ^
    -fill "#abcd00000000dcba" -draw "point 0,0" ^
    -fill "#0000abcd0000dcba" -draw "point 1,0" ^
    -fill "#00000000abcddcba" -draw "point 2,0" ^
    -fill "#1234000000004321" -draw "point 0,1" ^
    -fill "#0000123400004321" -draw "point 1,1" ^
    -fill "#0000000012344321" -draw "point 2,1" ^
    rgba_64bpp.png

convert -size 3x2 xc:none -depth 8 ^
    -fill "#ab0000ba" -draw "point 0,0" ^
    -fill "#00ab00ba" -draw "point 1,0" ^
    -fill "#0000abba" -draw "point 2,0" ^
    -fill "#12000021" -draw "point 0,1" ^
    -fill "#00120021" -draw "point 1,1" ^
    -fill "#00001221" -draw "point 2,1" ^
    rgba_32bpp.png

convert -size 4x1 xc:none -colorspace CMYK ^
    -fill cmyk(100,0,0,0) -draw "point 0,0" ^
    -fill cmyk(0,100,0,0) -draw "point 1,0" ^
    -fill cmyk(0,0,100,0) -draw "point 2,0" ^
    -fill cmyk(0,0,0,100) -draw "point 3,0" ^
    cmyk_32bpp.tif
