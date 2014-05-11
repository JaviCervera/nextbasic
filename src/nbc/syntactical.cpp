#include "syntactical.h"
#include "error.h"

using namespace std;

Syntactical::Syntactical(const vector<Token>& tokens) : stream(tokens), scanner(tokens), inLoop(0), currentFunction(NULL) {
    // Scan all global identifiers
    scanner.ParseConstants();
    scanner.ParseStructs();
    scanner.ParseGlobals();
    scanner.ParseFunctions();

    // Parse
    while (stream.HasNext() && Error::Get() == "" ) {
        // Skip empty statements at the beginning
        stream.SkipEmpty();

        switch ( stream.Peek().Type() ) {
        case TokenConst:
            ParseConstant();
            break;
        case TokenDim:
            ParseDim(SCOPE_GLOBAL);
            break;
        case TokenStruct:
            ParseStruct();
            break;
        case TokenExtern:
            ParseExtern();
            break;
        case TokenFunction:
            ParseFunction(false);
            break;
        case TokenProgram:
            ParseProgram();
            break;
        default:
            Error::Set("Unexpected token '" + stream.Peek().Data() + "'", stream.Peek());
        }
    }

    // Check if there was an error
    if ( Error::Get() != "" ) return;

    // Make sure that there is a program
    if ( scanner.GetProgram().Offset() == -1 ) {
        Error::Set("Main program not found", Token());
    }
}

// $Def(constant)
void Syntactical::ParseConstant() {
    // Stream points to "Const", because ParseDef skips the first token
    // (it will think its "Def")
    ParseDim(SCOPE_CONST);
}

// Dim/Const name [%|#|$] [($Literal|$Const[, $Literal|$Const]*)] [As $Type] [= $Literal|$Const] $EndSt
// It can be initialized only if it is not an array
// Constant arrays are not supported
// Constants must be initialized
IdType Syntactical::ParseDim(DimScope scope) {
    bool isArray = false;
    vector<int> indexPath;

    // Dim
    stream.Skip(1);

    // Name
    if ( stream.Peek().Type() != TokenIdentifier ) {
        Error::Set("Expected identifier", stream.Next());
        return TypeVoid;
    }
    if ( !IsValidIdentifier(stream.Peek().Data(), (scope == SCOPE_LOCAL) || (scope == SCOPE_STRUCT) || (scope == SCOPE_FOR)) ) {
        Error::Set("Identifier defined multiple times", stream.Next());
        return TypeVoid;
    }
    const Token& nameToken = stream.Next();

    // Optional symbolic type (assumed int)
    bool typeSpecified = false;
    IdType idType = TypeInt;
    string typeName = "int";
    if ( stream.Peek().Type() == TokenPercent ) {
        stream.Skip(1); // %
        typeSpecified = true;
    } else if ( stream.Peek().Type() == TokenSharp ) {
        stream.Skip(1); // #
        idType = TypeFloat;
        typeName = "float";
        typeSpecified = true;
    } else if ( stream.Peek().Type() == TokenDollar ) {
        stream.Skip(1); // $
        idType = TypeString;
        typeName = "string";
        typeSpecified = true;
    }

    // Optional array decl
    if ( stream.Peek().Type() == TokenOpenParen ) {
        isArray = true;

        // Arrays cannot be constant
        if ( scope == SCOPE_CONST ) {
            Error::Set("Arrays cannot be constant", stream.Next());
            return TypeVoid;
        }

        stream.Skip(1); // (

        // Parse all dimensions
        while ( stream.Peek().Type() == TokenIntLiteral || (stream.Peek().Type() == TokenIdentifier && scanner.CountConstantOccurences(stream.Peek().Data()) > 0) ) {
            if ( stream.Peek().Type() == TokenIntLiteral ) {
				indexPath.push_back(Val(stream.Next().Data()));
            } else {
                // Make sure that constant is of integer type
                if ( scanner.GetConstant(stream.Peek().Data())->Type() != TypeInt ) {
                    Error::Set("Constant must be of integer type", stream.Next());
                    return TypeVoid;
                }

                indexPath.push_back(ResolveIntConstant(scanner.GetConstant(stream.Next().Data())));
            }

            // Next must be "," or ")"
            if ( stream.Peek().Type() != TokenComma && stream.Peek().Type() != TokenCloseParen ) {
                Error::Set("Expected ',' or ')'", stream.Next());
                return TypeVoid;
            }
            if ( stream.Peek().Type() == TokenComma )
                stream.Skip(1);
        }

        // Make sure that next token is ")"
        if ( stream.Peek().Type() != TokenCloseParen ) {
            Error::Set("Expected ')'", stream.Next());
            return TypeVoid;
        }
        stream.Skip(1); // )
    }

    // Optional "As" type
    if ( stream.Peek().Type() == TokenAs ) {
        // Check that type was not already specified
        if ( typeSpecified ) {
            Error::Set("Type was already specified", stream.Next());
            return TypeVoid;
        }

        stream.Skip(1); // As

        // Check type
        if ( scope == SCOPE_CONST && stream.Peek().Type() == TokenIdentifier ) {
            Error::Set("Constants must be of primitive type", stream.Next());
            return TypeVoid;
        }
        if ( !scanner.IsType(stream.Peek()) ) {
            Error::Set("Expected type", stream.Next());
            return TypeVoid;
        } else {
            idType = IdTypeFromTokenType(stream.Peek().Type());
            typeName = stream.Next().Data();

            // If field type is a struct, set correct type
            if ( scanner.CountStructOccurences(typeName) > 0 )
                idType = IdType(idType + scanner.StructIndex(typeName) + 1);
        }
    }

    // Optional assignment (mandatory in constants and For vars, forbidden in arrays)
    // Can be an expression, except for constants and fields, where it must be
    // a literal or a constant (or New if it's a field)
    if ( scope == SCOPE_CONST && stream.Peek().Type() != TokenAssign ) {
        Error::Set("Expected constant initialization", stream.Next());
        return TypeVoid;
    }
    if ( scope == SCOPE_FOR && stream.Peek().Type() != TokenAssign ) {
        Error::Set("Expected variable initialization", stream.Next());
        return TypeVoid;
    }
    if ( stream.Peek().Type() == TokenAssign ) { 
        // Check that it is not an array
        if ( isArray ) {
            Error::Set("Arrays cannot be initialized", stream.Next());
            return TypeVoid;
        }

        stream.Next();  // =

        // Check literal or constant if it's a constant or field
        if ( (scope == SCOPE_CONST || scope == SCOPE_STRUCT) && (stream.Peek().Type() != TokenIntLiteral
                                                                 && stream.Peek().Type() != TokenFloatLiteral
                                                                 && stream.Peek().Type() != TokenStringLiteral
                                                                 && (stream.Peek().Type() != TokenIdentifier
                                                                     || (stream.Peek().Type() == TokenIdentifier
                                                                         && scanner.CountConstantOccurences(stream.Peek().Data()) == 0))) ) {
            // New operator is allowed in a field
            if ( scope != SCOPE_STRUCT ) {
                Error::Set("Expected literal or constant", stream.Next());
                return TypeVoid;
            } else if ( stream.Peek().Type() != TokenNew ) {
                Error::Set("Expected literal, constant or New", stream.Next());
                return TypeVoid;
            }
        }

        // Eval expression
        int expOffset = stream.Pos();
        IdType expType = ParseExpression(false);
        if ( Error::Get() != "" ) return TypeVoid;

        // Check expression type
        if ( !AreTypesCompatible(idType, expType) ) {
            stream.Seek(expOffset); // Move to beginning of expression
            Error::Set("Incompatible types", stream.Next());
            return TypeVoid;
        }

        // Add expression offset to locals, globals or constants list
        if ( scanner.CountLocalOccurences(nameToken.Data()) > 0 ) {
            scanner.GetLocal(nameToken.Data())->SetInitExpOffset(expOffset);
        } else if ( scanner.CountGlobalOccurences(nameToken.Data()) > 0 ) {
            scanner.GetGlobal(nameToken.Data())->SetInitExpOffset(expOffset);
        } else if ( scanner.CountConstantOccurences(nameToken.Data()) > 0 ) {
            scanner.GetConstant(nameToken.Data())->SetInitExpOffset(expOffset);
        }
    }

    // Add index path to locals or globals list if an array
    if ( isArray ) {
        if ( scanner.CountLocalOccurences(nameToken.Data()) > 0 ) {
            scanner.GetLocal(nameToken.Data())->SetIndexPath(indexPath);
        } else if ( scanner.CountGlobalOccurences(nameToken.Data()) > 0 ) {
            scanner.GetGlobal(nameToken.Data())->SetIndexPath(indexPath);
        }
    }

    // $EndSt (not if declaring For control variable)
    if ( scope != SCOPE_FOR ) ParseEndStatement();

    return idType;
}

// Struct name $EndSt $Fields EndStruct $EndSt    NOTE: A field is $Dim $EndSt
void Syntactical::ParseStruct() {
    // Struct
    stream.Skip(1);

    // Name
    if ( stream.Peek().Type() != TokenIdentifier ) {
        Error::Set("Expected identifier", stream.Next());
        return;
    }
    if ( !IsValidIdentifier(stream.Peek().Data(), false) ) {
        Error::Set("Identifier defined multiple times", stream.Next());
        return;
    }
    const Token& nameToken = stream.Next();

    // $EndSt
    ParseEndStatement();
    if ( Error::Get() != "" ) return;

    // Fill local stack with struct fields
    Struct* st = scanner.GetStruct(nameToken.Data());
    vector<Var> fields;
    for ( int i = 0; i < st->NumFields(); i++ ) {
        fields.push_back(st->Field(i));
    }
    scanner.SetLocals(fields);

    // $Fields
    while ( stream.HasNext() && stream.Peek().Type() != TokenEndStruct ) {
        // $Dim
        ParseDim(SCOPE_STRUCT);
        if ( Error::Get() != "" ) return;
    }

    // Set fields index path and init expressions
    for ( int i = 0; i < st->NumFields(); i++ ) {
        const Var& field = scanner.GetLocal(i);
        st->Field(i).SetIndexPath(field.IndexPath());
        st->Field(i).SetInitExpOffset(field.InitExpOffset());
    }

    // EndStruct
    if ( stream.Peek().Type() != TokenEndStruct ) {
        Error::Set("Expected EndStruct", stream.Next());
        return;
    }
    stream.Skip(1);

    // $EndSt
    ParseEndStatement();
}

// Extern [$StringLiteral] $EndSt [$ExternFunction]* EndExtern $EndSt
void Syntactical::ParseExtern() {
    // Extern
    stream.Skip(1);

    // Optional $StringLiteral
    if ( stream.Peek().Type() == TokenStringLiteral ) {
        stream.Skip(1);
    }

    // $EndSt
    ParseEndStatement();
    if ( Error::Get() != "" ) return;

    // [$ExternFunction]*
    while ( stream.Peek().Type() == TokenFunction ) {
        ParseFunction(true);
        if ( Error::Get() != "" ) return;
    }

    // EndExtern
    if ( stream.Peek().Type() != TokenEndExtern ) {
        Error::Set("Expected EndExtern", stream.Next());
        return;
    }
    stream.Skip(1);

    // $EndSt
    ParseEndStatement();
}

// TokenFunction name [%|#|$] $Args [As $Type] [$StringLiteral]|($EndSt $Block(EndFunction)) $EndSt
void Syntactical::ParseFunction(bool externFunc) {
    // Function
    stream.Skip(1);

    // Name
    if ( stream.Peek().Type() != TokenIdentifier ) {
        Error::Set("Expected identifier", stream.Next());
        return;
    }
    string name = stream.Peek().Data();
    if ( !IsValidIdentifier(name, false) ) {
        Error::Set("Identifier defined multiple times", stream.Next());
        return;
    }
    stream.Skip(1);

    // Set as current function for the parser
    currentFunction = scanner.GetFunction(name);

    // Optional primitive type
    bool symbolType = false;
    if ( stream.Peek().Type() == TokenPercent || stream.Peek().Type() == TokenSharp || stream.Peek().Type() == TokenDollar ) {
        symbolType = true;
        stream.Skip(1);
    }

    // $Args
    ParseArgs(externFunc);
    if ( Error::Get() != "" ) return;

    // Optional type (assumed void)
    if ( stream.Peek().Type() == TokenAs ) {
        stream.Skip(1); // As

        // Check that type wasn't specified as a symbol
        if ( symbolType ) {
            Error::Set("Type already defined", stream.Next());
            return;
        }

        // Check type
        if ( !scanner.IsType(stream.Peek()) ) {
			// "Struct" and "PChar" are valid return types for extern functions
			if ( !externFunc || (externFunc && Lower(stream.Peek().Data()) != "struct" && Lower(stream.Peek().Data()) != "pchar") ) {
                Error::Set("Expected type", stream.Next());
                return;
            }
        }
        stream.Skip(1);
    }

    // Case 1 (Extern): Optional $StringLiteral
    if ( externFunc ) {
        if ( stream.Peek().Type() == TokenStringLiteral )
            stream.Skip(1); // $StringLiteral
    // Case 2: $Block $EndSt
    } else {
        // $EndSt
        ParseEndStatement();
        if ( Error::Get() != "" ) return;

        // $Block
        scanner.GetFunction(name)->SetOffset(ParseBlock(vector<TokenType>(1, TokenEndFunction), &currentFunction->Locals(), NULL));
        if ( Error::Get() != "" ) return;

        // Set scanner locals as function locals
        if ( Error::Get() == "" ) {
            vector<Var> vec;
            for ( int i = 0; i < scanner.NumLocals(); i++ )
                vec.push_back(scanner.GetLocal(i));
            scanner.GetFunction(name)->SetLocals(vec);
        }
    }

    // $EndSt
    ParseEndStatement();
}

// ( [name [%|#|$|As $Type][, name [%|#|$|As Type]]*] )
std::vector<Var> Syntactical::ParseArgs(bool externFunc) {
    vector<Var> args;

    // Open paren
    if ( stream.Peek().Type() != TokenOpenParen ) {
        Error::Set("Expected '('", stream.Next());
        return args;
    }
    stream.Skip(1);

    // Args
    while ( stream.Peek().Type() == TokenIdentifier ) {
        // Name
        if ( !IsValidIdentifier(stream.Peek().Data(), false) ) {
            Error::Set("Identifier defined multiple times", stream.Next());
            return args;
        }
        string name = stream.Next().Data();

        // Optional type (assumed int)
        IdType idType = TypeInt;
        string typeName = "int";
        if ( stream.Peek().Type() == TokenPercent ) {
            stream.Skip(1); // %
        } else if ( stream.Peek().Type() == TokenSharp ) {
            stream.Skip(1); // #
            idType = TypeFloat;
            typeName = "float";
        } else if ( stream.Peek().Type() == TokenDollar ) {
            stream.Skip(1); // $
            idType = TypeString;
            typeName = "string";
        } else if ( stream.Peek().Type() == TokenAs ) {
            stream.Skip(1); // As

            // Check type
            if ( !scanner.IsType(stream.Peek()) ) {
				// "Struct" and "PChar" are valid arg types for extern functions
				if ( !externFunc || (externFunc && Lower(stream.Peek().Data()) != "struct" && Lower(stream.Peek().Data()) != "pchar") ) {
                    Error::Set("Expected type", stream.Next());
                    return args;
                }
            }

            idType = IdTypeFromTokenType(stream.Peek().Type());
            typeName = stream.Next().Data();

            // If field type is a struct, set correct type
            if ( scanner.CountStructOccurences(typeName) > 0 )
                idType = IdType(idType + scanner.StructIndex(typeName) + 1);
        }

        // Add argument
        args.push_back(Var(idType, name, typeName));

        if ( stream.Peek().Type() != TokenComma && stream.Peek().Type() != TokenCloseParen ) {
            Error::Set("Expected ',' or ')'", stream.Next());
            return args;
        }
        if ( stream.Peek().Type() == TokenComma )
            stream.Skip(1);
    }

    // Close paren
    stream.Skip(1);

    return args;
}

// Program $EndSt $Block(EndProgram) $EndSt
void Syntactical::ParseProgram() {
    // No current function (we are parsing the main program)
    currentFunction = NULL;

    // Program
    stream.Skip(1);

    // $EndSt
    ParseEndStatement();
    if ( Error::Get() != "" ) return;

    // $Block(EndProgram)
    int offset = ParseBlock(vector<TokenType>(1, TokenEndProgram), NULL, NULL);
    scanner.GetProgram().SetOffset(offset);
    if ( Error::Get() == "" ) {
        vector<Var> vec;
        for ( int i = 0; i < scanner.NumLocals(); i++ )
            vec.push_back(scanner.GetLocal(i));
        scanner.GetProgram().SetLocals(vec);
    }

    // $EndSt
    if ( Error::Get() == "") ParseEndStatement();
}

// ([$Def]|[$Statement])* $EndType
int Syntactical::ParseBlock(const vector<TokenType> &endTypes, const vector<Var> *args, TokenType *endType) {
    // Store offset
    int offset = stream.Pos();

    // Scan locals if function or program block
    if ( endTypes[0] == TokenEndFunction || endTypes[0]  == TokenEndProgram ) {
        scanner.ParseLocals(stream.Pos(), args);
    }

    // Defs and statements
    while ( !IsEndType(endTypes, stream.Peek().Type()) ) {
        if ( stream.Peek().Type() == TokenDim ) {
            ParseDim(SCOPE_LOCAL);
        } else {
            ParseStatement();
        }
        if ( Error::Get() != "" ) return -1;
    }

    // $EndType
    TokenType type = stream.Peek().Type();
    if ( endType != NULL ) *endType = type;
    stream.Skip(1);

    return offset;
}

// ($ControlStatement|$Expression) $EndSt
void Syntactical::ParseStatement() {
    // $ControlStatement
    if ( stream.Peek().IsKeyword() ) {
        ParseKeyword();
    // $Expression
    } else {
        ParseExpression(false);
    }
    if ( Error::Get() != "" ) return;

    // $EndSt
    ParseEndStatement();
}

// (:|$EOL)+
void Syntactical::ParseEndStatement() {
    if ( stream.Peek().Type() != TokenColon && stream.Peek().Type() != TokenEndOfLine ) {
        Error::Set("Expected new line", stream.Next());
        return;
    }
    stream.SkipEmpty();
}

// $If | $For | $Repeat | $While | $Return
void Syntactical::ParseKeyword() {
    switch ( stream.Peek().Type() ) {
    case TokenIf:
        ParseIf();
        break;
    case TokenSelect:
        ParseSelect();
        break;
    case TokenFor:
        ParseFor();
        break;
    case TokenRepeat:
        ParseRepeat();
        break;
    case TokenWhile:
        ParseWhile();
        break;
    case TokenReturn:
        ParseReturn();
        break;
    case TokenExit:
        ParseExit();
        break;
    default:
        Error::Set("Unexpected keyword '" + stream.Peek().Data() + "'", stream.Next());
    }
}

// If $Expression $EndSt $Block(ElseIf|Else|EndIf) $EndSt(if Else) [ElseIf $Expression $EndSt $Block(ElseIf|Else|EndIf) $EndSt(if Else)]* [Else $Block(EndIf)]
void Syntactical::ParseIf() {
    // Allocate end types
    vector<TokenType> endTypes;
    endTypes.push_back(TokenElseIf);
    endTypes.push_back(TokenElse);
    endTypes.push_back(TokenEndIf);

    // If
    stream.Skip(1);

    // $Expression
    const Token& expToken = stream.Peek();
    IdType type = ParseExpression(true);
    if ( Error::Get() != "" ) return;
    if ( type != TypeInt ) {
        Error::Set("Invalid conditional expression", expToken);
        return;
    }

    // $EndSt
    ParseEndStatement();
    if ( Error::Get() != "" ) return;

    // $Block
    TokenType endType = TokenEndOfFile;
    ParseBlock(endTypes, NULL, &endType);
    if ( Error::Get() != "" ) return;

    // $EndSt
    if ( endType == TokenElse ) {
        ParseEndStatement();
        if ( Error::Get() != "" ) return;
    }

    // Optional ElseIf sequence
    while ( endType == TokenElseIf ) {
        // $Expression
        const Token& expToken = stream.Peek();
        IdType type = ParseExpression(true);
        if ( Error::Get() != "" ) return;
        if ( type != TypeInt ) {
            Error::Set("Invalid conditional expression", expToken);
            return;
        }

        // $EndSt
        ParseEndStatement();
        if ( Error::Get() != "" ) return;

        // $Block
        ParseBlock(endTypes, NULL, &endType);
        if ( Error::Get() != "" ) return;

        // $EndSt
        if ( endType == TokenElse ) {
            ParseEndStatement();
            if ( Error::Get() != "" ) return;
        }
    }

    // Optional Else
    if ( endType == TokenElse ) {
        // $Block
        ParseBlock(vector<TokenType>(1, TokenEndIf), NULL, NULL);
    }
}

// Select $Expression $EndSt [Case [$Expression] $EndSt $Block(Case|Default|EndSelect) $EndSt(if Case or Default)]+ [Default $EndSt $Block(EndSelect)]
void Syntactical::ParseSelect() {
    // Allocate end types
    vector<TokenType> endTypes;
    endTypes.push_back(TokenCase);
    endTypes.push_back(TokenDefault);
    endTypes.push_back(TokenEndSelect);

    // Select
    stream.Skip(1);

    // $Expression
    IdType type1 = ParseExpression(false);
    if ( Error::Get() != "" ) return;

    // $EndSt
    ParseEndStatement();
    if ( Error::Get() != "" ) return;

    // Make sure there's at least one Case
    if ( stream.Peek().Type() != TokenCase ) {
        Error::Set("Expected 'Case'", stream.Peek());
        return;
    }
    stream.Skip(1); // case
    TokenType endType = TokenCase;

    // Case sequence
    while ( endType == TokenCase ) {
        // $Expression
        const Token& expToken = stream.Peek();
        IdType type2 = ParseExpression(false);
        if ( Error::Get() != "" ) return;
        if ( !AreTypesCompatible(type1, type2) ) {
            Error::Set("Incompatible type in expression", expToken);
            return;
        }

        // $EndSt
        ParseEndStatement();
        if ( Error::Get() != "" ) return;

        // $Block
        ParseBlock(endTypes, NULL, &endType);
        if ( Error::Get() != "" ) return;

        // $EndSt
        /*if ( endType == TokenCase || endType == TokenDefault ) {
            ParseEndStatement();
            if ( Error::Get() != "" ) return;
        }*/
    }

    // Optional Default
    if ( endType == TokenDefault ) {
        // $EndSt
        if ( endType == TokenCase || endType == TokenDefault ) {
            ParseEndStatement();
            if ( Error::Get() != "" ) return;
        }

        // $Block
        ParseBlock(vector<TokenType>(1, TokenEndSelect), NULL, NULL);
    }
}

// For $Dim|(var = $Expression) To $Expression [Step $Expression] $EndSt $Block(Next)
void Syntactical::ParseFor() {
    // For
    stream.Next();

    // $Dim
    if ( stream.Peek().Type() == TokenDim ) {
        const Token& dimTok = stream.Peek();
        IdType idType = ParseDim(SCOPE_FOR);
        if ( Error::Get() != "" ) return;

        // Check type
        if ( idType != TypeInt && idType != TypeFloat ) {
            Error::Set("'for' control variable must be of numeric type", dimTok);
            return;
        }
    // var = $Expression
    } else {
        // var
        if ( stream.Peek().Type() != TokenIdentifier ) {
            Error::Set("Expected identifier", stream.Next());
            return;
        }
        if ( scanner.CountLocalOccurences(stream.Peek().Data()) == 0  &&  scanner.CountGlobalOccurences(stream.Peek().Data()) == 0 ) {
            Error::Set("Variable '" + stream.Peek().Data() + "' not defined", stream.Next());
            return;
        }
        const Token& varTok = stream.Next();

        // Check type
        if ( scanner.CountLocalOccurences(varTok.Data()) > 0 ) {
            if ( scanner.GetLocal(varTok.Data())->Type() != TypeInt && scanner.GetLocal(varTok.Data())->Type() != TypeFloat ) {
                Error::Set("'for' control variable must be of numeric type", varTok);
                return;
            }
        } else {
            if ( scanner.GetGlobal(varTok.Data())->Type() != TypeInt && scanner.GetGlobal(varTok.Data())->Type() != TypeFloat ) {
                Error::Set("'for' control variable must be of numeric type", varTok);
                return;
            }
        }

        // Assign
        if ( stream.Peek().Type() != TokenAssign ) {
            Error::Set("Expected '='", stream.Next());
            return;
        }
        stream.Next();

        // $Expression
        const Token& expTok = stream.Peek();
        IdType type = ParseExpression(false);
        if ( Error::Get() != "" ) return;
        if ( type != TypeInt && type != TypeFloat ) {
            Error::Set("'for' variable initialization expression must be of numeric type", expTok);
            return;
        }
    }

    // To
    if ( stream.Peek().Type() != TokenTo ) {
        Error::Set("Expected 'To'", stream.Next());
        return;
    }
    stream.Skip(1);

    // $Expression
    const Token& expTok = stream.Peek();
    IdType type = ParseExpression(false);
    if ( Error::Get() != "" ) return;
    if ( type != TypeInt && type != TypeFloat ) {
        Error::Set("'for' variable termination expression must be of numeric type", expTok);
        return;
    }

    // Optional Step $Expression
    if ( stream.Peek().Type() == TokenStep ) {
        stream.Next();  // Step
        const Token& expTok = stream.Peek();
        type = ParseExpression(false);
        if ( Error::Get() != "" ) return;
        if ( type != TypeInt && type != TypeFloat ) {
            Error::Set("'for' variable step expression must be of numeric type", expTok);
            return;
        }
    }

    // $EndSt
    ParseEndStatement();
    if ( Error::Get() != "" ) return;

    // $Block Next
    inLoop++;
    ParseBlock(vector<TokenType>(1, TokenNext), NULL, NULL);
    inLoop--;
}

// Repeat $EndSt $Block(Until) $Expression
void Syntactical::ParseRepeat() {
    // Repeat
    stream.Next();

    // $EndSt
    ParseEndStatement();
    if ( Error::Get() != "" ) return;

    // $Block Until
    inLoop++;
    ParseBlock(vector<TokenType>(1, TokenUntil), NULL, NULL);
    inLoop--;
    if ( Error::Get() != "" ) return;

    // $Expression
    IdType type = ParseExpression(true);
    if ( Error::Get() != "" ) return;
    if ( type != TypeInt ) {
        Error::Set("Invalid conditional expression", stream.Peek());
        return;
    }
}

// While $Expression $EndSt $Block(EndWhile)
void Syntactical::ParseWhile() {
    // While
    stream.Next();

    // $Expression
    IdType type = ParseExpression(true);
    if ( Error::Get() != "" ) return;
    if ( type != TypeInt ) {
        Error::Set("Invalid conditional expression", stream.Peek());
        return;
    }

    // $EndSt
    ParseEndStatement();
    if ( Error::Get() != "" ) return;

    // $Block EndWhile
    inLoop++;
    ParseBlock(vector<TokenType>(1, TokenEndWhile), NULL, NULL);
    inLoop--;
}

// Return [$Expression]
void Syntactical::ParseReturn() {
    // Return
    Token tok = stream.Next();

    // Expression
    IdType type = TypeVoid;
    bool isNull = false;
    if ( !stream.Peek().IsEndStatement() ) {
        tok = stream.Peek();
        if ( tok.Type() == TokenNull ) {
            isNull = true;
        }
        type = ParseExpression(true);
        if ( Error::Get() != "" ) return;
    }

    // Check expression type
    if ( currentFunction == NULL  &&  !AreTypesCompatible(type, TypeInt) ) {                        // Program
        Error::Set("Main program must return a value", tok);
        return;
    } else if ( currentFunction != NULL && !AreTypesCompatible(currentFunction->Type(), type) ) {   // Function
        // Null is allowed for struct return types
        if ( currentFunction->Type() <= TypeStruct || (currentFunction->Type() > TypeStruct && !isNull) ) {
            Error::Set("Incompatible type in return expression", tok);
            return;
        }
    }
}

// Exit
void Syntactical::ParseExit() {
    // Exit
    const Token& tok = stream.Next();

    // Check that we are in a loop
    if ( inLoop == 0 )
        Error::Set("Unexpected 'Exit' outside loop", tok);
}

// $AssigmentExp | $BooleanExp
IdType Syntactical::ParseExpression(bool isConditional) {
    // Return expression type
    if ( isConditional )
        return ParseBooleanExp(isConditional);
    else
        return ParseAssignmentExp(isConditional);
}

// var = $Expression
IdType Syntactical::ParseAssignmentExp(bool isConditional) {
    // Parse expression
    int pos = stream.Pos();
    IdType expType = ParseBooleanExp(isConditional);
    if ( Error::Get() != "" ) return TypeVoid;

    // Is assignment
    if ( stream.Peek().Type() == TokenAssign ) {
        if ( !isConditional ) {
            // Restore previous position
            stream.Seek(pos);

            // Make sure it is a var on the left side
            expType = ParseVarAccess();
            if ( Error::Get() != "" ) return TypeVoid;
        }

        stream.Skip(1); // =

        // Expression
        IdType expType2 = ParseExpression(isConditional);
        if ( Error::Get() != "" ) return TypeVoid;
        if ( !AreTypesCompatible(expType, expType2) ) {
            Error::Set("Incompatible types", stream.Peek());
            return TypeVoid;
        }

        // If conditional, return type is int
        if ( isConditional ) expType = TypeInt;

        return expType;
    // Not assignment
    } else {
        return expType;
    }
}

// $RelationalExp [$BooleanOp $BooleanExp]
IdType Syntactical::ParseBooleanExp(bool isConditional) {
    IdType type = ParseRelationalExp(isConditional);
    if ( Error::Get() != "" ) return TypeVoid;
    if ( stream.Peek().IsBooleanOp() ) {
        stream.Next();  // boolop
        IdType type2 = ParseBooleanExp(isConditional);
        if ( Error::Get() != "" ) return TypeVoid;

        // Check types
        if ( type == TypeString || type2 == TypeString ) {
            Error::Set("Cannot perform boolean operations on strings", stream.Peek());
            return TypeVoid;
        }
        if ( !AreTypesCompatible(type, type2) ) {
            Error::Set("Incompatible types", stream.Peek());
            return TypeVoid;
        }

        return TypeInt;
    }

    return type;
}

// $AdditiveExp [$RelationalOp $RelationalExp]
IdType Syntactical::ParseRelationalExp(bool isConditional) {
    IdType type = ParseAdditiveExp(isConditional);
    if ( Error::Get() != "" ) return TypeVoid;
    if ( (isConditional && stream.Peek().IsRelationalOp()) || (!isConditional && stream.Peek().IsRelationalOp() && stream.Peek().Type() != TokenAssign) ) {
        TokenType op = stream.Next().Type();  // relop
        IdType type2 = ParseRelationalExp(isConditional);
        if ( Error::Get() != "" ) return TypeVoid;

        // Check types
        if ( (type == TypeString || type2 == TypeString) && op != TokenAssign && op != TokenNotEqual ) {
            Error::Set("Cannot perform relational operations on strings", stream.Peek());
            return TypeVoid;
        }
        if ( !AreTypesCompatible(type, type2) ) {
            Error::Set("Incompatible types", stream.Peek());
            return TypeVoid;
        }

        return TypeInt;
    }

    return type;
}

// $MultiplicativeExp [$AdditiveOp $AdditiveExp]
IdType Syntactical::ParseAdditiveExp(bool isConditional) {
    IdType type = ParseMultiplicativeExp(isConditional);
    if ( Error::Get() != "" ) return TypeVoid;
    if ( stream.Peek().IsAdditiveOp() ) {
        TokenType addop = stream.Next().Type();  // addop
        IdType type2 = ParseAdditiveExp(isConditional);
        if ( Error::Get() != "" ) return TypeVoid;

        // Check types
        if ( addop != TokenPlus && (type == TypeString || type2 == TypeString) ) {
            Error::Set("Cannot perform operation on string", stream.Peek());
            return TypeVoid;
        }
        if ( !AreTypesCompatible(type, type2) ) {
            Error::Set("Incompatible types", stream.Peek());
            return TypeVoid;
        }

        return CastTypes(type, type2);
    }

    return type;
}

// $Factor [$MultiplicativeOp $MultiplicativeExp]
IdType Syntactical::ParseMultiplicativeExp(bool isConditional) {
    IdType type = ParseFactor(isConditional);
    if ( Error::Get() != "" ) return TypeVoid;
    if ( stream.Peek().IsMultiplicativeOp() ) {
        stream.Next();  // mulop
        IdType type2 = ParseMultiplicativeExp(isConditional);
        if ( Error::Get() != "" ) return TypeVoid;

        // Check types
        if ( type == TypeString || type2 == TypeString ) {
            Error::Set("Cannot perform multiplicative operations on strings", stream.Peek());
            return TypeVoid;
        }
        if ( !AreTypesCompatible(type, type2) ) {
            Error::Set("Incompatible types", stream.Peek());
            return TypeVoid;
        }

        return CastTypes(type, type2);
    }

    return type;
}

// $UnaryOp $Factor | ( $Expression ) | $Var | $FuncPtr | $FuncCall | $Literal | new $StructName | delete $Var
IdType Syntactical::ParseFactor(bool isConditional) {
    // $UnaryOp $Factor
    if ( stream.Peek().IsUnaryOp() ) {
        TokenType unop = stream.Next().Type();  // unop
        IdType type = ParseFactor(isConditional);
        if ( unop == TokenNot )
            return TypeInt;
        else
            return type;
    // ( $Expression )  -- ( $Type ) $Factor is not supported anymore
    } else if ( stream.Peek().Type() == TokenOpenParen ) {
        IdType type = TypeVoid;
        stream.Skip(1);  // (

        // Cannot cast to string
        /*if ( stream.Peek().Type() == TokenStringKeyword ) {
            Error::Set("Cannot cast to string", stream.Next());
            return TypeVoid;
        }

        // If next token is Int, Float, or a Struct type, it is a cast
        if ( stream.Peek().Type() == TokenIntKeyword || stream.Peek().Type() == TokenFloatKeyword || (stream.Peek().Type() == TokenIdentifier && scanner.CountStructOccurences(stream.Peek().Data()) > 0) ) {
            // Get type
            const Token& typeTok = stream.Next();
            type = IdTypeFromTokenType(typeTok.Type());

            // Check that there's a ")" after the type
            if ( stream.Peek().Type() != TokenCloseParen ) {
                Error::Set("Expected ')'", stream.Next());
                return TypeVoid;
            }
            stream.Skip(1); // )

            // Parse expression to cast
            IdType type2 = ParseFactor(isConditional);
            if ( Error::Get() != "" ) return TypeVoid;
            if ( type2 == TypeString ) {
                if ( type == TypeStruct )
                    Error::Set("Cannot cast a Struct type to a numeric type", stream.Next());
                else
                    Error::Set("Cannot cast string to a numeric type", stream.Next());
                return TypeVoid;
            }

            // If we are casting to a struct type
            if ( type == TypeStruct ) {
                // Check that expression to cast is TypeStruct
                if ( type2 != TypeStruct ) {
                    Error::Set("Only functions that return a generic Struct can be cast to a Struct type", tok);
                    return TypeVoid;
                }

                type = IdType(TypeStruct + scanner.StructIndex(typeTok.Data()) + 1);
            }
        // It is a parenthesized expression
        } else {*/
            type = ParseExpression(isConditional);
            if ( Error::Get() != "" ) return TypeVoid;
            if ( stream.Peek().Type() != TokenCloseParen ) {
                Error::Set("Expected ')'", stream.Next());
                return TypeVoid;
            }
            stream.Skip(1); // )
        //}
        return type;
    // $Const | $Var | $FuncPtr | $FuncCall
    } else if ( stream.Peek().Type() == TokenIdentifier ) {
        // $Const
        if ( scanner.CountConstantOccurences(stream.Peek().Data()) > 0 ) {
            string name = stream.Next().Data(); // identifier
            return scanner.GetConstant(name)->Type();
        // $Var
        } else if ( scanner.CountLocalOccurences(stream.Peek().Data()) > 0 || scanner.CountGlobalOccurences(stream.Peek().Data()) > 0 ) {
            return ParseVarAccess();
        // $FuncPtr | $FuncCall
        } else if ( scanner.CountFunctionOccurences(stream.Peek().Data()) > 0 ) {
            // $FuncCall
            if ( stream.Peek(1).Type() == TokenOpenParen )
                return ParseFunctionCall();
            // $FuncPtr
            else {
                stream.Skip(1); // Func name
                return TypeInt;
            }
        // Unknown
        } else {
            Error::Set("Unknown identifier '" + stream.Peek().Data() + "'", stream.Peek());
            return TypeVoid;
        }
    // $Literal
    } else if ( stream.Peek().Type() == TokenIntLiteral || stream.Peek().Type() == TokenFloatLiteral || stream.Peek().Type() == TokenStringLiteral ) {
        return IdTypeFromTokenType(stream.Next().Type());
    // new $StructName
    } else if ( stream.Peek().Type() == TokenNew ) {
        stream.Skip(1); // new

        // Check identifier
        if ( stream.Peek().Type() != TokenIdentifier ) {
            Error::Set("Expected struct name", stream.Next());
            return TypeVoid;
        }
        string type = stream.Next().Data(); // type

        // Check type
        if ( scanner.CountStructOccurences(type) == 0 ) {
            Error::Set("Identifier '" + type + "' is not a struct", stream.Next());
            return TypeVoid;
        }
        return IdType(TypeStruct + scanner.StructIndex(type) + 1);
    // delete var
    } else if ( stream.Peek().Type() == TokenDelete ) {
        stream.Skip(1); // delete

        // Get type of var to delete
        IdType type = ParseFactor(isConditional);
        if ( Error::Get() != "" ) return TypeVoid;

        // Check type
        if ( type == TypeStruct ) {
            Error::Set("Cannot delete a generic Struct", stream.Next());
            return TypeVoid;
        } else if ( type < TypeStruct ) {
            Error::Set("Only struct types can be deleted", stream.Next());
            return TypeVoid;
        }

        return TypeVoid;    // delete has no return value
    // True | False
    } else if ( stream.Peek().IsBooleanLiteral() ) {
        stream.Skip(1); // True | False
        return TypeInt;
    // Null
    } else if ( stream.Peek().IsNullLiteral() ) {
        stream.Skip(1); // Null
        return TypeStruct;
    } else {
        Error::Set("Invalid expression", stream.Next());
        return TypeVoid;
    }
}

// $Var [. $MemberAccess]|[( $IndexPath )]
IdType Syntactical::ParseVarAccess() {
    // Name
    if ( stream.Peek().Type() != TokenIdentifier ) {
        Error::Set("Expected identifier", stream.Next());
        return TypeVoid;
    }
    string name = stream.Next().Data();

    // Check that identifier is a var
    if ( scanner.CountLocalOccurences(name) == 0 && scanner.CountGlobalOccurences(name) == 0 ) {
        Error::Set("Identifier is not a var", stream.Next());
        return TypeVoid;
    }

    // Check member access
    if ( stream.Peek().Type() == TokenDot ) {
        // Check that it is a struct
        if ( scanner.CountLocalOccurences(name) > 0 ) {
            if ( scanner.CountStructOccurences(scanner.GetLocal(name)->StructName()) == 0 ) {
                Error::Set("Cannot access member on non-struct variable", stream.Next());
                return TypeVoid;
            }
            stream.Skip(1); // .
            return ParseMemberAccess(*scanner.GetStruct(scanner.GetLocal(name)->StructName()));
        } else {
            if ( scanner.CountStructOccurences(scanner.GetGlobal(name)->StructName()) == 0 ) {
                Error::Set("Cannot access member on non-struct variable", stream.Next());
                return TypeVoid;
            }
            stream.Skip(1); // .
            return ParseMemberAccess(*scanner.GetStruct(scanner.GetGlobal(name)->StructName()));
        }
    }

    // Check array access
    int pathComponents = 0;
    if ( stream.Peek().Type() == TokenOpenParen ) {
        stream.Skip(1); // (

        // Indices
        while ( stream.Peek().Type() != TokenCloseParen ) {
            IdType type = ParseExpression(true);
            if ( Error::Get() != "" ) return TypeVoid;

            // Check type
            if ( !AreTypesCompatible(type, TypeInt) ) {
                Error::Set("Expected integer expression in array access", stream.Peek());
                return TypeVoid;
            }

            // Check , or )
            if ( stream.Peek().Type() != TokenComma && stream.Peek().Type() != TokenCloseParen ) {
                Error::Set("Expected ',' or ')'", stream.Next());
                return TypeVoid;
            }

            // Skip "," if there's one
            if ( stream.Peek().Type() == TokenComma )
                stream.Next();

            pathComponents++;
        }

        stream.Skip(1); // )
    }

    // Make sure that the number of indices is correct
    int correctPathComponents = 0;
    if ( scanner.CountLocalOccurences(name) > 0 ) {
        correctPathComponents = scanner.GetLocal(name)->IndexPath().size();
    } else {
        correctPathComponents = scanner.GetGlobal(name)->IndexPath().size();
    }
    if ( pathComponents != correctPathComponents ) {
		Error::Set("Invalid array access (expected " + Str(correctPathComponents) + " indices, found " + Str(pathComponents) + ")", stream.Next());
        return TypeVoid;
    }

    // Return var type
    if ( scanner.CountLocalOccurences(name) > 0 )
        return scanner.GetLocal(name)->Type();
    else
        return scanner.GetGlobal(name)->Type();
}

// $FieldName [. $MemberAccess]|[( $IndexPath )]
IdType Syntactical::ParseMemberAccess(const Struct &structure) {
    // Name
    if ( stream.Peek().Type() != TokenIdentifier ) {
        Error::Set("Expected identifier", stream.Next());
        return TypeVoid;
    }
    string name = stream.Next().Data();

    // Check name
    if ( structure.Field(name) == NULL ) {
        Error::Set("Could not find field '" + name + "' in struct '" + structure.Name() + "'", stream.Next());
        return TypeVoid;
    }

    // Additional field accesses
    if ( stream.Peek().Type() == TokenDot ) {
        // Check that it is a struct
        if ( scanner.CountStructOccurences(structure.Field(name)->StructName()) == 0 ) {
            Error::Set("Cannot access member on non-struct variable", stream.Next());
            return TypeVoid;
        }

        stream.Skip(1); // .

        return ParseMemberAccess(*scanner.GetStruct(structure.Field(name)->StructName()));
    }

    // Check array access
    int pathComponents = 0;
    if ( stream.Peek().Type() == TokenOpenParen ) {
        stream.Skip(1); // (

        // Params
        while ( stream.Peek().Type() != TokenCloseParen ) {
            IdType type = ParseExpression(true);
            if ( Error::Get() != "" ) return TypeVoid;

            // Check type
            if ( !AreTypesCompatible(type, TypeInt) ) {
                Error::Set("Expected integer expression in array access", stream.Peek());
                return TypeVoid;
            }

            // Check , or )
            if ( stream.Peek().Type() != TokenComma && stream.Peek().Type() != TokenCloseParen ) {
                Error::Set("Expected ',' or ')'", stream.Next());
                return TypeVoid;
            }

            // Skip "," if there's one
            if ( stream.Peek().Type() == TokenComma )
                stream.Next();

            pathComponents++;
        }

        stream.Skip(1); // )
    }

    // Make sure that the number of indices is correct
    if ( (int)structure.Field(name)->IndexPath().size() != pathComponents ) {
		Error::Set("Invalid array access (expected " + Str(structure.Field(name)->IndexPath().size()) + " indices, found " + Str(pathComponents) + ")", stream.Next());
        return TypeVoid;
    }

    return structure.Field(name)->Type();
}

// $FuncName ( $Params )
IdType Syntactical::ParseFunctionCall() {
    // FuncName
    const Token& nameToken = stream.Next();

    // (
    if ( stream.Peek().Type() != TokenOpenParen ) {
        Error::Set("Expected '('", stream.Next());
        return TypeVoid;
    }
    stream.Skip(1);

    // Params
    int numParams = 0;
    while ( stream.Peek().Type() != TokenCloseParen ) {
        // Check that we are within the corrent param count
        if ( numParams+1 > scanner.GetFunction(nameToken.Data())->NumArgs() ) {
			Error::Set("Incorrect number of parameters in function call (expected " + Str(scanner.GetFunction(nameToken.Data())->NumArgs()) + ")", stream.Next());
            return TypeVoid;
        }

        // Parse param expression
        IdType type = ParseExpression(true);
        if ( Error::Get() != "" ) return TypeVoid;

        // Check type
        if ( !AreTypesCompatible(scanner.GetFunction(nameToken.Data())->Local(numParams).Type(), type) ) {
            Error::Set("Incompatible types", stream.Peek());
            return TypeVoid;
        }

        // Check , or )
        if ( stream.Peek().Type() != TokenComma && stream.Peek().Type() != TokenCloseParen ) {
            Error::Set("Expected ',' or ')'", stream.Next());
            return TypeVoid;
        }

        if ( stream.Peek().Type() == TokenComma )
            stream.Next();

        numParams++;
    }

    // )
    if ( stream.Peek().Type() != TokenCloseParen ) {
        Error::Set("Expected ')'", stream.Next());
        return TypeVoid;
    }
    stream.Next();

    // Check number of params
    if ( scanner.FunctionArguments(nameToken.Data()) != numParams ) {
        Error::Set("Function call does not match number of arguments", nameToken);
        return TypeVoid;
    }

    // Return function type
    return scanner.GetFunction(nameToken.Data())->Type();
}

bool Syntactical::AreTypesCompatible(IdType type1, IdType type2) {
    if ( type1 == type2 ) {
        return true;
    } else {
        switch ( type1 ) {
        case TypeInt:
            switch ( type2 ) {
            case TypeFloat:
                return true;
            case TypeString:
                return false;
            default:
                return false;
            }
            break;
        case TypeFloat:
            switch ( type2 ) {
            case TypeInt:
                return true;
            case TypeString:
                return false;
            default:
                return false;
            }
            break;
        case TypeString:
            switch ( type2 ) {
            case TypeInt:
                return false;
            case TypeFloat:
                return false;
			case TypePChar:
				return true;
            default:
                return false;
            }
            break;
		case TypePChar:
			switch ( type2 ) {
			case TypeString:
				return true;
			default:
				return false;
			}
			break;
		case TypeStruct:
            if ( type2 >= TypeStruct )
                return true;
            else
                return false;
            break;
        default:
            // We can assign a generic Struct to any user type
            if ( type2 == TypeStruct )
                return true;
            else
                return false;
        }
    }
}

IdType Syntactical::CastTypes(IdType type1, IdType type2) {
    if ( type1 == TypeString || type2 == TypeString )
        return TypeString;
    else if ( type1 == TypeFloat || type2 == TypeFloat )
        return TypeFloat;
    else
        return TypeInt;
}

bool Syntactical::IsValidIdentifier(const string &name, bool checkLocals) {
    if ( NumDefinitions(name, checkLocals) > 1 )
        return false;
    else
        return true;
}

int Syntactical::NumDefinitions(const string &name, bool checkLocals) {
    int count = 0;
    count += scanner.CountConstantOccurences(name);
    count += scanner.CountStructOccurences(name);
    count += scanner.CountFunctionOccurences(name);
    count += scanner.CountGlobalOccurences(name);
    if ( checkLocals ) count += scanner.CountLocalOccurences(name);
    return count;
}

bool Syntactical::IsEndType(const vector<TokenType> &endTypes, TokenType token) {
    for ( vector<TokenType>::const_iterator it = endTypes.begin(); it != endTypes.end(); it++ ) {
        if ( *it == token )
            return true;
    }
    return false;
}

int Syntactical::ResolveIntConstant(const Var* constant) {
    int constVal;

    // Save current stream pos
    int offset = stream.Pos();

    // Move to constant init expression
    stream.Seek(constant->InitExpOffset());

    // If it is a literal, return its value
    if ( stream.Peek().Type() == TokenIntLiteral ) {
		constVal = Val(stream.Peek().Data());
    // If it is a float literal, return its value cast to int (it may happen because
    // a constant assign a float constant as its init expression
    } else if ( stream.Peek().Type() == TokenFloatLiteral ) {
		constVal = (int)ValF(stream.Peek().Data());
    // If it's a constant, get its value
    } else {
        constVal = ResolveIntConstant(scanner.GetConstant(stream.Peek().Data()));
    }

    // Restore stream pos
    stream.Seek(offset);

    // Return expression value
    return constVal;
}
