#ifndef INTERPRETER_CLASS
#define INTERPRETER_CLASS
#include <string>
#include <math.h>
#include <memory>
#include <variant>
#include "Expression.h"
#include "Types.h"
#include "Error.h"
#include "Token.h"
#include "Result.h"
using std::string;

class Interpreter {
    // public:
    //     Object visit(std::shared_ptr<Expression> n);
};
class Expression;
class PrefixExpression;
class BinOpExpression;
class NumberExpression;
class Visitor {
    public:
        Result visit(Expression* e);
        Result visit(PrefixExpression* e);
        Result visit(BinOpExpression* e);
        Result visit(NumberExpression* e);
    private:
};
#endif