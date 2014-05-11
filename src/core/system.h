#ifndef SYSTEM_H
#define SYSTEM_H

#include "../common/defs.h"
#include <string>

#define PLATFORM_WINDOWS    1
#define PLATFORM_MAC        2
#define PLATFORM_LINUX      3

EXPORT int CALL PlatformId();
EXPORT std::string CALL ProgramName();
EXPORT int CALL CommandLine();	// Returns an Array*
EXPORT std::string CALL GetEnv(std::string var);
EXPORT int CALL System(std::string command);
EXPORT std::string CALL RunProgram(std::string program);
EXPORT void CALL End(int exitCode);

// Internal functions
void __nb_setprogramname__(const char* name);
void __nb_setcommandline__(int num, char* args[]);

#endif // SYSTEM_H
