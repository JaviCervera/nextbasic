#ifndef SYNTACTICAL_H
#define SYNTACTICAL_H

#include "tokenstream.h"
#include "scanner.h"
#include <vector>

enum DimScope {
    SCOPE_GLOBAL,
    SCOPE_LOCAL,
    SCOPE_CONST,
    SCOPE_STRUCT,
    SCOPE_FOR
};

class Syntactical {
public:
    Syntactical(const std::vector<Token>& tokens);
    Scanner& GetScanner() { return scanner; }
protected:
    void ParseConstant();
    IdType ParseDim(DimScope scope = SCOPE_GLOBAL);
    void ParseStruct();
    void ParseExtern();
    void ParseFunction(bool externFunc);
    std::vector<Var> ParseArgs(bool externFunc);
    void ParseProgram();
    int ParseBlock(const std::vector<TokenType>& endTypes, const std::vector<Var>* args, TokenType* endType);
    void ParseStatement();
    void ParseEndStatement();
    void ParseKeyword();
    void ParseIf();
    void ParseSelect();
    void ParseFor();
    void ParseRepeat();
    void ParseWhile();
    void ParseReturn();
    void ParseExit();
    IdType ParseExpression(bool isConditional);
    IdType ParseAssignmentExp(bool isConditional);
    IdType ParseBooleanExp(bool isConditional);
    IdType ParseRelationalExp(bool isConditional);
    IdType ParseAdditiveExp(bool isConditional);
    IdType ParseMultiplicativeExp(bool isConditional);
    IdType ParseFactor(bool isConditional);
    IdType ParseVarAccess();
    IdType ParseMemberAccess(const Struct& structure);
    IdType ParseFunctionCall();
    bool AreTypesCompatible(IdType type1, IdType type2);
    IdType CastTypes(IdType type1, IdType type2);
    bool IsValidIdentifier(const std::string& name, bool checkLocals);
    int NumDefinitions(const std::string& name, bool checkLocals);
    bool IsEndType(const std::vector<TokenType>& endTypes, TokenType token);
    int ResolveIntConstant(const Var* constant);
private:
    TokenStream stream;
    Scanner scanner;
    int inLoop;

    const Function* currentFunction;
};

#endif // SYNTACTICAL_H
