#include "scanner.h"
#include "error.h"
#include <iostream>

using namespace std;

void Scanner::ParseConstants() {
    // Move to beginning of stream
    stream.Seek(0);

    // Parse whole buffer
    while ( stream.HasNext() ) {
        // If "const" keyword is found
        if ( stream.Next().Type() == TokenConst ) {
            // If identifier is found
            if ( stream.Peek().Type() == TokenIdentifier ) {
                const Token& nameToken = stream.Next();  // Name

                // Parse optional symbolic type (assumed int)
                IdType type = TypeInt;
                if ( stream.Peek().Type() == TokenPercent ) {
                    stream.Skip(1); // %
                } else if ( stream.Peek().Type() == TokenSharp) {
                    stream.Skip(1); // #
                    type = TypeFloat;
                } else if ( stream.Peek().Type() == TokenDollar ) {
                    stream.Skip(1); // $
                    type = TypeString;
                } else if ( stream.Peek().Type() == TokenAs ) {
                    stream.Skip(1); // As
                    if ( stream.Peek().Type() == TokenIntKeyword || stream.Peek().Type() == TokenFloatKeyword || stream.Peek().Type() == TokenStringKeyword ) {
                        type = IdTypeFromTokenType(stream.Next().Type());
                    }
                }

                // Add to constants list
                constants.push_back(Var(type, nameToken.Data(), ""));
            }
        }
    }
}

void Scanner::ParseStructs() {
    // Parse whole buffer looking only for struct names
    stream.Seek(0);
    while ( stream.HasNext() ) {
        // If "struct" keyword is found
        if ( stream.Next().Type() == TokenStruct ) {
            if ( stream.Peek().Type() == TokenIdentifier ) {
                string name = stream.Next().Data(); // name
                structs.push_back(Struct(name));
            }
        }
    }

    // Parse whole buffer and parse struct fields
    stream.Seek(0);
    while ( stream.HasNext() ) {
        // If "struct" keyword is found
        if ( stream.Next().Type() == TokenStruct ) {
            if ( stream.Peek().Type() == TokenIdentifier ) {
                vector<Var> fields;
                string name = stream.Next().Data(); // name

                // While we don't reach "endstruct"
                while ( stream.HasNext() && stream.Peek().Type() != TokenEndStruct ) {
                    // We find a "dim" keyword
                    if ( stream.Next().Type() == TokenDim ) {
                        // We find an identifier after "dim"
                        if ( stream.Peek().Type() == TokenIdentifier ) {
                            const Token& nameToken = stream.Next(); // Name

                            // Parse optional type (assumed int)
                            IdType type = TypeInt;
                            string typeName = "int";
                            if ( stream.Peek().Type() == TokenPercent ) {
                                stream.Skip(1); // %
                            } else if ( stream.Peek().Type() == TokenSharp) {
                                stream.Skip(1); // #
                                type = TypeFloat;
                                typeName = "float";
                            } else if ( stream.Peek().Type() == TokenDollar ) {
                                stream.Skip(1); // $
                                type = TypeString;
                                typeName = "string";
                            } else if ( stream.Peek().Type() == TokenAs ) {
                                stream.Skip(1); // As
                                if ( IsType(stream.Peek()) ) {
                                    type = IdTypeFromTokenType(stream.Peek().Type());
                                    typeName = stream.Next().Data();
                                }
                            }

                            // If field type is a struct, set correct type
                            if ( CountStructOccurences(typeName) > 0 )
                                type = IdType(type + StructIndex(typeName) + 1);

                            // Add field
                            fields.push_back(Var(type, nameToken.Data(), typeName));
                        }
                    }
                }
                stream.Skip(1); // EndStruct
                GetStruct(name)->SetFields(fields);
            }
        }
    }
}

void Scanner::ParseGlobals() {
    // Move to beginning of stream
    stream.Seek(0);

    // Parse whole buffer
    int brace = 0;
    int inExtern = 0;
    while ( stream.HasNext() ) {
        // Skip defs in program, functions, structs and externs
        if ( stream.Peek().Type() == TokenExtern ) {
            inExtern++;
            stream.Skip(1);
        } else if ( stream.Peek().Type() == TokenEndExtern ) {
            inExtern--;
            stream.Skip(1);
        } else if ( inExtern == 0 && (stream.Peek().Type() == TokenProgram || stream.Peek().Type() == TokenFunction || stream.Peek().Type() == TokenStruct) ) {
            brace++;
            stream.Skip(1);
        } else if ( inExtern == 0 && (stream.Peek().Type() == TokenEndProgram || stream.Peek().Type() == TokenEndFunction || stream.Peek().Type() == TokenEndStruct) ) {
            brace--;
            stream.Skip(1);
        // Found "dim" keyword
        } else if ( brace == 0 && inExtern == 0 && stream.Peek().Type() == TokenDim ) {
            stream.Skip(1); // Dim
            const Token& nameToken = stream.Next();  // Name

            // Parse optional type (assumed int)
            IdType type = TypeInt;
            string typeName = "int";
            if ( stream.Peek().Type() == TokenPercent ) {
                stream.Skip(1); // %
            } else if ( stream.Peek().Type() == TokenSharp) {
                stream.Skip(1); // #
                type = TypeFloat;
                typeName = "float";
            } else if ( stream.Peek().Type() == TokenDollar ) {
                stream.Skip(1); // $
                type = TypeString;
                typeName = "string";
            } else if ( stream.Peek().Type() == TokenAs ) {
                stream.Skip(1); // As
                if ( IsType(stream.Peek()) ) {
                    type = IdTypeFromTokenType(stream.Peek().Type());
                    typeName = stream.Next().Data();
                }
            }

            // If field type is a struct, set correct type
            if ( CountStructOccurences(typeName) > 0 )
                type = IdType(type + StructIndex(typeName) + 1);

            // Add global
            globals.push_back(Var(type, nameToken.Data(), typeName));
        } else {
            stream.Skip(1);
        }
    }
}

void Scanner::ParseFunctions() {
    // Move to beginning of stream
    stream.Seek(0);

    // Parse whole buffer
    string currentDll = "";
    while ( stream.HasNext() ) {
        const Token& tok = stream.Next();
        if ( tok.Type() == TokenExtern ) {
            if ( stream.Peek().Type() == TokenStringLiteral )
                currentDll = stream.Next().Data();
        } else if ( tok.Type() == TokenEndExtern ) {
            currentDll = "";
        } else if ( tok.Type() == TokenFunction ) {
            // Name
            const Token& nameToken = stream.Next();

            // If an identifier is found correctly
            if ( nameToken.Type() == TokenIdentifier ) {
                // Optional %,#,$
                IdType type = TypeVoid;
                string typeName = "";
                if ( stream.Peek().Type() == TokenPercent ) {
                    stream.Skip(1); // %
                    type = TypeInt;
                    typeName = "int";
                } else if ( stream.Peek().Type() == TokenSharp ) {
                    stream.Skip(1); // #
                    type = TypeFloat;
                    typeName = "float";
                } else if ( stream.Peek().Type() == TokenDollar ) {
                    stream.Skip(1); // $
                    type = TypeString;
                    typeName = "string";
                }

                // Add args
                vector<Var> args;
                stream.Skip(1);  // (
                while ( stream.HasNext() && stream.Peek().Type() != TokenCloseParen ) {
                    string argName = stream.Next().Data();  // arg name
                    IdType argType = TypeInt;
                    string argTypeName = "int";
                    if ( stream.Peek().Type() == TokenPercent ) {
                        stream.Skip(1); // %
                    } else if ( stream.Peek().Type() == TokenSharp ) {
                        stream.Skip(1); // #
                        argType = TypeFloat;
                        argTypeName = "float";
                    } else if ( stream.Peek().Type() == TokenDollar ) {
                        stream.Skip(1); // $
                        argType = TypeString;
                        argTypeName = "string";
                    } else if ( stream.Peek().Type() == TokenAs ) {
                        stream.Skip(1);  // As
                        argType = IdTypeFromTokenType(stream.Peek().Type());
                        argTypeName = stream.Next().Data();

                        // If field type is a struct, set correct type
                        if ( CountStructOccurences(argTypeName) > 0 )
                            argType = IdType(argType + StructIndex(argTypeName) + 1);
                    }

                    // Push var into args array
                    args.push_back(Var(argType, argName, argTypeName));

                    if ( stream.Peek().Type() == TokenComma ) stream.Skip(1);  // comma
                }
                stream.Skip(1);  // )

                // Parse optional type with "As" syntax
                if ( stream.Peek().Type() == TokenAs ) {
                    stream.Skip(1); // As
                    type = IdTypeFromTokenType(stream.Peek().Type());
                    typeName = stream.Next().Data();

                    // If field type is a struct, set correct type
                    if ( CountStructOccurences(typeName) > 0 )
                        type = IdType(type + StructIndex(typeName) + 1);
                }

                // Parse optional extern name for external functions
                string externName = "";
                if ( stream.Peek().Type() == TokenStringLiteral ) {
                    externName = stream.Next().Data();
                }

                // Add function to list
                Function func(nameToken.Data(), type, args);
                func.SetExternName(externName);
                func.SetLibName(currentDll);
                functions.push_back(func);
            }
        }
    }
}

void Scanner::ParseLocals(int pos, const std::vector<Var> *args) {
    // Move stream to specified position
    stream.Seek(pos);

    // Clear previous locals
    locals.clear();

    // Add arguments
    if ( args != NULL ) {
        for ( vector<Var>::const_iterator it = args->begin(); it != args->end(); it++ ) {
            locals.push_back(*it);
        }
    }

    // Parse whole function or program
    while ( stream.HasNext() && stream.Peek().Type() != TokenEndFunction && stream.Peek().Type() != TokenEndProgram ) {
        // If "dim" is found
        if ( stream.Next().Type() == TokenDim ) {
            const Token& nameToken = stream.Next();  // Name

            // Parse optional type (assumed int)
            IdType type = TypeInt;
            string typeName = "int";
            if ( stream.Peek().Type() == TokenPercent ) {
                stream.Skip(1); // %
            } else if ( stream.Peek().Type() == TokenSharp ) {
                stream.Skip(1); // #
                type = TypeFloat;
                typeName = "float";
            } else if ( stream.Peek().Type() == TokenDollar ) {
                stream.Skip(1); // $
                type = TypeString;
                typeName = "string";
            } else if ( stream.Peek().Type() == TokenAs ) {
                stream.Skip(1); // As
                if ( IsType(stream.Peek()) ) {
                    type = IdTypeFromTokenType(stream.Peek().Type());
                    typeName = stream.Next().Data();

                    // If field type is a struct, set correct type
                    if ( CountStructOccurences(typeName) > 0 )
                        type = IdType(type + StructIndex(typeName) + 1);
                }
            }

            // Add local
            locals.push_back(Var(type, nameToken.Data(), typeName));
        }
    }
}

int Scanner::CountConstantOccurences(string name) const {
    int count = 0;
	name = Lower(name);
    for ( vector<Var>::const_iterator it = constants.begin(); it != constants.end(); it++ ) {
		if ( Lower((*it).Name()) == name )
            count++;
    }
    return count;
}

int Scanner::CountStructOccurences(string name) const {
    int count = 0;
	name = Lower(name);
    for ( vector<Struct>::const_iterator it = structs.begin(); it != structs.end(); it++ ) {
		if ( Lower((*it).Name()) == name )
            count++;
    }
    return count;
}

int Scanner::CountGlobalOccurences(string name) const {
    int count = 0;
	name = Lower(name);
    for ( vector<Var>::const_iterator it = globals.begin(); it != globals.end(); it++ ) {
		if ( Lower((*it).Name()) == name )
            count++;
    }
    return count;
}

int Scanner::CountFunctionOccurences(string name) const {
    int count = 0;
	name = Lower(name);
    for ( vector<Function>::const_iterator it = functions.begin(); it != functions.end(); it++ ) {
		if ( Lower((*it).Name()) == name )
            count++;
    }
    return count;
}

int Scanner::CountLocalOccurences(string name) const {
    int count = 0;
	name = Lower(name);
    for ( vector<Var>::const_iterator it = locals.begin(); it != locals.end(); it++ ) {
		if ( Lower((*it).Name()) == name )
            count++;
    }
    return count;
}

int Scanner::FunctionArguments(string name) const {
	name = Lower(name);
    for ( vector<Function>::const_iterator it = functions.begin(); it != functions.end(); it++ ) {
		if ( Lower((*it).Name()) == name )
            return (*it).NumArgs();
    }
    return 0;
}

// Does not report pchar as a valid type, since it is handled specially
bool Scanner::IsType(const Token &token) const {
    if ( token.Type() == TokenIntKeyword )
        return true;
    else if ( token.Type() == TokenFloatKeyword )
        return true;
    else if ( token.Type() == TokenStringKeyword )
        return true;
    else if ( token.Type() == TokenIdentifier && CountStructOccurences(token.Data()) > 0 )
        return true;
    else
        return false;
}
