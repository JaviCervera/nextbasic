#ifndef TIME_H
#define TIME_H

#include "../common/defs.h"
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

EXPORT int CALL Millisecs();
EXPORT void CALL Delay(int msecs);
EXPORT std::string CALL CurrentDate();
EXPORT std::string CALL CurrentTime();

#ifdef __cplusplus
}
#endif

#endif // TIME_H
