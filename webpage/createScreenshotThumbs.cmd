convert screenshot_english_help_settings.png -filter Hermite -resize 130x130 +dither -colors 128 screenshot_help_settings_thumb.png
convert screenshot_english_step01.png        -filter Hermite -resize 130x130 +dither -colors 128 screenshot_step01_thumb.png
convert screenshot_english_step02.png        -filter Hermite -resize 130x130 +dither -colors 128 screenshot_step02_thumb.png
convert screenshot_english_step03.png        -filter Hermite -resize 130x130 +dither -colors 128 screenshot_step03_thumb.png
convert screenshot_english_step04.png        -filter Hermite -resize 130x130 +dither -colors 128 screenshot_step04_thumb.png
convert screenshot_english_step05.png        -filter Hermite -resize 130x130 +dither -colors 128 screenshot_step05_thumb.png

for %%i in (screenshot_*.png) do pngout %%i