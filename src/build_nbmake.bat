@echo off
cd ..
cd bin
nbc ../src/nbmake.nb
g++ -w -O3 -m32 -o nbmake.exe ../src/nbmake.cpp -L../modules/core -lcore.win32 -lgdi32 -lwinmm
cd ..
cd src
del nbmake.cpp
pause