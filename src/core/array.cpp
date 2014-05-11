#include "array.h"

using namespace std;

extern "C" {

EXPORT Array* CALL CreateArray() {
	return new Array;
}

EXPORT void CALL FreeArray(Array* arr) {
	delete arr;
}

EXPORT int CALL CountArray(Array* arr) {
	return arr->size();
}

EXPORT void CALL ArrayAddInt(Array* arr, int i) {
	arr->push_back(CollectionValue(i));
}

EXPORT void CALL ArrayAddFloat(Array* arr, float f) {
	arr->push_back(CollectionValue(f));
}

EXPORT void CALL ArrayAddString(Array* arr, string s) {
	arr->push_back(CollectionValue(s));
}

EXPORT void CALL ArrayAddObject(Array* arr, void* obj) {
	arr->push_back(CollectionValue(obj));
}

EXPORT void CALL ArraySetInt(Array* arr, int index, int i) {
	arr->at(index) = CollectionValue(i);
}

EXPORT void CALL ArraySetFloat(Array* arr, int index, float f) {
	arr->at(index) = CollectionValue(f);
}

EXPORT void CALL ArraySetString(Array* arr, int index, string s) {
	arr->at(index) = CollectionValue(s);
}

EXPORT void CALL ArraySetObject(Array* arr, int index, void* obj) {
	arr->at(index) = CollectionValue(obj);
}

EXPORT int CALL ArrayInt(Array* arr, int index) {
	return arr->at(index).Int();
}

EXPORT float CALL ArrayFloat(Array* arr, int index) {
	return arr->at(index).Float();
}

EXPORT string ArrayString(Array* arr, int index) {
	return arr->at(index).String();
}

EXPORT void* CALL ArrayObject(Array* arr, int index) {
	return arr->at(index).Object();
}

EXPORT void CALL ArrayRemoveAt(Array* arr, int index) {
	arr->erase(arr->begin() + index);
}

EXPORT void CALL ArrayRemoveObject(Array* arr, void* obj) {
	for ( Array::iterator it = arr->begin(); it != arr->end(); it++ ) {
		if ( (*it).Object() == obj ) {
			arr->erase(it);
			break;
		}
	}
}

EXPORT void CALL ClearArray(Array* arr) {
	arr->clear();
}

} // extern "C"
