#ifndef EXPRESSION_CLASS
#define EXPRESSION_CLASS
#include <string>
#include <memory>
#include <variant>
#include "Interpreter.h"
#include "Token.h"
using namespace std;
class Visitor;
struct Result;
class Expression {
    public:
        Expression();
        virtual std::string toString();
        virtual Result accept(Visitor& v);
        virtual ~Expression();
};
class PostfixExpression : public Expression {
    public:
        PostfixExpression(shared_ptr<Expression> left, Token tok);
        std::string toString() override;
    private:
        shared_ptr<Expression> left;
        Token tok;
};

class PrefixExpression : public Expression {
    public:
        PrefixExpression(Token tok, shared_ptr<Expression> right);
        std::string toString() override;
        Result accept(Visitor& v) override;
    private:
        Token tok;
        shared_ptr<Expression> right;
};

class NameExpression : public Expression {
    public:
        NameExpression(std::string name);
        std::string toString() override;
    private:
        std::string name;
};

class NumberExpression : public Expression {
    public:
        NumberExpression(Token t);
        std::string toString() override;
        int getInt();
        double getDouble();
        Result accept(Visitor& v) override;
    private:
        std::variant<int, double> value;
};

class OperatorExpression : public Expression {
    public:
        OperatorExpression(shared_ptr<Expression> left, Token op, shared_ptr<Expression> right);
        std::string toString() override;
        Result accept(Visitor& v) override;
        Token op;
        shared_ptr<Expression> left;
        shared_ptr<Expression> right;
};
#endif