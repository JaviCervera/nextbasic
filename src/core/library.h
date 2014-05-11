#ifndef LIBRARY_H
#define LIBRARY_H

#include "../common/defs.h"
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

EXPORT void* CALL LoadLibrary(std::string libname);
EXPORT void CALL FreeLibrary(void* lib);
EXPORT void* CALL LibraryFunction(void* lib, std::string funcname);
EXPORT void CALL PushLibraryInt(int val);
EXPORT void CALL PushLibraryFloat(float val);
EXPORT void CALL PushLibraryString(std::string str);
EXPORT void CALL PushLibraryObject(void* obj);
EXPORT void CALL CallVoidFunction(void* func);
EXPORT int CALL CallIntFunction(void* func);
EXPORT float CALL CallFloatFunction(void* func);
EXPORT std::string CALL CallStringFunction(void* func);
EXPORT void* CALL CallObjectFunction(void* func);
EXPORT void CALL CallVoidCFunction(void* func);
EXPORT int CALL CallIntCFunction(void* func);
EXPORT float CALL CallFloatCFunction(void* func);
EXPORT std::string CALL CallStringCFunction(void* func);
EXPORT void* CALL CallObjectCFunction(void* func);

#ifdef __cplusplus
}
#endif

#endif // LIBRARY_H
