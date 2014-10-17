#include "preprocessor.h"
#include "../core/string.h"
#include "error.h"
#include "tokenstream.h"
#include <iostream>

using namespace std;

Preprocessor::Preprocessor() : isGui(false) {
//AddModule("core");
}

void Preprocessor::Preprocess(const std::vector<Token> &tokens) {
    // Create stream
    TokenStream stream(tokens);

	// This will point to first non preprocessor token
	int first = 0;

	// Go to the first non end-of-line token
    while ( stream.HasNext() && stream.Peek().Type() == TokenEndOfLine ) {
        first++;
        stream.Skip(1);
    }

    // Parse preprocessor tokens
    while ( stream.HasNext() && stream.Peek().IsPreprocKeyword() ) {
        TokenType type = stream.Next().Type();

        // $Include
        if ( type == TokenPreprocInclude ) {
            if ( stream.Peek().Type() != TokenStringLiteral ) {
                Error::Set("Expected include name", stream.Peek());
                return;
            }

            bool present = false;
            string file = RealPath(Lower(stream.Next().Data().c_str()));
            for ( vector<string>::const_iterator it = includes.begin(); it != includes.end(); it++ ) {
                if ( *it == file ) {
                    present = true;
                    break;
                }
            }
            if ( !present ) includes.push_back(file);
		// $Use
		} else if ( type == TokenPreprocUse ) {
            if ( stream.Peek().Type() != TokenIdentifier ) {
                Error::Set("Expected module identifier", stream.Peek());
                return;
            }

            bool present = false;
            string file = Lower(stream.Next().Data().c_str());
            for ( vector<string>::const_iterator it = modules.begin(); it != modules.end(); it++ ) {
                if ( *it == file ) {
                    present = true;
                    break;
                }
            }
            if ( !present ) modules.push_back(file);
        // $Link
        } else if ( type == TokenPreprocLink ) {
            if ( stream.Peek().Type() != TokenStringLiteral ) {
                Error::Set("Expected link name", stream.Peek());
                return;
            }

            bool present = false;
            string file = Lower(stream.Next().Data().c_str());
            for ( vector<string>::const_iterator it = links.begin(); it != links.end(); it++ ) {
                if ( *it == file ) {
                    present = true;
                    break;
                }
            }
            if ( !present ) links.push_back(file);
        // $Option
        } else if ( type == TokenPreprocOption ) {
            if ( stream.Peek().Type() != TokenIdentifier ) {
                Error::Set("Expected option identifier", stream.Peek());
                return;
            }

            string option = stream.Next().Data().c_str();
            if ( Lower(option.c_str()) == string("console") ) {
                isGui = false;
            } else if ( Lower(option.c_str()) == string("gui") ) {
                isGui = true;
            } else {
                Error::Set("Unknown option " + option, stream.Peek(-2));
                return;
            }
        }

        // Skip preprocessor directive and empty or comment lines after it
        first += 2;
        while ( stream.Peek().Type() == TokenEndOfLine ) {
            first++;
            stream.Skip(1);
        }
    }

    // Save preprocessed tokens vector
    for ( vector<Token>::const_iterator it = tokens.begin()+first; it != tokens.end(); it++ ) {
        preprocessedTokens.push_back(*it);
    }
}
