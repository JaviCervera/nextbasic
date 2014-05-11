#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "../common/defs.h"
#include "collectionvalue.h"

EXPORT int CALL CreateDictionary();
EXPORT void CALL FreeDictionary(int dict);
EXPORT int CALL CountDictionary(int dict);
EXPORT void CALL DictionarySetInt(int dict, std::string key, int val);
EXPORT void CALL DictionarySetFloat(int dict, std::string key, float val);
EXPORT void CALL DictionarySetString(int dict, std::string key, std::string str);
EXPORT void CALL DictionarySetObject(int dict, std::string key, void* obj);
EXPORT int CALL DictionaryInt(int dict, std::string key);
EXPORT float CALL DictionaryFloat(int dict, std::string key);
EXPORT std::string CALL DictionaryString(int dict, std::string key);
EXPORT void* CALL DictionaryObject(int dict, std::string key);
EXPORT int CALL DictionaryHasKey(int dict, std::string key);
EXPORT std::string CALL DictionaryKey(int dict, int index);
EXPORT void CALL DictionaryRemove(int dict, std::string key);
EXPORT void CALL ClearDictionary(int dict);

#endif // DICTIONARY_H
