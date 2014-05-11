#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#ifdef _WIN32
#define realpath(N,R) _fullpath((R),(N),FILENAME_MAX)
#endif

using namespace std;

extern "C" {

EXPORT string CALL Str(int val) {
	char str[32];
	sprintf(str, "%i", val);
	return string(str);
}

EXPORT string CALL StrF(float val) {
	char str[32];
	sprintf(str, "%f", val);
	return string(str);
}

EXPORT int CALL Val(string str) {
	int ret = 0;
	if ( str.length() > 2  &&  str[0] == '0'  &&  str[1] == 'x' ) {
		str = Replace(str, "0x", "");
		sscanf(str.c_str(), "%x", &ret);
	} else {
		sscanf(str.c_str(), "%i", &ret);
	}
	return ret;
}

EXPORT float CALL ValF(string str) {
	return atof(str.c_str());
}

EXPORT string CALL Left(string str, int n) {
	return str.substr(0, n);
}

EXPORT string CALL Right(string str, int n)  {
	return str.substr(str.length() - n, n);
}

EXPORT string CALL Mid(string str, int ofs, int n) {
	return str.substr(ofs-1, n);
}

EXPORT string CALL Replace(string str, string find, string rep) {
	while ( str.find(find) != string::npos ) {
		str.replace(str.find(find), find.length(), rep);
	}
	return str;
}

EXPORT int CALL Find(string str1, string str2, int ofs) {
	size_t pos = str1.find(str2, ofs-1);
	return ( pos != string::npos ) ? pos+1 : 0;
}

EXPORT string CALL Upper(string str) {
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
	return str;
}

EXPORT string CALL Lower(string str) {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	return str;
}

EXPORT string CALL LTrim(string str) {
	str.erase(str.begin(), find_if(str.begin(), str.end(), not1(ptr_fun<int, int>(isspace))));
	return str;
}

EXPORT string CALL RTrim(string str) {
	str.erase(find_if(str.rbegin(), str.rend(), not1(ptr_fun<int, int>(isspace))).base(), str.end());
	return str;
}

EXPORT string CALL Trim(string str) {
	return LTrim(RTrim(str));
}

EXPORT string CALL LSet(string str, int len, string c) {
	if ( len > (int)str.length() ) {
		return string(len - str.length(), c[0]) + str;
	} else {
		return str;
	}
}

EXPORT string CALL RSet(string str, int len, string c) {
	if ( len > (int)str.length() ) {
		return str + string(len - str.length(), c[0]);
	} else {
		return str;
	}
}

EXPORT string CALL Chr(int asc) {
	return string(1, (char)asc);
}

EXPORT int CALL Asc(string chr) {
	return (int)chr[0];
}

EXPORT int CALL Len(string str) {
	return str.length();
}

EXPORT string CALL Hex(int val) {
	char str[32];
	sprintf(str, "%x", val);
	return string(str);
}

EXPORT string CALL StripExt(string filename) {
	return filename.substr(0, filename.find('.'));
}

EXPORT string CALL StripDir(string filename) {
	filename = Replace(filename, "\\", "/");
	return filename.substr(filename.rfind('/')+1, filename.length() - filename.rfind('/')-1);
}

EXPORT string CALL ExtractExt(string filename) {
	return filename.substr(filename.rfind('.')+1, filename.length() - filename.rfind('.')-1);
}

EXPORT string CALL ExtractDir(string filename) {
	filename = Replace(filename, "\\", "/");
	return filename.substr(0, filename.rfind('/'));
}

EXPORT string CALL RealPath(string filename) {
	char path[FILENAME_MAX];
	realpath(filename.c_str(), path);
	return string(path);
}

EXPORT string CALL LoadString(string filename) {
	long size;
	char* buf = NULL;
	std::string str = "";

	// Open file to read
	FILE* f = fopen(filename.c_str(), "rb");

	// If it does not exist, return NULL
	if ( f == NULL ) return NULL;

	// Get file size
	fseek(f, 0, SEEK_END);
	size = ftell(f);
	fseek(f, 0, SEEK_SET);

	// Allocate contents in a buffer
	buf = (char*)malloc(size+1);
	fread(buf, sizeof(char), size, f);
	buf[size] = '\0';

	// Create temp string from buffer
	str = buf;

	// Free resources
	free(buf);
	fclose(f);

	// Return string
	return str;
}

EXPORT void CALL SaveString(string str, string filename, int append) {
	FILE* f = fopen(filename.c_str(), (append == 1) ? "ab" : "wb");
	if ( f == NULL ) return;
	fwrite(str.c_str(), sizeof(char), str.length(), f);
	fclose(f);
}

EXPORT Array* CALL SplitString(string str, string delim) {
	if ( (str.length() == 0) || (delim[0] == '\0') )
		return CreateArray();

	// Fill array with strings
	Array* arr = CreateArray();
	string txt = "";
	for ( unsigned int i = 0; i < str.length(); i++ ) {
		if ( str[i] == delim[0] ) {
			ArrayAddString(arr, txt);
			txt = "";
		} else {
			txt += str[i];
		}
	}
	ArrayAddString(arr, txt);
	return arr;
}

} // extern "C"
