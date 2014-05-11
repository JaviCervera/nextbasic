#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum TokenType {
    // End of file and line
    TokenEndOfFile,
    TokenEndOfLine,

    // Preprocessor
    TokenPreprocInclude,
	TokenPreprocUse,
    TokenPreprocLink,
    TokenPreprocOption,

    // Literals
    TokenIntLiteral,
    TokenFloatLiteral,
    TokenStringLiteral,

    // Symbols
    TokenNot,
    TokenAnd,
    TokenOr,
    TokenNotEqual,
    TokenGreater,
    TokenLesser,
    TokenGreaterEqual,
    TokenLesserEqual,
    TokenPlus,
    TokenMinus,
    TokenMul,
    TokenDiv,
    TokenMod,
    TokenAssign,
    TokenComma,
    TokenColon,
    TokenDot,
    TokenOpenParen,
    TokenCloseParen,
    TokenPercent,
    TokenSharp,
    TokenDollar,

    // Keywords
    TokenProgram,
    TokenEndProgram,
    TokenIf,
    TokenElse,
    TokenElseIf,
    TokenEndIf,
    TokenSelect,
    TokenCase,
    TokenDefault,
    TokenEndSelect,
    TokenFor,
    TokenTo,
    TokenStep,
    TokenNext,
    TokenRepeat,
    TokenUntil,
    TokenWhile,
    TokenEndWhile,
    TokenExit,
    TokenDim,
    TokenAs,
    TokenIntKeyword,
    TokenFloatKeyword,
    TokenStringKeyword,
	TokenPCharKeyword,
    TokenFunction,
    TokenEndFunction,
    TokenReturn,
    TokenConst,
    TokenStruct,
    TokenEndStruct,
    TokenExtern,
    TokenEndExtern,
    TokenNew,
    TokenDelete,
    TokenTrue,
    TokenFalse,
    TokenNull,

    // Identifiers
    TokenIdentifier,

    // Script token codes
    TokenScriptFunction,
    TokenHostFunction,
    TokenGlobalVar,
    TokenLocalVar
};

class Token {
public:
    Token() : type(TokenEndOfFile), data(""), file(""), line(0) {}
    Token(TokenType type, const std::string& data, const std::string& file, int line) : type(type), data(data), file(file), line(line) {}

    static bool IsPreprocKeyword(TokenType type) { return (type >= TokenPreprocInclude && type <= TokenPreprocOption); }
    static bool IsKeyword(TokenType type) { return (type >= TokenIf && type <= TokenReturn); }
    static bool IsBooleanLiteral(TokenType type) { return (type == TokenTrue || type == TokenFalse); }
    static bool IsNullLiteral(TokenType type) { return (type == TokenNull); }
    static bool IsBooleanOp(TokenType type) { return (type >= TokenAnd && type <= TokenOr); }
    static bool IsRelationalOp(TokenType type) { return (type >= TokenNotEqual && type <= TokenLesserEqual) || type == TokenAssign; }
    static bool IsAdditiveOp(TokenType type) { return (type >= TokenPlus && type <= TokenMinus); }
    static bool IsMultiplicativeOp(TokenType type) { return (type >= TokenMul && type <= TokenMod); }
    static bool IsUnaryOp(TokenType type) { return ((type == TokenNot) || (type == TokenMinus)); }
    static bool IsEol(TokenType type) { return (type == TokenEndOfLine); }
    static bool IsEndStatement(TokenType type) { return (type == TokenColon) || (type == TokenEndOfLine); }

    TokenType Type() const { return type; }
    const std::string& Data() const { return data; }
    const std::string& File() const { return file; }
    int Line() const { return line; }
    bool IsPreprocKeyword() const { return IsPreprocKeyword(type); }
    bool IsKeyword() const { return IsKeyword(type); }
    bool IsBooleanLiteral() const { return IsBooleanLiteral(type); }
    bool IsNullLiteral() const { return IsNullLiteral(type); }
    bool IsBooleanOp() const { return IsBooleanOp(type); }
    bool IsRelationalOp() const { return IsRelationalOp(type); }
    bool IsAdditiveOp() const { return IsAdditiveOp(type); }
    bool IsMultiplicativeOp() const { return IsMultiplicativeOp(type); }
    bool IsUnaryOp() const { return IsUnaryOp(type); }
    bool IsEol() const { return IsEol(type); }
    bool IsEndStatement() const { return IsEndStatement(type); }
private:
    TokenType type;
    std::string data;
    std::string file;
    int line;
};

#endif // TOKEN_H
