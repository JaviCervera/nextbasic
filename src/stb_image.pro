#Target info
win32:TARGET = ../../modules/stb_image/stb_image.win32
mac:TARGET = ../modules/stb_image/stb_image.mac
unix:!mac:TARGET = ../modules/stb_image/stb_image.linux

#Project config
TEMPLATE = lib
CONFIG -= qt

#To build a static library, uncomment these lines
CONFIG += staticlib
#To build a shared library, uncomment these lines
#CONFIG += shared
#DEFINES += BUILD_SHARED
#win32:LIBS += -lwinmm
#mac:LIBS += -framework AppKit
#unix:!mac:LIBS +=

#Ensure that project builds in 32 bit mode
QMAKE_CFLAGS += -m32 -O3
QMAKE_CXXFLAGS += -m32 -O3
QMAKE_LFLAGS += -m32

win32:DEFINES += _CRT_SECURE_NO_WARNINGS

SOURCES += \ 
    stb_image/stb_image.c

HEADERS += 