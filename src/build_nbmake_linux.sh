cd ..
cd bin
./nbc ../src/nbmake.nb
g++ -w -O3 -m32 -o nbmake ../src/nbmake.cpp -L../modules/core -lcore.linux
cd ..
cd src
rm nbmake.cpp
