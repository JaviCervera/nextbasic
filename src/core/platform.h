#ifndef PLATFORM_H
#define PLATFORM_H

#include <string>

int plat_Millisecs();
void plat_Delay(int msecs);
void* plat_LoadLibrary(const std::string& libname);
void plat_FreeLibrary(void* lib);
void* plat_LibraryFunction(void* lib, const std::string& funcname);

#endif // PLATFORM_H
