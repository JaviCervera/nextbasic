#ifndef DEFS_H
#define DEFS_H

// Export mode and call convention
#if defined(BUILD_SHARED) && defined(_WIN32)
#define EXPORT __declspec(dllexport)
#define CALL _stdcall
#else
#define EXPORT
#define CALL
#endif

// BOOL type and values
#define FALSE 0
#define TRUE 1
typedef int BOOL;

#endif // DEFS_H
