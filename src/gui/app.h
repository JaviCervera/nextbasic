#ifndef GUIAPP_H
#define GUIAPP_H

#include "../common/defs.h"
#include "event.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT int CALL RunApp(wxEventHandler handler);

#ifdef __cplusplus
}
#endif

#endif // GUIAPP_H