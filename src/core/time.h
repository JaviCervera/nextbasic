#ifndef TIME_H
#define TIME_H

#include "../common/defs.h"
#include <string>

EXPORT int CALL Millisecs();
EXPORT void CALL Delay(int msecs);
EXPORT std::string CALL CurrentDate();
EXPORT std::string CALL CurrentTime();

#endif // TIME_H
