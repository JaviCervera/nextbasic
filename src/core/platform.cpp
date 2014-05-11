#include "platform.h"
#include "array.h"
#include "string.h"

#if defined(_WIN32)
#undef UNICODE
#include <Windows.h>
#elif defined(__APPLE__)
#include <CoreServices/CoreServices.h>
#include <dlfcn.h>
#include <memory.h>
#include <stdlib.h>
#include <time.h>
#elif defined(__linux__)
#include <dlfcn.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/sysinfo.h>
#endif

using namespace std;

#ifndef _WIN32
static string __nb_stripmangling__(const string& str) {
    Array* arr = SplitString(str, "@");
	string out = ArrayString(arr, 0);
	FreeArray(arr);
	if ( Left(out, 1) == "_" ) out = Right(out, Len(out) - 1);
	return out;
}
#endif

int plat_Millisecs() {
#if defined(_WIN32)
    return timeGetTime();
#elif defined(__linux__)
    static long basetime = -1;
    long t;
    struct timeval tv;
    gettimeofday(&tv, 0);
    t = tv.tv_sec * 1000;
    t += tv.tv_usec / 1000;
    if ( basetime == -1 ) {
        struct sysinfo info;
        sysinfo(&info);
        basetime = t - info.uptime * 1000;
    }
    return (int)(t - basetime);
#elif defined(__APPLE__)
    double t;
    UnsignedWide uw;
    Microseconds( &uw );
    t=(uw.hi<<(32-9))|(uw.lo>>9);
    return t/(1000.0/512.0);
#endif
}

void plat_Delay(int msecs) {
#if defined(_WIN32)
    Sleep(msecs);
#else
    struct timespec req;
    memset(&req, 0, sizeof(struct timespec));
    req.tv_sec = 0;
    req.tv_nsec = msecs * 1000000L;
    nanosleep(&req, (struct timespec*)0);
#endif
}

void* plat_LoadLibrary(const string& libname) {
#if defined(_WIN32)
	return (void*)LoadLibrary((libname + ".dll").c_str());
#elif defined(__APPLE__)
	return dlopen((libname + ".dylib").c_str(), 101);
#elif defined(__linux__)
	return dlopen((libname + ".so").c_str(), 101);
#endif
}

void plat_FreeLibrary(void* lib) {
#if defined(_WIN32)
    FreeLibrary((HMODULE)lib);
#else
    dlclose(lib);
#endif
}

void* plat_LibraryFunction(void* lib, const string& funcname) {
#if defined(_WIN32)
	return (void*)GetProcAddress((HMODULE)lib, funcname.c_str());
#else
	return dlsym(lib, __nb_stripmangling__(funcname).c_str());
#endif
}
