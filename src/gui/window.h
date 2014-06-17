#ifndef GUIWINDOW_H
#define GUIWINDOW_H

#include "../common/defs.h"

#define WINDOW_TITLEBAR		1
#define WINDOW_RESIZABLE	2
#define WINDOW_TOOL			4
#define WINDOW_MODAL		8
#define WINDOW_CENTER		16


#ifdef __cplusplus
extern "C" {
#endif

EXPORT void* CALL CreateWindow(void* parent, int x, int y, int width, int height, int flags);
EXPORT void CALL SetWindowTitle(void* window, const char* title);

#ifdef __cplusplus
}
#endif

#endif // GUIWINDOW_H