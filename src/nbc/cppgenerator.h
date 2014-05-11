#ifndef CGENERATOR_H
#define CGENERATOR_H

#include "tokenstream.h"
#include "scanner.h"
#include <string>
#include <vector>

class CppGenerator {
public:
	CppGenerator(const std::string& filename, const std::vector<Token>& tokens, Scanner& scanner, const std::vector<std::string>& modules, const std::vector<std::string>& links, bool isGuiApp);
protected:
    void WriteIncludes();
	void WriteConstants();
	void WriteStructs();
    void WriteExternStaticFunctions();
    void WriteExternSharedFunctions();
    void WriteFunctionDecls();
    void WriteLibsInitializer();
    void WriteGlobalDecls();
    void WriteFunctions();
    void WriteSharedFunction(const Function& func);
    void WriteFunctionDecl(const Function& func);
    void WriteFunction(const Function& func);
    void WriteProgram();
    void WriteGlobalInit(const Var& global);
    void WriteLocalDecl(const Var& local);
    void WriteLocalInit(const Var& local);
    std::string ConvertDim();
    std::string ConvertBlock(int pos, TokenType *endType);
    std::string ConvertStatement();
    std::string ConvertKeyword();
    std::string ConvertIf();
    std::string ConvertSelect();
    std::string ConvertFor();
    std::string ConvertRepeat();
    std::string ConvertWhile();
    std::string ConvertReturn();
    std::string ConvertExit();
    std::string ConvertExpression(bool isConditional);
    std::string ConvertAssignmentExp(bool isConditional);
    std::string ConvertBooleanExp(bool isConditional);
    std::string ConvertRelationalExp(bool isConditional);
    std::string ConvertAdditiveExp(bool isConditional);
    std::string ConvertMultiplicativeExp(bool isConditional);
    std::string ConvertFactor(bool isConditional);
    std::string ConvertVarAccess();
    std::string ConvertMemberAccess(const Struct& structure);
    std::string ConvertFunctionCall();
    std::string ConvertType(IdType type);
    std::string ConvertToken(const Token& tok);
    std::string SkipEmpty();
	std::string InitFields(const Struct& st);
    std::string DefaultInitForType(IdType type);
    std::string StripTrailingSemicolon(std::string str);
    std::string StripTrailingAsterisk(std::string str);
    bool IsEndType(TokenType type) const;
    IdType VarType(const std::string &var) const;
    IdType CastTypes(IdType type1, IdType type2) const;
private:
    std::string filename;
    TokenStream stream;
    Scanner& scanner;
    int numTabs;
    const Function* currentFunction;
    std::string lastIdentifier;
    IdType lastExpType;
    int selectNum;
};

#endif // CGENERATOR_H
