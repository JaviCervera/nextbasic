#ifndef STRING_H
#define STRING_H

#include "../common/defs.h"
#include "array.h"
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

EXPORT std::string CALL Str(int val);
EXPORT std::string CALL StrF(float val);
EXPORT int CALL Val(std::string str);
EXPORT float CALL ValF(std::string str);
EXPORT std::string CALL Left(std::string str, int n);
EXPORT std::string CALL Right(std::string str, int n);
EXPORT std::string CALL Mid(std::string str, int ofs, int n);
EXPORT std::string CALL Replace(std::string str, std::string find, std::string rep);
EXPORT int CALL Find(std::string str1, std::string str2, int ofs);
EXPORT std::string CALL Upper(std::string str);
EXPORT std::string CALL Lower(std::string str);
EXPORT std::string CALL LTrim(std::string str);
EXPORT std::string CALL RTrim(std::string str);
EXPORT std::string CALL Trim(std::string str);
EXPORT std::string CALL LSet(std::string str, int len, std::string c);
EXPORT std::string CALL RSet(std::string str, int len, std::string c);
EXPORT std::string CALL Chr(int asc);
EXPORT int CALL Asc(std::string chr);
EXPORT int CALL Len(std::string str);
EXPORT std::string CALL Hex(int val);
EXPORT std::string CALL StripExt(std::string filename);
EXPORT std::string CALL StripDir(std::string filename);
EXPORT std::string CALL ExtractExt(std::string filename);
EXPORT std::string CALL ExtractDir(std::string filename);
EXPORT std::string CALL RealPath(std::string filename);
EXPORT std::string CALL LoadString(std::string filename);
EXPORT void CALL SaveString(std::string str, std::string filename, int append);
EXPORT Array* CALL SplitString(std::string str, std::string delim);

#ifdef __cplusplus
}
#endif

#endif // STRING_H
