win32:TARGET = ../../bin/nbc
mac:TARGET = ../bin/nbc
unix:!mac:TARGET = ../bin/nbc
TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

#Ensure that project builds in 32 bit mode
QMAKE_CFLAGS += -m32
QMAKE_CXXFLAGS += -m32
QMAKE_LFLAGS += -m32

win32:DEFINES += _CRT_SECURE_NO_WARNINGS
LIBS += -L../modules/core
win32:LIBS += -lcore.win32 -lwinmm
mac:LIBS += -lcore.mac -framework AppKit
unix:!mac:LIBS += -lcore.linux -ldl

SOURCES += \
    nbc/syntactical.cpp \
    nbc/scanner.cpp \
    nbc/main.cpp \
    nbc/lexical.cpp \
    nbc/cppgenerator.cpp \
    nbc/error.cpp \
    nbc/preprocessor.cpp

HEADERS += \
    nbc/tokenstream.h \
    nbc/token.h \
    nbc/syntactical.h \
    nbc/scanner.h \
    nbc/lexical.h \
    nbc/idtype.h \
    nbc/cppgenerator.h \
    nbc/error.h \
    nbc/preprocessor.h \
    core/array.h \
    core/string.h \
    core/filesystem.h \
    core/collectionvalue.h

OTHER_FILES += \
    todo.txt
