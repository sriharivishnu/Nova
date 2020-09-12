#include "Interpreter.h"
#include "optional"
#include "Statement.h"
Result Visitor::visit(Context& context, Expression* e) {
    throw UndefinedOperationException(e->getToken().startPos, "Visited unknown expression");
}

Result Visitor::visit(Context& context, PrefixExpression* e) {
    if (e->getToken().isOneOf(Token::Type::INC, Token::Type::DEC)) {
        std::string name = e->right->getToken().getValue();
        std::optional<type> value = context.symbols->get(name);
        if (!value) throw UndefinedVariable(make_shared<Context>(context), e->right->getToken().getValue(), e->getToken().startPos);
        int val = std::get<int>(*value);
        if (e->getToken().is(Token::Type::INC)) val++;
        else if (e->getToken().is(Token::Type::DEC)) val--;
        context.symbols->set(name, val);
        return Result(val);
    }
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

Result Visitor::visit(Context& context, PostfixExpression* e) {
    if (e->getToken().isOneOf(Token::Type::INC, Token::Type::DEC)) {
        std::string name = e->left->getToken().getValue();
        std::optional<type> value = context.symbols->get(name);
        if (!value) throw UndefinedVariable(make_shared<Context>(context), e->left->getToken().getValue(), e->left->getToken().startPos);
        int val = std::get<int>(*value);
        if (e->getToken().is(Token::Type::INC)) context.symbols->set(name, val + 1);
        else if (e->getToken().is(Token::Type::DEC)) context.symbols->set(name, val - 1);;
        return Result(val);
    }
    throw UndefinedOperationException(e->getToken().startPos, "Visited unknown unary operation: " + e->getToken().getValue());
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
                throw DivisionByZero(make_shared<Context>(context), e->right->getToken().startPos);
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
    throw UndefinedVariable(make_shared<Context>(context), e->name, e->getToken().startPos);
}

Result Visitor::visit(Context& context, ConditionalExpression* e) {
    if (e->condition->accept(context, *this)) {
        return e->thenBranch->accept(context, *this);
    } 
    for (int i = 0; i< e->elif_conditions.size(); i++) {
        if (e->elif_conditions[i]->accept(context, *this)) {
            return e->elif_thens[i]->accept(context, *this);
        }
    }
    return e->elseBranch->accept(context, *this);
}

Result Visitor::visit(Context& parent, CallFunctionExpression* e) {
    Visitor v;
    std::shared_ptr<function_statement> decl = parent.functions->get(e->getToken().getValue());
    if (!decl) throw UndefinedVariable(make_shared<Context>(parent), e->getToken().getValue(), e->getToken().startPos);
    if (e->params.size() > decl->params.size()) {
        throw Error(e->getToken().startPos, "Function Call Exception", "Too many Params for " + decl->name + ": expected, " + std::to_string(decl->params.size()) + " params but called with " + std::to_string(e->params.size()));
    }
    else if (e->params.size() < decl->params.size()) {
        throw Error(e->getToken().startPos, "Function Call Exception", "Too few Params for " + decl->name + ": expected, " + std::to_string(decl->params.size()) + " params but called with " + std::to_string(e->params.size()));
    }
    std::shared_ptr<SymbolTable> symbols = make_shared<SymbolTable>(parent.symbols);
    for (int i = 0; i < decl->params.size(); i++) {
        symbols->set(decl->params[i], e->params[i]->accept(parent, v));
    }
    Context context(decl->name, std::make_shared<Context>(parent), decl->pos, symbols, parent.functions);
    std::optional res = decl->toRun->execute(context);
    if (res) return *res;
    else return Result(0);
}
