convert -size 3x1 xc:white -depth 16 ^
    -fill "#f00" -draw "point 0,0" ^
    -fill "#0f0" -draw "point 1,0" ^
    -fill "#00f" -draw "point 2,0" ^
    rgb_48bpp.png

convert -size 1x1 xc:white -depth 16 ^
    -fill "#AABBCCDDEEFF" -draw "point 0,0" ^
    rgb_48bpp_failing.png

convert rgb_48bpp.png -depth 8 rgb_24bpp.png
convert rgb_48bpp.png -colors 255 -depth 8 palette_8bpp.png

convert -size 3x2 xc:none -depth 16 ^
    -fill "#ff0000ff" -draw "point 0,0" ^
    -fill "#00ff00ff" -draw "point 1,0" ^
    -fill "#0000ffff" -draw "point 2,0" ^
    -fill "#ff000080" -draw "point 0,1" ^
    -fill "#00ff0080" -draw "point 1,1" ^
    -fill "#0000ff80" -draw "point 2,1" ^
    rgba_64bpp.png

convert rgba_64bpp.png -depth 8 rgba_32bpp.png

convert -size 4x1 xc:none -colorspace CMYK ^
    -fill cmyk(100,0,0,0) -draw "point 0,0" ^
    -fill cmyk(0,100,0,0) -draw "point 1,0" ^
    -fill cmyk(0,0,100,0) -draw "point 2,0" ^
    -fill cmyk(0,0,0,100) -draw "point 3,0" ^
    cmyk_32bpp.tif
