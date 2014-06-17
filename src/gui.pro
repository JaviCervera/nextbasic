#Target info
win32:TARGET = ../../modules/gui/wxplain.win32
mac:TARGET = ../modules/gui/wxplain.mac
unix:!mac:TARGET = ../modules/gui/wxplain.linux

#Project config
TEMPLATE = lib
CONFIG -= qt

#To build a static library, uncomment these lines
CONFIG += staticlib
#To build a shared library, uncomment these lines
#CONFIG += shared
#DEFINES += BUILD_SHARED
#LIBS += -L../modules/gui
#win32:LIBS += -L../modules/core -lcore.win32 -lwx_msw-2.9.win32 -lwxregex-2.9.win32 -lwxscintilla-2.9.win32 -lwxexpat-2.9.win32 -lwxtiff-2.9.win32 -lwxjpeg-2.9.win32 -lwxpng-2.9.win32 -lwxzlib-2.9.win32 -lrpcrt4 -loleaut32 -lole32 -luuid -lwinspool -lwinmm -lshell32 -lcomctl32 -lcomdlg32 -ladvapi32 -lwsock32 -lgdi32 -lstdc++
#mac:LIBS += -L../modules/core -lcore.mac -framework IOKit -framework Carbon -framework Cocoa -framework AudioToolbox -framework System -framework OpenGL -framework QuickTime -lwx_osx_cocoa-2.9.mac -framework WebKit -lwxscintilla-2.9.mac -lwxtiff-2.9.mac -lwxjpeg-2.9.mac -lwxpng-2.9.mac -lz -lpthread -liconv -lstdc++
#unix:!mac:LIBS += -L../modules/core -lcore.linux -pthread -lwx_gtk2-2.9.linux -lwxscintilla-2.9.linux -lgtk-x11-2.0 -lgdk-x11-2.0 -latk-1.0 -lgio-2.0 -lpangoft2-1.0 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lcairo -lpango-1.0 -lfreetype -lfontconfig -lgobject-2.0 -lgthread-2.0 -lrt -lglib-2.0 -lX11 -lSM -lgtk-x11-2.0 -lgdk-x11-2.0 -latk-1.0 -lgio-2.0 -lpangoft2-1.0 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lcairo -lpango-1.0 -lfreetype -lfontconfig -lgobject-2.0 -lglib-2.0 -lpng -lwxtiff-2.9.linux -lwxjpeg-2.9.linux -lz -lstdc++

#Ensure that project builds in 32 bit mode
QMAKE_CFLAGS += -m32 -O3
QMAKE_CXXFLAGS += -m32 -O3
QMAKE_LFLAGS += -m32

#Additional compiler flags required by wxWidgets
win32:QMAKE_CFLAGS += -mthreads
win32:QMAKE_CXXFLAGS += -mthreads

#wxWidgets headers path
INCLUDEPATH += gui/wxWidgets/include
win32:INCLUDEPATH += gui/wxWidgets/include/win32
mac:INCLUDEPATH += gui/wxWidgets/include/mac
unix:!mac:INCLUDEPATH += gui/wxWidgets/include/linux

#Definitions needed to build a wxWidgets-based project
win32:DEFINES += _LARGEFILE_SOURCE=unknown wxDEBUG_LEVEL=0 __WXMSW__
mac:DEFINES += _FILE_OFFSET_BITS=64 wxDEBUG_LEVEL=0 __WXMAC__ __WXOSX__ __WXOSX_COCOA__
unix:!mac:DEFINES += _FILE_OFFSET_BITS=64 wxDEBUG_LEVEL=0 __WXGTK__

#Project source files
SOURCES += \ 
    gui/bitmap.cpp \
    gui/app.cpp \
    gui/window.cpp \
    gui/widget.cpp \
    gui/toolbar.cpp \
    gui/tabbar.cpp \
    gui/statusbar.cpp \
    gui/scintillaeditor.cpp \
    gui/requester.cpp \
    gui/menu.cpp \
    gui/editor.cpp

#Project header files
HEADERS += \ 
    gui/event.h \
    gui/bitmap.h \
    gui/app.h \
    gui/window.h \
    gui/widget.h \
    gui/toolbar.h \
    gui/tabbar.h \
    gui/statusbar.h \
    gui/scintillaeditor.h \
    gui/requester.h \
    gui/menu.h \
    gui/internal.h \
    gui/gui.h \
    gui/editor.h
