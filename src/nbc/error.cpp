#include "error.h"
#include "../core/string.h"

using namespace std;

string Error::Get() {
    if ( msg == "" ) {
        return "";
    } else {
        string str = msg + " on file '" + token.File() + "'";
		if ( token.Type() != TokenEndOfFile ) str += " at line " + Str(token.Line());
        return str;
    }
}

void Error::Set(const string& msg, const Token& token) {
    Error::msg = msg;
    Error::token = token;
}

string Error::msg;
Token Error::token;
