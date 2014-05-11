#include "file.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

extern "C" {

EXPORT File* CALL ReadFile(string filename) {
    File* file = NULL;
	FILE* f = fopen(filename.c_str(), "rb");
    if ( f == NULL ) return NULL;

    // Open file
	file = (File*)malloc(sizeof(File*));
    file->handle = f;

    // Get size
    fseek(f, 0, SEEK_END);
    file->size = (int)ftell(f);
    fseek(f, 0, SEEK_SET);

    // Return file
    return file;
}

EXPORT File* CALL WriteFile(string filename, int append) {
    File* file = NULL;
	FILE* f = fopen(filename.c_str(), (append == 1) ? "ab" : "wb");
    if ( f == NULL ) return NULL;

    // Open file
	file = (File*)malloc(sizeof(File*));
    file->handle = f;

    // Get size
    file->size = -1;

    // Return file
    return file;
}

EXPORT void CALL CloseFile(File* file) {
	fclose((FILE*)file->handle);
    free(file);
}

EXPORT int CALL FilePos(File* file) {
	return (int)ftell((FILE*)file->handle);
}

EXPORT void CALL SeekFile(File* file, int pos) {
	fseek((FILE*)file->handle, pos, SEEK_SET);
}

EXPORT int CALL Eof(File* file) {
    return FilePos(file) == file->size;
}

EXPORT int CALL ReadByte(File* file) {
    char c;
	fread(&c, 1, sizeof(char), (FILE*)file->handle);
    return (int)c;
}

EXPORT int CALL ReadShort(File* file) {
    short s;
	fread(&s, 1, sizeof(short), (FILE*)file->handle);
    return (int)s;
}

EXPORT int CALL ReadInt(File* file) {
    int i;
	fread(&i, 1, sizeof(int), (FILE*)file->handle);
    return i;
}

EXPORT float CALL ReadFloat(File* file) {
    float f;
	fread(&f, 1, sizeof(float), (FILE*)file->handle);
    return f;
}

EXPORT string CALL ReadString(File* file) {
    char c;
	string str;

    // Read first char
	fread(&c, 1, sizeof(char), (FILE*)file->handle);

    // While we haven't reached the end of the string
    while ( c != '\0' ) {
		str += c;
		fread(&c, 1, sizeof(char), (FILE*)file->handle);
    }

    // Return string
    return str;
}

EXPORT string CALL ReadLine(File* file) {
    char c;
	string str;

    // Read first char
	fread(&c, 1, sizeof(char), (FILE*)file->handle);

    // While we haven't reached the end of the string
    while ( c != '\r' && c != '\n' ) {
		str += c;
        if ( !Eof(file) )
			fread(&c, 1, sizeof(char), (FILE*)file->handle);
        else
            break;
    }

    // Skip '\n' if present
    if ( c == '\r' && !Eof(file) ) {
		fread(&c, 1, sizeof(char), (FILE*)file->handle);
        if ( c != '\n' ) {
            SeekFile(file, FilePos(file)-1);
        }
    }

    // Return string
    return str;
}

EXPORT int CALL ReadBytes(File* file, void* buffer, int offset, int count) {
	return fread((char*)buffer + offset, count, sizeof(char), (FILE*)file->handle);
}

EXPORT void CALL WriteByte(File* file, int val) {
    unsigned char b = (unsigned char)val;
	fwrite(&b, 1, sizeof(char), (FILE*)file->handle);
}

EXPORT void CALL WriteShort(File* file, int val) {
    unsigned short s = (unsigned short)val;
	fwrite(&s, 1, sizeof(short), (FILE*)file->handle);
}

EXPORT void CALL WriteInt(File* file, int val) {
	fwrite(&val, 1, sizeof(int), (FILE*)file->handle);
}

EXPORT void CALL WriteFloat(File* file, float val) {
	fwrite(&val, 1, sizeof(float), (FILE*)file->handle);
}

EXPORT void CALL WriteString(File* file, string val) {
    char c = '\0';
	fwrite(val.c_str(), val.length(), sizeof(char), (FILE*)file->handle);
	fwrite(&c, 1, sizeof(char), (FILE*)file->handle);
}

EXPORT void CALL WriteLine(File* file, string val) {
    char c;
	fwrite(val.c_str(), val.length(), sizeof(char), (FILE*)file->handle);
    c = '\r';
	fwrite(&c, 1, sizeof(char), (FILE*)file->handle);
    c = '\n';
	fwrite(&c, 1, sizeof(char), (FILE*)file->handle);
}

EXPORT int CALL WriteBytes(File* file, void* buffer, int offset, int count) {
	return fwrite((char*)buffer + offset, count, sizeof(char), (FILE*)file->handle);
}

} // extern "C"
