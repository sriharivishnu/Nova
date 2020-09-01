#include "Interpreter.h"
#include "Error.h"
#include "Expression.h"
// Object Interpreter::visit(std::shared_ptr<Expression> n) {
    // switch (n->op)
    // {
    // case Operation::LITERAL:
    //     printf("WE GOT A LITERAL\n");
    //     break;
    // case Operation::BINARY:
    //     printf("WE GOT A BINARY\n");
    //     visit(n->children[0]);
    //     visit(n->children[1]);
    //     break;
    // case Operation::UNARY:
    //     printf("WE GOT A UNARY\n");
    //     visit(n->children[0]);
    //     break;
    // default:
    //     throw UndefinedOperationException(n->tok.getValue());
    //     break;
    // };
    // return Object(types::INT);
// }