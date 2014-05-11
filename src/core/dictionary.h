#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "../common/defs.h"
#include "collectionvalue.h"
#include <map>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

typedef std::map<std::string, CollectionValue> Dictionary;

EXPORT Dictionary* CALL CreateDictionary();
EXPORT void CALL FreeDictionary(Dictionary* dict);
EXPORT int CALL CountDictionary(Dictionary* dict);
EXPORT void CALL DictionarySetInt(Dictionary* dict, std::string key, int val);
EXPORT void CALL DictionarySetFloat(Dictionary* dict, std::string key, float val);
EXPORT void CALL DictionarySetString(Dictionary* dict, std::string key, std::string str);
EXPORT void CALL DictionarySetObject(Dictionary* dict, std::string key, void* obj);
EXPORT int CALL DictionaryInt(Dictionary* dict, std::string key);
EXPORT float CALL DictionaryFloat(Dictionary* dict, std::string key);
EXPORT std::string CALL DictionaryString(Dictionary* dict, std::string key);
EXPORT void* CALL DictionaryObject(Dictionary* dict, std::string key);
EXPORT int CALL DictionaryHasKey(Dictionary* dict, std::string key);
EXPORT std::string CALL DictionaryKey(Dictionary* dict, int index);
EXPORT void CALL DictionaryRemove(Dictionary* dict, std::string key);
EXPORT void CALL ClearDictionary(Dictionary* dict);

#ifdef __cplusplus
}
#endif

#endif // DICTIONARY_H
