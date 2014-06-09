#include "lexical.h"
#include "../core/array.h"
#include "../core/string.h"
#include <map>

using namespace std;

Lexical::Lexical(const string& filename) {
	// Open file
	buffer = LoadString(filename);
	if ( buffer == "" ) {
		error = "Could not open file '" + filename + "'";
		return;
	}
	buffer = Replace(Replace(buffer, "\r\n", "\n"), "\r", "\n") + "\n";
	
	// Init vars
	p = 0;
	file = filename;
	line = 1;
	
	// Fill symbols table
	string spacedSymbols = "<> >= <= > < + - * / = , : . ( ) % # $";
	int arr = SplitString(spacedSymbols, " ");
	for ( int i = 0; i < CountArray(arr); i++ ) {
		symbols.push_back(ArrayString(arr, i));
	}
	FreeArray(arr);

    // Fill preprocessor table
	string spacedPreprocessor = "$include $use $link $option";
	arr = SplitString(spacedPreprocessor, " ");
	for ( int i = 0; i < CountArray(arr); i++ ) preprocessor.push_back(ArrayString(arr, i));
	FreeArray(arr);

    // Parse all tokens
    while ( true ) {
        Token token = NextToken();
        if ( token.Type() == TokenEndOfFile ) {
            errorToken = token;
            break;
        }
        tokens.push_back(token);
    }
}

Token Lexical::NextToken() {
    // Skip white spaces
    SkipSpaces();

    // Check end of file
    if ( p == (int)buffer.length() ) return Token(TokenEndOfFile, "", file, line);

    // Check end of line
    if ( buffer[p] == '\n' ) {
        p++;
        return Token(TokenEndOfLine, "\n", file, line++);
    }

    // Check preprocessor
    string preproc = CheckPreprocessor();
    if ( preproc != "" ) {
        p += preproc.length();
        return Token(GetType(preproc), preproc, file, line);
    }

	// Check number
	if ( IsNumber(buffer[p])
			|| (p < (int)buffer.length()-1 && (buffer[p] == '$' && IsNumber(buffer[p+1]))) ) {
		TokenType type = TokenIntLiteral;
		bool isHex = (buffer[p] == '$');
		string str(1, buffer[p++]);
		while ( IsNumber(buffer[p]) || (isHex && IsHexChar(buffer[p])) ) str += buffer[p++];
		if ( buffer[p] == '.' ) {
			if ( isHex ) {
				error = "Invalid decimal number";
				return Token(TokenEndOfFile, "", file, line);
			}
			type = TokenFloatLiteral;
			str += ".";
			p++;
			if ( !IsNumber(buffer[p]) ) {
				error = "Invalid decimal number";
				return Token(TokenEndOfFile, "", file, line);
			}
			while ( IsNumber(buffer[p]) ) str += buffer[p++];
		}
		return Token(type, str, file, line);
	}

    // Check symbol
    string symbol = CheckSymbol();
    if ( symbol != "" ) {
        p += symbol.length();
        return Token(GetType(symbol), symbol, file, line);
    }

    // Check string
    if ( buffer[p] == '"' ) {
        string str = "";
        p++;    // Skip "
        while ( p < (int)buffer.length() && buffer[p] != '"' && buffer[p] != '\n' ) str += buffer[p++];
        if ( buffer[p] != '"' ) {
            error = "String must be closed";
            return Token(TokenEndOfFile, "", file, line);
        }
        p++;    // Skip "
        return Token(TokenStringLiteral, str, file, line);
    }

    // Check keyword or identifier
    if ( IsAlpha(buffer[p]) ) {
        string str = "";
        while ( p < (int)buffer.length() && (IsAlpha(buffer[p]) || IsNumber(buffer[p])) ) str += buffer[p++];
        return Token(GetType(str), str, file, line);
    }

    // Not recognized;
    error = "Unrecognized token";
    string str = "";
    str += buffer[p];
    return Token(TokenEndOfFile, str, file, line);
}

void Lexical::SkipSpaces() {
    while ( p < (int)buffer.length() && ((buffer[p] == ' ') || (buffer[p] == '\t') || IsSingleLineComment()) ) {
        if ( IsSingleLineComment() ) {
            while ( p < (int)buffer.length() && buffer[p] != '\n' ) p++;
        } else {
            p++;
        }
    }
}

bool Lexical::IsSingleLineComment() {
	if ( buffer[p] == '\'' )
        return true;
    else
        return false;
}

bool Lexical::IsNumber(char c) {
    if ( c >= '0' && c <= '9' )
        return true;
    else
        return false;
}

bool Lexical::IsAlpha(char c) {
    if ( c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') )
        return true;
    else
        return false;
}

bool Lexical::IsHexChar(char c) {
	if ( (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') )
		return true;
	else
		return false;
}

string Lexical::CheckSymbol() {
    for ( vector<string>::iterator it = symbols.begin(); it != symbols.end(); it++ ) {
        string str = "";
        for ( unsigned int i = 0; i < (*it).length(); i++ ) {
            if ( p+i >= buffer.length() ) continue;
            str += buffer[p+i];
        }
        if ( str == *it ) return str;
    }
    return "";
}

string Lexical::CheckPreprocessor() {
    for ( vector<string>::iterator it = preprocessor.begin(); it != preprocessor.end(); it++ ) {
        string str = "";
        for ( unsigned int i = 0; i < (*it).length(); i++ ) {
            if ( p+i >= buffer.length() ) continue;
            str += buffer[p+i];
        }
		if ( Lower(str) == *it ) return str;
    }
    return "";
}

TokenType Lexical::GetType(const string& symbol) {
    static map<string,TokenType> type;
    if ( type.size() == 0 ) {
        // Preprocessor
        type["$include"] = TokenPreprocInclude;
		type["$use"] = TokenPreprocUse;
        type["$link"] = TokenPreprocLink;
        type["$option"] = TokenPreprocOption;

        // Symbols
        type["not"] = TokenNot;
        type["and"] = TokenAnd;
        type["or"] = TokenOr;
        type["<>"] = TokenNotEqual;
        type[">"] = TokenGreater;
        type["<"] = TokenLesser;
        type[">="] = TokenGreaterEqual;
        type["<="] = TokenLesserEqual;
        type["+"] = TokenPlus;
        type["-"] = TokenMinus;
        type["*"] = TokenMul;
        type["/"] = TokenDiv;
        type["mod"] = TokenMod;
        type["="] = TokenAssign;
        type[","] = TokenComma;
        type[":"] = TokenColon;
        type["."] = TokenDot;
        type["("] = TokenOpenParen;
        type[")"] = TokenCloseParen;
        type["%"] = TokenPercent;
        type["#"] = TokenSharp;
        type["$"] = TokenDollar;

        // Keywords
        type["program"] = TokenProgram;
        type["endprogram"] = TokenEndProgram;
        type["if"] = TokenIf;
        type["else"] = TokenElse;
        type["elseif"] = TokenElseIf;
        type["endif"] = TokenEndIf;
        type["select"] = TokenSelect;
        type["case"] = TokenCase;
        type["default"] = TokenDefault;
        type["endselect"] = TokenEndSelect;
        type["for"] = TokenFor;
        type["to"] = TokenTo;
        type["step"] = TokenStep;
        type["next"] = TokenNext;
        type["repeat"] = TokenRepeat;
        type["until"] = TokenUntil;
        type["while"] = TokenWhile;
        type["endwhile"] = TokenEndWhile;
        type["exit"] = TokenExit;
        type["dim"] = TokenDim;
        type["as"] = TokenAs;
        type["int"] = TokenIntKeyword;
        type["float"] = TokenFloatKeyword;
        type["string"] = TokenStringKeyword;
		type["pchar"] = TokenPCharKeyword;
        type["function"] = TokenFunction;
        type["endfunction"] = TokenEndFunction;
        type["return"] = TokenReturn;
        type["const"] = TokenConst;
        type["struct"] = TokenStruct;
        type["endstruct"] = TokenEndStruct;
        type["extern"] = TokenExtern;
        type["endextern"] = TokenEndExtern;
        type["new"] = TokenNew;
        type["delete"] = TokenDelete;
        type["true"] = TokenTrue;
        type["false"] = TokenFalse;
        type["null"] = TokenNull;
    }

	if ( type.count(Lower(symbol)) > 0 )
		return type[Lower(symbol)];
    else
        return TokenIdentifier;
}
