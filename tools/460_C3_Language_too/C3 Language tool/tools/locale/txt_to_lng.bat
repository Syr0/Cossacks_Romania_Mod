@echo off
setlocal enabledelayedexpansion

REM Define the base path for the locale directories
set "basePath=F:\SteamLibrary\steamapps\common\Cossacks 3\mods\Romania\data\locale"

REM Define the path to the editorlang.exe tool
set "editorTool=F:\SteamLibrary\steamapps\common\Cossacks 3\mods\Romania\tools\460_C3_Language_too\C3 Language tool\tools\locale\editorlang.exe"

REM Enumerate over all subdirectories and process units.txt and units.lng files
for /r "%basePath%" %%d in (.) do (
    if exist "%%d\units.txt" (
        if exist "%%d\units.lng" (
            call "%editorTool%" "%%d\units.txt" "%%d\units.lng" c
        )
    )
)

endlocal
