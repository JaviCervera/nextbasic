#include "system.h"
#include "array.h"
#include "string.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(_WIN32)
#undef UNICODE
#include <windows.h>
#define popen _popen
#define pclose _pclose
#elif defined(__APPLE__)
#include <libproc.h>
#elif defined(__gnu_linux__)
#include <unistd.h>
#endif

using namespace std;

static string programName;
static int clArguments = CreateArray();

EXPORT int CALL PlatformId() {
#if defined(_WIN32)
    return PLATFORM_WINDOWS;
#elif defined(__APPLE__)
    return PLATFORM_MAC;
#elif defined(__gnu_linux__)
    return PLATFORM_LINUX;
#else
    return 0;
#endif
}

EXPORT string CALL ProgramName() {
	return programName;
}

EXPORT int CALL CommandLine() {
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

void __nb_setprogramname__() {
#if defined(_WIN32)
	char pathbuf[PATH_MAX];
	GetModuleFileName(NULL, pathbuf, PATH_MAX);
	programName = pathbuf;
#elif defined(__APPLE__)
	char pathbuf[PROC_PIDPATHINFO_MAXSIZE];
	pid_t pid = getpid();
	proc_pidpath (pid, pathbuf, sizeof(pathbuf));
	programName = pathbuf;
#elif defined(__gnu_linux__)
	char pathbuf[PATH_MAX];
	ssize_t len = readlink("/proc/self/exe", pathbuf, sizeof(pathbuf)-1);
	pathbuf[len] = '\0';
	programName = pathbuf;
#else
#error "Implement retrieval of binary path. Some help here: http://stackoverflow.com/questions/1023306/finding-current-executables-path-without-proc-self-exe/1024937#1024937"
#endif
}

void __nb_setcommandline__(int num, char* args[]) {
	ClearArray(clArguments);
	for ( int i = 0; i < num; i++ )
        ArrayAddString(clArguments, string(args[i]));
}
