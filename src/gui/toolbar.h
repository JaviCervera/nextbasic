#ifndef GUITOOLBAR_H
#define GUITOOLBAR_H

#include "../common/defs.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT void* CALL CreateToolBar(void* parent);
EXPORT void CALL AddToolBarButton(void* toolbar, int id, void* icon, const char* tooltip);
EXPORT void CALL AddToolBarSeparator(void* toolbar);
EXPORT void CALL AddToolBarWidget(void* toolbar, void* widget);

#ifdef __cplusplus
}
#endif

#endif // GUITOOLBAR_H