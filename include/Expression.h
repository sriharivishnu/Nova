#ifndef EXPRESSION_CLASS
#define EXPRESSION_CLASS
#include <string>
#include <memory>
#include <variant>
#include <vector>
#include "Context.h"
#include "Interpreter.h"
#include "Token.h"
using namespace std;
class Visitor;
struct Result;
struct Context;
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
        Result accept(Context& context, Visitor& v) override;
        std::string toString() override;
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

class UpdateExpression : public Expression {
    public:
        UpdateExpression(std::string name, shared_ptr<Expression> right, Token eq);
        Result accept(Context& context, Visitor& v) override;
        std::string toString() override;
        std::string name;
        shared_ptr<Expression> right;
};

class ConditionalExpression : public Expression {
    public:
        ConditionalExpression(
            Token tok_, 
            shared_ptr<Expression> condition, 
            shared_ptr<Expression> then, 
            vector<shared_ptr<Expression>> elif_conditions, 
            vector<shared_ptr<Expression>> elif_thens, 
            shared_ptr<Expression> elseBranch);
        Result accept(Context& context, Visitor& v) override;
        std::string toString() override;
        shared_ptr<Expression> condition;
        shared_ptr<Expression> thenBranch;
        vector<shared_ptr<Expression>> elif_conditions; 
        vector<shared_ptr<Expression>> elif_thens;
        shared_ptr<Expression> elseBranch;
};

class CallFunctionExpression : public Expression {
    public:
        CallFunctionExpression(
            Token tok_, 
            vector<shared_ptr<Expression>> params
        );
        Result accept(Context& context, Visitor& v) override;
        std::string toString() override;
        vector<shared_ptr<Expression>> params;
};
#endif