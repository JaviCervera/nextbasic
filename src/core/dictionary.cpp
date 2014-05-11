#include "dictionary.h"
#include <map>

typedef std::map<std::string, CollectionValue> Dictionary;

using namespace std;

EXPORT int CALL CreateDictionary() {
	return int(new Dictionary);
}

EXPORT void CALL FreeDictionary(int dict) {
	delete (Dictionary*)dict;
}

EXPORT int CALL CountDictionary(int dict) {
	return ((Dictionary*)dict)->size();
}

EXPORT void CALL DictionarySetInt(int dict, string key, int val) {
	(*(Dictionary*)dict)[key] = CollectionValue(val);
}

EXPORT void CALL DictionarySetFloat(int dict, string key, float val) {
	(*(Dictionary*)dict)[key] = CollectionValue(val);
}

EXPORT void CALL DictionarySetString(int dict, string key, string str) {
	(*(Dictionary*)dict)[key] = CollectionValue(str);
}

EXPORT void CALL DictionarySetObject(int dict, string key, void* obj) {
	(*(Dictionary*)dict)[key] = CollectionValue(obj);
}

EXPORT int CALL DictionaryInt(int dict, string key) {
	return (*(Dictionary*)dict)[key].Int();
}

EXPORT float CALL DictionaryFloat(int dict, string key) {
	return (*(Dictionary*)dict)[key].Float();
}

EXPORT string CALL DictionaryString(int dict, string key) {
	return (*(Dictionary*)dict)[key].String();
}

EXPORT void* CALL DictionaryObject(int dict, string key) {
	return (*(Dictionary*)dict)[key].Object();
}

EXPORT int CALL DictionaryHasKey(int dict, string key) {
	return ((Dictionary*)dict)->count(key) > 0;
}

EXPORT string CALL DictionaryKey(int dict, int index) {
	Dictionary::iterator it = ((Dictionary*)dict)->begin();
	for ( int i = 0; i < index; i++ ) it++;
	return it->first;
}

EXPORT void CALL DictionaryRemove(int dict, string key) {
	((Dictionary*)dict)->erase(key);
}

EXPORT void CALL ClearDictionary(int dict) {
	((Dictionary*)dict)->clear();
}
