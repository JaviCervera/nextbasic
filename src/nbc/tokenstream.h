#ifndef TOKENSTREAM_H
#define TOKENSTREAM_H

#include "token.h"
#include <vector>

class TokenStream {
public:
    TokenStream(const std::vector<Token>& tokens) : tokens(tokens), p(0) {}
    void Reset() { Seek(0); }
    const Token& Next() { return tokens[p++]; }
    const Token& Peek(int ofs=0) const { return tokens[p+ofs]; }
    void Back() { p--; }
    bool HasNext() const { return p < (int)tokens.size(); }
    void Seek(int pos) { p = pos; }
    void Skip(int count) { p += count; }
    void SkipEmpty() { while ( HasNext() && (Peek().Type() == TokenColon || Peek().Type() == TokenEndOfLine) ) p++; }
    int Pos() const { return p; }
private:
    const std::vector<Token>& tokens;
    int p;
};

#endif // TOKENSTREAM_H
