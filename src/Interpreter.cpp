#include "Interpreter.h"

void Interpreter::visit(Node n) {
    switch (n.op)
    {
    case Operation::LITERAL:
        printf("WE GOT A LITERAL\n");
        break;
    case Operation::BINARY:
        printf("WE GOT A BINARY\n");
        visit(n.children[0]);
        visit(n.children[1]);
        break;
    case Operation::UNARY:
        printf("WE GOT A UNARY\n");
        visit(n.children[0]);
        break;
    default:
        break;
    }
}