#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "../common/defs.h"
#include <string>

#define FILETYPE_NONE   0
#define FILETYPE_FILE   1
#define FILETYPE_DIR    2

EXPORT int CALL DirContents(std::string path);	// Returns an Array*
EXPORT std::string CALL CurrentDir();
EXPORT void CALL ChangeDir(std::string path);
EXPORT void CALL CreateDir(std::string path);
EXPORT void CALL DeleteDir(std::string path);
EXPORT int CALL FileType(std::string filename);
EXPORT int CALL FileSize(std::string filename);
EXPORT void CALL CopyFile(std::string filename1, std::string filename2);
EXPORT void CALL DeleteFile(std::string filename);

#endif // FILESYSTEM_H
