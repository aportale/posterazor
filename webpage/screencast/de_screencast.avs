function trimAudio(clip audioClip, float startSecond, float endSecond)
{
    fps = 1000
    dummyVideoFrames = Round((endSecond - startSecond) * fps)
    dummyVideo = BlankClip(Round(endSecond * fps), width = 1, height = 1, fps = fps)
    dummyClip = AudioDub(dummyVideo, audioClip)
    trimmedClip = dummyClip.trim(Round(startSecond * dummyClip.Framerate), 0)
    trimmedAudio = GetChannel(trimmedClip, 1).killvideo
    return trimmedAudio
}

function audioNoise(float lengthSeconds)
{
    uncutAudio = WAVSource("de_audio_uncut.wav")
    noiseStart = 2299401 / 44100.0
    noiseEnd   = 2311009 / 44100.0
    noiseSample = trimAudio(uncutAudio, noiseStart, noiseEnd)
    noiseSampleReverse = noiseSample.reverse()
    noiseSample = noiseSample + noiseSample.reverse()
    noiseSampleLength = (noiseEnd - noiseStart) * 2 # '* 2' because it has the reversed noise appended
    noiseAudio = noiseSample.loop(ceil(lengthSeconds / noiseSampleLength))
    return noiseAudio.trimAudio(0, lengthSeconds)
}

function audioClip(float startSecond, float endSecond, float appendedSilenceSeconds)
{
    uncutAudio = WAVSource("de_audio_uncut.wav")
    return uncutAudio.trimAudio(startSecond, endSecond) + audioNoise(appendedSilenceSeconds)
}

clipwidth = 480
clipheight = 360

# 01  Wir besuchen die Internetseite des PosteRazors
  a01 = audioNoise(3) + audioClip(0.52, 3.705, 3)

# 02  Dort klicken wir auf den link "Herunterladen" und wählen die passende Version für unser Betriebssystem aus
  a02 = audioClip(3.789, 10.215, 1)

downloadPosterazorAudio = a01 + a02

downloadScreencastStart = 50
downloadLoadPageFrameRemovalStart = 240
downloadLoadPageRemovalEnd = 296
downloadScreencastEnd = 519

downloadPosterazorVideo =
    \   AviSource("de_download.avi").trim(downloadScreencastStart, downloadLoadPageFrameRemovalStart)
    \ + AviSource("de_download.avi").trim(downloadLoadPageRemovalEnd, downloadScreencastEnd)

downloadPosterazor = AudioDub(downloadPosterazorVideo, downloadPosterazorAudio)


# 03  Nach der Installation starten wir das Programm
  a03 = audioClip(10.194, 13.042, 0)

# 04  Wir laden das Bild, das wir vergrössern wollen...
  a04 = audioClip(13.308, 17.466, 1)
  
# 05  ...und gehen weiter
  a05 = audioClip(17.669, 23.060, 1)

# 06  Da unser Drucker A4-Seiten bedruckt, können wir im zweiten Schritt alles so lassen, wie es ist
  a06 = audioClip(23.288, 32.576, 1)

# 07  Im Schritt drei vergrössern wir die Überlappung der Posterteile auf 2 Zentimeter, um später das Poster besser zusammenkleben zu können
  a07 = audioClip(0, 2, 0)

# 08  Das finale Poster hat gerade eine breite von zwei DIN A4-Seiten. Wir möchten aber eine Breite von 32 Zentimetern haben.
  a08 = audioClip(0, 2, 0)

# 09  Der letze Schritt speichert das Poster
  a09 = audioClip(0, 2, 0)

# 10  Die PDF-datei wird automatisch geöffnet...
  a10 = audioClip(0, 2, 0)

# 11  ...Sie enthält alle vier DIN A4-Seiten,...
  a11 = audioClip(0, 2, 0)

# 12  ...die wir nun ausdrucken.
  a12 = audioClip(0, 2, 0)

usePosteRazorAudio = a03 + a04 + a05 + a06 + a07 + a08 + a09 + a10 + a11 + a12

useScreencastStart = 28
use03FrameStretchFrame = 29
use03FrameStretchLength = 30
use06FrameStretchFrame = 210
use06FrameStretchLength = 80
use07FrameStretchFrame = 275
use07FrameStretchLength = 70
useScreencastEnd = 1190

usePosteRazorVideo =
    \   AviSource("de_posterazor.avi").trim(useScreencastStart, use03FrameStretchFrame)
    \ + AviSource("de_posterazor.avi").trim(use03FrameStretchFrame, use03FrameStretchFrame).loop(use03FrameStretchLength)
    \ + AviSource("de_posterazor.avi").trim(use03FrameStretchFrame, use06FrameStretchFrame)
    \ + AviSource("de_posterazor.avi").trim(use06FrameStretchFrame, use06FrameStretchFrame).loop(use06FrameStretchLength)
    \ + AviSource("de_posterazor.avi").trim(use06FrameStretchFrame, use07FrameStretchFrame)
    \ + AviSource("de_posterazor.avi").trim(use07FrameStretchFrame, use07FrameStretchFrame).loop(use07FrameStretchLength)
    \ + AviSource("de_posterazor.avi").trim(use07FrameStretchFrame, useScreencastEnd)

usePosteRazor = AudioDub(usePosteRazorVideo, usePosteRazorAudio)
usePosteRazor
__end__

screencastvideo = downloadPosterazor.FadeOut(10) + usePosteRazor.FadeIn(10)

#screencastvideo

#qtlogo = ImageReader("../qt-logo.png", 0, 0, 30, pixel_type="rgb32").Spline64Resize(45, 45)
#qtlogomask = qtlogo.showalpha()
#video = video.TemporalSoften(4,4,8).Spline64Resize(clipwidth, clipheight).Overlay(qtlogo, clipwidth - Width(qtlogo) - 5, clipheight - Height(qtlogo) - 10, qtlogomask, 0.65)
#video = AudioDub(video, video.killVideo.Amplify(0.6))

#video
