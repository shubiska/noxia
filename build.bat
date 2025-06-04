@echo off
if not exist "build" (
    mkdir "build"
)
clang -c src/noxia.c -o build/noxia.obj -O2
llvm-lib /OUT:build/noxia.lib build/noxia.obj
llvm-lib /OUT:build/noxia.a build/noxia.obj
