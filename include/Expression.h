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
        virtual Result accept(Context& context, Visitor& v);
        virtual Token getToken();
        virtual ~Expression();
    protected:
        Token tok;
};
class PostfixExpression : public Expression {
    public:
        PostfixExpression(shared_ptr<Expression> left, Token tok);
        std::string toString() override;
    private:
        shared_ptr<Expression> left;
};

class PrefixExpression : public Expression {
    public:
        PrefixExpression(Token tok, shared_ptr<Expression> right);
        std::string toString() override;
        Result accept(Context& context, Visitor& v) override;
        shared_ptr<Expression> right;
};

class NameExpression : public Expression {
    public:
        NameExpression(std::string name, Token tok);
        std::string toString() override;
        Result accept(Context& context, Visitor& v) override;
        std::string name;
};

class NumberExpression : public Expression {
    public:
        NumberExpression(Token t);
        std::string toString() override;
        int getInt();
        double getDouble();
        Result accept(Context& context, Visitor& v) override;
    private:
        std::variant<int, double> value;
};

class BinOpExpression : public Expression {
    public:
        BinOpExpression(shared_ptr<Expression> left, Token op, shared_ptr<Expression> right);
        std::string toString() override;
        Result accept(Context& context, Visitor& v) override;
        shared_ptr<Expression> left;
        shared_ptr<Expression> right;
};

class ComparisonExpression : public Expression {
    public:
        ComparisonExpression(shared_ptr<Expression> left, Token op, shared_ptr<Expression> right);
        std::string toString() override;
        Result accept(Context& context, Visitor& v) override;
        shared_ptr<Expression> left;
        shared_ptr<Expression> right;
};

class AssignmentExpression : public Expression {
    public:
        AssignmentExpression(std::string name, shared_ptr<Expression> right, Token eq);
        Result accept(Context& context, Visitor& v) override;
        std::string toString() override;
        std::string name;
        shared_ptr<Expression> right;
};
#endif