clipwidth = 480
clipheight = 360

# Let's create our first Qt Gui project, what about a classic "Hello World" dialog. We will also take a look at the basic structure of a Qt Gui project.
#  introVideo = AVISource("intro.avi").Trim(10, 320).ConvertToYUY2.Tweak(bright = 15, cont = 1.1).ConvertToRGB32
#  introAudio = introVideo.killVideo
#  introVideo = introVideo.killAudio
#  intro = AudioDub(introVideo, ConvertToMono(introAudio.ResampleAudio(44100).Amplify(1.5)))

# 01  Wir besuchen die Internetseite des PosteRazors
  a01 = tone(4.0, 440, 44100, 1, "silence") + WAVSource("01.wav") + tone(5.0, 440, 44100, 1, "silence")

# 02  Dort klicken wir auf den "Download"-link und wählen die passende Version für unser Betriebssystem aus
  a02 = WAVSource("02.wav") + tone(5.0, 440, 44100, 1, "silence")
  downloadPosterazorVideo = AVISource("de_posterazor_download_screencast.avi", false).trim(45, 630)
  downloadPosterazorAudio = a01 + a02
  downloadPosterazor = AudioDub(downloadPosterazorVideo, downloadPosterazorAudio)


# 03  Nach der Installation starten wir das Programm
  a03 = WAVSource("03.wav") + tone(2.5, 440, 44100, 1, "silence")

# 04  Wir laden das bild, das wir vergrössern wollen ... und gehen weiter
  a04 = WAVSource("04.wav") + tone(1.5, 440, 44100, 1, "silence")

# 05  Da unser Drucker A4-Seiten bedruckt, können wir im zweiten Schritt alles so lassen, wie es ist
  a05 = WAVSource("05.wav") + tone(1.0, 440, 44100, 1, "silence")

# 06  Im Schritt drei vergrössern wir die Überlappung der Posterteile auf 2 Zentimeter, um später das Poster besser zusammenkleben zu können
  a06 = WAVSource("06.wav") + tone(2.0, 440, 44100, 1, "silence")

# 07  Das finale Poster hat gerade eine breite von zwei DIN A4-Seiten. Wir möchten aber eine Breite von 32 Zentimetern haben.
  a07 = WAVSource("07.wav") + tone(4.0, 440, 44100, 1, "silence")

# 08  Der letze Schritt speichert das Poster
  a08 = WAVSource("08.wav") + tone(9.0, 440, 44100, 1, "silence")

# 09  Die PDF-datei wird automatisch geöffnet ... Sie enthält alle vier DIN A4-Seiten, ... die wir nun ausdrucken.
  a09 = WAVSource("09.wav")

  usePosteRazorPause05Frame = 250
  usePosteRazorVideoStartToPause05 = AVISource("de_posterazor_screencast.avi", false).trim(20, usePosteRazorPause05Frame)
  usePosteRazorPause05Loop = AVISource("de_posterazor_screencast.avi", false).trim(usePosteRazorPause05Frame, 1).loop(160)
 
  usePosteRazorPause06Frame = 280
  usePosteRazorVideoPause05ToPause06 = AVISource("de_posterazor_screencast.avi", false).trim(usePosteRazorPause05Frame, usePosteRazorPause06Frame)
  usePosteRazorPause06Loop = AVISource("de_posterazor_screencast.avi", false).trim(usePosteRazorPause06Frame, 1).loop(90)

  usePosteRazorPause07Frame = 435
  usePosteRazorVideoPause06ToPause07 = AVISource("de_posterazor_screencast.avi", false).trim(usePosteRazorPause06Frame, usePosteRazorPause07Frame)
  usePosteRazorPause07Loop = AVISource("de_posterazor_screencast.avi", false).trim(usePosteRazorPause07Frame, 1).loop(50)
  usePosteRazorVideoPause07ToEnd = AVISource("de_posterazor_screencast.avi", false).trim(usePosteRazorPause07Frame, 1180)

  usePosteRazorVideo = usePosteRazorVideoStartToPause05 + usePosteRazorPause05Loop + usePosteRazorVideoPause05ToPause06 + usePosteRazorPause06Loop + usePosteRazorVideoPause06ToPause07 + usePosteRazorPause07Loop + usePosteRazorVideoPause07ToEnd
  usePosteRazorAudio = a03 + a04 + a05 + a06 + a07 + a08 + a09
  usePosteRazor = AudioDub(usePosteRazorVideo, usePosteRazorAudio)

screencastvideo = downloadPosterazor.FadeOut(10) + usePosteRazor.FadeIn(10)

screencastvideo

#qtlogo = ImageReader("../qt-logo.png", 0, 0, 30, pixel_type="rgb32").Spline64Resize(45, 45)
#qtlogomask = qtlogo.showalpha()
#video = video.TemporalSoften(4,4,8).Spline64Resize(clipwidth, clipheight).Overlay(qtlogo, clipwidth - Width(qtlogo) - 5, clipheight - Height(qtlogo) - 10, qtlogomask, 0.65)
#video = AudioDub(video, video.killVideo.Amplify(0.6))

#video
