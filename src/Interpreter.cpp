#include "Interpreter.h"

Result Visitor::visit(Context& context, Expression* e) {
    throw UndefinedOperationException(Position(0,0,0), "Visited unknown expression");
}
Result Visitor::visit(Context& context, PrefixExpression* e) {
    Result rightSide = e->right->accept(context, *this);
    switch(e->getToken().type) {
        case Token::Type::PLUS:
            return rightSide;
        case Token::Type::MINUS:
            if (rightSide.isType<int>()) {
                return Result(-1 * rightSide.getValue<int>());
            }
            else if (rightSide.isType<double>()) {
                return Result(-1 * rightSide.getValue<double>());
            }
            throw TypeException(e->getToken().startPos, "Expected 'int' or 'double' type");
        default:
            throw UndefinedOperationException(e->getToken().startPos, "Visited unknown unary expression: " + e->getToken().getValue());
    }
    return rightSide;
}
Result Visitor::visit(Context& context, BinOpExpression* e) {
    Result leftRes = e->left.get()->accept(context, *this);
    Result rightRes = e->right.get()->accept(context, *this); 
    int first = leftRes.getTypeOrThrow<int>(e->getToken().startPos);
    int second = rightRes.getTypeOrThrow<int>(e->getToken().startPos);
    switch(e->getToken().type) {
        case Token::Type::PLUS:
            return Result(first + second);
        case Token::Type::MINUS:
            return Result(first - second);
        case Token::Type::MULT:
            return Result(first * second);
        case Token::Type::DIV:
            if (second == 0) {
                throw DivisionByZero(context, e->getToken().startPos);
            }
            return Result(first / second);
        case Token::Type::CAROT:
            return Result((int) pow(first, second));
        default:
            throw UndefinedOperationException(e->getToken().startPos, e->getToken().getValue());
    }
    return Result(-1);
}

Result Visitor::visit(Context& context, NumberExpression* e) {
    // return e->getInt();
    return Result(e->getInt());
}

Result Visitor::visit(Context& context, AssignmentExpression* e) {
    return e->right->accept(context, *this);
}

