#include "memory.h"
#include <stdlib.h>
#include <string.h>

using namespace std;

extern "C" {

EXPORT void* CALL AllocMem(int size) {
    return malloc(size);
}

EXPORT void CALL FreeMem(void* address) {
	free(address);
}

EXPORT void* CALL ResizeMem(void* address, int size) {
	return realloc(address, size);
}

EXPORT void CALL CopyMem(void* from, void* to, int size) {
	memcpy(to, from, size);
}

EXPORT void CALL SetMem(void* address, int val, int size) {
	memset(address, val, size);
}

EXPORT int CALL PeekByte(void* address) {
    char c;
	memcpy(&c, address, sizeof(char));
    return (int)c;
}

EXPORT int CALL PeekShort(void* address) {
    short s;
	memcpy(&s, address, sizeof(short));
    return (int)s;
}

EXPORT int CALL PeekInt(void* address) {
    int i;
	memcpy(&i, address, sizeof(int));
    return i;
}

EXPORT float CALL PeekFloat(void* address) {
    float f;
	memcpy(&f, address, sizeof(float));
    return f;
}

EXPORT string CALL PeekString(void* address, int size) {
    if ( size > 0 ) {
		return string((char*)address, size);
    } else {
		return string((char*)address);
    }
}

EXPORT void CALL PokeByte(void* address, int val) {
	memcpy(address, &val, sizeof(char));
}

EXPORT void CALL PokeShort(void* address, int val) {
	memcpy(address, &val, sizeof(short));
}

EXPORT void CALL PokeInt(void* address, int val) {
	memcpy(address, &val, sizeof(int));
}

EXPORT void CALL PokeFloat(void* address, float val) {
	memcpy(address, &val, sizeof(float));
}

EXPORT void CALL PokeString(void* address, string val) {
	strcpy((char*)address, val.c_str());
}

} // extern "C"
