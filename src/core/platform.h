#ifndef PLATFORM_H
#define PLATFORM_H

#include <string>

#ifdef __cplusplus
extern "C" {
#endif

int plat_Millisecs();
void plat_Delay(int msecs);
void* plat_LoadLibrary(const std::string& libname);
void plat_FreeLibrary(void* lib);
void* plat_LibraryFunction(void* lib, const std::string& funcname);

#ifdef __cplusplus
}
#endif

#endif // PLATFORM_H
