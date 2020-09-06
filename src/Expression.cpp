#include "Interpreter.h"
using namespace std;

/*
GENERICS
*/
Expression::Expression() {};
std::string Expression::toString() {
    return "(null)";
}
Result Expression::accept(Context& context, Visitor& v) {
    return v.visit(context, this);
}
Token Expression::getToken() {return tok;}

Expression::~Expression() = default;


PostfixExpression::PostfixExpression(shared_ptr<Expression> left, Token tok_) : left(left){
    tok = tok_;
}
std::string PostfixExpression::toString() {
    return "(" + left->toString() + tok.getValue() + ")";
}

PrefixExpression::PrefixExpression(Token tok_, shared_ptr<Expression> right) : right(right) {
    tok = tok_;
}
std::string PrefixExpression::toString() {
    return "(" + tok.getValue() + right->toString() + ")";
}
Result PrefixExpression::accept(Context& context, Visitor& v) {
    return v.visit(context, this);
}

/*
SPECIFICS
*/

//Identifier
NameExpression::NameExpression(std::string name, Token tok_) : name(name) {
    tok = tok_;
}
Result NameExpression::accept(Context& context, Visitor& v) {
    return v.visit(context, this);
}
std::string NameExpression::toString() {
    return name;
}

//Number
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
Result NumberExpression::accept(Context& context, Visitor& v) {
    return v.visit(context, this);
}

//Binary Operation
BinOpExpression::BinOpExpression(shared_ptr<Expression> left, Token op, shared_ptr<Expression> right) 
    : left(left), right(right) { tok = op; }
std::string BinOpExpression::toString() {
    return "(" + left->toString() + tok.getValue()+ right->toString() + ")";
}
Result BinOpExpression::accept(Context& context, Visitor& v) {
    return v.visit(context, this);
}

//Assignment
AssignmentExpression::AssignmentExpression(std::string name, shared_ptr<Expression> right, Token eq) 
: name(name), right(right) { tok = eq; }
std::string AssignmentExpression::toString() {
    return "(" + name + tok.getValue()+ right->toString() + ")";
}
Result AssignmentExpression::accept(Context& context, Visitor& v) {
    return v.visit(context, this);
}