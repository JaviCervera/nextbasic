#Target info
win32:TARGET = ../../modules/gles20/gles20.win32
mac:TARGET = ../modules/gles20/gles20.mac
unix:!mac:TARGET = ../modules/gles20/gles20.linux

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

DEFINES += GLEW_STATIC
win32:DEFINES += _CRT_SECURE_NO_WARNINGS

SOURCES += \ 
    gles20/gles20.cpp \
    gles20/glew.c

HEADERS += \ 
    gles20/glew.h \
    gles20/glxew.h \
    gles20/wglew.h
