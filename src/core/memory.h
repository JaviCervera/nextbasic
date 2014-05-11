#ifndef MEMORY_H
#define MEMORY_H

#include "../common/defs.h"
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

EXPORT void* CALL AllocMem(int size);
EXPORT void CALL FreeMem(void* address);
EXPORT void* CALL ResizeMem(void* address, int size);
EXPORT void CALL CopyMem(void* from, void* to, int size);
EXPORT void CALL SetMem(void* address, int val, int size);
EXPORT int CALL PeekByte(void* address);
EXPORT int CALL PeekShort(void* address);
EXPORT int CALL PeekInt(void* address);
EXPORT float CALL PeekFloat(void* address);
EXPORT std::string CALL PeekString(void* address, int size);
EXPORT void CALL PokeByte(void* address, int val);
EXPORT void CALL PokeShort(void* address, int val);
EXPORT void CALL PokeInt(void* address, int val);
EXPORT void CALL PokeFloat(void* address, float val);
EXPORT void CALL PokeString(void* address, std::string val);

#ifdef __cplusplus
}
#endif

#endif // MEMORY_H
