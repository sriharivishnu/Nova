#ifndef EXPRESSION_CLASS
#define EXPRESSION_CLASS
#include <string>
#include <memory>
#include <variant>
#include <vector>
#include "Context.h"
#include "Statement.h"
#include "Interpreter.h"
#include "Token.h"
#include "types.h"
using namespace std;
class Visitor;
struct Result;
struct Context;
class statement;
class Expression {
    public:
        Expression();
        virtual std::string toString();
        virtual shared_obj accept(Context& context, Visitor& v);
        virtual Token getToken();
        virtual ~Expression();
    protected:
        Token tok;
};
class PostfixExpression : public Expression {
    public:
        PostfixExpression(shared_ptr<Expression> left, Token tok);
        shared_obj accept(Context& context, Visitor& v) override;
        std::string toString() override;
        shared_ptr<Expression> left;
};

class PrefixExpression : public Expression {
    public:
        PrefixExpression(Token tok, shared_ptr<Expression> right);
        std::string toString() override;
        shared_obj accept(Context& context, Visitor& v) override;
        shared_ptr<Expression> right;
};

class NameExpression : public Expression {
    public:
        NameExpression(std::string name, Token tok);
        std::string toString() override;
        shared_obj accept(Context& context, Visitor& v) override;
        std::string name;
};

class NumberExpression : public Expression {
    public:
        NumberExpression(const Token& t);
        std::string toString() override;
        int getInt();
        double getDouble();
        shared_obj accept(Context& context, Visitor& v) override;
    private:
        std::variant<int, double> value;
};

class StringExpression : public Expression {
    public:
        StringExpression(const Token& t);
        std::string toString() override;
        shared_obj accept(Context& context, Visitor& v) override;
        std::string getValue();
    private:
        std::string value;
};

class BinOpExpression : public Expression {
    public:
        BinOpExpression(shared_ptr<Expression> left, Token op, shared_ptr<Expression> right);
        std::string toString() override;
        shared_obj accept(Context& context, Visitor& v) override;
        shared_ptr<Expression> left;
        shared_ptr<Expression> right;
};

class ComparisonExpression : public Expression {
    public:
        ComparisonExpression(shared_ptr<Expression> left, Token op, shared_ptr<Expression> right);
        std::string toString() override;
        shared_obj accept(Context& context, Visitor& v) override;
        shared_ptr<Expression> left;
        shared_ptr<Expression> right;
};

class AssignmentExpression : public Expression {
    public:
        AssignmentExpression(std::string name, shared_ptr<Expression> right, Token eq);
        shared_obj accept(Context& context, Visitor& v) override;
        std::string toString() override;
        std::string name;
        shared_ptr<Expression> right;
};

class UpdateExpression : public Expression {
    public:
        UpdateExpression(std::string name, shared_ptr<Expression> right, Token eq);
        shared_obj accept(Context& context, Visitor& v) override;
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
        shared_obj accept(Context& context, Visitor& v) override;
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
        shared_obj accept(Context& context, Visitor& v) override;
        std::string toString() override;
        vector<shared_ptr<Expression>> params;
};

class IndexExpression : public Expression {
    public:
        IndexExpression(
            Token tok_, 
            shared_ptr<Expression> index
        );
        shared_obj accept(Context& context, Visitor& v) override;
        std::string toString() override;
        shared_ptr<Expression> index;
};

class ListExpression : public Expression {
    public:
        ListExpression(Token t, vector<shared_ptr<Expression>> values);
        std::string toString() override;
        shared_obj accept(Context& context, Visitor& v) override;
        vector<shared_ptr<Expression>> getValue();
    private:
        vector<shared_ptr<Expression>> value;
};

class FuncDefExpression : public Expression {
    public:
        FuncDefExpression(Token t, std::string name, vector<std::string> params, shared_ptr<statement> toRun, bool anonymous);
        std::string toString() override;
        shared_obj accept(Context& context, Visitor& v) override;
        vector<std::string> params;
        std::string name;
        shared_ptr<statement> body;
        bool lambda = false;
};
#endif