#ifndef INTERPRETER_CLASS
#define INTERPRETER_CLASS
#include <string>
#include <math.h>
#include <memory>
#include <variant>
#include "Context.h"
#include "Expression.h"
#include "Error.h"
#include "Token.h"
#include "Result.h"
using std::string;

class Expression;
class PrefixExpression;
class BinOpExpression;
class ComparisonExpression;
class NumberExpression;
class AssignmentExpression;
class NameExpression;
class ConditionalExpression;

class Visitor {
    public:
        Result visit(Context& context, Expression* e);
        Result visit(Context& context, PrefixExpression* e);
        Result visit(Context& context, BinOpExpression* e);
        Result visit(Context& context, ComparisonExpression* e);
        Result visit(Context& context, NumberExpression* e);
        Result visit(Context& context, AssignmentExpression* e);
        Result visit(Context& context, NameExpression* e);
        Result visit(Context& context, ConditionalExpression* e);
};
#endif