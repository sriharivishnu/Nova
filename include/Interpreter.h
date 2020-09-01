#ifndef INTERPRETER_CLASS
#define INTERPRETER_CLASS
#include "Expression.h"
#include "Types.h"
#include <memory>
class Interpreter {
    public:
        Object visit(std::shared_ptr<Expression> n);

};
#endif