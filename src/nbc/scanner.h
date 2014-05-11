#ifndef SCANNER_H
#define SCANNER_H

#include "../core/string.h"
#include "idtype.h"
#include "tokenstream.h"
#include <string>
#include <vector>

class Var {
public:
    Var(IdType type, const std::string& name, const std::string& structName) : type(type), name(name), structName(structName), initExpOffset(0) {}
    IdType Type() const { return type; }
    const std::string& Name() const { return name; }
    const std::string& StructName() const { return structName; }
    int InitExpOffset() const { return initExpOffset; }
    void SetInitExpOffset(int offset) { initExpOffset = offset; }
    void SetIndexPath(const std::vector<int>& path) { indexPath = path; }
    const std::vector<int> IndexPath() const { return indexPath; }
private:
    IdType type;
    std::string name;
    std::string structName;
    int initExpOffset;
    std::vector<int> indexPath;
};

class Struct {
public:
    Struct(const std::string& name) : name(name) {}
    const std::string& Name() const { return name; }
    int NumFields() const { return fields.size(); }
    const Var& Field(int index) const { return fields[index]; }
    Var& Field(int index) { return fields[index]; }
	Var* Field(const std::string& name) { for ( std::vector<Var>::iterator it = fields.begin(); it != fields.end(); it++ ) if ( Lower((*it).Name()) == Lower(name) ) return &(*it); return NULL; }
	const Var* Field(const std::string& name) const { for ( std::vector<Var>::const_iterator it = fields.begin(); it != fields.end(); it++ ) if ( Lower((*it).Name()) == Lower(name) ) return &(*it); return NULL; }
    void SetFields(const std::vector<Var>& fields) { this->fields = fields; }
private:
    std::string name;
    std::vector<Var> fields;
};

class Function {
public:
    Function(const std::string& name, IdType type, const std::vector<Var>& args) : name(name), type(type), numArgs(args.size()), offset(-1), libName("") { SetLocals(args); }
    const std::string& Name() const { return name; }
    IdType Type() const { return type; }
    int NumArgs() const { return numArgs; }
    int NumLocals() const { return locals.size(); }
    void SetLocals(const std::vector<Var>& locals) { this->locals = locals; }
    void SetNumArgs(int numArgs) { this->numArgs = numArgs; }
    const Var& Local(int index) const { return locals[index]; }
    const std::vector<Var>& Locals() const { return locals; }
	int LocalIndex(const std::string& name) const { for ( unsigned int i = 0; i < locals.size(); i++ ) if ( Lower(locals[i].Name()) == Lower(name) ) return i; return -1; }
    void SetOffset(int offset) { this->offset = offset; }
    int Offset() const { return offset; }
    bool IsExtern() const { return offset == -1; }
    void SetExternName(const std::string& name) { externName = name; }
    const std::string& ExternName() const { return externName; }
    void SetLibName(const std::string& name) { libName = name; }
    const std::string& LibName() const { return libName; }
private:
    std::string name;
    IdType type;
    int numArgs;
    std::vector<Var> locals;
    int offset;
    std::string externName;
    std::string libName;
};

class Program {
public:
    Program() : offset(-1) {}
    int NumLocals() const { return locals.size(); }
    void SetLocals(const std::vector<Var>& locals) { this->locals = locals; }
    const Var& Local(int index) const { return locals[index]; }
	int LocalIndex(const std::string& name) const { for ( unsigned int i = 0; i < locals.size(); i++ ) if ( Lower(locals[i].Name()) == Lower(name) ) return i; return -1; }
    void SetOffset(int offset) { this->offset = offset; }
    int Offset() const { return offset; }
private:
    std::vector<Var> locals;
    int offset;
};

class Scanner {
public:
    Scanner(const std::vector<Token>& tokens) : stream(tokens) {}

    void AddConstant(const Var& var) { constants.push_back(var); }
    Function* AddFunction(const Function& func) { functions.push_back(func); return &functions.back(); }

    void ParseConstants();
    void ParseStructs();
    void ParseGlobals();
    void ParseFunctions();
    void ParseLocals(int pos, const std::vector<Var>* args);

    int CountConstantOccurences(std::string name) const;
    int CountStructOccurences(std::string name) const;
    int CountGlobalOccurences(std::string name) const;
    int CountFunctionOccurences(std::string name) const;
    int CountLocalOccurences(std::string name) const;

    int NumConstants() const { return constants.size(); }
    int NumStructs() const { return structs.size(); }
    int NumGlobals() const { return globals.size(); }
    int NumFunctions() const { return functions.size(); }
    int NumLocals() const { return locals.size(); }

    const Var& GetConstant(int index) const { return constants[index]; }
	Var* GetConstant(const std::string& name) { for ( std::vector<Var>::iterator it = constants.begin(); it != constants.end(); it++ ) if ( Lower((*it).Name()) == Lower(name) ) return &(*it); return NULL; }
	const Var* GetConstant(const std::string& name) const { for ( std::vector<Var>::const_iterator it = constants.begin(); it != constants.end(); it++ ) if ( Lower((*it).Name()) == Lower(name) ) return &(*it); return NULL; }
	int ConstantIndex(const std::string& name) const { for ( unsigned int i = 0; i < constants.size(); i++ ) if ( Lower(constants[i].Name()) == Lower(name) ) return i; return -1; }

    const Struct& GetStruct(int index) const { return structs[index]; }
	const Struct* GetStruct(const std::string& name) const { for ( std::vector<Struct>::const_iterator it = structs.begin(); it != structs.end(); it++ ) if ( Lower((*it).Name()) == Lower(name) ) return &(*it); return NULL; }
	Struct* GetStruct(const std::string& name) { for ( std::vector<Struct>::iterator it = structs.begin(); it != structs.end(); it++ ) if ( Lower((*it).Name()) == Lower(name) ) return &(*it); return NULL; }
	int StructIndex(const std::string& name) const { for ( unsigned int i = 0; i < structs.size(); i++ ) if ( Lower(structs[i].Name()) == Lower(name) ) return i; return -1; }

    const Var& GetGlobal(int index) const { return globals[index]; }
	Var* GetGlobal(const std::string& name) { for ( std::vector<Var>::iterator it = globals.begin(); it != globals.end(); it++ ) if ( Lower((*it).Name()) == Lower(name) ) return &(*it); return NULL; }
	const Var* GetGlobal(const std::string& name) const { for ( std::vector<Var>::const_iterator it = globals.begin(); it != globals.end(); it++ ) if ( Lower((*it).Name()) == Lower(name) ) return &(*it); return NULL; }
	int GlobalIndex(const std::string& name) const { for ( unsigned int i = 0; i < globals.size(); i++ ) if ( Lower(globals[i].Name()) == Lower(name) ) return i; return -1; }

    const Function& GetFunction(int index) const { return functions[index]; }
	const Function* GetFunction(const std::string& name) const { for ( std::vector<Function>::const_iterator it = functions.begin(); it != functions.end(); it++ ) if ( Lower((*it).Name()) == Lower(name) ) return &(*it); return NULL; }
	Function* GetFunction(const std::string& name) { for ( std::vector<Function>::iterator it = functions.begin(); it != functions.end(); it++ ) if ( Lower((*it).Name()) == Lower(name) ) return &(*it); return NULL; }
	int FunctionIndex(const std::string& name) const { for ( unsigned int i = 0; i < functions.size(); i++ ) if ( Lower(functions[i].Name()) == Lower(name) ) return i; return -1; }
    int FunctionArguments(std::string name) const;

    const Program& GetProgram() const { return program; }
    Program& GetProgram() { return program; }

    const Var& GetLocal(int index) const { return locals[index]; }
	Var* GetLocal(const std::string& name) { for ( std::vector<Var>::iterator it = locals.begin(); it != locals.end(); it++ ) if ( Lower((*it).Name()) == Lower(name) ) return &(*it); return NULL; }
	const Var* GetLocal(const std::string& name) const { for ( std::vector<Var>::const_iterator it = locals.begin(); it != locals.end(); it++ ) if ( Lower((*it).Name()) == Lower(name) ) return &(*it); return NULL; }

    void SetLocals(const std::vector<Var>& locals) { this->locals = locals; }

    bool IsType(const Token& token) const;
private:
    TokenStream stream;
    std::vector<Var> constants;
    std::vector<Struct> structs;
    std::vector<Var> globals;
    std::vector<Function> functions;
    Program program;
    std::vector<Var> locals;
};

#endif // SCANNER_H
