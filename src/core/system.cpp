#include "system.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#define popen _popen
#define pclose _pclose
#endif

using namespace std;

static string programName;
static Array* clArguments = CreateArray();

extern "C" {

EXPORT int CALL PlatformId() {
#if defined(_WIN32)
    return PLATFORM_WINDOWS;
#elif defined(__APPLE__)
    return PLATFORM_MAC;
#elif defined(__linux__)
    return PLATFORM_LINUX;
#else
    return 0;
#endif
}

EXPORT string CALL ProgramName() {
	return programName;
}

EXPORT Array* CALL CommandLine() {
    return clArguments;
}

EXPORT string CALL GetEnv(string var) {
	return string(getenv(var.c_str()));
}

EXPORT int CALL System(string command) {
	return system(command.c_str());
}

EXPORT string CALL RunProgram(string program) {
	string str;

    // Open program
	FILE* pipe = popen(program.c_str(), "rt");
	if ( pipe == NULL ) return "";

    // Read pipe
    while ( !feof(pipe) ) {
        char tmp[128];
		if ( fgets(tmp, 128, pipe) != NULL ) str += tmp;
    }

    // Close pipe
    pclose(pipe);

    // Return string
	return str;
}

EXPORT void CALL End(int exitCode) {
    exit(exitCode);
}

void __nb_setprogramname__(const char* name) {
	programName = string(name);
}

void __nb_setcommandline__(int num, char* args[]) {
	ClearArray(clArguments);
	for ( int i = 0; i < num; i++ )
        ArrayAddString(clArguments, string(args[i]));
}

} // extern "C"
