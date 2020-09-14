#ifndef INTERPRETER_CLASS
#define INTERPRETER_CLASS
#include <string>
#include <math.h>
#include <memory>
#include <variant>
#include "helper.h"
#include "Expression.h"
#include "Result.h"
#include "types.h"
using std::string;
using shared_obj = std::shared_ptr<object>;
 
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
        shared_obj visit(Context& context, Expression* e);
        shared_obj visit(Context& context, PrefixExpression* e);
        shared_obj visit(Context& context, PostfixExpression* e);
        shared_obj visit(Context& context, BinOpExpression* e);
        shared_obj visit(Context& context, ComparisonExpression* e);
        shared_obj visit(Context& context, NumberExpression* e);
        shared_obj visit(Context& context, StringExpression* e);
        shared_obj visit(Context& context, AssignmentExpression* e);
        shared_obj visit(Context& context, UpdateExpression* e);
        shared_obj visit(Context& context, NameExpression* e);
        shared_obj visit(Context& context, ConditionalExpression* e);
        shared_obj visit(Context& context, CallFunctionExpression* e);
};
#endif