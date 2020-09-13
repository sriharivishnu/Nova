#ifndef INTERPRETER_CLASS
#define INTERPRETER_CLASS
#include <string>
#include <math.h>
#include <memory>
#include <variant>
#include "Expression.h"
#include "Error.h"
#include "Token.h"
#include "Result.h"
using std::string;
using type = std::variant<std::string, int, double>;

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

struct Context;

class Expression;
class PrefixExpression;
class PostfixExpression;
class BinOpExpression;
class ComparisonExpression;
class NumberExpression;
class StringExpression;
class AssignmentExpression;
class UpdateExpression;
class NameExpression;
class ConditionalExpression;
class CallFunctionExpression;

class Visitor {
    public:
        Result visit(Context& context, Expression* e);
        Result visit(Context& context, PrefixExpression* e);
        Result visit(Context& context, PostfixExpression* e);
        Result visit(Context& context, BinOpExpression* e);
        Result visit(Context& context, ComparisonExpression* e);
        Result visit(Context& context, NumberExpression* e);
        Result visit(Context& context, StringExpression* e);
        Result visit(Context& context, AssignmentExpression* e);
        Result visit(Context& context, UpdateExpression* e);
        Result visit(Context& context, NameExpression* e);
        Result visit(Context& context, ConditionalExpression* e);
        Result visit(Context& context, CallFunctionExpression* e);
};
#endif