#ifndef ARRAY_H
#define ARRAY_H

#include "../common/defs.h"
#include "collectionvalue.h"

EXPORT int CALL CreateArray();
EXPORT void CALL FreeArray(int arr);
EXPORT int CALL CountArray(int arr);
EXPORT void CALL ArrayAddInt(int arr, int i);
EXPORT void CALL ArrayAddFloat(int arr, float f);
EXPORT void CALL ArrayAddString(int arr, std::string s);
EXPORT void CALL ArrayAddObject(int arr, void* obj);
EXPORT void CALL ArraySetInt(int arr, int index, int i);
EXPORT void CALL ArraySetFloat(int arr, int index, float f);
EXPORT void CALL ArraySetString(int arr, int index, std::string s);
EXPORT void CALL ArraySetObject(int arr, int index, void* obj);
EXPORT int CALL ArrayInt(int arr, int index);
EXPORT float CALL ArrayFloat(int arr, int index);
EXPORT std::string CALL ArrayString(int arr, int index);
EXPORT int CALL ArrayObject(int arr, int index);
EXPORT void CALL ArrayRemoveAt(int arr, int index);
EXPORT void CALL ArrayRemoveObject(int arr, void* obj);
EXPORT void CALL ClearArray(int arr);

#endif // ARRAY_H
