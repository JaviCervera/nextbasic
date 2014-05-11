#ifndef LEXICAL_H
#define LEXICAL_H

#include "token.h"
#include <string>
#include <vector>

class Lexical {
public:
	Lexical(const std::string& filename);
	
    const std::vector<Token>& Tokens() const { return tokens; }
	const std::string& Error() const { return error; }
    const Token& ErrorToken() const { return errorToken; }
protected:
    Token NextToken();
    void SkipSpaces();
    bool IsSingleLineComment();
    bool IsNumber(char c);
    bool IsAlpha(char c);
	bool IsHexChar(char c);
    std::string CheckSymbol();
    std::string CheckPreprocessor();
    TokenType GetType(const std::string& symbol);
private:
	std::string buffer;
	int p;
	
	std::string file;
	int line;
	
	std::vector<std::string> symbols;
    std::vector<std::string> preprocessor;

	std::string error;
    Token errorToken;

    std::vector<Token> tokens;
};

#endif // LEXICAL_H
