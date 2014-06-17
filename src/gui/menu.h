#ifndef GUIMENU_H
#define GUIMENU_H

#include "../common/defs.h"

#define ID_ABOUT	5014
#define ID_QUIT		5006

#ifdef __cplusplus
extern "C" {
#endif

EXPORT void* CALL CreateMenuBar(void* win);
EXPORT void* CALL AddMenuTitle(void* menubar, const char* title);
EXPORT void CALL AddMenuItem(void* menu, int id, const char* text);
EXPORT void CALL AddMenuSeparator(void* menu);
EXPORT void* CALL AddSubMenu(void* menu, int id, const char* title);

#ifdef __cplusplus
}
#endif

#endif // GUIMENU_H