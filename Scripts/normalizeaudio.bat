@echo off
mkdir normalized
for %%f in (*.wav) do (
    echo Analyzing %%f...
    ffmpeg -i "%%f" -af loudnorm=I=-16:TP=-1.5:LRA=11:print_format=json -f null NUL > temp_stats.txt

    for /f "tokens=*" %%A in ('type temp_stats.txt ^| findstr "input_i input_tp input_lra input_thresh target_offset"') do (
        set line=%%A
        call set line=%%line: =%%
        setlocal EnableDelayedExpansion
        for %%B in (!line!) do set "params=!params! %%B"
        endlocal
    )

    echo Normalizing %%f...
    ffmpeg -i "%%f" -af "loudnorm=I=-16:TP=-1.5:LRA=11:measured_I=%input_i%:measured_TP=%input_tp%:measured_LRA=%input_lra%:measured_thresh=%input_thresh%:offset=%target_offset%:linear=true:print_format=summary" "normalized\%%~nf_normalized.wav"
    set params=
)

pause