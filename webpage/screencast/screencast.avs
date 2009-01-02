Import("tools.avsi")

global englishlanguage = true
global gAudioClip = WAVSource(englishlanguage ? "de_audio_uncut.wav" : "de_audio_uncut.wav")
global gAudioNoiseStart = englishlanguage ? (2299401 / 44100.0) : (2299401 / 44100.0)
global gAudioNoiseEnd   = englishlanguage ? (2311009 / 44100.0) : (2311009 / 44100.0)

# 01
#  We visit the PosteRazor web site
  en_a01 = audioNoise(3) + audioClip(0.52, 3.705, 3)
#  Wir besuchen die Internetseite des PosteRazors
  de_a01 = audioNoise(3) + audioClip(0.52, 3.705, 3)

# 02
#  There, we click on the "Download" link and choose the version that is suited for our Operating System
  en_a02 = audioClip(3.789, 10.215, 1)
#  Dort klicken wir auf den link "Herunterladen" und wählen die passende Version für unser Betriebssystem aus
  de_a02 = audioClip(3.789, 10.215, 1)

downloadPosterazorAudio = englishlanguage ?
    \ en_a01 + en_a02
    \ :
    \ de_a01 + de_a02

en_downloadScreencastStart = 17
en_downloadLoadPageFrameRemovalStart = 240
en_downloadLoadPageRemovalEnd = 296
en_downloadScreencastEnd = 519

de_downloadScreencastStart = 50
de_downloadLoadPageFrameRemovalStart = 240
de_downloadLoadPageRemovalEnd = 296
de_downloadScreencastEnd = 519

downloadPosteRazorVideoSource = AviSource(englishlanguage ? "en_download.avi" : "de_download.avi")
downloadPosterazorVideo = englishlanguage ?
    \   downloadPosteRazorVideoSource.trim(en_downloadScreencastStart, en_downloadLoadPageFrameRemovalStart)
    \ + downloadPosteRazorVideoSource.trim(en_downloadLoadPageRemovalEnd, en_downloadScreencastEnd)
    \ :
    \   downloadPosteRazorVideoSource.trim(de_downloadScreencastStart, de_downloadLoadPageFrameRemovalStart)
    \ + downloadPosteRazorVideoSource.trim(de_downloadLoadPageRemovalEnd, de_downloadScreencastEnd)

downloadPosterazor = AudioDub(downloadPosterazorVideo, downloadPosterazorAudio)

# 03
#  After the installation we launch the Program
  en_a03 = audioClip(10.194, 13.042, 0)
#  Nach der Installation starten wir das Programm
  de_a03 = audioClip(10.194, 13.042, 0)

# 04
#  We load the image which we want to enlarge...
  en_a04 = audioClip(13.308, 15.971, 1)
#  Wir laden das Bild, das wir vergrössern wollen...
  de_a04 = audioClip(13.308, 15.971, 1)

# 05
#  ...and proceed
  en_a05 = audioClip(16.000, 17.300, 1)
#  ...und gehen weiter
  de_a05 = audioClip(16.000, 17.300, 1)

# 06
#  Since our printer uses A4 sheets, we can leave everything in step two as it is.
  en_a06 = audioClip(17.669, 23.060, 1)
#  Da unser Drucker A4-Seiten bedruckt, können wir im zweiten Schritt alles so lassen, wie es ist.
  de_a06 = audioClip(17.669, 23.060, 1)

# 07
#  In step three, we increase the overlapping of the poster tiles to 2 centimeters, in order to assemble the poster more easily later on
  en_a07 = audioClip(23.288, 32.576, 2)
#  Im Schritt drei vergrössern wir die Überlappung der Posterteile auf 2 Zentimeter, um später das Poster besser zusammenkleben zu können
  de_a07 = audioClip(23.288, 32.576, 2)

# 08
#  The final poster, currently has a width of two A4 sheets. However, we want to give it a width of 32 centimeters.
  en_a08 = audioClip(32.887, 40.801, 6)
#  Das finale Poster hat gerade eine breite von zwei DIN A4-Seiten. Wir möchten aber eine Breite von 32 Zentimetern haben.
  de_a08 = audioClip(32.887, 40.801, 6)

# 09
#  The last step saves the poster.
  en_a09 = audioClip(41.471, 44.011, 3)
#  Der letze Schritt speichert das Poster.
  de_a09 = audioClip(41.471, 44.011, 3)

# 10
#  The PDF document is opened automatically...
  en_a10 = audioClip(44.274, 47.245, 0)
#  Die PDF-datei wird automatisch geöffnet...
  de_a10 = audioClip(44.274, 47.245, 0)

# 11
#  ...it contains all the four pages...
  en_a11 = audioClip(47.293, 50.126, 0)
#  ...Sie enthält alle vier DIN A4-Seiten,...
  de_a11 = audioClip(47.293, 50.126, 0)

# 12
#  ...which we now print out.
  en_a12 = audioClip(50.126, 51.650, 0) + audioNoise(4)
#  ...die wir nun ausdrucken.
  de_a12 = audioClip(50.126, 51.650, 0) + audioNoise(4)

usePosteRazorAudio = englishlanguage ?
    \ en_a03 + en_a04 + en_a05 + en_a06 + en_a07 + en_a08 + en_a09 + en_a10 + en_a11 + en_a12
    \ :
    \ de_a03 + de_a04 + de_a05 + de_a06 + de_a07 + de_a08 + de_a09 + de_a10 + de_a11 + de_a12

de_useScreencastStart = 28
de_use03FrameStretchFrame = 29
de_use03FrameStretchLength = 30
de_use06FrameStretchFrame = 210
de_use06FrameStretchLength = 80
de_use07FrameStretchFrame = 275
de_use07FrameStretchLength = 70
de_use08FrameStretchFrame = 487
de_use08FrameStretchLength = 40
de_use12FrameStretchFrame = 1190
de_use12FrameStretchLength = 60
de_useScreencastEnd = de_use08FrameStretchFrame + de_use08FrameStretchLength

usePosteRazorVideoSource = AviSource(englishlanguage ? "de_posterazor.avi" : "de_posterazor.avi")
usePosteRazorVideo = englishlanguage ?
    \   usePosteRazorVideoSource
    \ :
    \   usePosteRazorVideoSource.trim(de_useScreencastStart,     de_use03FrameStretchFrame)
    \ + usePosteRazorVideoSource.trim(de_use03FrameStretchFrame, de_use03FrameStretchFrame).loop(de_use03FrameStretchLength)
    \ + usePosteRazorVideoSource.trim(de_use03FrameStretchFrame, de_use06FrameStretchFrame)
    \ + usePosteRazorVideoSource.trim(de_use06FrameStretchFrame, de_use06FrameStretchFrame).loop(de_use06FrameStretchLength)
    \ + usePosteRazorVideoSource.trim(de_use06FrameStretchFrame, de_use07FrameStretchFrame)
    \ + usePosteRazorVideoSource.trim(de_use07FrameStretchFrame, de_use07FrameStretchFrame).loop(de_use07FrameStretchLength)
    \ + usePosteRazorVideoSource.trim(de_use07FrameStretchFrame, de_use08FrameStretchFrame)
    \ + usePosteRazorVideoSource.trim(de_use08FrameStretchFrame, de_use08FrameStretchFrame).loop(de_use08FrameStretchLength)
    \ + usePosteRazorVideoSource.trim(de_use08FrameStretchFrame, de_use12FrameStretchFrame)
    \ + usePosteRazorVideoSource.trim(de_use12FrameStretchFrame, de_use12FrameStretchFrame).loop(de_use12FrameStretchLength)
                                                                      
usePosteRazor = AudioDub(usePosteRazorVideo, usePosteRazorAudio)

screencastvideo = downloadPosterazor.FadeOut(10) + usePosteRazor.FadeIn(10)

screencastvideo
