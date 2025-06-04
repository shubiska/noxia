@echo off
call build.bat
clang src/app.c build/noxia.lib -o build/app.exe -O2 -fuse-ld=lld -lmsvcrt -luser32 -lwinmm -lgdi32 -lopengl32
@REM -Wl,/SUBSYSTEM:WINDOWS -Wl,/ENTRY:mainCRTStartup
"build/app.exe"
