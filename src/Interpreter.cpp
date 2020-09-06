#include "Interpreter.h"

Result Visitor::visit(Expression* e) {
    throw UndefinedOperationException(Position(0,0,0), "Visited unknown expression");
}
Result Visitor::visit(PrefixExpression* e) {
    Result rightSide = e->right->accept(*this);
    switch(e->tok.type) {
        case Token::Type::PLUS:
            return rightSide;
        case Token::Type::MINUS:
            if (rightSide.isType<int>()) {
                return Result(-1 * rightSide.getValue<int>());
            }
            else if (rightSide.isType<double>()) {
                return Result(-1 * rightSide.getValue<double>());
            }
            throw TypeException(e->tok.startPos, "Expected 'int' or 'double' type");
    }
    return rightSide;
}
Result Visitor::visit(BinOpExpression* e) {
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

