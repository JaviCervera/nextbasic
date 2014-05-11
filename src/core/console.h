#ifndef CONSOLE_H
#define CONSOLE_H

#include "../common/defs.h"
#include <string>

EXPORT void CALL Print(std::string str);
EXPORT void CALL Write(std::string str);
EXPORT std::string CALL Input(std::string prompt);

#endif // CONSOLE_H
