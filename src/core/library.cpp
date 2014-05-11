#include "library.h"
#include "array.h"
#include "platform.h"

static Array* __nb_libStack__ = 0;

#ifdef _WIN32
#ifdef __TINYC__
#define CALLCONV
#else
#define CALLCONV __stdcall
#endif
#else
#define CALLCONV
#endif

using namespace std;

extern "C" {

typedef void (CALLCONV *__nb_voidfunc0__)();
typedef void (CALLCONV *__nb_voidfunc1__)(void*);
typedef void (CALLCONV *__nb_voidfunc2__)(void*, void*);
typedef void (CALLCONV *__nb_voidfunc3__)(void*, void*, void*);
typedef void (CALLCONV *__nb_voidfunc4__)(void*, void*, void*, void*);
typedef void (CALLCONV *__nb_voidfunc5__)(void*, void*, void*, void*, void*);
typedef void (CALLCONV *__nb_voidfunc6__)(void*, void*, void*, void*, void*, void*);
typedef void (CALLCONV *__nb_voidfunc7__)(void*, void*, void*, void*, void*, void*, void*);
typedef void (CALLCONV *__nb_voidfunc8__)(void*, void*, void*, void*, void*, void*, void*, void*);
typedef void (CALLCONV *__nb_voidfunc9__)(void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void (CALLCONV *__nb_voidfunc10__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void (CALLCONV *__nb_voidfunc11__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void (CALLCONV *__nb_voidfunc12__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void (CALLCONV *__nb_voidfunc13__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void (CALLCONV *__nb_voidfunc14__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void (CALLCONV *__nb_voidfunc15__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void (CALLCONV *__nb_voidfunc16__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef int (CALLCONV *__nb_intfunc0__)();
typedef int (CALLCONV *__nb_intfunc1__)(void*);
typedef int (CALLCONV *__nb_intfunc2__)(void*, void*);
typedef int (CALLCONV *__nb_intfunc3__)(void*, void*, void*);
typedef int (CALLCONV *__nb_intfunc4__)(void*, void*, void*, void*);
typedef int (CALLCONV *__nb_intfunc5__)(void*, void*, void*, void*, void*);
typedef int (CALLCONV *__nb_intfunc6__)(void*, void*, void*, void*, void*, void*);
typedef int (CALLCONV *__nb_intfunc7__)(void*, void*, void*, void*, void*, void*, void*);
typedef int (CALLCONV *__nb_intfunc8__)(void*, void*, void*, void*, void*, void*, void*, void*);
typedef int (CALLCONV *__nb_intfunc9__)(void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef int (CALLCONV *__nb_intfunc10__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef int (CALLCONV *__nb_intfunc11__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef int (CALLCONV *__nb_intfunc12__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef int (CALLCONV *__nb_intfunc13__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef int (CALLCONV *__nb_intfunc14__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef int (CALLCONV *__nb_intfunc15__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef int (CALLCONV *__nb_intfunc16__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef float (CALLCONV *__nb_floatfunc0__)();
typedef float (CALLCONV *__nb_floatfunc1__)(void*);
typedef float (CALLCONV *__nb_floatfunc2__)(void*, void*);
typedef float (CALLCONV *__nb_floatfunc3__)(void*, void*, void*);
typedef float (CALLCONV *__nb_floatfunc4__)(void*, void*, void*, void*);
typedef float (CALLCONV *__nb_floatfunc5__)(void*, void*, void*, void*, void*);
typedef float (CALLCONV *__nb_floatfunc6__)(void*, void*, void*, void*, void*, void*);
typedef float (CALLCONV *__nb_floatfunc7__)(void*, void*, void*, void*, void*, void*, void*);
typedef float (CALLCONV *__nb_floatfunc8__)(void*, void*, void*, void*, void*, void*, void*, void*);
typedef float (CALLCONV *__nb_floatfunc9__)(void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef float (CALLCONV *__nb_floatfunc10__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef float (CALLCONV *__nb_floatfunc11__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef float (CALLCONV *__nb_floatfunc12__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef float (CALLCONV *__nb_floatfunc13__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef float (CALLCONV *__nb_floatfunc14__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef float (CALLCONV *__nb_floatfunc15__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef float (CALLCONV *__nb_floatfunc16__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef char* (CALLCONV *__nb_stringfunc0__)();
typedef char* (CALLCONV *__nb_stringfunc1__)(void*);
typedef char* (CALLCONV *__nb_stringfunc2__)(void*, void*);
typedef char* (CALLCONV *__nb_stringfunc3__)(void*, void*, void*);
typedef char* (CALLCONV *__nb_stringfunc4__)(void*, void*, void*, void*);
typedef char* (CALLCONV *__nb_stringfunc5__)(void*, void*, void*, void*, void*);
typedef char* (CALLCONV *__nb_stringfunc6__)(void*, void*, void*, void*, void*, void*);
typedef char* (CALLCONV *__nb_stringfunc7__)(void*, void*, void*, void*, void*, void*, void*);
typedef char* (CALLCONV *__nb_stringfunc8__)(void*, void*, void*, void*, void*, void*, void*, void*);
typedef char* (CALLCONV *__nb_stringfunc9__)(void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef char* (CALLCONV *__nb_stringfunc10__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef char* (CALLCONV *__nb_stringfunc11__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef char* (CALLCONV *__nb_stringfunc12__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef char* (CALLCONV *__nb_stringfunc13__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef char* (CALLCONV *__nb_stringfunc14__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef char* (CALLCONV *__nb_stringfunc15__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef char* (CALLCONV *__nb_stringfunc16__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void* (CALLCONV *__nb_objectfunc0__)();
typedef void* (CALLCONV *__nb_objectfunc1__)(void*);
typedef void* (CALLCONV *__nb_objectfunc2__)(void*, void*);
typedef void* (CALLCONV *__nb_objectfunc3__)(void*, void*, void*);
typedef void* (CALLCONV *__nb_objectfunc4__)(void*, void*, void*, void*);
typedef void* (CALLCONV *__nb_objectfunc5__)(void*, void*, void*, void*, void*);
typedef void* (CALLCONV *__nb_objectfunc6__)(void*, void*, void*, void*, void*, void*);
typedef void* (CALLCONV *__nb_objectfunc7__)(void*, void*, void*, void*, void*, void*, void*);
typedef void* (CALLCONV *__nb_objectfunc8__)(void*, void*, void*, void*, void*, void*, void*, void*);
typedef void* (CALLCONV *__nb_objectfunc9__)(void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void* (CALLCONV *__nb_objectfunc10__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void* (CALLCONV *__nb_objectfunc11__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void* (CALLCONV *__nb_objectfunc12__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void* (CALLCONV *__nb_objectfunc13__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void* (CALLCONV *__nb_objectfunc14__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void* (CALLCONV *__nb_objectfunc15__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void* (CALLCONV *__nb_objectfunc16__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void (*__nb_voidcfunc0__)();
typedef void (*__nb_voidcfunc1__)(void*);
typedef void (*__nb_voidcfunc2__)(void*, void*);
typedef void (*__nb_voidcfunc3__)(void*, void*, void*);
typedef void (*__nb_voidcfunc4__)(void*, void*, void*, void*);
typedef void (*__nb_voidcfunc5__)(void*, void*, void*, void*, void*);
typedef void (*__nb_voidcfunc6__)(void*, void*, void*, void*, void*, void*);
typedef void (*__nb_voidcfunc7__)(void*, void*, void*, void*, void*, void*, void*);
typedef void (*__nb_voidcfunc8__)(void*, void*, void*, void*, void*, void*, void*, void*);
typedef void (*__nb_voidcfunc9__)(void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void (*__nb_voidcfunc10__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void (*__nb_voidcfunc11__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void (*__nb_voidcfunc12__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void (*__nb_voidcfunc13__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void (*__nb_voidcfunc14__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void (*__nb_voidcfunc15__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void (*__nb_voidcfunc16__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef int (*__nb_intcfunc0__)();
typedef int (*__nb_intcfunc1__)(void*);
typedef int (*__nb_intcfunc2__)(void*, void*);
typedef int (*__nb_intcfunc3__)(void*, void*, void*);
typedef int (*__nb_intcfunc4__)(void*, void*, void*, void*);
typedef int (*__nb_intcfunc5__)(void*, void*, void*, void*, void*);
typedef int (*__nb_intcfunc6__)(void*, void*, void*, void*, void*, void*);
typedef int (*__nb_intcfunc7__)(void*, void*, void*, void*, void*, void*, void*);
typedef int (*__nb_intcfunc8__)(void*, void*, void*, void*, void*, void*, void*, void*);
typedef int (*__nb_intcfunc9__)(void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef int (*__nb_intcfunc10__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef int (*__nb_intcfunc11__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef int (*__nb_intcfunc12__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef int (*__nb_intcfunc13__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef int (*__nb_intcfunc14__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef int (*__nb_intcfunc15__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef int (*__nb_intcfunc16__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef float (*__nb_floatcfunc0__)();
typedef float (*__nb_floatcfunc1__)(void*);
typedef float (*__nb_floatcfunc2__)(void*, void*);
typedef float (*__nb_floatcfunc3__)(void*, void*, void*);
typedef float (*__nb_floatcfunc4__)(void*, void*, void*, void*);
typedef float (*__nb_floatcfunc5__)(void*, void*, void*, void*, void*);
typedef float (*__nb_floatcfunc6__)(void*, void*, void*, void*, void*, void*);
typedef float (*__nb_floatcfunc7__)(void*, void*, void*, void*, void*, void*, void*);
typedef float (*__nb_floatcfunc8__)(void*, void*, void*, void*, void*, void*, void*, void*);
typedef float (*__nb_floatcfunc9__)(void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef float (*__nb_floatcfunc10__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef float (*__nb_floatcfunc11__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef float (*__nb_floatcfunc12__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef float (*__nb_floatcfunc13__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef float (*__nb_floatcfunc14__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef float (*__nb_floatcfunc15__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef float (*__nb_floatcfunc16__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef char* (*__nb_stringcfunc0__)();
typedef char* (*__nb_stringcfunc1__)(void*);
typedef char* (*__nb_stringcfunc2__)(void*, void*);
typedef char* (*__nb_stringcfunc3__)(void*, void*, void*);
typedef char* (*__nb_stringcfunc4__)(void*, void*, void*, void*);
typedef char* (*__nb_stringcfunc5__)(void*, void*, void*, void*, void*);
typedef char* (*__nb_stringcfunc6__)(void*, void*, void*, void*, void*, void*);
typedef char* (*__nb_stringcfunc7__)(void*, void*, void*, void*, void*, void*, void*);
typedef char* (*__nb_stringcfunc8__)(void*, void*, void*, void*, void*, void*, void*, void*);
typedef char* (*__nb_stringcfunc9__)(void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef char* (*__nb_stringcfunc10__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef char* (*__nb_stringcfunc11__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef char* (*__nb_stringcfunc12__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef char* (*__nb_stringcfunc13__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef char* (*__nb_stringcfunc14__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef char* (*__nb_stringcfunc15__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef char* (*__nb_stringcfunc16__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void* (*__nb_objectcfunc0__)();
typedef void* (*__nb_objectcfunc1__)(void*);
typedef void* (*__nb_objectcfunc2__)(void*, void*);
typedef void* (*__nb_objectcfunc3__)(void*, void*, void*);
typedef void* (*__nb_objectcfunc4__)(void*, void*, void*, void*);
typedef void* (*__nb_objectcfunc5__)(void*, void*, void*, void*, void*);
typedef void* (*__nb_objectcfunc6__)(void*, void*, void*, void*, void*, void*);
typedef void* (*__nb_objectcfunc7__)(void*, void*, void*, void*, void*, void*, void*);
typedef void* (*__nb_objectcfunc8__)(void*, void*, void*, void*, void*, void*, void*, void*);
typedef void* (*__nb_objectcfunc9__)(void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void* (*__nb_objectcfunc10__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void* (*__nb_objectcfunc11__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void* (*__nb_objectcfunc12__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void* (*__nb_objectcfunc13__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void* (*__nb_objectcfunc14__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void* (*__nb_objectcfunc15__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);
typedef void* (*__nb_objectcfunc16__)(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*);

static void __nb_callvoidfunc0__(__nb_voidfunc0__ func) {
	func();
}

static void __nb_callvoidfunc1__(__nb_voidfunc1__ func, void* p0) {
	func(p0);
}

static void __nb_callvoidfunc2__(__nb_voidfunc2__ func, void* p0, void* p1) {
	func(p0, p1);
}

static void __nb_callvoidfunc3__(__nb_voidfunc3__ func, void* p0, void* p1, void* p2) {
	func(p0, p1, p2);
}

static void __nb_callvoidfunc4__(__nb_voidfunc4__ func, void* p0, void* p1, void* p2, void* p3) {
	func(p0, p1, p2, p3);
}

static void __nb_callvoidfunc5__(__nb_voidfunc5__ func, void* p0, void* p1, void* p2, void* p3, void* p4) {
	func(p0, p1, p2, p3, p4);
}

static void __nb_callvoidfunc6__(__nb_voidfunc6__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5) {
	func(p0, p1, p2, p3, p4, p5);
}

static void __nb_callvoidfunc7__(__nb_voidfunc7__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6) {
	func(p0, p1, p2, p3, p4, p5, p6);
}

static void __nb_callvoidfunc8__(__nb_voidfunc8__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7) {
	func(p0, p1, p2, p3, p4, p5, p6, p7);
}

static void __nb_callvoidfunc9__(__nb_voidfunc9__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8) {
	func(p0, p1, p2, p3, p4, p5, p6, p7, p8);
}

static void __nb_callvoidfunc10__(__nb_voidfunc10__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9) {
	func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
}

static void __nb_callvoidfunc11__(__nb_voidfunc11__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10) {
	func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
}

static void __nb_callvoidfunc12__(__nb_voidfunc12__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11) {
	func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
}

static void __nb_callvoidfunc13__(__nb_voidfunc13__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12) {
	func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12);
}

static void __nb_callvoidfunc14__(__nb_voidfunc14__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13) {
	func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13);
}

static void __nb_callvoidfunc15__(__nb_voidfunc15__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13, void* p14) {
	func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14);
}

static void __nb_callvoidfunc16__(__nb_voidfunc16__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13, void* p14, void* p15) {
	func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15);
}

static int __nb_callintfunc0__(__nb_intfunc0__ func) {
	return func();
}

static int __nb_callintfunc1__(__nb_intfunc1__ func, void* p0) {
	return func(p0);
}

static int __nb_callintfunc2__(__nb_intfunc2__ func, void* p0, void* p1) {
	return func(p0, p1);
}

static int __nb_callintfunc3__(__nb_intfunc3__ func, void* p0, void* p1, void* p2) {
	return func(p0, p1, p2);
}

static int __nb_callintfunc4__(__nb_intfunc4__ func, void* p0, void* p1, void* p2, void* p3) {
	return func(p0, p1, p2, p3);
}

static int __nb_callintfunc5__(__nb_intfunc5__ func, void* p0, void* p1, void* p2, void* p3, void* p4) {
	return func(p0, p1, p2, p3, p4);
}

static int __nb_callintfunc6__(__nb_intfunc6__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5) {
	return func(p0, p1, p2, p3, p4, p5);
}

static int __nb_callintfunc7__(__nb_intfunc7__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6) {
	return func(p0, p1, p2, p3, p4, p5, p6);
}

static int __nb_callintfunc8__(__nb_intfunc8__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7);
}

static int __nb_callintfunc9__(__nb_intfunc9__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8);
}

static int __nb_callintfunc10__(__nb_intfunc10__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
}

static int __nb_callintfunc11__(__nb_intfunc11__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
}

static int __nb_callintfunc12__(__nb_intfunc12__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
}

static int __nb_callintfunc13__(__nb_intfunc13__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12);
}

static int __nb_callintfunc14__(__nb_intfunc14__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13);
}

static int __nb_callintfunc15__(__nb_intfunc15__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13, void* p14) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14);
}

static int __nb_callintfunc16__(__nb_intfunc16__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13, void* p14, void* p15) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15);
}

static float __nb_callfloatfunc0__(__nb_floatfunc0__ func) {
	return func();
}

static float __nb_callfloatfunc1__(__nb_floatfunc1__ func, void* p0) {
	return func(p0);
}

static float __nb_callfloatfunc2__(__nb_floatfunc2__ func, void* p0, void* p1) {
	return func(p0, p1);
}

static float __nb_callfloatfunc3__(__nb_floatfunc3__ func, void* p0, void* p1, void* p2) {
	return func(p0, p1, p2);
}

static float __nb_callfloatfunc4__(__nb_floatfunc4__ func, void* p0, void* p1, void* p2, void* p3) {
	return func(p0, p1, p2, p3);
}

static float __nb_callfloatfunc5__(__nb_floatfunc5__ func, void* p0, void* p1, void* p2, void* p3, void* p4) {
	return func(p0, p1, p2, p3, p4);
}

static float __nb_callfloatfunc6__(__nb_floatfunc6__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5) {
	return func(p0, p1, p2, p3, p4, p5);
}

static float __nb_callfloatfunc7__(__nb_floatfunc7__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6) {
	return func(p0, p1, p2, p3, p4, p5, p6);
}

static float __nb_callfloatfunc8__(__nb_floatfunc8__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7);
}

static float __nb_callfloatfunc9__(__nb_floatfunc9__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8);
}

static float __nb_callfloatfunc10__(__nb_floatfunc10__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
}

static float __nb_callfloatfunc11__(__nb_floatfunc11__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
}

static float __nb_callfloatfunc12__(__nb_floatfunc12__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
}

static float __nb_callfloatfunc13__(__nb_floatfunc13__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12);
}

static float __nb_callfloatfunc14__(__nb_floatfunc14__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13);
}

static float __nb_callfloatfunc15__(__nb_floatfunc15__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13, void* p14) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14);
}

static float __nb_callfloatfunc16__(__nb_floatfunc16__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13, void* p14, void* p15) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15);
}

static char* __nb_callstringfunc0__(__nb_stringfunc0__ func) {
	return func();
}

static char* __nb_callstringfunc1__(__nb_stringfunc1__ func, void* p0) {
	return func(p0);
}

static char* __nb_callstringfunc2__(__nb_stringfunc2__ func, void* p0, void* p1) {
	return func(p0, p1);
}

static char* __nb_callstringfunc3__(__nb_stringfunc3__ func, void* p0, void* p1, void* p2) {
	return func(p0, p1, p2);
}

static char* __nb_callstringfunc4__(__nb_stringfunc4__ func, void* p0, void* p1, void* p2, void* p3) {
	return func(p0, p1, p2, p3);
}

static char* __nb_callstringfunc5__(__nb_stringfunc5__ func, void* p0, void* p1, void* p2, void* p3, void* p4) {
	return func(p0, p1, p2, p3, p4);
}

static char* __nb_callstringfunc6__(__nb_stringfunc6__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5) {
	return func(p0, p1, p2, p3, p4, p5);
}

static char* __nb_callstringfunc7__(__nb_stringfunc7__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6) {
	return func(p0, p1, p2, p3, p4, p5, p6);
}

static char* __nb_callstringfunc8__(__nb_stringfunc8__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7);
}

static char* __nb_callstringfunc9__(__nb_stringfunc9__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8);
}

static char* __nb_callstringfunc10__(__nb_stringfunc10__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
}

static char* __nb_callstringfunc11__(__nb_stringfunc11__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
}

static char* __nb_callstringfunc12__(__nb_stringfunc12__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
}

static char* __nb_callstringfunc13__(__nb_stringfunc13__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12);
}

static char* __nb_callstringfunc14__(__nb_stringfunc14__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13);
}

static char* __nb_callstringfunc15__(__nb_stringfunc15__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13, void* p14) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14);
}

static char* __nb_callstringfunc16__(__nb_stringfunc16__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13, void* p14, void* p15) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15);
}

static void* __nb_callobjectfunc0__(__nb_objectfunc0__ func) {
	return func();
}

static void* __nb_callobjectfunc1__(__nb_objectfunc1__ func, void* p0) {
	return func(p0);
}

static void* __nb_callobjectfunc2__(__nb_objectfunc2__ func, void* p0, void* p1) {
	return func(p0, p1);
}

static void* __nb_callobjectfunc3__(__nb_objectfunc3__ func, void* p0, void* p1, void* p2) {
	return func(p0, p1, p2);
}

static void* __nb_callobjectfunc4__(__nb_objectfunc4__ func, void* p0, void* p1, void* p2, void* p3) {
	return func(p0, p1, p2, p3);
}

static void* __nb_callobjectfunc5__(__nb_objectfunc5__ func, void* p0, void* p1, void* p2, void* p3, void* p4) {
	return func(p0, p1, p2, p3, p4);
}

static void* __nb_callobjectfunc6__(__nb_objectfunc6__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5) {
	return func(p0, p1, p2, p3, p4, p5);
}

static void* __nb_callobjectfunc7__(__nb_objectfunc7__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6) {
	return func(p0, p1, p2, p3, p4, p5, p6);
}

static void* __nb_callobjectfunc8__(__nb_objectfunc8__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7);
}

static void* __nb_callobjectfunc9__(__nb_objectfunc9__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8);
}

static void* __nb_callobjectfunc10__(__nb_objectfunc10__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
}

static void* __nb_callobjectfunc11__(__nb_objectfunc11__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
}

static void* __nb_callobjectfunc12__(__nb_objectfunc12__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
}

static void* __nb_callobjectfunc13__(__nb_objectfunc13__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12);
}

static void* __nb_callobjectfunc14__(__nb_objectfunc14__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13);
}

static void* __nb_callobjectfunc15__(__nb_objectfunc15__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13, void* p14) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14);
}

static void* __nb_callobjectfunc16__(__nb_objectfunc16__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13, void* p14, void* p15) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15);
}

static void __nb_callvoidcfunc0__(__nb_voidcfunc0__ func) {
	func();
}

static void __nb_callvoidcfunc1__(__nb_voidcfunc1__ func, void* p0) {
	func(p0);
}

static void __nb_callvoidcfunc2__(__nb_voidcfunc2__ func, void* p0, void* p1) {
	func(p0, p1);
}

static void __nb_callvoidcfunc3__(__nb_voidcfunc3__ func, void* p0, void* p1, void* p2) {
	func(p0, p1, p2);
}

static void __nb_callvoidcfunc4__(__nb_voidcfunc4__ func, void* p0, void* p1, void* p2, void* p3) {
	func(p0, p1, p2, p3);
}

static void __nb_callvoidcfunc5__(__nb_voidcfunc5__ func, void* p0, void* p1, void* p2, void* p3, void* p4) {
	func(p0, p1, p2, p3, p4);
}

static void __nb_callvoidcfunc6__(__nb_voidcfunc6__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5) {
	func(p0, p1, p2, p3, p4, p5);
}

static void __nb_callvoidcfunc7__(__nb_voidcfunc7__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6) {
	func(p0, p1, p2, p3, p4, p5, p6);
}

static void __nb_callvoidcfunc8__(__nb_voidcfunc8__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7) {
	func(p0, p1, p2, p3, p4, p5, p6, p7);
}

static void __nb_callvoidcfunc9__(__nb_voidcfunc9__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8) {
	func(p0, p1, p2, p3, p4, p5, p6, p7, p8);
}

static void __nb_callvoidcfunc10__(__nb_voidcfunc10__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9) {
	func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
}

static void __nb_callvoidcfunc11__(__nb_voidcfunc11__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10) {
	func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
}

static void __nb_callvoidcfunc12__(__nb_voidcfunc12__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11) {
	func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
}

static void __nb_callvoidcfunc13__(__nb_voidcfunc13__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12) {
	func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12);
}

static void __nb_callvoidcfunc14__(__nb_voidcfunc14__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13) {
	func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13);
}

static void __nb_callvoidcfunc15__(__nb_voidcfunc15__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13, void* p14) {
	func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14);
}

static void __nb_callvoidcfunc16__(__nb_voidcfunc16__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13, void* p14, void* p15) {
	func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15);
}

static int __nb_callintcfunc0__(__nb_intcfunc0__ func) {
	return func();
}

static int __nb_callintcfunc1__(__nb_intcfunc1__ func, void* p0) {
	return func(p0);
}

static int __nb_callintcfunc2__(__nb_intcfunc2__ func, void* p0, void* p1) {
	return func(p0, p1);
}

static int __nb_callintcfunc3__(__nb_intcfunc3__ func, void* p0, void* p1, void* p2) {
	return func(p0, p1, p2);
}

static int __nb_callintcfunc4__(__nb_intcfunc4__ func, void* p0, void* p1, void* p2, void* p3) {
	return func(p0, p1, p2, p3);
}

static int __nb_callintcfunc5__(__nb_intcfunc5__ func, void* p0, void* p1, void* p2, void* p3, void* p4) {
	return func(p0, p1, p2, p3, p4);
}

static int __nb_callintcfunc6__(__nb_intcfunc6__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5) {
	return func(p0, p1, p2, p3, p4, p5);
}

static int __nb_callintcfunc7__(__nb_intcfunc7__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6) {
	return func(p0, p1, p2, p3, p4, p5, p6);
}

static int __nb_callintcfunc8__(__nb_intcfunc8__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7);
}

static int __nb_callintcfunc9__(__nb_intcfunc9__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8);
}

static int __nb_callintcfunc10__(__nb_intcfunc10__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
}

static int __nb_callintcfunc11__(__nb_intcfunc11__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
}

static int __nb_callintcfunc12__(__nb_intcfunc12__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
}

static int __nb_callintcfunc13__(__nb_intcfunc13__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12);
}

static int __nb_callintcfunc14__(__nb_intcfunc14__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13);
}

static int __nb_callintcfunc15__(__nb_intcfunc15__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13, void* p14) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14);
}

static int __nb_callintcfunc16__(__nb_intcfunc16__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13, void* p14, void* p15) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15);
}

static float __nb_callfloatcfunc0__(__nb_floatcfunc0__ func) {
	return func();
}

static float __nb_callfloatcfunc1__(__nb_floatcfunc1__ func, void* p0) {
	return func(p0);
}

static float __nb_callfloatcfunc2__(__nb_floatcfunc2__ func, void* p0, void* p1) {
	return func(p0, p1);
}

static float __nb_callfloatcfunc3__(__nb_floatcfunc3__ func, void* p0, void* p1, void* p2) {
	return func(p0, p1, p2);
}

static float __nb_callfloatcfunc4__(__nb_floatcfunc4__ func, void* p0, void* p1, void* p2, void* p3) {
	return func(p0, p1, p2, p3);
}

static float __nb_callfloatcfunc5__(__nb_floatcfunc5__ func, void* p0, void* p1, void* p2, void* p3, void* p4) {
	return func(p0, p1, p2, p3, p4);
}

static float __nb_callfloatcfunc6__(__nb_floatcfunc6__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5) {
	return func(p0, p1, p2, p3, p4, p5);
}

static float __nb_callfloatcfunc7__(__nb_floatcfunc7__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6) {
	return func(p0, p1, p2, p3, p4, p5, p6);
}

static float __nb_callfloatcfunc8__(__nb_floatcfunc8__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7);
}

static float __nb_callfloatcfunc9__(__nb_floatcfunc9__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8);
}

static float __nb_callfloatcfunc10__(__nb_floatcfunc10__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
}

static float __nb_callfloatcfunc11__(__nb_floatcfunc11__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
}

static float __nb_callfloatcfunc12__(__nb_floatcfunc12__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
}

static float __nb_callfloatcfunc13__(__nb_floatcfunc13__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12);
}

static float __nb_callfloatcfunc14__(__nb_floatcfunc14__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13);
}

static float __nb_callfloatcfunc15__(__nb_floatcfunc15__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13, void* p14) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14);
}

static float __nb_callfloatcfunc16__(__nb_floatcfunc16__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13, void* p14, void* p15) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15);
}

static char* __nb_callstringcfunc0__(__nb_stringcfunc0__ func) {
	return func();
}

static char* __nb_callstringcfunc1__(__nb_stringcfunc1__ func, void* p0) {
	return func(p0);
}

static char* __nb_callstringcfunc2__(__nb_stringcfunc2__ func, void* p0, void* p1) {
	return func(p0, p1);
}

static char* __nb_callstringcfunc3__(__nb_stringcfunc3__ func, void* p0, void* p1, void* p2) {
	return func(p0, p1, p2);
}

static char* __nb_callstringcfunc4__(__nb_stringcfunc4__ func, void* p0, void* p1, void* p2, void* p3) {
	return func(p0, p1, p2, p3);
}

static char* __nb_callstringcfunc5__(__nb_stringcfunc5__ func, void* p0, void* p1, void* p2, void* p3, void* p4) {
	return func(p0, p1, p2, p3, p4);
}

static char* __nb_callstringcfunc6__(__nb_stringcfunc6__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5) {
	return func(p0, p1, p2, p3, p4, p5);
}

static char* __nb_callstringcfunc7__(__nb_stringcfunc7__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6) {
	return func(p0, p1, p2, p3, p4, p5, p6);
}

static char* __nb_callstringcfunc8__(__nb_stringcfunc8__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7);
}

static char* __nb_callstringcfunc9__(__nb_stringcfunc9__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8);
}

static char* __nb_callstringcfunc10__(__nb_stringcfunc10__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
}

static char* __nb_callstringcfunc11__(__nb_stringcfunc11__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
}

static char* __nb_callstringcfunc12__(__nb_stringcfunc12__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
}

static char* __nb_callstringcfunc13__(__nb_stringcfunc13__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12);
}

static char* __nb_callstringcfunc14__(__nb_stringcfunc14__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13);
}

static char* __nb_callstringcfunc15__(__nb_stringcfunc15__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13, void* p14) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14);
}

static char* __nb_callstringcfunc16__(__nb_stringcfunc16__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13, void* p14, void* p15) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15);
}

static void* __nb_callobjectcfunc0__(__nb_objectcfunc0__ func) {
	return func();
}

static void* __nb_callobjectcfunc1__(__nb_objectcfunc1__ func, void* p0) {
	return func(p0);
}

static void* __nb_callobjectcfunc2__(__nb_objectcfunc2__ func, void* p0, void* p1) {
	return func(p0, p1);
}

static void* __nb_callobjectcfunc3__(__nb_objectcfunc3__ func, void* p0, void* p1, void* p2) {
	return func(p0, p1, p2);
}

static void* __nb_callobjectcfunc4__(__nb_objectcfunc4__ func, void* p0, void* p1, void* p2, void* p3) {
	return func(p0, p1, p2, p3);
}

static void* __nb_callobjectcfunc5__(__nb_objectcfunc5__ func, void* p0, void* p1, void* p2, void* p3, void* p4) {
	return func(p0, p1, p2, p3, p4);
}

static void* __nb_callobjectcfunc6__(__nb_objectcfunc6__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5) {
	return func(p0, p1, p2, p3, p4, p5);
}

static void* __nb_callobjectcfunc7__(__nb_objectcfunc7__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6) {
	return func(p0, p1, p2, p3, p4, p5, p6);
}

static void* __nb_callobjectcfunc8__(__nb_objectcfunc8__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7);
}

static void* __nb_callobjectcfunc9__(__nb_objectcfunc9__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8);
}

static void* __nb_callobjectcfunc10__(__nb_objectcfunc10__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9);
}

static void* __nb_callobjectcfunc11__(__nb_objectcfunc11__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
}

static void* __nb_callobjectcfunc12__(__nb_objectcfunc12__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
}

static void* __nb_callobjectcfunc13__(__nb_objectcfunc13__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12);
}

static void* __nb_callobjectcfunc14__(__nb_objectcfunc14__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13);
}

static void* __nb_callobjectcfunc15__(__nb_objectcfunc15__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13, void* p14) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14);
}

static void* __nb_callobjectcfunc16__(__nb_objectcfunc16__ func, void* p0, void* p1, void* p2, void* p3, void* p4, void* p5, void* p6, void* p7, void* p8, void* p9, void* p10, void* p11, void* p12, void* p13, void* p14, void* p15) {
	return func(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15);
}

static void __nb_InitLibraryStack__() {
    if ( __nb_libStack__ == 0 ) {
        __nb_libStack__ = CreateArray();
    }
}

EXPORT void* CALL LoadLibrary(string libname) {
	return plat_LoadLibrary(libname);
}

EXPORT void CALL FreeLibrary(void* lib) {
    plat_FreeLibrary(lib);
}

EXPORT void* CALL LibraryFunction(void* lib, string funcname) {
	return plat_LibraryFunction(lib, funcname);
}

EXPORT void CALL PushLibraryInt(int val) {
    __nb_InitLibraryStack__();
    ArrayAddInt(__nb_libStack__, val);
}

EXPORT void CALL PushLibraryFloat(float val) {
    __nb_InitLibraryStack__();
    ArrayAddFloat(__nb_libStack__, val);
}

EXPORT void CALL PushLibraryString(string str) {
    __nb_InitLibraryStack__();
    ArrayAddString(__nb_libStack__, str);
}

EXPORT void CALL PushLibraryObject(void* obj) {
    __nb_InitLibraryStack__();
    ArrayAddObject(__nb_libStack__, obj);
}

EXPORT void CALL CallVoidFunction(void* func) {
    int i;
    void* p[16];

    // Pop params from stack
    __nb_InitLibraryStack__();
    for ( i = 0; i < CountArray(__nb_libStack__); i++ ) {
        p[i] = ArrayObject(__nb_libStack__, i);
    }

    // Call proper function
    switch ( CountArray(__nb_libStack__) ) {
    case 0:
        __nb_callvoidfunc0__((__nb_voidfunc0__)func);
        break;
    case 1:
        __nb_callvoidfunc1__((__nb_voidfunc1__)func, p[0]);
        break;
    case 2:
        __nb_callvoidfunc2__((__nb_voidfunc2__)func, p[0], p[1]);
        break;
    case 3:
        __nb_callvoidfunc3__((__nb_voidfunc3__)func, p[0], p[1], p[2]);
        break;
    case 4:
        __nb_callvoidfunc4__((__nb_voidfunc4__)func, p[0], p[1], p[2], p[3]);
        break;
    case 5:
        __nb_callvoidfunc5__((__nb_voidfunc5__)func, p[0], p[1], p[2], p[3], p[4]);
        break;
    case 6:
        __nb_callvoidfunc6__((__nb_voidfunc6__)func, p[0], p[1], p[2], p[3], p[4], p[5]);
        break;
    case 7:
        __nb_callvoidfunc7__((__nb_voidfunc7__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6]);
        break;
    case 8:
        __nb_callvoidfunc8__((__nb_voidfunc8__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
        break;
    case 9:
        __nb_callvoidfunc9__((__nb_voidfunc9__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
        break;
    case 10:
        __nb_callvoidfunc10__((__nb_voidfunc10__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9]);
        break;
    case 11:
        __nb_callvoidfunc11__((__nb_voidfunc11__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10]);
        break;
    case 12:
        __nb_callvoidfunc12__((__nb_voidfunc12__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11]);
        break;
    case 13:
        __nb_callvoidfunc13__((__nb_voidfunc13__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12]);
        break;
    case 14:
        __nb_callvoidfunc14__((__nb_voidfunc14__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13]);
        break;
    case 15:
        __nb_callvoidfunc15__((__nb_voidfunc15__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13], p[14]);
        break;
    case 16:
        __nb_callvoidfunc16__((__nb_voidfunc16__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13], p[14], p[15]);
        break;
    }

    // Clear library stack
    ClearArray(__nb_libStack__);
}

EXPORT int CALL CallIntFunction(void* func) {
    int i;
    void* p[16];
	int ret = 0;

    // Pop params from stack
    __nb_InitLibraryStack__();
    for ( i = 0; i < CountArray(__nb_libStack__); i++ ) {
        p[i] = ArrayObject(__nb_libStack__, i);
    }

    // Call proper function
    switch ( CountArray(__nb_libStack__) ) {
    case 0:
        ret = __nb_callintfunc0__((__nb_intfunc0__)func);
        break;
    case 1:
        ret = __nb_callintfunc1__((__nb_intfunc1__)func, p[0]);
        break;
    case 2:
        ret = __nb_callintfunc2__((__nb_intfunc2__)func, p[0], p[1]);
        break;
    case 3:
        ret = __nb_callintfunc3__((__nb_intfunc3__)func, p[0], p[1], p[2]);
        break;
    case 4:
        ret = __nb_callintfunc4__((__nb_intfunc4__)func, p[0], p[1], p[2], p[3]);
        break;
    case 5:
        ret = __nb_callintfunc5__((__nb_intfunc5__)func, p[0], p[1], p[2], p[3], p[4]);
        break;
    case 6:
        ret = __nb_callintfunc6__((__nb_intfunc6__)func, p[0], p[1], p[2], p[3], p[4], p[5]);
        break;
    case 7:
        ret = __nb_callintfunc7__((__nb_intfunc7__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6]);
        break;
    case 8:
        ret = __nb_callintfunc8__((__nb_intfunc8__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
        break;
    case 9:
        ret = __nb_callintfunc9__((__nb_intfunc9__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
        break;
    case 10:
        ret = __nb_callintfunc10__((__nb_intfunc10__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9]);
        break;
    case 11:
        ret = __nb_callintfunc11__((__nb_intfunc11__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10]);
        break;
    case 12:
        ret = __nb_callintfunc12__((__nb_intfunc12__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11]);
        break;
    case 13:
        ret = __nb_callintfunc13__((__nb_intfunc13__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12]);
        break;
    case 14:
        ret = __nb_callintfunc14__((__nb_intfunc14__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13]);
        break;
    case 15:
        ret = __nb_callintfunc15__((__nb_intfunc15__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13], p[14]);
        break;
    case 16:
        ret = __nb_callintfunc16__((__nb_intfunc16__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13], p[14], p[15]);
        break;
    }

    // Clear library stack
    ClearArray(__nb_libStack__);

    return ret;
}

EXPORT float CALL CallFloatFunction(void* func) {
    int i;
    void* p[16];
	float ret = 0.0f;

    // Pop params from stack
    __nb_InitLibraryStack__();
    for ( i = 0; i < CountArray(__nb_libStack__); i++ ) {
        p[i] = ArrayObject(__nb_libStack__, i);
    }

    // Call proper function
    switch ( CountArray(__nb_libStack__) ) {
    case 0:
        ret = __nb_callfloatfunc0__((__nb_floatfunc0__)func);
        break;
    case 1:
        ret = __nb_callfloatfunc1__((__nb_floatfunc1__)func, p[0]);
        break;
    case 2:
        ret = __nb_callfloatfunc2__((__nb_floatfunc2__)func, p[0], p[1]);
        break;
    case 3:
        ret = __nb_callfloatfunc3__((__nb_floatfunc3__)func, p[0], p[1], p[2]);
        break;
    case 4:
        ret = __nb_callfloatfunc4__((__nb_floatfunc4__)func, p[0], p[1], p[2], p[3]);
        break;
    case 5:
        ret = __nb_callfloatfunc5__((__nb_floatfunc5__)func, p[0], p[1], p[2], p[3], p[4]);
        break;
    case 6:
        ret = __nb_callfloatfunc6__((__nb_floatfunc6__)func, p[0], p[1], p[2], p[3], p[4], p[5]);
        break;
    case 7:
        ret = __nb_callfloatfunc7__((__nb_floatfunc7__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6]);
        break;
    case 8:
        ret = __nb_callfloatfunc8__((__nb_floatfunc8__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
        break;
    case 9:
        ret = __nb_callfloatfunc9__((__nb_floatfunc9__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
        break;
    case 10:
        ret = __nb_callfloatfunc10__((__nb_floatfunc10__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9]);
        break;
    case 11:
        ret = __nb_callfloatfunc11__((__nb_floatfunc11__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10]);
        break;
    case 12:
        ret = __nb_callfloatfunc12__((__nb_floatfunc12__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11]);
        break;
    case 13:
        ret = __nb_callfloatfunc13__((__nb_floatfunc13__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12]);
        break;
    case 14:
        ret = __nb_callfloatfunc14__((__nb_floatfunc14__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13]);
        break;
    case 15:
        ret = __nb_callfloatfunc15__((__nb_floatfunc15__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13], p[14]);
        break;
    case 16:
        ret = __nb_callfloatfunc16__((__nb_floatfunc16__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13], p[14], p[15]);
        break;
    }

    // Clear library stack
    ClearArray(__nb_libStack__);

    return ret;
}

EXPORT string CALL CallStringFunction(void* func) {
    int i;
    void* p[16];
	char* ret = '\0';

    // Pop params from stack
    __nb_InitLibraryStack__();
    for ( i = 0; i < CountArray(__nb_libStack__); i++ ) {
        p[i] = ArrayObject(__nb_libStack__, i);
    }

    // Call proper function
    switch ( CountArray(__nb_libStack__) ) {
    case 0:
        ret = __nb_callstringfunc0__((__nb_stringfunc0__)func);
        break;
    case 1:
        ret = __nb_callstringfunc1__((__nb_stringfunc1__)func, p[0]);
        break;
    case 2:
        ret = __nb_callstringfunc2__((__nb_stringfunc2__)func, p[0], p[1]);
        break;
    case 3:
        ret = __nb_callstringfunc3__((__nb_stringfunc3__)func, p[0], p[1], p[2]);
        break;
    case 4:
        ret = __nb_callstringfunc4__((__nb_stringfunc4__)func, p[0], p[1], p[2], p[3]);
        break;
    case 5:
        ret = __nb_callstringfunc5__((__nb_stringfunc5__)func, p[0], p[1], p[2], p[3], p[4]);
        break;
    case 6:
        ret = __nb_callstringfunc6__((__nb_stringfunc6__)func, p[0], p[1], p[2], p[3], p[4], p[5]);
        break;
    case 7:
        ret = __nb_callstringfunc7__((__nb_stringfunc7__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6]);
        break;
    case 8:
        ret = __nb_callstringfunc8__((__nb_stringfunc8__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
        break;
    case 9:
        ret = __nb_callstringfunc9__((__nb_stringfunc9__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
        break;
    case 10:
        ret = __nb_callstringfunc10__((__nb_stringfunc10__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9]);
        break;
    case 11:
        ret = __nb_callstringfunc11__((__nb_stringfunc11__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10]);
        break;
    case 12:
        ret = __nb_callstringfunc12__((__nb_stringfunc12__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11]);
        break;
    case 13:
        ret = __nb_callstringfunc13__((__nb_stringfunc13__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12]);
        break;
    case 14:
        ret = __nb_callstringfunc14__((__nb_stringfunc14__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13]);
        break;
    case 15:
        ret = __nb_callstringfunc15__((__nb_stringfunc15__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13], p[14]);
        break;
    case 16:
        ret = __nb_callstringfunc16__((__nb_stringfunc16__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13], p[14], p[15]);
        break;
    }

    // Clear library stack
    ClearArray(__nb_libStack__);

	return string(ret);
}

EXPORT void* CALL CallObjectFunction(void* func) {
    int i;
    void* p[16];
	void* ret = NULL;

    // Pop params from stack
    __nb_InitLibraryStack__();
    for ( i = 0; i < CountArray(__nb_libStack__); i++ ) {
        p[i] = ArrayObject(__nb_libStack__, i);
    }

    // Call proper function
    switch ( CountArray(__nb_libStack__) ) {
    case 0:
        ret = __nb_callobjectfunc0__((__nb_objectfunc0__)func);
        break;
    case 1:
        ret = __nb_callobjectfunc1__((__nb_objectfunc1__)func, p[0]);
        break;
    case 2:
        ret = __nb_callobjectfunc2__((__nb_objectfunc2__)func, p[0], p[1]);
        break;
    case 3:
        ret = __nb_callobjectfunc3__((__nb_objectfunc3__)func, p[0], p[1], p[2]);
        break;
    case 4:
        ret = __nb_callobjectfunc4__((__nb_objectfunc4__)func, p[0], p[1], p[2], p[3]);
        break;
    case 5:
        ret = __nb_callobjectfunc5__((__nb_objectfunc5__)func, p[0], p[1], p[2], p[3], p[4]);
        break;
    case 6:
        ret = __nb_callobjectfunc6__((__nb_objectfunc6__)func, p[0], p[1], p[2], p[3], p[4], p[5]);
        break;
    case 7:
        ret = __nb_callobjectfunc7__((__nb_objectfunc7__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6]);
        break;
    case 8:
        ret = __nb_callobjectfunc8__((__nb_objectfunc8__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
        break;
    case 9:
        ret = __nb_callobjectfunc9__((__nb_objectfunc9__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
        break;
    case 10:
        ret = __nb_callobjectfunc10__((__nb_objectfunc10__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9]);
        break;
    case 11:
        ret = __nb_callobjectfunc11__((__nb_objectfunc11__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10]);
        break;
    case 12:
        ret = __nb_callobjectfunc12__((__nb_objectfunc12__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11]);
        break;
    case 13:
        ret = __nb_callobjectfunc13__((__nb_objectfunc13__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12]);
        break;
    case 14:
        ret = __nb_callobjectfunc14__((__nb_objectfunc14__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13]);
        break;
    case 15:
        ret = __nb_callobjectfunc15__((__nb_objectfunc15__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13], p[14]);
        break;
    case 16:
        ret = __nb_callobjectfunc16__((__nb_objectfunc16__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13], p[14], p[15]);
        break;
    }

    // Clear library stack
    ClearArray(__nb_libStack__);

    return ret;
}


























EXPORT void CALL CallVoidCFunction(void* func) {
    int i;
    void* p[16];

    // Pop params from stack
    __nb_InitLibraryStack__();
    for ( i = 0; i < CountArray(__nb_libStack__); i++ ) {
        p[i] = ArrayObject(__nb_libStack__, i);
    }

    // Call proper function
    switch ( CountArray(__nb_libStack__) ) {
    case 0:
        __nb_callvoidcfunc0__((__nb_voidcfunc0__)func);
        break;
    case 1:
        __nb_callvoidcfunc1__((__nb_voidcfunc1__)func, p[0]);
        break;
    case 2:
        __nb_callvoidcfunc2__((__nb_voidcfunc2__)func, p[0], p[1]);
        break;
    case 3:
        __nb_callvoidcfunc3__((__nb_voidcfunc3__)func, p[0], p[1], p[2]);
        break;
    case 4:
        __nb_callvoidcfunc4__((__nb_voidcfunc4__)func, p[0], p[1], p[2], p[3]);
        break;
    case 5:
        __nb_callvoidcfunc5__((__nb_voidcfunc5__)func, p[0], p[1], p[2], p[3], p[4]);
        break;
    case 6:
        __nb_callvoidcfunc6__((__nb_voidcfunc6__)func, p[0], p[1], p[2], p[3], p[4], p[5]);
        break;
    case 7:
        __nb_callvoidcfunc7__((__nb_voidcfunc7__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6]);
        break;
    case 8:
        __nb_callvoidcfunc8__((__nb_voidcfunc8__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
        break;
    case 9:
        __nb_callvoidcfunc9__((__nb_voidcfunc9__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
        break;
    case 10:
        __nb_callvoidcfunc10__((__nb_voidcfunc10__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9]);
        break;
    case 11:
        __nb_callvoidcfunc11__((__nb_voidcfunc11__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10]);
        break;
    case 12:
        __nb_callvoidcfunc12__((__nb_voidcfunc12__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11]);
        break;
    case 13:
        __nb_callvoidcfunc13__((__nb_voidcfunc13__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12]);
        break;
    case 14:
        __nb_callvoidcfunc14__((__nb_voidcfunc14__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13]);
        break;
    case 15:
        __nb_callvoidcfunc15__((__nb_voidcfunc15__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13], p[14]);
        break;
    case 16:
        __nb_callvoidcfunc16__((__nb_voidcfunc16__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13], p[14], p[15]);
        break;
    }

    // Clear library stack
    ClearArray(__nb_libStack__);
}

EXPORT int CALL CallIntCFunction(void* func) {
    int i;
    void* p[16];
	int ret = 0;

    // Pop params from stack
    __nb_InitLibraryStack__();
    for ( i = 0; i < CountArray(__nb_libStack__); i++ ) {
        p[i] = ArrayObject(__nb_libStack__, i);
    }

    // Call proper function
    switch ( CountArray(__nb_libStack__) ) {
    case 0:
        ret = __nb_callintcfunc0__((__nb_intcfunc0__)func);
        break;
    case 1:
        ret = __nb_callintcfunc1__((__nb_intcfunc1__)func, p[0]);
        break;
    case 2:
        ret = __nb_callintcfunc2__((__nb_intcfunc2__)func, p[0], p[1]);
        break;
    case 3:
        ret = __nb_callintcfunc3__((__nb_intcfunc3__)func, p[0], p[1], p[2]);
        break;
    case 4:
        ret = __nb_callintcfunc4__((__nb_intcfunc4__)func, p[0], p[1], p[2], p[3]);
        break;
    case 5:
        ret = __nb_callintcfunc5__((__nb_intcfunc5__)func, p[0], p[1], p[2], p[3], p[4]);
        break;
    case 6:
        ret = __nb_callintcfunc6__((__nb_intcfunc6__)func, p[0], p[1], p[2], p[3], p[4], p[5]);
        break;
    case 7:
        ret = __nb_callintcfunc7__((__nb_intcfunc7__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6]);
        break;
    case 8:
        ret = __nb_callintcfunc8__((__nb_intcfunc8__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
        break;
    case 9:
        ret = __nb_callintcfunc9__((__nb_intcfunc9__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
        break;
    case 10:
        ret = __nb_callintcfunc10__((__nb_intcfunc10__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9]);
        break;
    case 11:
        ret = __nb_callintcfunc11__((__nb_intcfunc11__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10]);
        break;
    case 12:
        ret = __nb_callintcfunc12__((__nb_intcfunc12__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11]);
        break;
    case 13:
        ret = __nb_callintcfunc13__((__nb_intcfunc13__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12]);
        break;
    case 14:
        ret = __nb_callintcfunc14__((__nb_intcfunc14__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13]);
        break;
    case 15:
        ret = __nb_callintcfunc15__((__nb_intcfunc15__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13], p[14]);
        break;
    case 16:
        ret = __nb_callintcfunc16__((__nb_intcfunc16__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13], p[14], p[15]);
        break;
    }

    // Clear library stack
    ClearArray(__nb_libStack__);

    return ret;
}

EXPORT float CALL CallFloatCFunction(void* func) {
    int i;
    void* p[16];
	float ret = 0.0f;

    // Pop params from stack
    __nb_InitLibraryStack__();
    for ( i = 0; i < CountArray(__nb_libStack__); i++ ) {
        p[i] = ArrayObject(__nb_libStack__, i);
    }

    // Call proper function
    switch ( CountArray(__nb_libStack__) ) {
    case 0:
        ret = __nb_callfloatcfunc0__((__nb_floatcfunc0__)func);
        break;
    case 1:
        ret = __nb_callfloatcfunc1__((__nb_floatcfunc1__)func, p[0]);
        break;
    case 2:
        ret = __nb_callfloatcfunc2__((__nb_floatcfunc2__)func, p[0], p[1]);
        break;
    case 3:
        ret = __nb_callfloatcfunc3__((__nb_floatcfunc3__)func, p[0], p[1], p[2]);
        break;
    case 4:
        ret = __nb_callfloatcfunc4__((__nb_floatcfunc4__)func, p[0], p[1], p[2], p[3]);
        break;
    case 5:
        ret = __nb_callfloatcfunc5__((__nb_floatcfunc5__)func, p[0], p[1], p[2], p[3], p[4]);
        break;
    case 6:
        ret = __nb_callfloatcfunc6__((__nb_floatcfunc6__)func, p[0], p[1], p[2], p[3], p[4], p[5]);
        break;
    case 7:
        ret = __nb_callfloatcfunc7__((__nb_floatcfunc7__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6]);
        break;
    case 8:
        ret = __nb_callfloatcfunc8__((__nb_floatcfunc8__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
        break;
    case 9:
        ret = __nb_callfloatcfunc9__((__nb_floatcfunc9__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
        break;
    case 10:
        ret = __nb_callfloatcfunc10__((__nb_floatcfunc10__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9]);
        break;
    case 11:
        ret = __nb_callfloatcfunc11__((__nb_floatcfunc11__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10]);
        break;
    case 12:
        ret = __nb_callfloatcfunc12__((__nb_floatcfunc12__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11]);
        break;
    case 13:
        ret = __nb_callfloatcfunc13__((__nb_floatcfunc13__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12]);
        break;
    case 14:
        ret = __nb_callfloatcfunc14__((__nb_floatcfunc14__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13]);
        break;
    case 15:
        ret = __nb_callfloatcfunc15__((__nb_floatcfunc15__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13], p[14]);
        break;
    case 16:
        ret = __nb_callfloatcfunc16__((__nb_floatcfunc16__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13], p[14], p[15]);
        break;
    }

    // Clear library stack
    ClearArray(__nb_libStack__);

    return ret;
}

EXPORT string CALL CallStringCFunction(void* func) {
    int i;
    void* p[16];
	char* ret = '\0';

    // Pop params from stack
    __nb_InitLibraryStack__();
    for ( i = 0; i < CountArray(__nb_libStack__); i++ ) {
        p[i] = ArrayObject(__nb_libStack__, i);
    }

    // Call proper function
    switch ( CountArray(__nb_libStack__) ) {
    case 0:
        ret = __nb_callstringcfunc0__((__nb_stringcfunc0__)func);
        break;
    case 1:
        ret = __nb_callstringcfunc1__((__nb_stringcfunc1__)func, p[0]);
        break;
    case 2:
        ret = __nb_callstringcfunc2__((__nb_stringcfunc2__)func, p[0], p[1]);
        break;
    case 3:
        ret = __nb_callstringcfunc3__((__nb_stringcfunc3__)func, p[0], p[1], p[2]);
        break;
    case 4:
        ret = __nb_callstringcfunc4__((__nb_stringcfunc4__)func, p[0], p[1], p[2], p[3]);
        break;
    case 5:
        ret = __nb_callstringcfunc5__((__nb_stringcfunc5__)func, p[0], p[1], p[2], p[3], p[4]);
        break;
    case 6:
        ret = __nb_callstringcfunc6__((__nb_stringcfunc6__)func, p[0], p[1], p[2], p[3], p[4], p[5]);
        break;
    case 7:
        ret = __nb_callstringcfunc7__((__nb_stringcfunc7__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6]);
        break;
    case 8:
        ret = __nb_callstringcfunc8__((__nb_stringcfunc8__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
        break;
    case 9:
        ret = __nb_callstringcfunc9__((__nb_stringcfunc9__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
        break;
    case 10:
        ret = __nb_callstringcfunc10__((__nb_stringcfunc10__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9]);
        break;
    case 11:
        ret = __nb_callstringcfunc11__((__nb_stringcfunc11__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10]);
        break;
    case 12:
        ret = __nb_callstringcfunc12__((__nb_stringcfunc12__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11]);
        break;
    case 13:
        ret = __nb_callstringcfunc13__((__nb_stringcfunc13__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12]);
        break;
    case 14:
        ret = __nb_callstringcfunc14__((__nb_stringcfunc14__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13]);
        break;
    case 15:
        ret = __nb_callstringcfunc15__((__nb_stringcfunc15__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13], p[14]);
        break;
    case 16:
        ret = __nb_callstringcfunc16__((__nb_stringcfunc16__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13], p[14], p[15]);
        break;
    }

    // Clear library stack
    ClearArray(__nb_libStack__);

	return string(ret);
}

EXPORT void* CALL CallObjectCFunction(void* func) {
    int i;
    void* p[16];
	void* ret = NULL;

    // Pop params from stack
    __nb_InitLibraryStack__();
    for ( i = 0; i < CountArray(__nb_libStack__); i++ ) {
        p[i] = ArrayObject(__nb_libStack__, i);
    }

    // Call proper function
    switch ( CountArray(__nb_libStack__) ) {
    case 0:
        ret = __nb_callobjectcfunc0__((__nb_objectcfunc0__)func);
        break;
    case 1:
        ret = __nb_callobjectcfunc1__((__nb_objectcfunc1__)func, p[0]);
        break;
    case 2:
        ret = __nb_callobjectcfunc2__((__nb_objectcfunc2__)func, p[0], p[1]);
        break;
    case 3:
        ret = __nb_callobjectcfunc3__((__nb_objectcfunc3__)func, p[0], p[1], p[2]);
        break;
    case 4:
        ret = __nb_callobjectcfunc4__((__nb_objectcfunc4__)func, p[0], p[1], p[2], p[3]);
        break;
    case 5:
        ret = __nb_callobjectcfunc5__((__nb_objectcfunc5__)func, p[0], p[1], p[2], p[3], p[4]);
        break;
    case 6:
        ret = __nb_callobjectcfunc6__((__nb_objectcfunc6__)func, p[0], p[1], p[2], p[3], p[4], p[5]);
        break;
    case 7:
        ret = __nb_callobjectcfunc7__((__nb_objectcfunc7__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6]);
        break;
    case 8:
        ret = __nb_callobjectcfunc8__((__nb_objectcfunc8__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
        break;
    case 9:
        ret = __nb_callobjectcfunc9__((__nb_objectcfunc9__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8]);
        break;
    case 10:
        ret = __nb_callobjectcfunc10__((__nb_objectcfunc10__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9]);
        break;
    case 11:
        ret = __nb_callobjectcfunc11__((__nb_objectcfunc11__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10]);
        break;
    case 12:
        ret = __nb_callobjectcfunc12__((__nb_objectcfunc12__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11]);
        break;
    case 13:
        ret = __nb_callobjectcfunc13__((__nb_objectcfunc13__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12]);
        break;
    case 14:
        ret = __nb_callobjectcfunc14__((__nb_objectcfunc14__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13]);
        break;
    case 15:
        ret = __nb_callobjectcfunc15__((__nb_objectcfunc15__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13], p[14]);
        break;
    case 16:
        ret = __nb_callobjectcfunc16__((__nb_objectcfunc16__)func, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13], p[14], p[15]);
        break;
    }

    // Clear library stack
    ClearArray(__nb_libStack__);

    return ret;
}

} // extern "C"
