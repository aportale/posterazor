Import("tools.avsi")

global gEnglishLanguage = false
global gScreenCast3D = true
global gAudioClip = 0
global gAudioNoiseStart = 0
global gAudioNoiseEnd = 0
global gClipHeight = 480

global gOldStyleGradient = ImageReader("oldstylegradient.png", 0, 0, 25, pixel_type="rgb32")
global gOldStyleGradientAlpha = gOldStyleGradient.showalpha()

function setupScreencastAudioGlobals()
{
    global gAudioClip = WAVSource(gEnglishLanguage ? "en_screencastaudio.wav" : "de_screencastaudio.wav")
    global gAudioNoiseStart = (gEnglishLanguage ? 2017804 : 2299401) / 44100.0
    global gAudioNoiseEnd = (gEnglishLanguage ? 2029098 : 2311009) / 44100.0
}

function introClip()
{
    introClip = gEnglishLanguage ?
        \  AviSource("en_intro.avi")
        \ .DelayAudio(-0.65)
        \ .trim(36, 551)
        \ :
        \  AviSource("de_intro.avi")
        \ .DelayAudio(-0.62)
        \ .trim(125, 600)
    introClip = introClip
        \ .ConvertToYUY2()
        \ .FieldDeinterlace()
        \ .Crop(10, 7, -10, -7)
        \ .TemporalSoften(4,4,8)
        \ .LanczosResize(640, 480)
        \ .Crop(0, 20, 0, -100)
        \ .AddBorders(0, (gClipHeight - 360) / 2, 0, (gClipHeight - 360) / 2, $000000)
    return AudioDub(introClip, GetChannel(introClip, 1).SSRC(44100, false).ConvertAudioTo16bit())
}

function audioDownloadPosteRazor()
{
    setupScreencastAudioGlobals()

    # 01
    #  We visit the PosteRazor web site
      en_a01 = audioNoise(3) + audioClip(0.430, 2.912, 3.5)
    #  Wir besuchen die Internetseite des PosteRazors
      de_a01 = audioNoise(3) + audioClip(0.520, 3.705, 3)

    # 02
    #  There, we click on the "Download" link and choose the version that is suited for our Operating System
      en_a02 = audioClip(3.124, 8.803, 3)
    #  Dort klicken wir auf den link "Herunterladen" und wählen die passende Version für unser Betriebssystem aus
      de_a02 = audioClip(3.789, 10.215, 1)

    return gEnglishLanguage ?
        \ en_a01 + en_a02
        \ :
        \ de_a01 + de_a02
}

function videoDownloadPosteRazor_2D()
{
    en_ScreencastStart = 0
    en_01FrameStretchFrame = en_ScreencastStart + 1
    en_01FrameStretchLength = 20
    en_02FrameStretchFrame = 370
    en_02FrameStretchLength = 22
    en_ScreencastEnd = en_02FrameStretchFrame

    de_ScreencastStart = 50
    de_LoadPageFrameRemovalStart = 240
    de_LoadPageRemovalEnd = 296
    de_ScreencastEnd = 519

    videoSource = AviSource(gEnglishLanguage ? "en_download.avi" : "de_download.avi") #.ShowFrameNumber
    return gEnglishLanguage ?
        \   videoSource.trim(en_ScreencastStart, en_01FrameStretchFrame)
        \ + videoSource.trim(en_01FrameStretchFrame, en_01FrameStretchFrame).loop(en_01FrameStretchLength)
        \ + videoSource.trim(en_01FrameStretchFrame, en_02FrameStretchFrame)
        \ + videoSource.trim(en_02FrameStretchFrame, en_02FrameStretchFrame).loop(en_02FrameStretchLength)
        \ + videoSource.trim(en_02FrameStretchFrame, en_ScreencastEnd)
        \ :
        \   videoSource.trim(de_ScreencastStart, de_LoadPageFrameRemovalStart)
        \ + videoSource.trim(de_LoadPageRemovalEnd, de_ScreencastEnd)
}

function ImageSourceFiles3D()
{
    return gEnglishLanguage ? "en_screencast_3d/%04d.png" : "de_screencast_3d/%04d.png"
}

function videoDownloadPosteRazor_3D()
{
    return
        \  ImageSource(ImageSourceFiles3D() , start = 1, end = 414, fps = 25)
}

function audioUsePosteRazor()
{
    setupScreencastAudioGlobals()

    # 03
    #  After the installation we launch the Program
      en_a03 = audioClip(12.300, 15.374, 0)
    #  Nach der Installation starten wir das Programm
      de_a03 = audioClip(10.194, 13.042, 0)

    # 04
    #  We load the image which we want to enlarge...
      en_a04 = audioClip(15.623, 18.367, 1)
    #  Wir laden das Bild, das wir vergrössern wollen...
      de_a04 = audioClip(13.308, 15.971, 1)

    # 05
    #  ...and proceed
      en_a05 = audioClip(18.813, 19.647, 1)
    #  ...und gehen weiter
      de_a05 = audioClip(16.000, 17.300, 1)

    # 06
    #  Since our printer uses A4 sheets, we can leave everything in step two as it is.
      en_a06 = audioClip(20.050, 25.575, 1)
    #  Da unser Drucker A4-Seiten bedruckt, können wir im zweiten Schritt alles so lassen, wie es ist.
      de_a06 = audioClip(17.669, 23.060, 1)

    # 07
    #  In step three, we increase the overlapping of the poster tiles to 2 centimeters, in order to assemble the poster more easily later on
      en_a07 = audioClip(26.043, 35.585, 2)
    #  Im Schritt drei vergrössern wir die Überlappung der Posterteile auf 2 Zentimeter, um später das Poster besser zusammenkleben zu können
      de_a07 = audioClip(23.288, 32.576, 2)

    # 08
    #  The final poster, currently has a width of two A4 sheets. However, we want to give it a width of 32 centimeters.
      en_a08 = audioClip(37.771, 45.566, 6)
    #  Das finale Poster hat gerade eine breite von zwei DIN A4-Seiten. Wir möchten aber eine Breite von 32 Zentimetern haben.
      de_a08 = audioClip(32.887, 40.801, 6)

    # 09
    #  The last step saves the poster.
      en_a09 = audioClip(48.047, 50.579, 3)
    #  Der letze Schritt speichert das Poster.
      de_a09 = audioClip(41.471, 44.011, 3)

    # 10
    #  The PDF document is opened automatically...
      en_a10 = audioClip(51.062, 53.982, 0.5)
    #  Die PDF-datei wird automatisch geöffnet...
      de_a10 = audioClip(44.274, 47.245, 0)

    # 11
    #  ...it contains all the four pages...
      en_a11 = audioClip(57.706, 59.894, 0.5)
    #  ...Sie enthält alle vier DIN A4-Seiten,...
      de_a11 = audioClip(47.293, 50.126, 0)

    # 12
    #  ...which we now print out.
      en_a12 = audioClip(61.716, 63.092, 0) + audioNoise(4)
    #  ...die wir nun ausdrucken.
      de_a12 = audioClip(50.126, 51.650, 0) + audioNoise(4)

    return gEnglishLanguage ?
        \ en_a03 + en_a04 + en_a05 + en_a06 + en_a07 + en_a08 + en_a09 + en_a10 + en_a11 + en_a12
        \ :
        \ de_a03 + de_a04 + de_a05 + de_a06 + de_a07 + de_a08 + de_a09 + de_a10 + de_a11 + de_a12
}

function videoUsePosteRazor_2D()
{
    en_ScreencastStart = 130
    en_03FrameStretchFrame = en_ScreencastStart + 1
    en_03FrameStretchLength = 28
    en_06FrameStretchFrame = 340
    en_06FrameStretchLength = 109
    en_07FrameStretchFrame = 343
    en_07FrameStretchLength = 101
    en_08FrameStretchFrame = 511
    en_08FrameStretchLength = 100
    en_09aFrameStretchFrame = 707
    en_09aFrameStretchLength = 37
    en_09bFrameStretchFrame = 720
    en_09bFrameStretchLength = 41
    en_ScreencastEnd = 1085

    de_ScreencastStart = 28
    de_03FrameStretchFrame = 29
    de_03FrameStretchLength = 30
    de_06FrameStretchFrame = 210
    de_06FrameStretchLength = 80
    de_07FrameStretchFrame = 275
    de_07FrameStretchLength = 70
    de_08FrameStretchFrame = 487
    de_08FrameStretchLength = 40
    de_12FrameStretchFrame = 1190
    de_12FrameStretchLength = 60
    de_ScreencastEnd = de_08FrameStretchFrame + de_08FrameStretchLength

    videoSource = AviSource(gEnglishLanguage ? "en_posterazor.avi" : "de_posterazor.avi") #.ShowFrameNumber
    return gEnglishLanguage ?
        \   videoSource.trim(en_ScreencastStart,     en_03FrameStretchFrame)
        \ + videoSource.trim(en_03FrameStretchFrame, en_03FrameStretchFrame).loop(en_03FrameStretchLength)
        \ + videoSource.trim(en_03FrameStretchFrame, en_06FrameStretchFrame)
        \ + videoSource.trim(en_06FrameStretchFrame, en_06FrameStretchFrame).loop(en_06FrameStretchLength)
        \ + videoSource.trim(en_06FrameStretchFrame, en_07FrameStretchFrame)
        \ + videoSource.trim(en_07FrameStretchFrame, en_07FrameStretchFrame).loop(en_07FrameStretchLength)
        \ + videoSource.trim(en_07FrameStretchFrame, en_08FrameStretchFrame)
        \ + videoSource.trim(en_08FrameStretchFrame, en_08FrameStretchFrame).loop(en_08FrameStretchLength)
        \ + videoSource.trim(en_08FrameStretchFrame, en_09aFrameStretchFrame)
        \ + videoSource.trim(en_09aFrameStretchFrame, en_09aFrameStretchFrame).loop(en_09aFrameStretchLength)
        \ + videoSource.trim(en_09aFrameStretchFrame, en_09bFrameStretchFrame)
        \ + videoSource.trim(en_09bFrameStretchFrame, en_09bFrameStretchFrame).loop(en_09bFrameStretchLength)
        \ + videoSource.trim(en_09bFrameStretchFrame, en_ScreencastEnd)
        \ :
        \   videoSource.trim(de_ScreencastStart,     de_03FrameStretchFrame)
        \ + videoSource.trim(de_03FrameStretchFrame, de_03FrameStretchFrame).loop(de_03FrameStretchLength)
        \ + videoSource.trim(de_03FrameStretchFrame, de_06FrameStretchFrame)
        \ + videoSource.trim(de_06FrameStretchFrame, de_06FrameStretchFrame).loop(de_06FrameStretchLength)
        \ + videoSource.trim(de_06FrameStretchFrame, de_07FrameStretchFrame)
        \ + videoSource.trim(de_07FrameStretchFrame, de_07FrameStretchFrame).loop(de_07FrameStretchLength)
        \ + videoSource.trim(de_07FrameStretchFrame, de_08FrameStretchFrame)
        \ + videoSource.trim(de_08FrameStretchFrame, de_08FrameStretchFrame).loop(de_08FrameStretchLength)
        \ + videoSource.trim(de_08FrameStretchFrame, de_12FrameStretchFrame)
        \ + videoSource.trim(de_12FrameStretchFrame, de_12FrameStretchFrame).loop(de_12FrameStretchLength)
}

function videoUsePosteRazor_3D()
{
    return
        \  ImageSource(ImageSourceFiles3D(), start = 417, end = 1792, fps = 25)
}

function setupAssemblingAudioGlobals()
{
    global gAudioClip = WAVSource(gEnglishLanguage ? "en_assemblingaudio.wav" : "de_assemblingaudio.wav")
    global gAudioNoiseStart = (gEnglishLanguage ? 2017804 : 2299401) / 44100.0
    global gAudioNoiseEnd = (gEnglishLanguage ? 2029098 : 2311009) / 44100.0
}

function audioAssemblingPoster()
{
    setupAssemblingAudioGlobals()

    # 01
    #  Here are the four printed sheets, a pair of scissors, a glue stick and an adhesive tape.
      en_a01 = audioClip(12.300, 15.374, 0)
    #  Hier sind vier ausgedruckten Seiten, eine Schere, ein Klebestift und ein Klebeband.
      de_a01 = audioClip(10.194, 13.042, 0)

    # 02
    #  First we cut off the top and left borders which will be glued to another page.
      en_a02 = audioClip(15.623, 18.367, 1)
    #  Zuerst scheiden wir die obene und lenken Ränder ab, die an eine andere Seite geklebt werden.
      de_a02 = audioClip(13.308, 15.971, 1)

    # 03
    #  The cutting does not need very precise since we have 2 centimeters of overlapping.
      en_a03 = audioClip(15.623, 18.367, 1)
    #  Das Schneiden muss nicht allzu präzise sein, da wir 2 Zentimeter Überlappung haben.
      de_a03 = audioClip(13.308, 15.971, 1)

    # 04
    #  Then we apply glue on an untrimmed border.
      en_a04 = audioClip(18.813, 19.647, 1)
    #  Dann tragen wir Klebe auf einen unbeschittenen Rand auf.
      de_a04 = audioClip(16.000, 17.300, 1)

    # 05
    #  Now we stick the neighboring page on it. Thanks to the overlapping, we will have no white gaps.
      en_a05 = audioClip(20.050, 25.575, 1)
    #  Den angrenzenden Bogen kleben wir nun an. Durch die Überlappung entstehen keine weissen Lücken.
      de_a05 = audioClip(17.669, 23.060, 1)

    # 06
    #  Afterwards, we take the adhesive tape and reinforce the middle and the sides.
      en_a06 = audioClip(26.043, 35.585, 2)
    #  Danach nehmen wir das Klebeband und stabilisieren die Mitte und die Seiten.
      de_a06 = audioClip(23.288, 32.576, 2)

    # 07
    #  Also the corners can be reinforced to prevent them from easily ripping.
      en_a07 = audioClip(37.771, 45.566, 6)
    #  Auch die Ecken können verstärkt werden, damit sie nicht leicht einreissen.
      de_a07 = audioClip(32.887, 40.801, 6)

    # 08
    #  It is done! Thanks for watching and have fun making posters.
      en_a08 = audioClip(48.047, 50.579, 3)
    #  Es ist vollbracht! Danke fürs Zuschauen und viel Spass beim Poster machen.
      de_a08 = audioClip(41.471, 44.011, 3)


    return gEnglishLanguage ?
        \ en_a01 + en_a02 + en_a03 + en_a04 + en_a05 + en_a06 + en_a07
        \ :
        \ de_a01 + de_a02 + de_a03 + de_a04 + de_a05 + de_a06 + de_a07
}

function videoAssemblingPoster()
{
    aClip =
        \  AviSource("assembling.avi")
        \ .ConvertToYUY2()
        \ .FieldDeinterlace()
        \ .Crop(10, 7, -10, -7)
        \ .TemporalSoften(4,4,8)
        \ .LanczosResize(640, 480)
    dissolveLength = 6
    sheetOnTable = Dissolve(
        \   aClip.frame(   88), aClip.frame(  116), aClip.frame(  159), aClip.frame(  187)
        \ , aClip.frame(  225)
        \ , dissolveLength)
    toolsOnTable = Dissolve(
        \   aClip.frame(  319), aClip.frame(  360), aClip.frame(  415), aClip.frame(  434)
        \ , dissolveLength)
    bordersToCut = Dissolve(
        \   ImageSource("borderstocut1.png", end=34, fps=25).ConvertToYUY2()
        \ , ImageSource("borderstocut2.png", end=34, fps=25).ConvertToYUY2()
        \ , ImageSource("borderstocut3.png", end=34, fps=25).ConvertToYUY2()
        \ , ImageSource("borderstocut4.png", end=34, fps=25).ConvertToYUY2()
        \ , dissolveLength)
    cutBorders = Dissolve(
        \   aClip.frame(  862), aClip.frame(  906), aClip.frame(  941), aClip.frame( 1044)
        \ , aClip.frame( 1093), aClip.frame( 1125), aClip.frame( 1281), aClip.frame( 1494)
        \ , aClip.frame( 1570)
        \ , dissolveLength)
    overlapping = Dissolve(
        \   aClip.frame( 3056), aClip.frame( 3069), aClip.frame( 3101), aClip.frame( 3540)
        \ , aClip.frame( 3546), aClip.frame( 3636), aClip.frame( 3843), aClip.frame( 4171)
        \ , dissolveLength)
    glueing = Dissolve(
        \   aClip.frame( 2149), aClip.frame( 2212), aClip.frame( 2234), aClip.frame( 2260)
        \ , overlapping
        \ , aClip.frame( 5951), aClip.frame( 6001), aClip.frame( 6106), aClip.frame( 6177)
        \ , aClip.frame( 6714), aClip.frame( 7661), aClip.frame( 7916)
        \ , dissolveLength)
    reinforcingSides = Dissolve(
        \   aClip.frame( 8468), aClip.frame( 8555), aClip.frame( 8943), aClip.frame( 9472)
        \ , aClip.frame( 9556), aClip.frame( 9830)
        \ , dissolveLength)
    reinforcingCorners = Dissolve(
        \   aClip.frame(11203), aClip.frame(11393), aClip.frame(11424), aClip.frame(11450)
        \ , aClip.frame(11490), aClip.frame(11508), aClip.frame(11570)
        \ , dissolveLength)
    voila = Dissolve(
        \   aClip.frame(12341), aClip.frame(12338), aClip.frame(12416), aClip.frame(12447)
        \ , aClip.frame(12447), aClip.frame(12447)
        \ , dissolveLength)
    return Dissolve(
        \   sheetOnTable, toolsOnTable, bordersToCut, cutBorders, glueing, reinforcingSides, reinforcingCorners, voila
        \ , dissolveLength)
}

function completeClip()
{
    downloadPosteRazor =
        \ AudioDub(gScreenCast3D ? videoDownloadPosteRazor_3D() :videoDownloadPosteRazor_2D(), audioDownloadPosteRazor())
        \ .ConvertToYUY2()
    usePosteRazor =
        \ AudioDub(gScreenCast3D ? videoUsePosteRazor_3D() : videoUsePosteRazor_2D(), audioUsePosteRazor())
        \ .ConvertToYUY2()
    return Dissolve(
        \   textClip(downloadPosterazor, gEnglishLanguage ? "Make Your Own Poster!" : "Mach' Dein Eigenes Poster!")
        \ , introClip()
        \ , textClip(downloadPosterazor, gEnglishLanguage ? "Downloading PosteRazor" : "PosteRazor herunterladen")
        \ , downloadPosteRazor
        \ , textClip(downloadPosterazor, gEnglishLanguage ? "Using PosteRazor" : "PosteRazors Benutzung")
        \ , usePosteRazor
        \ , textClip(downloadPosterazor, gEnglishLanguage ? "Assembling the poster" : "Das Poster zusammenfügen")
        \ , AudioDub(videoAssemblingPoster(), audioDownloadPosteRazor())
        \ , textClip(downloadPosterazor, "http://posterazor.sourceforge.net/")
        \ , 6)
        \ .Overlay(gOldStyleGradient, mask = gOldStyleGradientAlpha)
}

completeClip()