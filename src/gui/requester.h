#ifndef GUIREQUESTER_H
#define GUIREQUESTER_H

#include "../common/defs.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT void CALL Notify(void* parent, const char* title, const char* text);

#ifdef __cplusplus
}
#endif

#endif // GUIREQUESTER_H