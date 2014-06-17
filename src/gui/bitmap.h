#ifndef GUIBITMAP_H
#define GUIBITMAP_H

#include "../common/defs.h"

#ifdef __cplusplus
extern "C" {
#endif

EXPORT void* CALL LoadBitmap(const char* filename);
EXPORT void CALL FreeBitmap(void* bitmap);

#ifdef __cplusplus
}
#endif

#endif // GUIBITMAP_H