#include <utility>
#include <Expression.h>


#include "Interpreter.h"
using namespace std;

/*
GENERICS
*/
Expression::Expression() = default;;
std::string Expression::toString() {
    return "(null)";
}
shared_obj Expression::accept(Context& context, Visitor& v) {
    return v.visit(context, this);
}
Token Expression::getToken() {return tok;}

Expression::~Expression() = default;


PostfixExpression::PostfixExpression(shared_ptr<Expression> left, Token tok_) : left(std::move(left)){
    tok = tok_;
}
shared_obj PostfixExpression::accept(Context& context, Visitor& v) {
    return v.visit(context, this);
}
std::string PostfixExpression::toString() {
    return "(" + left->toString() + tok.getValue() + ")";
}

PrefixExpression::PrefixExpression(Token tok_, shared_ptr<Expression> right) : right(std::move(right)) {
    tok = std::move(tok_);
}
std::string PrefixExpression::toString() {
    return "(" + tok.getValue() + right->toString() + ")";
}
shared_obj PrefixExpression::accept(Context& context, Visitor& v) {
    return v.visit(context, this);
}

/*
SPECIFICS
*/

//Identifier
NameExpression::NameExpression(std::string name, Token tok_) : name(std::move(name)) {
    tok = tok_;
}
shared_obj NameExpression::accept(Context& context, Visitor& v) {
    return v.visit(context, this);
}
std::string NameExpression::toString() {
    return name;
}

//Number
NumberExpression::NumberExpression(const Token& t) {
    if (t.is(Token::Type::INT)) value = stoi(t.getValue());
    else if(t.is(Token::Type::DOUBLE)) value = stod(t.getValue());
    tok = t;
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
shared_obj NumberExpression::accept(Context& context, Visitor& v) {
    return v.visit(context, this);
}

StringExpression::StringExpression(const Token& t) {
    tok = t;
    value = t.getValue();
}
std::string StringExpression::toString() {
    return getValue();
}
std::string StringExpression::getValue() {
    return value;
}
shared_obj StringExpression::accept(Context& context, Visitor& v) {
    return v.visit(context, this);
}

ListExpression::ListExpression(Token t, std::vector<shared_ptr<Expression>> values) : value(std::move(values)) {
    tok = t;
}
std::string ListExpression::toString() {
    std::string str("[");
    for (int i = 0 ; i < value.size(); i++) {
        if (value[i]) str += value[i]->toString();
        else str += "null";
        if (i != value.size() - 1) str += ", ";
    }
    str.push_back(']');
    return str;
}
shared_obj ListExpression::accept(Context& context, Visitor& v) {
    return v.visit(context, this);
}
vector<shared_ptr<Expression>> ListExpression::getValue() { return value;}

//Binary Operation
BinOpExpression::BinOpExpression(shared_ptr<Expression> left, Token op, shared_ptr<Expression> right) 
    : left(std::move(left)), right(std::move(right)) { tok = op; }
std::string BinOpExpression::toString() {
    return "(" + left->toString() + tok.getValue()+ right->toString() + ")";
}
shared_obj BinOpExpression::accept(Context& context, Visitor& v) {
    return v.visit(context, this);
}

ComparisonExpression::ComparisonExpression(shared_ptr<Expression> left, Token op, shared_ptr<Expression> right) 
:left(std::move(left)), right(std::move(right)) {
    tok = std::move(op);
}
std::string ComparisonExpression::toString() {
    return "(" + left->toString() + tok.getValue() + right->toString() + ")";
}

shared_obj ComparisonExpression::accept(Context& context, Visitor& v) {
    return v.visit(context, this);
}

//Assignment
AssignmentExpression::AssignmentExpression(std::string name, shared_ptr<Expression> right, Token eq) 
: name(std::move(name)), right(std::move(right)) { tok = std::move(eq); }
std::string AssignmentExpression::toString() {
    return "(" + name + tok.getValue()+ right->toString() + ")";
}
shared_obj AssignmentExpression::accept(Context& context, Visitor& v) {
    return v.visit(context, this);
}

UpdateExpression::UpdateExpression(std::string name, shared_ptr<Expression> right, Token eq)
: name(std::move(name)), right(std::move(right)) { tok = std::move(eq); }
std::string UpdateExpression::toString() {
    return "(" + name + tok.getValue()+ right->toString() + ")";
}
shared_obj UpdateExpression::accept(Context& context, Visitor& v) {
    return v.visit(context, this);
}

//Conditional
ConditionalExpression::ConditionalExpression(
            Token tok_, 
            shared_ptr<Expression> condition_, 
            shared_ptr<Expression> then_, 
            vector<shared_ptr<Expression>> elif_conditions_, 
            vector<shared_ptr<Expression>> elif_thens_, 
            shared_ptr<Expression> elseBranch_)
: condition(std::move(condition_)),
    thenBranch(std::move(then_)),
    elif_conditions(std::move(elif_conditions_)),
    elif_thens(std::move(elif_thens_)),
    elseBranch(std::move(elseBranch_))
{
    tok = std::move(tok_);
}
shared_obj ConditionalExpression::accept(Context& context, Visitor& v) {
    return v.visit(context, this);
}
std::string ConditionalExpression::toString() {
    return "(if " + condition->toString() + ", then {" + thenBranch->toString() + "} else {" + elseBranch->toString() + "})";
}

CallFunctionExpression::CallFunctionExpression(
            Token tok_, 
            vector<shared_ptr<Expression>> params
        ) : params(std::move(params)) { tok = std::move(tok_);}
shared_obj CallFunctionExpression::accept(Context& context, Visitor& v) {
    return v.visit(context, this);
};
std::string CallFunctionExpression::toString() {
    std::string call = tok.getValue() + "(";
    for (int i = 0; i < params.size(); i++) {
        call += params[i]->toString();
        if (i != params.size() - 1) call.append(",");
    }
    call.append(")");
    return call;
};

IndexExpression::IndexExpression(
            Token tok_, 
            shared_ptr<Expression> index
        ) : index(std::move(index)) { tok = std::move(tok_); }
shared_obj IndexExpression::accept(Context& context, Visitor& v) {
    return v.visit(context, this);
}
std::string IndexExpression::toString() {
    return getToken().getValue() + "[" + index->toString() + "]";
}

FuncDefExpression::FuncDefExpression(
    Token tok_, 
    std::string name, 
    vector<std::string> params, 
    shared_ptr<statement> toRun,
    bool anonymous) 
: params(std::move(params)), name(std::move(name)), body(std::move(toRun)), lambda(anonymous) { tok = tok_; }
std::string FuncDefExpression::toString() {
    std::string ans = name + "(";
    for (int i = 0; i < params.size() -1; i++) ans += params[i] + ",";
    if (!params.empty()) ans += params[params.size() - 1];
    return ans;
}
shared_obj FuncDefExpression::accept(Context& context, Visitor& v) {
    return v.visit(context, this);
}

MemberAccessExpression::MemberAccessExpression(shared_ptr<Expression> obj_, const Token &name_, const vector<shared_ptr<Expression>>& args_)
: obj(std::move(obj_)), name(name_.getValue()), args(args_) {}

std::string MemberAccessExpression::toString() {
    std::string res = name + "(";
    for (int i = 0; i < args.size() - 1; i++) {
        res += args[i]->toString() + ", ";
    }
    res += args[args.size() - 1]->toString();
    return res;
}

shared_obj MemberAccessExpression::accept(Context &context, Visitor &v) {
    return v.visit(context, this);
}
