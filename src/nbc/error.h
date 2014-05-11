#ifndef ERROR_H
#define ERROR_H

#include "token.h"
#include <string>

class Error {
public:
    static std::string Get();
    static void Set(const std::string& msg, const Token& token);
protected:
    Error() {}
private:
    static std::string msg;
    static Token token;
};

#endif // ERROR_H
