#ifndef ARRAY_H
#define ARRAY_H

#include "../common/defs.h"
#include "collectionvalue.h"
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

typedef std::vector<CollectionValue> Array;

EXPORT Array* CALL CreateArray();
EXPORT void CALL FreeArray(Array* arr);
EXPORT int CALL CountArray(Array* arr);
EXPORT void CALL ArrayAddInt(Array* arr, int i);
EXPORT void CALL ArrayAddFloat(Array* arr, float f);
EXPORT void CALL ArrayAddString(Array* arr, std::string s);
EXPORT void CALL ArrayAddObject(Array* arr, void* obj);
EXPORT void CALL ArraySetInt(Array* arr, int index, int i);
EXPORT void CALL ArraySetFloat(Array* arr, int index, float f);
EXPORT void CALL ArraySetString(Array* arr, int index, std::string s);
EXPORT void CALL ArraySetObject(Array* arr, int index, void* obj);
EXPORT int CALL ArrayInt(Array* arr, int index);
EXPORT float CALL ArrayFloat(Array* arr, int index);
EXPORT std::string CALL ArrayString(Array* arr, int index);
EXPORT void* CALL ArrayObject(Array* arr, int index);
EXPORT void CALL ArrayRemoveAt(Array* arr, int index);
EXPORT void CALL ArrayRemoveObject(Array* arr, void* obj);
EXPORT void CALL ClearArray(Array* arr);

#ifdef __cplusplus
}
#endif

#endif // ARRAY_H
