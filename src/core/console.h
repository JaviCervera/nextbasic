#ifndef CONSOLE_H
#define CONSOLE_H

#include "../common/defs.h"
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

EXPORT void CALL Print(std::string str);
EXPORT void CALL Write(std::string str);
EXPORT std::string CALL Input(std::string prompt);

#ifdef __cplusplus
}
#endif

#endif // CONSOLE_H
