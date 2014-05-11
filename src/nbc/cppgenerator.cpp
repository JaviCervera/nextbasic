#include "cppgenerator.h"
#include "error.h"
#include "../core/string.h"
#include <map>
#include <iostream>

using namespace std;

CppGenerator::CppGenerator(const string &filename, const vector<Token> &tokens, Scanner &scanner, const std::vector<string>& modules, const std::vector<string>& links, bool isGuiApp)
	: filename(filename), stream(tokens), scanner(scanner), numTabs(0), selectNum(0) {

	// Create or empty file
	SaveString("", filename, false);

	// Write nbmake info
	string modulesStr = "//$modules:";
	for ( std::vector<string>::const_iterator it = modules.begin(); it != modules.end(); it++ ) {
		modulesStr += *it;
		if ( it != modules.end() - 1 ) modulesStr += ",";
	}
	modulesStr += "\n";
	SaveString(modulesStr, filename, true);
	string linksStr = "//$libs:";
	for ( std::vector<string>::const_iterator it = links.begin(); it != links.end(); it++ ) {
		linksStr += *it;
		if ( it != links.end() - 1 ) linksStr += ",";
	}
	linksStr += "\n";
	SaveString(linksStr, filename, true);
	if ( isGuiApp ) {
		SaveString("//$options:gui\n", filename, true);
	} else {
		SaveString("//$options:console\n", filename, true);
	}

	// Write stuff
	WriteIncludes();
	WriteConstants();
	WriteStructs();
	WriteExternStaticFunctions();
	WriteExternSharedFunctions();
	WriteLibsInitializer();
	WriteGlobalDecls();
	WriteFunctionDecls();
	WriteFunctions();
	WriteProgram();
}

void CppGenerator::WriteIncludes() {
	// Required includes
	SaveString("#include <string.h>\n", filename, true);
	SaveString("#include <string>\n", filename, true);
	SaveString("#if defined(_WIN32)\n#define CALLCONV __stdcall\n#else\n#define CALLCONV\n#endif\n\n", filename, true);
	SaveString("extern \"C\" {\n\n", filename, true);
	SaveString("void __nb_setprogramname__(const char* name);\n", filename, true);
	SaveString("void __nb_setcommandline__(int num, char* args[]);\n\n", filename, true);
}

// [#define nb_$ConstantName $Value $NewLine]*
void CppGenerator::WriteConstants() {
	int i;
	for ( i = 0; i < scanner.NumConstants(); i++ ) {
		const Var& constant = scanner.GetConstant(i);
		stream.Seek(constant.InitExpOffset());
		string str = StripTrailingSemicolon(ConvertStatement());
		SaveString("#define nb_" + constant.Name() + " " + str + "\n", filename, true);
	}
	if ( i > 0 ) SaveString("\n", filename, true);
}

// [typedef struct { $NewLine [$Tab $Type nb_$FieldName [$IndexPath] ; $NewLine]* } nb_$StructName ; $NewLine $NewLine]*
void CppGenerator::WriteStructs() {
	int i;
	for ( i = 0; i < scanner.NumStructs(); i++ ) {
		const Struct& st = scanner.GetStruct(i);

		// Write header
		SaveString("struct nb_" + st.Name() + " {\n", filename, true);

		// Write fields
		for ( int j = 0; j < st.NumFields(); j++ ) {
			const Var& field = st.Field(j);
			string fieldStr = "\t" + ConvertType(field.Type()) + " nb_" + field.Name();
			for ( int k = 0; k < (int)field.IndexPath().size(); k++ ) {
				fieldStr += "[" + Str(field.IndexPath()[k]) + "]";
			}
			fieldStr += ";\n";
			SaveString(fieldStr, filename, true);
		}

		// Write constructor
		SaveString("\tnb_" + st.Name() + "() {\n", filename, true);
		SaveString(InitFields(st), filename, true);
		SaveString("\t}\n", filename, true);

		// Write footer
		SaveString("};\n\n", filename, true);
	}
	if ( i > 0 ) SaveString("\n", filename, true);
}

void CppGenerator::WriteExternStaticFunctions() {
	int i;
	for ( i = 0; i < scanner.NumFunctions(); i++ ) {
		const Function& func = scanner.GetFunction(i);
		if ( func.IsExtern() && func.LibName() == "" ) WriteFunction(func);
	}
	if ( i > 0 ) SaveString("\n", filename, true);
}

void CppGenerator::WriteExternSharedFunctions() {
	int i;
	for ( i = 0; i < scanner.NumFunctions(); i++ ) {
		const Function& func = scanner.GetFunction(i);
		if ( func.IsExtern() && func.LibName() != "" ) WriteSharedFunction(func);
	}
	if ( i > 0 ) SaveString("\n", filename, true);
}

void CppGenerator::WriteFunctionDecls() {
	int i;
	for ( i = 0; i < scanner.NumFunctions(); i++ ) {
		const Function& func = scanner.GetFunction(i);
		if ( !func.IsExtern() ) WriteFunctionDecl(func);
	}
	if ( i > 0 ) SaveString("\n", filename, true);
}

void CppGenerator::WriteLibsInitializer() {
	SaveString("void __nb_loadfuncs__() {\n", filename, true);

	// Write lib handles & initialization
	vector<string> addedLibs;
	for ( int i = 0; i < scanner.NumFunctions(); i++ ) {
		const Function& func = scanner.GetFunction(i);
		if ( func.IsExtern() && func.LibName() != "" ) {
			// Check if it has been already written
			bool added = false;
			for ( vector<string>::const_iterator it = addedLibs.begin(); it != addedLibs.end(); it++ ) {
				if ( func.LibName() == *it )
					added = true;
			}

			if ( !added ) {
				addedLibs.push_back(func.LibName());
				SaveString("\tint __nb_" + func.LibName() + "Lib__ = LoadLibrary(\"" + func.LibName() + "\");\n", filename, true);
			}
		}
	}
	if ( addedLibs.size() > 0 ) SaveString("\n", filename, true);

	// Write pointer assignments
	for ( int i = 0; i < scanner.NumFunctions(); i++ ) {
		const Function& func = scanner.GetFunction(i);
		if ( func.IsExtern() && func.LibName() != "" ) {
			string externName = func.ExternName();
			if ( externName == "" )
				externName = func.Name();
			SaveString("\t" + func.Name() + " = (" + func.Name() + "Ptr)LibraryFunction(__nb_" + func.LibName() + "Lib__, \"" + externName + "\");\n", filename, true);
		}
	}

	SaveString("}\n\n", filename, true);
}

// [$Type nb_$VarName [$IndexPath] ; $NewLine]*
void CppGenerator::WriteGlobalDecls() {
	int i;
	for ( i = 0; i < scanner.NumGlobals(); i++ ) {
		const Var& global = scanner.GetGlobal(i);
		string str = "";
		if ( global.IndexPath().size() != 0 ) {
			for ( int i = 0; i < (int)global.IndexPath().size(); i++ ) {
				str += "[" + Str(global.IndexPath()[i]) + "]";
			}
		}
		SaveString(ConvertType(global.Type()) + " nb_" + global.Name() + str + ";\n", filename, true);
	}
	if ( i > 0 ) SaveString("\n", filename, true);
}

// [$Function]*
void CppGenerator::WriteFunctions() {
	int i;
	for ( i = 0; i < scanner.NumFunctions(); i++ ) {
		const Function& func = scanner.GetFunction(i);
		if ( !func.IsExtern() ) WriteFunction(func);
	}
	if ( i > 0 ) SaveString("\n", filename, true);
}

// typedef $Type ( CALLCONV * $FuncName Ptr ) ( [$ArgType] [, $ArgType]* ) ;
// $FuncName Ptr $FuncName ; $NewLine
void CppGenerator::WriteSharedFunction(const Function &func) {
	// Get correct name
	string name = func.Name();
	if ( func.ExternName() != "" ) name = func.ExternName();

	// Type Name
	SaveString("typedef " + ConvertType(func.Type()) + " (CALLCONV *" + name + "Ptr)(", filename, true);

	// Arguments
	for ( int i = 0; i < func.NumArgs(); i++ ) {
		const Var& arg = func.Local(i);
		if ( i != 0 ) SaveString(", ", filename, true);
		SaveString(ConvertType(arg.Type()), filename, true);
	}
	SaveString("); ", filename, true);

	// Func pointer
	SaveString(func.Name() + "Ptr " + func.Name() + ";\n", filename, true);
}

// $Type nb_$FuncName ( [$ArgType nb_$ArgName] [, $ArgType nb_$ArgName]* ) ; $NewLine
void CppGenerator::WriteFunctionDecl(const Function &func) {
	currentFunction = &func;

	// Name
	if ( func.IsExtern() )
		SaveString(ConvertType(func.Type()) + " " + func.Name() + "(", filename, true);
	else
		SaveString(ConvertType(func.Type()) + " nb_" + func.Name() + "(", filename, true);

	// Set scanner locals
	vector<Var> locals;
	for ( int i = 0; i < func.NumLocals(); i++) {
		locals.push_back(func.Local(i));
	}
	scanner.SetLocals(locals);

	// Arguments
	for ( int i = 0; i < func.NumArgs(); i++ ) {
		const Var& arg = func.Local(i);
		if ( i != 0 ) SaveString(", ", filename, true);
		SaveString(ConvertType(arg.Type()) + " nb_" + arg.Name(), filename, true);
	}
	SaveString(")", filename, true);

	// ; $NewLine
	SaveString(";\n", filename, true);
}

// $Type nb_$FuncName ( [$ArgType nb_$ArgName] [, $ArgType nb_$ArgName]* ) { $NewLine [($LocalType nb_$LocalName) = $Statement | (char* nb_$LocalName = 0; __nb_strassign__( &nb_$LocalName, $Expression ); ) $NewLine]* $Block $NewLine } $NewLine $NewLine
void CppGenerator::WriteFunction(const Function &func) {
	currentFunction = &func;

	// Get correct name
	string name = func.Name();
	if ( func.ExternName() != "" ) name = func.ExternName();

	// Name
	if ( func.IsExtern() )
		SaveString(ConvertType(func.Type()) + " " + name + "(", filename, true);
	else
		SaveString(ConvertType(func.Type()) + " nb_" + name + "(", filename, true);

	// Set scanner locals
	vector<Var> locals;
	for ( int i = 0; i < func.NumLocals(); i++) {
		locals.push_back(func.Local(i));
	}
	scanner.SetLocals(locals);

	// Arguments
	for ( int i = 0; i < func.NumArgs(); i++ ) {
		const Var& arg = func.Local(i);
		if ( i != 0 ) SaveString(", ", filename, true);
		SaveString(ConvertType(arg.Type()) + " nb_" + arg.Name(), filename, true);
	}
	SaveString(")", filename, true);

	// Extern function
	if ( func.IsExtern() ) {
		SaveString(";\n", filename, true);
		// NextBasic function
	} else {
		SaveString(" {\n", filename, true);

		// Check if there are any Select structures
		int offset = stream.Pos();                  // Save stream pos
		vector<IdType> selectTypes;                 // Expression types in Select structures
		stream.Seek(currentFunction->Offset()); // Move to beginning of block
		while ( stream.Peek().Type() != TokenEndFunction ) {
			if ( stream.Next().Type() == TokenSelect ) {
				ConvertExpression(true);
				selectTypes.push_back(lastExpType);
			}
		}
		stream.Seek(offset);   // Restore stream position

		// Write select control vars (if any)
		int i = 0;
		string str = "";
		for ( vector<IdType>::const_iterator it = selectTypes.begin(); it != selectTypes.end(); it++ ) {
			if ( str != "" ) str += " ";
			str += ConvertType(*it) + " select" + Str(i) + ";";
			i++;
		}
		if ( str != "" ) SaveString("\t" + str + "\n", filename, true);

		// Local decls
		for ( int i = func.NumArgs(); i < func.NumLocals(); i++ ) {
			WriteLocalDecl(func.Local(i));
		}
		if ( func.NumLocals() > 0 ) SaveString("\n", filename, true);

		// Local inits
		for ( int i = func.NumArgs(); i < func.NumLocals(); i++ ) {
			WriteLocalInit(func.Local(i));
		}
		if ( func.NumLocals() > 0 ) SaveString("\n", filename, true);

		// Block
		numTabs = 0;
		selectNum = 0;
		SaveString("\t" + ConvertBlock(func.Offset(), NULL) + "\n", filename, true);

		// Default return statement
		if ( func.Type() != TypeVoid ) SaveString(string("\treturn ") + DefaultInitForType(func.Type()) + ";\n", filename, true);

		// End
		SaveString("}\n\n", filename, true);
	}
}

// int main(int argc, char** argv) { $NewLine [($LocalType nb_$LocalName) = $Statement | (char* nb_$LocalName = 0; __nb_strassign__( &nb_$LocalName, $Expression ); ) $NewLine]* $Block $NewLine } $NewLine $NewLine
void CppGenerator::WriteProgram() {
	currentFunction = NULL;

	// Name
	SaveString("int main(int argc, char** argv) {\n", filename, true);

	// Set scanner locals
	vector<Var> locals;
	for ( int i = 0; i < scanner.GetProgram().NumLocals(); i++) {
		locals.push_back(scanner.GetProgram().Local(i));
	}
	scanner.SetLocals(locals);

	// Check if there are any Select structures
	int offset = stream.Pos();                  // Save stream pos
	vector<IdType> selectTypes;                 // Expression types in Select structures
	stream.Seek(scanner.GetProgram().Offset()); // Move to beginning of block
	while ( stream.Peek().Type() != TokenEndProgram ) {
		if ( stream.Next().Type() == TokenSelect ) {
			ConvertExpression(true);
			selectTypes.push_back(lastExpType);
		}
	}
	stream.Seek(offset);   // Restore stream position

	// Write select control vars (if any)
	int i = 0;
	string str = "";
	for ( vector<IdType>::const_iterator it = selectTypes.begin(); it != selectTypes.end(); it++ ) {
		if ( str != "" ) str += " ";
		str += ConvertType(*it) + " select" + Str(i) + ";";
		i++;
	}
	if ( str != "" ) SaveString("\t" + str + "\n", filename, true);

	// Local decls
	for ( int i = 0; i < scanner.GetProgram().NumLocals(); i++ ) {
		WriteLocalDecl(scanner.GetProgram().Local(i));
	}
	if ( scanner.GetProgram().NumLocals() > 0 ) SaveString("\n", filename, true);

	// Set program name
	SaveString("\t__nb_setprogramname__(RealPath(argv[0]).c_str());\n", filename, true);

	// Set command line
	SaveString("\t__nb_setcommandline__(argc-1, &argv[1]);\n", filename, true);

	// Set correct path if bundled
	SaveString("#ifdef __APPLE__\n", filename, true);
	SaveString("\tint pathArr = SplitString(ProgramName(), \"/\");\n", filename, true);
	SaveString("\tif ( ArrayString(pathArr, CountArray(pathArr) - 2) == \"MacOS\"  &&  ArrayString(pathArr, CountArray(pathArr) - 3) == \"Contents\") {\n", filename, true);
	SaveString("\t\tstd::string path;\n", filename, true);
	SaveString("\t\tfor ( int i = 0; i < CountArray(pathArr)-4; i++ ) path += ArrayString(pathArr, i) + \"/\";\n", filename, true);
	SaveString("\t\tChangeDir(path);\n", filename, true);
	SaveString("\t}\n", filename, true);
	SaveString("\tFreeArray(pathArr);\n", filename, true);
	SaveString("#endif\n", filename, true);

	// Load shared libs
	SaveString("\t__nb_loadfuncs__();\n", filename, true);

	// Local inits
	for ( int i = 0; i < scanner.GetProgram().NumLocals(); i++ ) {
		WriteLocalInit(scanner.GetProgram().Local(i));
	}
	if ( scanner.GetProgram().NumLocals() > 0 ) SaveString("\n", filename, true);

	// Write global and arrays initialization
	for ( int i = 0; i < scanner.NumGlobals(); i++ ) {
		WriteGlobalInit(scanner.GetGlobal(i));
	}
	SaveString("\n", filename, true);

	// Block
	numTabs = 0;
	selectNum = 0;
	SaveString("\t" + ConvertBlock(scanner.GetProgram().Offset(), NULL) + "\n", filename, true);

	// Default return statement
	SaveString(string("\treturn ") + DefaultInitForType(TypeInt) + ";\n", filename, true);

	// End
	SaveString("}\n\n} // extern \"C\"\n", filename, true);
}

void CppGenerator::WriteGlobalInit(const Var& global) {
	string str = "";

	lastIdentifier = "nb_" + global.Name();

	if ( global.IndexPath().size() == 0 ) {
		str = "\tnb_" + global.Name();
		lastIdentifier = "nb_" + global.Name();
		str += " = ";
		if ( global.InitExpOffset() != 0 ) {
			stream.Seek(global.InitExpOffset());
			str += ConvertExpression(false) + ";";
		} else {
			str += DefaultInitForType(global.Type()) + ";";
		}
	} else {
		str = "\tmemset(nb_" + global.Name() + ", 0, sizeof(" + ConvertType(global.Type()) + ")";

		// Get total number of indices
		int totalIndices = 1;
		for ( int j = 0; j < (int)global.IndexPath().size(); j++ )
			totalIndices *= global.IndexPath()[j];
		str += " * " + Str(totalIndices) + ");";
		if ( global.Type() == TypeString ) {
			// Assign strings
			str += " for ( arrIt = 0; arrIt < " + Str(totalIndices) + "; arrIt++ ) ";
			str += "__nb_strassign__((char**)&nb_" + global.Name() + "[arrIt], " + DefaultInitForType(global.Type()) + ", 0);";
		}
	}

	SaveString(str + "\n", filename, true);
}

void CppGenerator::WriteLocalDecl(const Var& local) {
	string str = "\t" + ConvertType(local.Type()) + " nb_" + local.Name();
	for ( int i = 0; i < (int)local.IndexPath().size(); i++ )
		str += "[" + Str(local.IndexPath()[i]) + "]";
	str += ";\n";
	SaveString(str, filename, true);
}

void CppGenerator::WriteLocalInit(const Var& local) {
	string str = "";
	if ( local.IndexPath().size() == 0 ) {
		str = "\tnb_" + local.Name();
		lastIdentifier = "nb_" + local.Name();
		str += " = ";
		/*if ( local.InitExpOffset() != 0 ) {
			stream.Seek(local.InitExpOffset());
			str += ConvertExpression(false) + ";";
		} else {*/
		str += DefaultInitForType(local.Type()) + ";";
		//}
	} else {
		str = "\tmemset(nb_" + local.Name() + ", 0, sizeof(" + ConvertType(local.Type()) + ")";

		// Get total number of indices
		int totalIndices = 1;
		for ( int j = 0; j < (int)local.IndexPath().size(); j++ )
			totalIndices *= local.IndexPath()[j];
		str += " * " + Str(totalIndices) + ");";

		if ( local.Type() == TypeString ) {
			// Assign strings
			str += " for ( int arrIt = 0; arrIt < " + Str(totalIndices) + "; arrIt++ ) ";
			str += "nb_" + local.Name() + "[arrIt] = " + DefaultInitForType(local.Type()) + ";";
		}
	}

	SaveString(str + "\n", filename, true);
}

// Dim/Const name [%|#|$] [$IndexPath] [As $Type] [= $Expression] $EndSt
// Only returns var initialization if there was one
string CppGenerator::ConvertDim() {
	string ret = "";

	stream.Skip(1); // Dim/Const

	// Name
	string name = ConvertToken(stream.Next());

	// Symbolic type
	if ( stream.Peek().Type() == TokenPercent )
		stream.Skip(1); // %
	else if ( stream.Peek().Type() == TokenSharp )
		stream.Skip(1); // #
	else if ( stream.Peek().Type() == TokenDollar )
		stream.Skip(1); // $

	// Array access
	if ( stream.Peek().Type() == TokenOpenParen ) {
		while ( stream.Peek().Type() != TokenCloseParen )
			stream.Skip(1); // Whatever
		stream.Skip(1); // )
	}

	// As Type
	if ( stream.Peek().Type() == TokenAs )
		stream.Skip(2); // As $Type

	// Assignment
	if ( stream.Peek().Type() == TokenAssign ) {
		stream.Skip(1); // =
		ret = name;
		lastIdentifier = name;
		ret += " = ";
		ret += ConvertExpression(false) + ";";
	}

	string empty = SkipEmpty();
	if ( ret != "" )
		ret += empty;

	return ret;
}

// [$Statement]*    NOTE: We skip var definitions
string CppGenerator::ConvertBlock(int pos, TokenType* endType) {
	// Move stream to block offset
	stream.Seek(pos);

	// Inc tab count
	numTabs++;

	// Create return var
	string str = SkipEmpty();

	// Defs and statements
	while ( !IsEndType(stream.Peek().Type()) ) {
		if ( stream.Peek().Type() == TokenDim ) {
			string dim = ConvertDim();
			if ( dim != "" )
				str += dim;
		} else {
			str += ConvertStatement();
		}
	}

	// $EndType
	TokenType type = stream.Peek().Type();
	if ( endType != NULL ) *endType = type;
	stream.Skip(1);

	// Dec tab count
	numTabs--;

	return str;
}

// $ControlStatement | $Expression ;
string CppGenerator::ConvertStatement() {
	string str = "";
	if ( stream.Peek().IsKeyword() )
		str = ConvertKeyword() + ";";
	else
		str = ConvertExpression(false) + ";";
	str += SkipEmpty();
	return str;
}

// $If | $For | $Repeat | $While | $Return
string CppGenerator::ConvertKeyword() {
	switch ( stream.Peek().Type() ) {
	case TokenIf:
		return ConvertIf();
	case TokenSelect:
		return ConvertSelect();
	case TokenFor:
		return ConvertFor();
	case TokenRepeat:
		return ConvertRepeat();
	case TokenWhile:
		return ConvertWhile();
	case TokenReturn:
		return ConvertReturn();
	case TokenExit:
		return ConvertExit();
	default:
		break;
	}
	return "";
}

// if ( $Expression ) { $Block } [else if ( $Expression ) { $Block }]* [else { $Block }]
string CppGenerator::ConvertIf() {
	// If
	string str = "if ";
	stream.Skip(1);

	// $Expression
	str += "( " + ConvertExpression(true) + " ) ";

	// $Block
	TokenType endType = TokenEndOfFile;
	str += "{ " + ConvertBlock(stream.Pos(), &endType) + " } ";

	// Optional ElseIf sequence
	while ( endType == TokenElseIf ) {
		// $Expression
		str += "else if ( " + ConvertExpression(true) + " ) ";

		// $Block
		str += "{ " + ConvertBlock(stream.Pos(), &endType) + " } ";
	}

	// Optional Else
	if ( endType == TokenElse ) {
		// $Block
		str += "else { " + ConvertBlock(stream.Pos(), NULL) + " } ";
	}

	return str;
}

// if ( ($Expression) == ($Expression) ) { $Block } [else if ( ($Expression) == ($Expression) ) { $Block }]* [else { $Block }]
string CppGenerator::ConvertSelect() {
	// If
	stream.Skip(1);

	// Save expression on the left
	string exp = ConvertExpression(true);
	SkipEmpty();    // $EndSt
	stream.Skip(1); // Case

	// Select expression and first "if"
	string str = string("select") + Str(selectNum) + " = " + exp + "; if ";

	// ( ($Expression) == ($Expression) )
	str += string("( (select") + Str(selectNum) + ") == (" + ConvertExpression(true) + ") ) ";

	// $Block
	TokenType endType = TokenEndOfFile;
	str += "{ " + ConvertBlock(stream.Pos(), &endType) + " } ";

	// Optional additional cases
	while ( endType == TokenCase ) {
		string exp2 = ConvertExpression(true);

		// else if ( ($Expression) == ($Expression) )
		str += string("else if ( (select") + Str(selectNum) + ") == (" + exp2 + ") ) ";

		// $Block
		str += "{ " + ConvertBlock(stream.Pos(), &endType) + " } ";
	}

	// Optional Default
	if ( endType == TokenDefault ) {
		// $Block
		str += "else { " + ConvertBlock(stream.Pos(), NULL) + " } ";
	}

	// Increase select number
	selectNum++;

	return str;
}

// for ( $Expression ; $Expression ; $Expression ) { $Block }
string CppGenerator::ConvertFor() {
	// For
	string str = "for ( ";
	stream.Skip(1);

	// Init expression
	string varName = stream.Peek().Data();
	if ( stream.Peek().Type() == TokenDim ) {
		stream.Skip(1); // Def
		varName = stream.Next().Data();
		if ( scanner.CountLocalOccurences(varName) > 0 )
			varName = scanner.GetLocal(varName)->Name();
		else
			varName = scanner.GetGlobal(varName)->Name();
		str += "nb_" + varName + " = ";
		if ( stream.Peek().Type() == TokenAs )
			stream.Skip(2); // As $Type
		stream.Skip(1); // =
	}
	str += ConvertExpression(false) + ";";

	// To Expression
	stream.Skip(1); // To
	str += "nb_" + varName + " <= " + ConvertExpression(false) + ";";

	// Optional step expression
	if ( stream.Peek().Type() == TokenStep ) {
		stream.Skip(1); // Step
		str += "nb_" + varName + " += " + ConvertExpression(false) + " ) ";
	} else {
		str += "nb_" + varName + " ++ ) ";
	}

	// Block
	str += "{ " + ConvertBlock(stream.Pos(), NULL) + " } ";

	return str;
}

// do { $Block } while ( ! $Expression );
string CppGenerator::ConvertRepeat() {
	// Repeat
	string str = "do ";
	stream.Skip(1);

	// $Block
	str += "{ " + ConvertBlock(stream.Pos(), NULL) + " } ";

	// Until
	stream.Skip(1);
	str += "while ( !" + ConvertExpression(true) + " );";

	return str;
}

// while ( $Expression ) { $Block }
string CppGenerator::ConvertWhile() {
	// While
	string str = "while ";
	stream.Skip(1);

	// $Expression
	str += "( " + ConvertExpression(true) + " ) ";

	// $Block
	str += "{ " + ConvertBlock(stream.Pos(), NULL) + " } ";

	return str;
}

// return [$Expression]
string CppGenerator::ConvertReturn() {
	// return
	stream.Skip(1);

	// Optional expression
	if ( stream.Peek().Type() != TokenEndOfLine ) {
		// If function returns a Struct type, last identifier is a new "ret" variable
		bool isStructType = false;
		if ( currentFunction ) {
			if ( currentFunction->Type() > TypeStruct ) {
				lastIdentifier = "ret";
				isStructType = true;
			}
		}

		// Convert return expression
		string exp = ConvertExpression(true);

		// If returns a struct type, parse correctly
		if ( isStructType )
			return "{ " + ConvertType(currentFunction->Type()) + " ret = " + exp + "; return ret;" + " }";
		// Other type
		else
			return "return " + exp;
	}

	// Return without expression
	return "return";
}

// break
string CppGenerator::ConvertExit() {
	stream.Skip(1);
	return "break";
}

// $AssignmentExp | $BooleanExp
string CppGenerator::ConvertExpression(bool isConditional) {
	if ( isConditional )
		return ConvertBooleanExp(isConditional);
	else
		return ConvertAssignmentExp(isConditional);
}

// var = $Expression
string CppGenerator::ConvertAssignmentExp(bool isConditional) {
	// Parse expression
	string str = ConvertBooleanExp(isConditional);

	// Is assignment
	if ( stream.Peek().Type() == TokenAssign ) {
		stream.Skip(1); // =

		lastIdentifier = str;

		string varName = Right(str, str.length() - 3);

		IdType expType = VarType(str);
		if ( expType == -1 )
			expType = lastExpType;
		else
			lastExpType = expType;

		return str + " = " + ConvertExpression(isConditional);

		// Not assignment
	} else {
		return str;
	}
}

// $RelationalExp [$BooleanOp $BooleanExp]
string CppGenerator::ConvertBooleanExp(bool isConditional) {
	string str = ConvertRelationalExp(isConditional);
	if ( stream.Peek().IsBooleanOp() ) {
		str += " " + ConvertToken(stream.Next()) + " ";  // boolop
		str += ConvertBooleanExp(isConditional);
		lastExpType = TypeInt;
	}
	return str;
}

// $AdditiveExp [$RelationalOp $RelationalExp]
string CppGenerator::ConvertRelationalExp(bool isConditional) {
	string str = ConvertAdditiveExp(isConditional);
	if ( (isConditional && stream.Peek().IsRelationalOp()) || (!isConditional && stream.Peek().IsRelationalOp() && stream.Peek().Type() != TokenAssign) ) {
		const Token& tok = stream.Next();
		str += " " + ConvertToken(tok) + " " + ConvertRelationalExp(isConditional);
		lastExpType = TypeInt;
		return str;
	}
	return str;
}

// $MultiplicativeExp [$AdditiveOp $AdditiveExp]
string CppGenerator::ConvertAdditiveExp(bool isConditional) {
	string str = ConvertMultiplicativeExp(isConditional);
	if ( stream.Peek().IsAdditiveOp() ) {
		str += " " + ConvertToken(stream.Next()) + " ";  // addop
		str += ConvertAdditiveExp(isConditional);
	}
	return str;
}

// $Factor [$MultiplicativeOp $MultiplicativeExp]
string CppGenerator::ConvertMultiplicativeExp(bool isConditional) {
	string str = ConvertFactor(isConditional);
	if ( stream.Peek().IsMultiplicativeOp() ) {
		str += " " + ConvertToken(stream.Next()) + " ";  // mulop
		str += ConvertMultiplicativeExp(isConditional);
	}
	return str;
}

// $UnaryOp $Factor | ( $Expression ) | $Var | $FuncPtr | $FuncCall | $Literal | new $StructName | delete $Var
string CppGenerator::ConvertFactor(bool isConditional) {
	// $UnaryOp $Factor
	if ( stream.Peek().IsUnaryOp() ) {
		const Token& tok = stream.Next();  // unop
		string str = ConvertToken(tok) + ConvertFactor(isConditional);
		if ( tok.Type() == TokenNot ) lastExpType = TypeInt;
		return str;
		// ( $Expression )
	} else if ( stream.Peek().Type() == TokenOpenParen ) {
		string str = "(";
		stream.Skip(1);  // (

		/*// If it is a cast
		if ( stream.Peek().Type() == TokenIntKeyword || stream.Peek().Type() == TokenFloatKeyword || (stream.Peek().Type() == TokenIdentifier && scanner.CountStructOccurences(stream.Peek().Data()) > 0) ) {
			const Token& typeTok = stream.Next();
			IdType type = IdTypeFromTokenType(typeTok.Type());

			// If it is a struct, get proper type
			if ( type == TypeStruct )
				type = IdType(TypeStruct + scanner.StructIndex(typeTok.Data()) + 1);

			// Convert type
			str += ConvertType(type) + ")";

			stream.Skip(1); // )
			str += ConvertFactor(isConditional);
			lastExpType = type;
		// If it is an expression
		} else {*/
		str += ConvertExpression(isConditional) + ")";
		stream.Skip(1); // )
		//}
		return str;
		// $Const | $Var | $FuncPtr | $FuncCall
	} else if ( stream.Peek().Type() == TokenIdentifier ) {
		// $Const
		if ( scanner.CountConstantOccurences(stream.Peek().Data()) > 0 ) {
			lastExpType = scanner.GetConstant(stream.Peek().Data())->Type();
			return ConvertToken(stream.Next());  // identifier
			// $FuncPtr | $FuncCall
		} else if ( scanner.CountFunctionOccurences(stream.Peek().Data()) > 0 ) {
			const Function* func = scanner.GetFunction(stream.Peek().Data());
			string str ="";
			// $FuncCall
			if ( stream.Peek(1).Type() == TokenOpenParen ) {
				str = ConvertFunctionCall();
				lastExpType = func->Type();
				// $FuncPtr
			} else {
				str = "(int)" + ConvertToken(stream.Next());
				lastExpType = TypeInt;
			}
			return str;
			// $Var
		} else {
			string str = ConvertVarAccess();
			IdType type = VarType(str);
			lastExpType = type;
			return str;
		}
		// $Literal
	} else if ( stream.Peek().Type() == TokenIntLiteral || stream.Peek().Type() == TokenFloatLiteral || stream.Peek().Type() == TokenStringLiteral ) {
		lastExpType = IdTypeFromTokenType(stream.Peek().Type());
		if ( lastExpType == TypeString )
			return "std::string(" + ConvertToken(stream.Next()) + ")";
		else
			return ConvertToken(stream.Next());
		// new $StructName
	} else if ( stream.Peek().Type() == TokenNew ) {
		stream.Skip(1); // new
		lastExpType = IdType(TypeStruct + scanner.StructIndex(stream.Next().Data()) + 1);
		string convertedType = StripTrailingAsterisk(ConvertType(lastExpType));
		return "new " + convertedType;
		// delete var
	} else if ( stream.Peek().Type() == TokenDelete ) {
		stream.Skip(1); // delete

		// Convert element to delete
		string deleteExp = ConvertFactor(isConditional);

		// Delete does not return a value
		lastExpType = TypeVoid;

		return "delete " + deleteExp;
		// True | False
	} else if ( stream.Peek().IsBooleanLiteral() ) {
		lastExpType = TypeInt;
		string str = "0";
		if ( stream.Peek().Type() == TokenTrue )
			str = "1";
		stream.Skip(1); // True | False
		return str;
		// Null
	} else if ( stream.Peek().IsNullLiteral() ) {
		stream.Skip(1); // Null
		lastExpType = TypeStruct;
		return "0";
	}
	return "";
}

// $FuncName ( $Params )
string CppGenerator::ConvertFunctionCall() {
	// Get function
	Function* func = scanner.GetFunction(stream.Next().Data());

	// Name
	string str = func->Name();
	if ( func->ExternName() != "" ) str = func->ExternName();
	if ( !func->IsExtern() ) str = "nb_" + str;

	// Params
	str += "(";
	stream.Skip(1); // (
	int i = 0;
	while ( stream.Peek().Type() != TokenCloseParen ) {
		string tmpstr = ConvertExpression(false);
		if ( func->Local(i).Type() == TypePChar ) {
			str += "(" + tmpstr + ").c_str()";
		} else {
			str += tmpstr;
		}
		if ( stream.Peek().Type() == TokenComma ) {
			stream.Skip(1);
			str += ",";
		}
		i++;
	}
	stream.Skip(1); // )
	str += ")";

	return str;
}

// $Var [-> $MemberAccess]|[( $IndexPath )]
string CppGenerator::ConvertVarAccess() {
	string str = "";

	// Name
	const Token& nameToken = stream.Next();

	// Check member access
	if ( stream.Peek().Type() == TokenDot ) {
		stream.Skip(1); // .

		// It's a local
		if ( scanner.CountLocalOccurences(nameToken.Data()) > 0 ) {
			lastIdentifier = ConvertToken(nameToken) + "->" + ConvertMemberAccess(*scanner.GetStruct(scanner.GetLocal(nameToken.Data())->StructName()));
			// It's a global
		} else {
			lastIdentifier = ConvertToken(nameToken) + "->" + ConvertMemberAccess(*scanner.GetStruct(scanner.GetGlobal(nameToken.Data())->StructName()));
		}

		return lastIdentifier;
	}

	// Convert array access
	if ( stream.Peek().Type() == TokenOpenParen ) {
		stream.Skip(1); // (

		// Indices
		while ( stream.Peek().Type() != TokenCloseParen ) {
			str += "[" + ConvertExpression(false) + "]";
			if ( stream.Peek().Type() == TokenComma )
				stream.Skip(1);
		}

		stream.Skip(1); // )
	}

	lastIdentifier = ConvertToken(nameToken);
	return lastIdentifier + str;
}

// $FieldName [-> $MemberAccess]|[( $IndexPath )]
string CppGenerator::ConvertMemberAccess(const Struct &structure) {
	string str = "";

	// Name
	Token nameToken = stream.Next();
	nameToken = Token(nameToken.Type(), structure.Field(nameToken.Data())->Name(), nameToken.File(), nameToken.Line());

	// Additional field accesses
	if ( stream.Peek().Type() == TokenDot ) {
		stream.Skip(1); // .
		return ConvertToken(nameToken) + "->" + ConvertMemberAccess(*scanner.GetStruct(structure.Field(nameToken.Data())->StructName()));
	}

	// Array access
	if ( stream.Peek().Type() == TokenOpenParen ) {
		stream.Skip(1); // (

		// Indices
		while ( stream.Peek().Type() != TokenCloseParen ) {
			str += "[" + ConvertExpression(false) + "]";
			if ( stream.Peek().Type() == TokenComma )
				stream.Skip(1);
		}

		stream.Skip(1); // )
	}

	return ConvertToken(nameToken) + str;
}

string CppGenerator::ConvertType(IdType type) {
	switch ( type ) {
	case TypeVoid:
		return "void";
	case TypeInt:
		return "int";
	case TypeFloat:
		return "float";
	case TypeString:
		return "std::string";
	case TypePChar:
		return "const char*";
	case TypeStruct:
		return "void*";
	default:
		return "nb_" + scanner.GetStruct(type - 1 - TypeStruct).Name() + "*";
	}
}

string CppGenerator::ConvertToken(const Token &tok) {
	map<TokenType,string> desc;
	// Some are not used
	desc[TokenNot] = "!";
	desc[TokenAnd] = "&&";
	desc[TokenOr] = "||";
	desc[TokenNotEqual] = "!=";
	desc[TokenGreater] = ">";
	desc[TokenLesser] = "<";
	desc[TokenGreaterEqual] = ">=";
	desc[TokenLesserEqual] = "<=";
	desc[TokenPlus] = "+";
	desc[TokenMinus] = "-";
	desc[TokenMul] = "*";
	desc[TokenDiv] = "/";
	desc[TokenMod] = "%";
	desc[TokenAssign] = "==";
	desc[TokenComma] = ",";
	desc[TokenColon] = "";
	desc[TokenDot] = "->";
	desc[TokenOpenParen] = "(";
	desc[TokenCloseParen] = ")";
	desc[TokenIf] = "if";
	desc[TokenElse] = "else";
	desc[TokenElseIf] = "else if";
	desc[TokenEndIf] = "";
	desc[TokenSelect] = "if";
	desc[TokenCase] = "";
	desc[TokenDefault] = "else";
	desc[TokenEndSelect] = "";
	desc[TokenFor] = "for";
	desc[TokenTo] = "";
	desc[TokenStep] = "";
	desc[TokenNext] = "";
	desc[TokenRepeat] = "do";
	desc[TokenUntil] = "while";
	desc[TokenWhile] = "while";
	desc[TokenEndWhile] = "";
	desc[TokenReturn] = "return";
	desc[TokenExit] = "break";
	desc[TokenNew] = "malloc( sizeof(";
	desc[TokenDelete] = "free(";

	switch ( tok.Type() ) {
	case TokenIntLiteral:
		return Replace(tok.Data(), "$", "0x");
	case TokenFloatLiteral:
		return tok.Data() + "f";
	case TokenStringLiteral:
		return "\"" + tok.Data() + "\"";
	case TokenIdentifier:
		if ( scanner.CountFunctionOccurences(tok.Data()) > 0 )
			if ( scanner.GetFunction(tok.Data())->IsExtern() )
				return scanner.GetFunction(tok.Data())->Name();
		if ( scanner.CountConstantOccurences(tok.Data()) > 0 )
			return "nb_" + scanner.GetConstant(tok.Data())->Name();
		else if ( scanner.CountFunctionOccurences(tok.Data()) > 0 )
			return "nb_" + scanner.GetFunction(tok.Data())->Name();
		else if ( scanner.CountGlobalOccurences(tok.Data()) > 0 )
			return "nb_" + scanner.GetGlobal(tok.Data())->Name();
		else if ( scanner.CountLocalOccurences(tok.Data()) > 0 )
			return "nb_" + scanner.GetLocal(tok.Data())->Name();
		else if ( scanner.CountStructOccurences(tok.Data()) > 0 )
			return "nb_" + scanner.GetStruct(tok.Data())->Name();
		else
			return "nb_" + tok.Data();
	default:
		return desc[tok.Type()];
	}
}

string CppGenerator::SkipEmpty() {
	string str = "";
	while ( stream.Peek().Type() == TokenColon || stream.Peek().Type() == TokenEndOfLine ) {
		if ( stream.Peek().Type() == TokenEndOfLine )
			str += "\n";
		for ( int i = 0; i < numTabs; i++ )
			str += "\t";
		stream.Skip(1);
	}
	return str;
}

string CppGenerator::InitFields(const Struct &st) {
	string str = "";
	int pos = stream.Pos();
	for ( int i = 0; i < st.NumFields(); i++ ) {
		const Var& field = st.Field(i);
		if ( field.IndexPath().size() == 0 ) {
			stream.Seek(field.InitExpOffset());
			str += "\t\tthis->nb_" + field.Name() + " = " + ((field.InitExpOffset() != 0) ? ConvertExpression(false) : DefaultInitForType(field.Type())) + ";\n";
		} else {
			if ( field.Type() != TypeString ) {
				str += "\t\tmemset(this->nb_" + field.Name() + ", 0, sizeof(" + ConvertType(field.Type()) + ")";

				// Get total number of indices
				int totalIndices = 1;
				for ( int j = 0; j < (int)field.IndexPath().size(); j++ )
					totalIndices *= field.IndexPath()[j];
				str += " * " + Str(totalIndices) + ");\n";
			}
		}
	}
	stream.Seek(pos);
	return str;
}

string CppGenerator::DefaultInitForType(IdType type) {
	switch ( type ) {
	case TypeVoid:
		return "";
	case TypeInt:
		return "0";
	case TypeFloat:
		return "0.0f";
	case TypeString:
		return "\"\"";
	default:
		return "0";
	}
}

string CppGenerator::StripTrailingSemicolon(string str) {
	while ( Right(str, 1) == "\n" )
		str = Left(str, str.length() - 1);
	while ( Right(str, 1) == " " )
		str = Left(str, str.length() - 1);
	if ( Right(str, 1) == ";" )
		return Left(str, str.length() - 1);
	else
		return str;
}

string CppGenerator::StripTrailingAsterisk(string str) {
	while ( Right(str, 1) == "\n" )
		str = Left(str, str.length() - 1);
	while ( Right(str, 1) == " " )
		str = Left(str, str.length() - 1);
	if ( Right(str, 1) == "*" )
		return Left(str, str.length() - 1);
	else
		return str;
}

bool CppGenerator::IsEndType(TokenType type) const {
	if ( type == TokenEndProgram )
		return true;
	else if ( type == TokenElseIf )
		return true;
	else if ( type == TokenElse )
		return true;
	else if ( type == TokenEndIf )
		return true;
	else if ( type == TokenCase )
		return true;
	else if ( type == TokenDefault )
		return true;
	else if ( type == TokenEndSelect )
		return true;
	else if ( type == TokenNext )
		return true;
	else if ( type == TokenUntil )
		return true;
	else if ( type == TokenEndWhile )
		return true;
	else if ( type == TokenEndFunction )
		return true;
	else if ( type == TokenEndStruct )
		return true;
	else
		return false;
}

IdType CppGenerator::VarType(const string& var) const {
	Array* path = SplitString(Replace(var, "->", "."), ".");
	Array* arr = SplitString(Right(ArrayString(path, 0), ArrayString(path, 0).length() - 3), "[");
	string varName = ArrayString(arr, 0);
	FreeArray(arr);
	const Var* field = NULL;
	if ( scanner.CountLocalOccurences(varName) > 0 )
		field = scanner.GetLocal(varName);
	else if ( scanner.CountGlobalOccurences(varName) > 0 )
		field = scanner.GetGlobal(varName);
	else
		return (IdType)-1;
	for ( int i = 1; i < CountArray(path); i++ ) {
		const Struct& st = scanner.GetStruct(field->Type() - 1 - TypeStruct);
		Array* arr = SplitString(Right(ArrayString(path, i), ArrayString(path, i).length() - 3), "[");
		varName = ArrayString(arr, 0);  // Remove "nb_" and array access
		FreeArray(arr);
		field = st.Field(varName);
	}
	FreeArray(path);
	return field->Type();
}
