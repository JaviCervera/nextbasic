#Target info
win32:TARGET = ../../modules/core/core.win32
mac:TARGET = ../modules/core/core.mac
unix:!mac:TARGET = ../modules/core/core.linux

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
    core/console.cpp \
    core/array.cpp \
    core/dictionary.cpp \
    core/time.cpp \
    core/memory.cpp \
    core/math.cpp \
    core/string.cpp \
    core/file.cpp \
    core/platform.cpp \
    core/system.cpp \
    core/filesystem.cpp \
    core/library.cpp

HEADERS += \
    core/console.h \
    core/array.h \
    core/dictionary.h \
    core/time.h \
    core/memory.h \
    core/math.h \
    core/string.h \
    core/file.h \
    core/platform.h \
    core/system.h \
    core/filesystem.h \
    core/library.h \
    common/defs.h \
    core/collectionvalue.h
