#include <vector>

#include "Token.h"
#include "Node.h"
#include "Error.h"

#ifndef PARSER_CLASS
#define PARSER_CLASS

class ParseResult {
    public:
        bool result = false;
        Error error;
        Node node;
        ParseResult() {};
        ParseResult onError(Error e) {
            this->error = e;
            result = false;
            return *this;
        }
        ParseResult onSuccess(Node n) {
            this->node = n;
            result = true;
            return *this;
        }
};

class Parser {
    public:
        std::vector<Token> tokens;
        int cur;
        Token curToken {Token::Type::UNKNOWN, ""};

        Parser() { cur = 0; }
        
        Token advance();

        ParseResult factor();

        ParseResult term();

        ParseResult binOp();

        // ParseResult nextExpr();

        // ParseResult parse();
        
};

#endif