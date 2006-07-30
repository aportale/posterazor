convert screenshot_english_help_settings.png -filter Hermite -resize 120x120 -colors 128 +dither screenshotthumb_help_settings.png
convert screenshot_english_step01.png -filter Hermite -resize 120x120 -colors 128 +dither screenshotthumb_step01.png
convert screenshot_english_step02.png -filter Hermite -resize 120x120 -colors 128 +dither screenshotthumb_step02.png
convert screenshot_english_step03.png -filter Hermite -resize 120x120 -colors 128 +dither screenshotthumb_step03.png
convert screenshot_english_step04.png -filter Hermite -resize 120x120 -colors 128 +dither screenshotthumb_step04.png
convert screenshot_english_step05.png -filter Hermite -resize 120x120 -colors 128 +dither screenshotthumb_step05.png

for %%i in (screenshotthumb_*.png) do pngout %%i