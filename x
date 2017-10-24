"make" -f nbproject/Makefile-Debug.mk QMAKE= SUBPROJECTS= .build-conf
make[1]: Entering directory '/home/kurt/NetBeansProjects/234tree-in-cpp'
"make"  -f nbproject/Makefile-Debug.mk dist/Debug/GNU-Linux/4
make[2]: Entering directory '/home/kurt/NetBeansProjects/234tree-in-cpp'
mkdir -p build/Debug/GNU-Linux
rm -f "build/Debug/GNU-Linux/main.o.d"
g++    -c -g -std=c++14 -MMD -MP -MF "build/Debug/GNU-Linux/main.o.d" -o build/Debug/GNU-Linux/main.o main.cpp
mkdir -p dist/Debug/GNU-Linux
g++     -o dist/Debug/GNU-Linux/4 build/Debug/GNU-Linux/main.o 
make[2]: Leaving directory '/home/kurt/NetBeansProjects/234tree-in-cpp'
make[1]: Leaving directory '/home/kurt/NetBeansProjects/234tree-in-cpp'
