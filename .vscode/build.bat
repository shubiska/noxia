@echo off
if not exist "build" ( mkdir build )
gcc example/main.c -o build/noxia.exe -O2 -m64 -std=c99 -Wall -Werror -luser32 -lwinmm -lgdi32 -lopengl32
"build/noxia.exe"
