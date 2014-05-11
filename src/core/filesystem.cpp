#include "filesystem.h"
#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#ifndef _MSC_VER
#include <dirent.h>
#include <unistd.h>
#define _getcwd getcwd
#define _chdir chdir
#define _rmdir rmdir
#else
#include <direct.h>
#include "dirent.h"
//#undef CopyFile
//#undef DeleteFile
#endif

using namespace std;

EXPORT int CALL DirContents(std::string path) {
	// Open directory
	DIR* d = (DIR*)opendir(path.c_str());
	if ( d == NULL ) return 0;

	// Create structure
	int contents = CreateArray();

	// Copy directory contents
	struct dirent* entry;
	while ( (entry = (struct dirent*)readdir(d)) ) {
		ArrayAddString(contents, entry->d_name);
	}

	// Close directory
	closedir(d);

	return contents;
}

EXPORT string CALL CurrentDir() {
    char buf[FILENAME_MAX];
	_getcwd(buf, FILENAME_MAX);
	return string(buf);
}

EXPORT void CALL ChangeDir(string path) {
	_chdir(path.c_str());
}

EXPORT void CALL CreateDir(string path) {
#ifdef _WIN32
	_mkdir(path.c_str());
#else
	mkdir(path.c_str(), S_IRWXU | S_IRGRP | S_IXGRP);
#endif
}

EXPORT void CALL DeleteDir(string path) {
	_rmdir(path.c_str());
}

EXPORT int CALL FileType(string filename) {
    struct stat statbuf;
	if ( stat(filename.c_str(), &statbuf) == -1 )
        return FILETYPE_NONE;
    else if ( S_ISDIR(statbuf.st_mode) )
        return FILETYPE_DIR;
    else
        return FILETYPE_FILE;
}

EXPORT int CALL FileSize(string filename) {
    struct stat statbuf;
	if ( stat(filename.c_str(), &statbuf) == -1 )
        return -1;   // Does not exist
    else
        return statbuf.st_size;
}

EXPORT void CALL CopyFile(string filename1, string filename2) {
    // Open first file for reading
	FILE* f1 = fopen(filename1.c_str(), "rb");
    if ( f1 ) {
        int size;
        void* buffer;
        FILE* f2;

        // Read contents of file
        size = FileSize(filename1);
        buffer = malloc(size);
        fread(buffer, sizeof(char), size, f1);

        // Write to second file
		f2 = fopen(filename2.c_str(), "wb");
        if ( f2 ) {
            fwrite(buffer, sizeof(char), size, f2);
            fclose(f2);
        }

        // Free resources
        free(buffer);
        fclose(f1);
    }
}

EXPORT void CALL DeleteFile(string filename) {
	remove(filename.c_str());
}
