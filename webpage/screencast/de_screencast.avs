clipwidth = 480
clipheight = 360

# Let's create our first Qt Gui project, what about a classic "Hello World" dialog. We will also take a look at the basic structure of a Qt Gui project.
#  introVideo = AVISource("intro.avi").Trim(10, 320).ConvertToYUY2.Tweak(bright = 15, cont = 1.1).ConvertToRGB32
#  introAudio = introVideo.killVideo
#  introVideo = introVideo.killAudio
#  intro = AudioDub(introVideo, ConvertToMono(introAudio.ResampleAudio(44100).Amplify(1.5)))

# 01  Wir besuchen die Internetseite des PosteRazors
#  a01 = WAVSource("01.wav") + tone(4.0, 440, 44100, 1, "silence")
# 02  Dort klicken wir auf den "herunterladen"-link und wählen den passenden Download für unser Betriebssystem aus
#  a02 = WAVSource("02.wav") + tone(5.0, 440, 44100, 1, "silence")
  downloadPosterazorVideo = AVISource("de_posterazor_download_screencast.avi", false)
#  downloadPosterazorAudio = a01 + a02
  downloadPosterazor = downloadPosterazorVideo # AudioDub(createProjectVideo, createProjectAudio)

# 03  Nach der Installation starten wir das Programm direkt
#  a03 = WAVSource("03.wav") + tone(0, 440, 44100, 1, "silence")
# 04  Wir laden das bild, das wir vergrössern wollen ... und gehen weiter
#  a04 = WAVSource("04.wav") + tone(2.0, 440, 44100, 1, "silence")
# 05  Da der Drucker A4-Seiten bedruckt, können wir im zweiten Schritt alles so lassen, wie es ist
#  a05 = WAVSource("05.wav") + tone(1.0, 440, 44100, 1, "silence")
# 06  Im Schritt drei vergrössern wir die Überlappung auf 2 Zentimeter, um später die Posterteile besser zusammenkleben zu können
#  a06 = WAVSource("06.wav") + tone(1.0, 440, 44100, 1, "silence")
# 07  Das finale Poster hat gerade eine brete von zwei A4-Seiten. Wir möchten aber eine Breite von 32 Zentimetern haben.
#  a07 = WAVSource("07.wav") + tone(1.0, 440, 44100, 1, "silence")
# 08  Der letze Schritt speichert das Poster
#  a08 = WAVSource("08.wav") + tone(4.0, 440, 44100, 1, "silence")
# 09  Die PDF-datei wird automatisch geöffnet ... Sie enthält alle vier A4-Seiten, ... die wir nun ausdrucken.
#  a09 = WAVSource("09.wav") + tone(4.0, 440, 44100, 1, "silence")
  pausePosition = 630
  usePosteRazorVideo_StartTo05Pause = AVISource("de_posterazor_screencast.avi", false).Trim(100, pausePosition)
  usePosteRazorVideo_05Pause = AVISource("de_posterazor_screencast.avi", false).Trim(pausePosition, pausePosition).Loop(130)
  usePosteRazorVideo_05PauseToEnd = AVISource("de_posterazor_screencast.avi", false).Trim(pausePosition, 941)
  usePosteRazorVideo = usePosteRazorVideo_StartTo05Pause + usePosteRazorVideo_05Pause + usePosteRazorVideo_05PauseToEnd
#  usePosteRazorAudio = a03 + a04 + a05 + a06 + a07 + a08 + a09
  usePosteRazor = usePosteRazorVideo # AudioDub(usePosteRazorVideo, usePosteRazorAudio)

screencastvideo = Dissolve(downloadPosterazor, usePosteRazor, 6)

screencastvideo

#qtlogo = ImageReader("../qt-logo.png", 0, 0, 30, pixel_type="rgb32").Spline64Resize(45, 45)
#qtlogomask = qtlogo.showalpha()
#video = video.TemporalSoften(4,4,8).Spline64Resize(clipwidth, clipheight).Overlay(qtlogo, clipwidth - Width(qtlogo) - 5, clipheight - Height(qtlogo) - 10, qtlogomask, 0.65)
#video = AudioDub(video, video.killVideo.Amplify(0.6))

#video
