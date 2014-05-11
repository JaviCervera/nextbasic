#include "../core/file.h"
#include "../core/filesystem.h"
#include "../core/string.h"
#include "../core/system.h"
#include "../core/time.h"
#include "cppgenerator.h"
#include "error.h"
#include "lexical.h"
#include "preprocessor.h"
#include "syntactical.h"
#include <iostream>
#include <map>

using namespace std;

enum ErrorCode {
    NO_ERROR = 0,
    ERROR_USAGE = -1,
    ERROR_PREPROCESS = -2,
    ERROR_INCLUDE = -3,
    ERROR_LEXICAL = -4,
    ERROR_SYNTACTICAL = -5
};

enum BuildMode {
    MODE_CHECK,
	MODE_TRANSLATE
};

IdType GetType(string type);
void SaveTokens(const vector<Token>& tokens, const string& filename);

int main(int argc, char* argv[]) {
    int msecs = Millisecs();

    // Save app dir
    string appDir = ExtractDir(RealPath(argv[0]));

    // Check command line
    if ( argc != 2 && argc != 3 ) {
		cout << "Usage: " << StripDir(argv[0]).c_str() << " [option] sourcefile" << endl;
        cout << "Options:" << endl;
        cout << "-c: Check syntax (does not generate output)" << endl;
        return ERROR_USAGE;
    }

    // Get command line options
	BuildMode buildMode = MODE_TRANSLATE;
    if ( argc == 3 ) {
        if ( string(argv[1]) == "-c" ) {
            buildMode = MODE_CHECK;
		} else {
            cout << "Invalid option " << argv[1] << endl;
            return ERROR_USAGE;
        }
    }

    // Get filename
    string sourceFilename = RealPath(argv[argc-1]);

    // Create preprocessor
    Preprocessor preprocessor;

	// Lexical analysis
	Lexical lex(sourceFilename);
    if ( lex.Error() != "" ) {
        cout << lex.Error().c_str() << " on file '" << lex.ErrorToken().File().c_str() << "'' at line " << lex.ErrorToken().Line() << endl;
        return ERROR_LEXICAL;
    } else {
        // Set dir for preprocessing
		ChangeDir(ExtractDir(sourceFilename));

        // Preprocess main file
        cout << "Preprocessing '" << sourceFilename << "'..." << endl;
        preprocessor.Preprocess(lex.Tokens());
        if ( Error::Get() != "" ) {
            cout << Error::Get().c_str() << endl;
            return ERROR_PREPROCESS;
        }

        // Preprocess included files
        unsigned int current = 0;
        while ( current < preprocessor.Includes().size() ) {
			// Make sure that file exists
            string includeName = preprocessor.Includes()[current];
            if ( FileType(includeName.c_str()) == 0 ) {
                cout << "Could not find include file '" << includeName.c_str() << "'" << endl;
                return ERROR_INCLUDE;
            }

            // Lexical analysis of include file
            Lexical lex(includeName);
            if ( lex.Error() != "" ) {
                cout << lex.Error().c_str() << " on file '" << lex.ErrorToken().File().c_str() << "'' at line " << lex.ErrorToken().Line() << endl;
                return ERROR_LEXICAL;
            }

            // Set dir for preprocessing
            ChangeDir(ExtractDir(includeName.c_str()));

            // Preprocess file
            cout << "Preprocessing '" << includeName.c_str() << "'..." << endl;
            preprocessor.Preprocess(lex.Tokens());
            if ( Error::Get() != "" ) {
                cout << Error::Get().c_str() << endl;
                return ERROR_PREPROCESS;
            }

            // Iterate to next include file
            current++;
        }

        // Change to app dir
        ChangeDir(appDir.c_str());

        // Add core module as last on the list, since it is required this way under Linux
        preprocessor.AddModule("core");

        // Parse all modules
        for ( vector<string>::const_iterator it = preprocessor.Modules().begin(); it != preprocessor.Modules().end(); it++ ) {
            string moduleName = RealPath(("../modules/" + *it + "/" + *it + ".nb").c_str());

			// Make sure that file exists
            if ( FileType(moduleName.c_str()) == 0 ) {
                cout << "Could not find module " << moduleName.c_str() << endl;
                return ERROR_INCLUDE;
            }

            // Local modules not supported by now ...
            //if ( FileType(moduleName.c_str()) == 0 )
            //    moduleName = RealPath("modules/" + *it + "/" + *it + ".nb");

            Lexical lex(moduleName);
            if ( lex.Error() != "" ) {
                cout << lex.Error().c_str() << " on file '" << lex.ErrorToken().File().c_str() << "'' at line " << lex.ErrorToken().Line() << endl;
                return ERROR_LEXICAL;
            }

            cout << "Preprocessing module " << (*it).c_str() << " ..." << endl;
            preprocessor.Preprocess(lex.Tokens());
            if ( Error::Get() != "" ) {
                cout << Error::Get().c_str() << endl;
                return ERROR_PREPROCESS;
            }
        }
    }

    // Restore app dir
    ChangeDir(appDir.c_str());

	//SaveTokens(preprocessor.PreprocessedTokens(), "tokens.txt");

    // Syntactical analysis
    cout << "Syntactical analysis..." << endl;
    Syntactical syn(preprocessor.PreprocessedTokens());
    if ( Error::Get() != "" ) {
        cout << Error::Get().c_str() << endl;
        return ERROR_SYNTACTICAL;
    }

    // Generate output only if required
    if ( buildMode != MODE_CHECK ) {
		// C++ generator
		cout << "Generating C++ code..." << endl;
		string cppfilename = StripExt(sourceFilename) + ".cpp";
		CppGenerator(cppfilename, preprocessor.PreprocessedTokens(), syn.GetScanner(), preprocessor.Modules(), preprocessor.Links(), preprocessor.IsGuiApp());
    }

    cout << "Done in " << ((Millisecs()-msecs)/1000.0) << " seconds." << endl;

    return NO_ERROR;
}

IdType GetType(string type) {
	type = Trim(type);
    if ( type == "void")
        return TypeVoid;
    else if ( type == "int" )
        return TypeInt;
    else if ( type == "float" )
        return TypeFloat;
    else if ( type == "string" )
        return TypeString;
    else
        return TypeVoid;
}

void SaveTokens(const vector<Token>& tokens, const string& filename) {
    map<TokenType,string> desc;
    desc[TokenEndOfLine] = "TokenEndOfLine";
    desc[TokenPreprocInclude] = "TokenPreprocInclude";
	desc[TokenPreprocUse] = "TokenPreprocUse";
    desc[TokenPreprocLink] = "TokenPreprocLink";
    desc[TokenPreprocOption] = "TokenPreprocOption";
    desc[TokenIntLiteral] = "TokenInt";
    desc[TokenFloatLiteral] = "TokenFloat";
    desc[TokenStringLiteral] = "TokenString";
    desc[TokenNot] = "TokenNot";
    desc[TokenAnd] = "TokenAnd";
    desc[TokenOr] = "TokenOr";
    desc[TokenNotEqual] = "TokenNotEqual";
    desc[TokenGreater] = "TokenGreater";
    desc[TokenLesser] = "TokenLesser";
    desc[TokenGreaterEqual] = "TokenGreaterEqual";
    desc[TokenLesserEqual] = "TokenLesserEqual";
    desc[TokenPlus] = "TokenPlus";
    desc[TokenMinus] = "TokenMinus";
    desc[TokenMul] = "TokenMul";
    desc[TokenDiv] = "TokenDiv";
    desc[TokenMod] = "TokenMod";
    desc[TokenAssign] = "TokenAssign";
    desc[TokenComma] = "TokenComma";
    desc[TokenColon] = "TokenColon";
    desc[TokenDot] = "TokenDot";
    desc[TokenOpenParen] = "TokenOpenParen";
    desc[TokenCloseParen] = "TokenCloseParen";
    desc[TokenPercent] = "TokenPercent";
    desc[TokenSharp] = "TokenSharp";
    desc[TokenDollar] = "TokenDollar";
    desc[TokenProgram] = "TokenProgram";
    desc[TokenEndProgram] = "TokenEndProgram";
    desc[TokenIf] = "TokenIf";
    desc[TokenElse] = "TokenElse";
    desc[TokenElseIf] = "TokenElseIf";
    desc[TokenEndIf] = "TokenEndIf";
    desc[TokenSelect] = "TokenSelect";
    desc[TokenCase] = "TokenCase";
    desc[TokenDefault] = "TokenDefault";
    desc[TokenEndSelect] = "TokenEndSelect";
    desc[TokenFor] = "TokenFor";
    desc[TokenTo] = "TokenTo";
    desc[TokenStep] = "TokenStep";
    desc[TokenNext] = "TokenNext";
    desc[TokenRepeat] = "TokenRepeat";
    desc[TokenUntil] = "TokenUntil";
    desc[TokenWhile] = "TokenWhile";
    desc[TokenEndWhile] = "TokenEndWhile";
    desc[TokenExit] = "TokenExit";
    desc[TokenDim] = "TokenDim";
    desc[TokenAs] = "TokenAs";
	desc[TokenIntKeyword] = "TokenIntKeyword";
	desc[TokenFloatKeyword] = "TokenFloatKeyword";
	desc[TokenStringKeyword] = "TokenStringKeyword";
	desc[TokenPCharKeyword] = "TokenPCharKeyword";
    desc[TokenFunction] = "TokenFunction";
    desc[TokenEndFunction] = "TokenEndFunction";
    desc[TokenReturn] = "TokenReturn";
    desc[TokenConst] = "TokenConst";
    desc[TokenStruct] = "TokenStruct";
    desc[TokenEndStruct] = "TokenEndStruct";
    desc[TokenExtern] = "TokenExtern";
    desc[TokenEndExtern] = "TokenEndExtern";
    desc[TokenNew] = "TokenNew";
    desc[TokenDelete] = "TokenDelete";
    desc[TokenTrue] = "TokenTrue";
    desc[TokenFalse] = "TokenFalse";
    desc[TokenNull] = "TokenNull";
    desc[TokenIdentifier] = "TokenIdentifier";

	SaveString("", filename, false);
    for ( vector<Token>::const_iterator it = tokens.begin(); it != tokens.end(); it++ ) {
        string str = desc[(*it).Type()];
        if ( (*it).Type() == TokenIntLiteral || (*it).Type() == TokenFloatLiteral || (*it).Type() == TokenStringLiteral || (*it).Type() == TokenIdentifier )
			SaveString(str + ":" + (*it).Data() + "\n", filename, true);
        else
			SaveString(str + "\n", filename, true);
    }
}
