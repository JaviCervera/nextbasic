#ifndef IDTYPE_H
#define IDTYPE_H

#include "token.h"

enum IdType {
    TypeVoid,
    TypeInt,
    TypeFloat,
    TypeString,
	TypePChar,
    TypeStruct  // A struct has this type or higher (TypeStruct + struct index)
};

inline IdType IdTypeFromTokenType(TokenType tok) {
    if ( tok == TokenIntLiteral || tok == TokenIntKeyword )
        return TypeInt;
    else if ( tok == TokenFloatLiteral || tok == TokenFloatKeyword )
        return TypeFloat;
    else if ( tok == TokenStringLiteral || tok == TokenStringKeyword )
        return TypeString;
	else if ( tok == TokenPCharKeyword )
		return TypePChar;
    else if ( tok == TokenIdentifier || tok == TokenStruct )
		return TypeStruct;  // Here we only return TypeStruct. The struct index will be specified later on
    else
        return TypeVoid;
}

#endif // IDTYPE_H
