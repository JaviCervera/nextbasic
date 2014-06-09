#include "array.h"
#include <vector>

typedef std::vector<CollectionValue> Array;

using namespace std;

EXPORT int CALL CreateArray() {
	return int(new Array);
}

EXPORT void CALL FreeArray(int arr) {
	delete (Array*)arr;
}

EXPORT int CALL CountArray(int arr) {
	return ((Array*)arr)->size();
}

EXPORT void CALL ArrayAddInt(int arr, int i) {
	((Array*)arr)->push_back(CollectionValue(i));
}

EXPORT void CALL ArrayAddFloat(int arr, float f) {
	((Array*)arr)->push_back(CollectionValue(f));
}

EXPORT void CALL ArrayAddString(int arr, string s) {
	((Array*)arr)->push_back(CollectionValue(s));
}

EXPORT void CALL ArrayAddObject(int arr, void* obj) {
	((Array*)arr)->push_back(CollectionValue(obj));
}

EXPORT void CALL ArraySetInt(int arr, int index, int i) {
	((Array*)arr)->at(index) = CollectionValue(i);
}

EXPORT void CALL ArraySetFloat(int arr, int index, float f) {
	((Array*)arr)->at(index) = CollectionValue(f);
}

EXPORT void CALL ArraySetString(int arr, int index, string s) {
	((Array*)arr)->at(index) = CollectionValue(s);
}

EXPORT void CALL ArraySetObject(int arr, int index, void* obj) {
	((Array*)arr)->at(index) = CollectionValue(obj);
}

EXPORT int CALL ArrayInt(int arr, int index) {
	return ((Array*)arr)->at(index).Int();
}

EXPORT float CALL ArrayFloat(int arr, int index) {
	return ((Array*)arr)->at(index).Float();
}

EXPORT string ArrayString(int arr, int index) {
	return ((Array*)arr)->at(index).String();
}

EXPORT int CALL ArrayObject(int arr, int index) {
	return (int)((Array*)arr)->at(index).Object();
}

EXPORT void CALL ArrayRemoveAt(int arr, int index) {
	((Array*)arr)->erase(((Array*)arr)->begin() + index);
}

EXPORT void CALL ArrayRemoveObject(int arr, void* obj) {
	for ( Array::iterator it = ((Array*)arr)->begin(); it != ((Array*)arr)->end(); it++ ) {
		if ( (*it).Object() == obj ) {
			((Array*)arr)->erase(it);
			break;
		}
	}
}

EXPORT void CALL ClearArray(int arr) {
	((Array*)arr)->clear();
}
