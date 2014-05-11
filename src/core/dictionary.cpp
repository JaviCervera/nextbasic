#include "dictionary.h"

using namespace std;

extern "C" {

EXPORT Dictionary* CALL CreateDictionary() {
	return new Dictionary;
}

EXPORT void CALL FreeDictionary(Dictionary* dict) {
	delete dict;
}

EXPORT int CALL CountDictionary(Dictionary* dict) {
	return dict->size();
}

EXPORT void CALL DictionarySetInt(Dictionary* dict, string key, int val) {
	(*dict)[key] = CollectionValue(val);
}

EXPORT void CALL DictionarySetFloat(Dictionary* dict, string key, float val) {
	(*dict)[key] = CollectionValue(val);
}

EXPORT void CALL DictionarySetString(Dictionary* dict, string key, string str) {
	(*dict)[key] = CollectionValue(str);
}

EXPORT void CALL DictionarySetObject(Dictionary* dict, string key, void* obj) {
	(*dict)[key] = CollectionValue(obj);
}

EXPORT int CALL DictionaryInt(Dictionary* dict, string key) {
	return (*dict)[key].Int();
}

EXPORT float CALL DictionaryFloat(Dictionary* dict, string key) {
	return (*dict)[key].Float();
}

EXPORT string CALL DictionaryString(Dictionary* dict, string key) {
	return (*dict)[key].String();
}

EXPORT void* CALL DictionaryObject(Dictionary* dict, string key) {
	return (*dict)[key].Object();
}

EXPORT int CALL DictionaryHasKey(Dictionary* dict, string key) {
	return dict->count(key) > 0;
}

EXPORT string CALL DictionaryKey(Dictionary* dict, int index) {
	Dictionary::iterator it = dict->begin();
	for ( int i = 0; i < index; i++ ) it++;
	return it->first;
}

EXPORT void CALL DictionaryRemove(Dictionary* dict, string key) {
	dict->erase(key);
}

EXPORT void CALL ClearDictionary(Dictionary* dict) {
	dict->clear();
}

} // extern "C"
