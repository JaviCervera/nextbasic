#ifndef LIBRARY_H
#define LIBRARY_H

#include "../common/defs.h"
#include <string>

EXPORT int CALL LoadLibrary(std::string libname);
EXPORT void CALL FreeLibrary(int lib);
EXPORT int CALL LibraryFunction(int lib, std::string funcname);
EXPORT void CALL PushLibraryInt(int val);
EXPORT void CALL PushLibraryFloat(float val);
EXPORT void CALL PushLibraryString(std::string str);
EXPORT void CALL PushLibraryObject(int obj);
EXPORT void CALL CallVoidFunction(int func);
EXPORT int CALL CallIntFunction(int func);
EXPORT float CALL CallFloatFunction(int func);
EXPORT std::string CALL CallStringFunction(int func);
EXPORT int CALL CallObjectFunction(int func);
EXPORT void CALL CallVoidCFunction(int func);
EXPORT int CALL CallIntCFunction(int func);
EXPORT float CALL CallFloatCFunction(int func);
EXPORT std::string CALL CallStringCFunction(int func);
EXPORT int CALL CallObjectCFunction(int func);

#endif // LIBRARY_H
