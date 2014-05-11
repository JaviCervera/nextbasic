cd ..
cd bin
./nbc ../src/nbmake.nb
g++ -w -O3 -m32 -stdlib=libstdc++ -o nbmake ../src/nbmake.cpp -L../modules/core -lcore.mac
cd ..
cd src
rm nbmake.cpp