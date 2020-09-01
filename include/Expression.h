#ifndef EXPRESSION_CLASS
#define EXPRESSION_CLASS
#include <string>
#include <memory>
#include "Token.h"
#include <variant>
using namespace std;
class Statement {

};

class Expression {
    public:
        Expression() {};
        virtual std::string toString() {
            return "()";
        };
        virtual ~Expression() = default;
};
class PostfixExpression : public Expression {
    public:
        PostfixExpression(shared_ptr<Expression> left, Token tok) : left(left), tok(tok) {}
        std::string toString() override {
            return "(" + left->toString() + tok.getValue() + ")";
        }
    private:
        shared_ptr<Expression> left;
        Token tok;
};

class PrefixExpression : public Expression {
    public:
        PrefixExpression(Token tok, shared_ptr<Expression> right) : tok(tok), right(right) {}
        std::string toString() override {
            return "(" + tok.getValue() + right->toString() + ")";
        }
    private:
        Token tok;
        shared_ptr<Expression> right;
};

class NameExpression : public Expression {
    public:
        NameExpression(std::string name) : name(name) {}
        std::string toString() override {
            return name;
        }
    private:
        std::string name;
};

class NumberExpression : public Expression {
    public:
        NumberExpression(Token t) {
            if (t.is(Token::Type::INT)) value = stoi(t.getValue());
            else if(t.is(Token::Type::DOUBLE)) value = stod(t.getValue());
        }
        std::string toString() override {
            auto* str = get_if<int>(&value);
            if (str != nullptr) return to_string(*str);
            else return to_string(get<double>(value));
        }
    private:
        std::variant<int, double> value;
};

class OperatorExpression : public Expression {
    public:
        OperatorExpression(shared_ptr<Expression> left, Token op, shared_ptr<Expression> right) 
            : left(left), op(op), right(right) {}
        std::string toString() override {
            return "(" + left->toString() + op.getValue()+ right->toString() + ")";
        }
    private:
        shared_ptr<Expression> left;
        Token op;
        shared_ptr<Expression> right;
};
#endif