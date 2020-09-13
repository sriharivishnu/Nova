#ifndef PARSER_CLASS
#define PARSER_CLASS

#include <vector>
#include <string>
#include <functional>
#include <memory>
#include <unordered_map>

#include "Token.h"
#include "Expression.h"
#include "Statement.h"
#include "ParseHelper.h"
#include "Error.h"
using std::vector;
class PrefixParser;
class InfixParser;
class Parser {
    public:
        Parser(std::vector<Token> tokens);
        void addType(Token::Type type, shared_ptr<PrefixParser> prefix);
        void addType(Token::Type type, shared_ptr<InfixParser> prefix);
        Token consume();
        Token consume(Token::Type expected, std::string expectedStr = std::string(""));

        shared_ptr<Expression> parseExpression(int precedence);
        shared_ptr<Expression> parseExpression();

        shared_ptr<statement> parseStatement();

        shared_ptr<statement> parse();

        bool match(Token::Type expected);
        Token lookAhead(int distance);
        int getPrecedence();
    private:
        int cur = 0;
        vector<Token> tokens;
        vector<Token> mRead;
        unordered_map<Token::Type, std::shared_ptr<PrefixParser>> mPrefixParsables;
        unordered_map<Token::Type, std::shared_ptr<InfixParser>> mInfixParsables;
};

#endif