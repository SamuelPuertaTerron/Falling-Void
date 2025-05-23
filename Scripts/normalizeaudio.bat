@echo off
mkdir normalized
for %%f in (*.wav) do (
    echo Normalizing %%f...
    ffmpeg -i "%%f" -af loudnorm=I=-16:TP=-1.5:LRA=11 "normalized\%%~nf_normalized.wav"
)

pause