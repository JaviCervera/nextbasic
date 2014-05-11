#ifndef FILE_H
#define FILE_H

#include "../common/defs.h"
#include <string>

EXPORT int CALL ReadFile(std::string filename);
EXPORT int CALL WriteFile(std::string filename, int append);
EXPORT void CALL CloseFile(int file);
EXPORT int CALL FilePos(int file);
EXPORT void CALL SeekFile(int file, int pos);
EXPORT int CALL Eof(int file);
EXPORT int CALL ReadByte(int file);
EXPORT int CALL ReadShort(int file);
EXPORT int CALL ReadInt(int file);
EXPORT float CALL ReadFloat(int file);
EXPORT std::string CALL ReadString(int file);
EXPORT std::string CALL ReadLine(int file);
EXPORT int CALL ReadBytes(int file, int buffer, int offset, int count);
EXPORT void CALL WriteByte(int file, int val);
EXPORT void CALL WriteShort(int file, int val);
EXPORT void CALL WriteInt(int file, int val);
EXPORT void CALL WriteFloat(int file, float val);
EXPORT void CALL WriteString(int file, std::string val);
EXPORT void CALL WriteLine(int file, std::string val);
EXPORT int CALL WriteBytes(int file, int buffer, int offset, int count);

#endif // FILE_H
