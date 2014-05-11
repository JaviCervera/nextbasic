#ifndef FILE_H
#define FILE_H

#include "../common/defs.h"
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void* handle;
    int size;
} File;

EXPORT File* CALL ReadFile(std::string filename);
EXPORT File* CALL WriteFile(std::string filename, int append);
EXPORT void CALL CloseFile(File* file);
EXPORT int CALL FilePos(File* file);
EXPORT void CALL SeekFile(File* file, int pos);
EXPORT int CALL Eof(File* file);
EXPORT int CALL ReadByte(File* file);
EXPORT int CALL ReadShort(File* file);
EXPORT int CALL ReadInt(File* file);
EXPORT float CALL ReadFloat(File* file);
EXPORT std::string CALL ReadString(File* file);
EXPORT std::string CALL ReadLine(File* file);
EXPORT int CALL ReadBytes(File* file, void* buffer, int offset, int count);
EXPORT void CALL WriteByte(File* file, int val);
EXPORT void CALL WriteShort(File* file, int val);
EXPORT void CALL WriteInt(File* file, int val);
EXPORT void CALL WriteFloat(File* file, float val);
EXPORT void CALL WriteString(File* file, std::string val);
EXPORT void CALL WriteLine(File* file, std::string val);
EXPORT int CALL WriteBytes(File* file, void* buffer, int offset, int count);

#ifdef __cplusplus
}
#endif

#endif // FILE_H
