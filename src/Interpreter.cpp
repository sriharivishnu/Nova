#include "Interpreter.h"
#include "Error.h"

Result Visitor::visit(Expression* e) {
    throw UndefinedOperationException(Position(0,0,0), "Visited unknown expression");
}
Result Visitor::visit(OperatorExpression* e) {
    Result leftRes = e->left.get()->accept(*this);
    Result rightRes = e->right.get()->accept(*this);
    switch(e->op.type) {
        case Token::Type::PLUS:
            return Result(leftRes.getTypeOrThrow<int>(e->op.startPos) + rightRes.getTypeOrThrow<int>(e->op.startPos));
        case Token::Type::MINUS:
            return Result(leftRes.getTypeOrThrow<int>(e->op.startPos) - rightRes.getTypeOrThrow<int>(e->op.startPos));
        case Token::Type::MULT:
            return Result(leftRes.getTypeOrThrow<int>(e->op.startPos) * rightRes.getTypeOrThrow<int>(e->op.startPos));
        case Token::Type::DIV:
            return Result(leftRes.getTypeOrThrow<int>(e->op.startPos) / rightRes.getTypeOrThrow<int>(e->op.startPos));
        case Token::Type::CAROT:
            return Result((int) pow(leftRes.getTypeOrThrow<int>(e->op.startPos), rightRes.getTypeOrThrow<int>(e->op.startPos)));
        default:
            throw UndefinedOperationException(e->op.startPos, e->op.getValue());
    }
    return Result(-1);
}

Result Visitor::visit(NumberExpression* e) {
    // return e->getInt();
    return Result(e->getInt());
}

