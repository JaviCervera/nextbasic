#ifndef MEMORY_H
#define MEMORY_H

#include "../common/defs.h"
#include <string>

EXPORT int CALL AllocMem(int size);
EXPORT void CALL FreeMem(int address);
EXPORT int CALL ResizeMem(int address, int size);
EXPORT void CALL CopyMem(int from, int to, int size);
EXPORT void CALL SetMem(int address, int val, int size);
EXPORT int CALL PeekByte(int address);
EXPORT int CALL PeekShort(int address);
EXPORT int CALL PeekInt(int address);
EXPORT float CALL PeekFloat(int address);
EXPORT std::string CALL PeekString(int address, int size);
EXPORT void CALL PokeByte(int address, int val);
EXPORT void CALL PokeShort(int address, int val);
EXPORT void CALL PokeInt(int address, int val);
EXPORT void CALL PokeFloat(int address, float val);
EXPORT void CALL PokeString(int address, std::string val);

#endif // MEMORY_H
