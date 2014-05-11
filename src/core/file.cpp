#include "file.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct File {
	FILE* handle;
	int size;
};

EXPORT int ReadFile(string filename) {
    File* file = NULL;
	FILE* f = fopen(filename.c_str(), "rb");
	if ( f == NULL ) return 0;

    // Open file
	file = (File*)malloc(sizeof(File*));
    file->handle = f;

    // Get size
    fseek(f, 0, SEEK_END);
    file->size = (int)ftell(f);
    fseek(f, 0, SEEK_SET);

    // Return file
	return int(file);
}

EXPORT int WriteFile(string filename, int append) {
    File* file = NULL;
	FILE* f = fopen(filename.c_str(), (append == 1) ? "ab" : "wb");
	if ( f == NULL ) return 0;

    // Open file
	file = (File*)malloc(sizeof(File*));
    file->handle = f;

    // Get size
    file->size = -1;

    // Return file
	return int(file);
}

EXPORT void CALL CloseFile(int file) {
	fclose(((File*)file)->handle);
	free((File*)file);
}

EXPORT int CALL FilePos(int file) {
	return (int)ftell(((File*)file)->handle);
}

EXPORT void CALL SeekFile(int file, int pos) {
	fseek(((File*)file)->handle, pos, SEEK_SET);
}

EXPORT int CALL Eof(int file) {
	return FilePos(file) == ((File*)file)->size;
}

EXPORT int CALL ReadByte(int file) {
    char c;
	fread(&c, 1, sizeof(char), ((File*)file)->handle);
    return (int)c;
}

EXPORT int CALL ReadShort(int file) {
    short s;
	fread(&s, 1, sizeof(short), ((File*)file)->handle);
    return (int)s;
}

EXPORT int CALL ReadInt(int file) {
    int i;
	fread(&i, 1, sizeof(int), ((File*)file)->handle);
    return i;
}

EXPORT float CALL ReadFloat(int file) {
    float f;
	fread(&f, 1, sizeof(float), ((File*)file)->handle);
    return f;
}

EXPORT string CALL ReadString(int file) {
    char c;
	string str;

    // Read first char
	fread(&c, 1, sizeof(char), ((File*)file)->handle);

    // While we haven't reached the end of the string
    while ( c != '\0' ) {
		str += c;
		fread(&c, 1, sizeof(char), ((File*)file)->handle);
    }

    // Return string
    return str;
}

EXPORT string CALL ReadLine(int file) {
    char c;
	string str;

    // Read first char
	fread(&c, 1, sizeof(char), ((File*)file)->handle);

    // While we haven't reached the end of the string
    while ( c != '\r' && c != '\n' ) {
		str += c;
        if ( !Eof(file) )
			fread(&c, 1, sizeof(char), ((File*)file)->handle);
        else
            break;
    }

    // Skip '\n' if present
    if ( c == '\r' && !Eof(file) ) {
		fread(&c, 1, sizeof(char), ((File*)file)->handle);
        if ( c != '\n' ) {
            SeekFile(file, FilePos(file)-1);
        }
    }

    // Return string
    return str;
}

EXPORT int CALL ReadBytes(int file, int buffer, int offset, int count) {
	return fread((char*)buffer + offset, count, sizeof(char), ((File*)file)->handle);
}

EXPORT void CALL WriteByte(int file, int val) {
    unsigned char b = (unsigned char)val;
	fwrite(&b, 1, sizeof(char), ((File*)file)->handle);
}

EXPORT void CALL WriteShort(int file, int val) {
    unsigned short s = (unsigned short)val;
	fwrite(&s, 1, sizeof(short), ((File*)file)->handle);
}

EXPORT void CALL WriteInt(int file, int val) {
	fwrite(&val, 1, sizeof(int), ((File*)file)->handle);
}

EXPORT void CALL WriteFloat(int file, float val) {
	fwrite(&val, 1, sizeof(float), ((File*)file)->handle);
}

EXPORT void CALL WriteString(int file, string val) {
    char c = '\0';
	fwrite(val.c_str(), val.length(), sizeof(char), ((File*)file)->handle);
	fwrite(&c, 1, sizeof(char), ((File*)file)->handle);
}

EXPORT void CALL WriteLine(int file, string val) {
    char c;
	fwrite(val.c_str(), val.length(), sizeof(char), ((File*)file)->handle);
    c = '\r';
	fwrite(&c, 1, sizeof(char), ((File*)file)->handle);
    c = '\n';
	fwrite(&c, 1, sizeof(char), ((File*)file)->handle);
}

EXPORT int CALL WriteBytes(int file, int buffer, int offset, int count) {
	return fwrite((char*)buffer + offset, count, sizeof(char), ((File*)file)->handle);
}
