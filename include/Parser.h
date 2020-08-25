#include <vector>
#include <string>
#include <functional>

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
        std::string toString() {
            return node.toString();
        }
};

class Parser {
    public:
        std::vector<Token> tokens;
        int cur;
        Token curToken;

        Parser() { cur = 0; }
        Parser(std::vector<Token> tokens);

        Token advance();

        ParseResult parse();

        ParseResult factor();

        ParseResult term();

        ParseResult expr();

        ParseResult binOp(std::function<ParseResult ()> fun, std::vector<Token::Type> ops);


        // ParseResult parse();
        
};

#endif