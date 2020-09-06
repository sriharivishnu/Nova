#include "Interpreter.h"
using namespace std;

/*
GENERICS
*/
Expression::Expression() {};
std::string Expression::toString() {
    return "()";
}
Result Expression::accept(Visitor& v) {
    return v.visit(this);
}
Expression::~Expression() = default;


PostfixExpression::PostfixExpression(shared_ptr<Expression> left, Token tok) : left(left), tok(tok) {}
std::string PostfixExpression::toString() {
    return "(" + left->toString() + tok.getValue() + ")";
}

PrefixExpression::PrefixExpression(Token tok, shared_ptr<Expression> right) : tok(tok), right(right) {}
std::string PrefixExpression::toString() {
    return "(" + tok.getValue() + right->toString() + ")";
}
Result PrefixExpression::accept(Visitor& v) {
    return v.visit(this);
}

/*
SPECIFICS
*/

NameExpression::NameExpression(std::string name) : name(name) {}
std::string NameExpression::toString() {
    return name;
}

NumberExpression::NumberExpression(Token t) {
    if (t.is(Token::Type::INT)) value = stoi(t.getValue());
    else if(t.is(Token::Type::DOUBLE)) value = stod(t.getValue());
}
std::string NumberExpression::toString() {
    auto* str = get_if<int>(&value);
    if (str != nullptr) return to_string(*str);
    else return to_string(get<double>(value));
}
int NumberExpression::getInt() {
    auto* val = get_if<int>(&value);
    if (val == nullptr) return (int) get<double>(value);
    return *val;
}
double NumberExpression::getDouble() {
    return get<double>(value);
}
Result NumberExpression::accept(Visitor& v) {
    return v.visit(this);
}

BinOpExpression::BinOpExpression(shared_ptr<Expression> left, Token op, shared_ptr<Expression> right) 
    : left(left), op(op), right(right) {}
std::string BinOpExpression::toString() {
    return "(" + left->toString() + op.getValue()+ right->toString() + ")";
}
Result BinOpExpression::accept(Visitor& v) {
    return v.visit(this);
}
