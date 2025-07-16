@echo off
echo Creating bin folder...
if not exist bin mkdir bin

echo Compiling...
gcc -g -Wall -std=c99 src\*.c src\system\*.c src\map\*.c src\gameloop\*.c -Isrc/lib/raylib/include -Lsrc/lib/raylib/lib -lraylib -lm -lgdi32 -lwinmm -o bin/game.exe

if %errorlevel% neq 0 (
    echo Compilation failed!
    exit /b %errorlevel%
)

echo Compilation successful! Launching game with GDB...

:: Launch gdb with suppressed thread messages and no paging
gdb -q bin/game.exe -ex "set pagination off" -ex "set verbose off" -ex "set print thread-events off" -ex run
