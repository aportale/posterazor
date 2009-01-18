global gStillFrameLength = 30

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
    noiseSample = trimAudio(gAudioClip, gAudioNoiseStart, gAudioNoiseEnd)
    noiseSampleReverse = noiseSample.reverse()
    noiseSample = noiseSample + noiseSample.reverse()
    noiseSampleLength = (gAudioNoiseEnd - gAudioNoiseStart) * 2 # '* 2' because it has the reversed noise appended
    noiseAudio = noiseSample.loop(ceil(lengthSeconds / noiseSampleLength))
    return noiseAudio.trimAudio(0, lengthSeconds)
}

function audioClip(float startSecond, float endSecond, float appendedSilenceSeconds)
{
    return gAudioClip.trimAudio(startSecond, endSecond) + audioNoise(appendedSilenceSeconds)
}

function textClip(clip templateClip, string text)
{
    backgroundColor = $eeeeee
    textColor = $333333
    return
        \  BlankClip(clip = templateClip, length = StrLen(text) * 4, color = backgroundColor)
        \ .Subtitle(text, align = 5, text_color = textColor, halo_color = backgroundColor, size = 40)
        \ .ConvertToYV12()
}

function frame(clip sourceClip, int frame)
{
    return sourceClip.trim(frame, frame).loop(gStillFrameLength)
}
