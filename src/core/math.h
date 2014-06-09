#ifndef MATH_H
#define MATH_H

#include "../common/defs.h"

EXPORT float CALL Pi();
EXPORT float CALL Floor(float val);
EXPORT float CALL Ceil(float val);
EXPORT float CALL Sgn(float val);
EXPORT int CALL Abs(int val);
EXPORT float CALL AbsF(float val);
EXPORT float CALL Sqr(float val);
EXPORT float CALL Sin(float val);
EXPORT float CALL Cos(float val);
EXPORT float CALL Tan(float val);
EXPORT float CALL ASin(float val);
EXPORT float CALL ACos(float val);
EXPORT float CALL ATan(float val);
EXPORT float CALL ATan2(float y, float x);
EXPORT float CALL Exp(float val);
EXPORT float CALL Log(float val);
EXPORT float CALL Log10(float val);
EXPORT int CALL Rand(int min, int max);
EXPORT float CALL RandF(float min, float max);
EXPORT void CALL SeedRnd(int seed);
EXPORT float CALL Wrap(float value, float module);

#endif // MATH_H
