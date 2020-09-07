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
        case Token::Type::NOT:
            if (rightSide.isType<int>()) {
                return Result(rightSide.getValue<int>() == 0);
            }
            throw TypeException(e->getToken().startPos, "Expected 'int' type");
        default:
            throw UndefinedOperationException(e->getToken().startPos, "Visited unknown unary expression: " + e->getToken().getValue());
    }
    return rightSide;
}
Result Visitor::visit(Context& context, BinOpExpression* e) {
    Result leftRes = e->left->accept(context, *this);
    Result rightRes = e->right->accept(context, *this); 
    int first = leftRes.getTypeOrThrow<int>(e->left->getToken().startPos);
    int second = rightRes.getTypeOrThrow<int>(e->right->getToken().startPos);
    switch(e->getToken().type) {
        case Token::Type::PLUS:
            return Result(first + second);
        case Token::Type::MINUS:
            return Result(first - second);
        case Token::Type::MULT:
            return Result(first * second);
        case Token::Type::DIV:
            if (second == 0) {
                throw DivisionByZero(context, e->right->getToken().startPos);
            }
            return Result(first / second);
        case Token::Type::CAROT:
            return Result((int) pow(first, second));
        default:
            throw UndefinedOperationException(e->getToken().startPos, e->getToken().getValue());
    }
    return Result(-1);
}

Result Visitor::visit(Context& context, ComparisonExpression* e) {
    Result leftRes = e->left->accept(context, *this);
    Result rightRes = e->right->accept(context, *this);
    int first = leftRes.getTypeOrThrow<int>(e->left->getToken().startPos);
    int second = rightRes.getTypeOrThrow<int>(e->right->getToken().startPos);
    switch(e->getToken().type) {
        case Token::Type::NE:
            return Result(first != second);
        case Token::Type::EE:
            return Result(first == second);
        case Token::Type::GE:
            return Result(first >= second);
        case Token::Type::LE:
            return Result(first <= second);
        case Token::Type::GT:
            return Result(first > second);
        case Token::Type::LT:
            return Result(first < second);
        default:
            throw UndefinedOperationException(e->getToken().startPos, e->getToken().getValue());
    }
}

Result Visitor::visit(Context& context, NumberExpression* e) {
    if (e->getToken().is(Token::Type::INT)) return Result(e->getInt());
    else if (e->getToken().is(Token::Type::DOUBLE)) return Result(e->getDouble());
    throw Error(e->getToken().startPos, "Unknown Error: Not integer or double type" + e->getToken().getValue());
}

Result Visitor::visit(Context& context, AssignmentExpression* e) {
    Result res = e->right->accept(context, *this);
    context.symbols->set(e->name, res.getResult());
    return res;
}

Result Visitor::visit(Context& context, NameExpression* e) {
    std::optional<type> value = context.symbols->get(e->name);
    if (value) {
        return Result(*value);
    }
    throw UndefinedVariable(e->name, e->getToken().startPos);
}

