#ifndef GUISTATUSBAR_H
#define GUISTATUSBAR_H

#include "../common/defs.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT void* CALL CreateStatusBar(void* parent);
EXPORT void CALL SetStatusBarText(void* statusbar, const char* text);
EXPORT const char* CALL StatusBarText(void* statusbar);

#ifdef __cplusplus
}
#endif

#endif // GUISTATUSBAR_H