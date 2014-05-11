#include "console.h"
#include <stdio.h>

using namespace std;

EXPORT void CALL Print(string str) {
	printf("%s\n", str.c_str());
}

EXPORT void CALL Write(string str) {
	printf("%s", str.c_str());
}

EXPORT string CALL Input(string prompt) {
	char buffer[1024];
	printf("%s", prompt.c_str());
    fgets(buffer, 1024, stdin);
	return string(buffer);
}
