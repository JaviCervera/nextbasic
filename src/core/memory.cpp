#include "memory.h"
#include <stdlib.h>
#include <string.h>

using namespace std;

EXPORT int CALL AllocMem(int size) {
	return (int)malloc(size);
}

EXPORT void CALL FreeMem(int address) {
	free((void*)address);
}

EXPORT int CALL ResizeMem(int address, int size) {
	return (int)realloc((void*)address, size);
}

EXPORT void CALL CopyMem(int from, int to, int size) {
	memcpy((void*)to, (const void*)from, size);
}

EXPORT void CALL SetMem(int address, int val, int size) {
	memset((void*)address, val, size);
}

EXPORT int CALL PeekByte(int address) {
    char c;
	memcpy(&c, (void*)address, sizeof(char));
    return (int)c;
}

EXPORT int CALL PeekShort(int address) {
    short s;
	memcpy(&s, (void*)address, sizeof(short));
    return (int)s;
}

EXPORT int CALL PeekInt(int address) {
    int i;
	memcpy(&i, (void*)address, sizeof(int));
    return i;
}

EXPORT float CALL PeekFloat(int address) {
    float f;
	memcpy(&f, (void*)address, sizeof(float));
    return f;
}

EXPORT string CALL PeekString(int address, int size) {
    if ( size > 0 ) {
		return string((char*)address, size);
    } else {
		return string((char*)address);
    }
}

EXPORT void CALL PokeByte(int address, int val) {
	memcpy((void*)address, &val, sizeof(char));
}

EXPORT void CALL PokeShort(int address, int val) {
	memcpy((void*)address, &val, sizeof(short));
}

EXPORT void CALL PokeInt(int address, int val) {
	memcpy((void*)address, &val, sizeof(int));
}

EXPORT void CALL PokeFloat(int address, float val) {
	memcpy((void*)address, &val, sizeof(float));
}

EXPORT void CALL PokeString(int address, string val) {
	strcpy((char*)address, val.c_str());
}
