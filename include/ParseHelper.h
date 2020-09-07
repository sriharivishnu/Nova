#ifndef PARSER_HELPER
#define PARSER_HELPER
#include "Expression.h"
#include "Parser.h"
#include "Token.h"
#include <memory>
#include <vector>
#include <unordered_map>
using namespace std;

enum Precedence {
    ASSIGNMENT = 1,
    CONDITION = 2,
    SUM = 3, 
    PRODUCT = 4,
    EXPONENT = 5, 
    PREFIX = 6,
    POSTFIX = 7,
    CALL = 8
};
class Parser;
class PrefixParser {
    public:
        virtual shared_ptr<Expression> parse(Parser& parser, Token token);
        virtual ~PrefixParser() = default;
};
class InfixParser {
    public:
        virtual shared_ptr<Expression> parse(Parser& parser, shared_ptr<Expression> left, Token token);
        virtual int getPrecedence();
        virtual ~InfixParser() = default;
};

class NameParser : public PrefixParser {
    public:
        shared_ptr<Expression> parse(Parser& parser, Token token) override;
};

class NumberParser : public PrefixParser {
    public:
        shared_ptr<Expression> parse(Parser& parser, Token token) override;
};

class PrefixOperatorParser : public PrefixParser {
    public:
        PrefixOperatorParser(int precedence);
        shared_ptr<Expression> parse(Parser& parser, Token token);
        int getPrecedence();
    private:
        int precedence;
};

class PostfixOperatorParser : public InfixParser {
    public:
        PostfixOperatorParser(int precedence);
        int getPrecedence() override;
    private:
        int precedence = 0;
};

class BinaryOperatorParser : public InfixParser {
    public:
        BinaryOperatorParser(int precedence, bool isRight);
        shared_ptr<Expression> parse(Parser& parser, shared_ptr<Expression> left, Token tok) override;
        int getPrecedence() override;
    private:
        int precedence = 0;
        bool isRight = false;
};

class ComparisonParser : public InfixParser {
    public:
        ComparisonParser();
        shared_ptr<Expression> parse(Parser& parser, shared_ptr<Expression> left, Token tok) override;
        int getPrecedence() override;
};

class AssignmentParser : public PrefixParser {
    public:
        AssignmentParser();
        shared_ptr<Expression> parse(Parser& parser, Token token) override;        
};

class UpdateOrAssignParser : public InfixParser {
    public:
        UpdateOrAssignParser();
        shared_ptr<Expression> parse(Parser& parser, shared_ptr<Expression> left, Token tok) override;
        int getPrecedence() override;
};

class ConditionalParser : public PrefixParser {
    public:
        ConditionalParser();
        shared_ptr<Expression> parse(Parser& parser, Token tok) override;
};

class GroupParser : public PrefixParser {
    public:
        shared_ptr<Expression> parse(Parser& parser, Token token) override;
};

#endif