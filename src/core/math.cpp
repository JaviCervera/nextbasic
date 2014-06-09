#include "math.h"
#include <math.h>
#include <stdlib.h>

#define DEG2RAD 0.0174532925
#define RAD2DEG 57.2957795

EXPORT float CALL Pi() {
    return 3.141592f; /*65359f*/
}

EXPORT float CALL Floor(float val) {
    return (float)floor(val);
}

EXPORT float CALL Ceil(float val) {
    return (float)ceil(val);
}

EXPORT float CALL Sgn(float val) {
    if ( val > 0 )
        return 1.000000f;
    else if ( val < 0 )
        return -1.000000f;
    else
        return 0.000000f;
}

EXPORT int CALL Abs(int val) {
    return abs(val);
}

EXPORT float CALL AbsF(float val) {
    return (float)fabs(val);
}

EXPORT float CALL Sqr(float val) {
    return (float)sqrt(val);
}

EXPORT float CALL Sin(float val) {
    return (float)sin(val * DEG2RAD);
}

EXPORT float CALL Cos(float val) {
    return (float)cos(val * DEG2RAD);
}

EXPORT float CALL Tan(float val) {
    return (float)tan(val * DEG2RAD);
}

EXPORT float CALL ASin(float val) {
    return (float)(asin(val) * RAD2DEG);
}

EXPORT float CALL ACos(float val) {
    return (float)(acos(val) * RAD2DEG);
}

EXPORT float CALL ATan(float val) {
    return (float)(atan(val) * RAD2DEG);
}

EXPORT float CALL ATan2(float y, float x) {
    return (float)(atan2(y, x) * RAD2DEG);
}

EXPORT float CALL Exp(float val) {
    return (float)exp(val);
}

EXPORT float CALL Log(float val) {
    return (float)log(val);
}

EXPORT float CALL Log10(float val) {
    return (float)log10(val);
}

EXPORT int CALL Rand(int min, int max) {
    int range = (max - min) + 1;
    return min + (rand() % range);
}

EXPORT float CALL RandF(float min, float max) {
	return (float)(Rand((int)min * 1000, (int)max * 1000) / 1000.0);
}

EXPORT void CALL SeedRnd(int seed) {
    srand((unsigned int)seed);
}

EXPORT float CALL Wrap(float value, float module) {
    if (module == 0) return value;
    return (float)(value - module*floor(value/module));
}
