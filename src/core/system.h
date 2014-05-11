#ifndef SYSTEM_H
#define SYSTEM_H

#include "../common/defs.h"
#include "array.h"
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

#define PLATFORM_WINDOWS    1
#define PLATFORM_MAC        2
#define PLATFORM_LINUX      3

EXPORT int CALL PlatformId();
EXPORT std::string CALL ProgramName();
EXPORT Array* CALL CommandLine();
EXPORT std::string CALL GetEnv(std::string var);
EXPORT int CALL System(std::string command);
EXPORT std::string CALL RunProgram(std::string program);
EXPORT void CALL End(int exitCode);

// Internal functions
void __nb_setprogramname__(const char* name);
void __nb_setcommandline__(int num, char* args[]);

#ifdef __cplusplus
}
#endif

#endif // SYSTEM_H
