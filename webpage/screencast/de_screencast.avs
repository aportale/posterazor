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
    \   DirectShowSource("de_download.avi").trim(downloadScreencastStart, downloadLoadPageFrameRemovalStart)
    \ + DirectShowSource("de_download.avi").trim(downloadLoadPageRemovalEnd, downloadScreencastEnd)

downloadPosterazor = AudioDub(downloadPosterazorVideo, downloadPosterazorAudio)



# 03  Nach der Installation starten wir das Programm
  a03 = audioClip(0, 2, 1)

# 04  Wir laden das Bild, das wir vergrössern wollen...
  a04 = audioClip(0, 4, 1)
  
# 05  ...und gehen weiter
  a05 = audioClip(0, 2, 0)

# 06  Da unser Drucker A4-Seiten bedruckt, können wir im zweiten Schritt alles so lassen, wie es ist
  a06 = audioClip(0, 2, 0)

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

useScreencastStart = 50
useLoadPageFrameRemovalStart = 240
useLoadPageRemovalEnd = 296
useScreencastEnd = 519

usePosteRazorVideo =
    \   DirectShowSource("de_posterazor.avi", false).trim(useScreencastStart, useScreencastEnd)

usePosteRazor = AudioDub(usePosteRazorVideo, usePosteRazorAudio)

screencastvideo = downloadPosterazor.FadeOut(10) + usePosteRazor.FadeIn(10)

#screencastvideo

#qtlogo = ImageReader("../qt-logo.png", 0, 0, 30, pixel_type="rgb32").Spline64Resize(45, 45)
#qtlogomask = qtlogo.showalpha()
#video = video.TemporalSoften(4,4,8).Spline64Resize(clipwidth, clipheight).Overlay(qtlogo, clipwidth - Width(qtlogo) - 5, clipheight - Height(qtlogo) - 10, qtlogomask, 0.65)
#video = AudioDub(video, video.killVideo.Amplify(0.6))

#video
