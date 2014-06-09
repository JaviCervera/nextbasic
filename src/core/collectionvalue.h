#ifndef COLLECTIONVALUE_H
#define COLLECTIONVALUE_H

#include <string>

class CollectionValue {
public:
	CollectionValue() : ival(0), isString(false) {}
	CollectionValue(int v) : ival(v), isString(false) {}
	CollectionValue(float v) : fval(v), isString(false) {}
	CollectionValue(const std::string& v) : sval(new std::string(v)), isString(true) {}
	CollectionValue(void* v) : oval(v), isString(false) {}
	CollectionValue(const CollectionValue& other);
	~CollectionValue() { if ( isString ) delete sval; }
	CollectionValue& operator=(const CollectionValue& other);
	int Int() const { return ival; }
	float Float() const { return fval; }
	const std::string& String() const { return *sval; }
	void* Object() const { return isString ? (void*)sval->c_str() : oval; }
private:
	union {
		int ival;
		float fval;
		std::string* sval;
		void* oval;
	};
	bool isString;
};

inline CollectionValue::CollectionValue(const CollectionValue& other) {
	isString = other.isString;
	if ( isString ) {
		sval = new std::string(other.String());
	} else {
		oval = other.oval;
	}
}

inline CollectionValue& CollectionValue::operator=(const CollectionValue& other) {
	isString = other.isString;
	if ( isString ) {
		sval = new std::string(other.String());
	} else {
		oval = other.oval;
	}
	return *this;
}

#endif // COLLECTIONVALUE_H
