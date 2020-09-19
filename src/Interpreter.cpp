#include "Interpreter.h"
#include "optional"
#include "Statement.h"
#include "Error.h"
#include "Token.h"
shared_obj Visitor::visit(Context& context, Expression* e) {
    throw UndefinedOperationException(e->getToken().startPos, "Visited unknown expression");
}

shared_obj Visitor::visit(Context& context, PrefixExpression* e) {
    if (e->getToken().isOneOf(Token::Type::INC, Token::Type::DEC)) {
        std::string name = e->right->getToken().getValue();
        std::optional<shared_obj> value = context.symbols->get(name);
        if (!value) throw UndefinedVariable(make_shared<Context>(context), e->right->getToken().getValue(), e->getToken().startPos);
        shared_obj val = value->get()->inc();
        if (!context.symbols->update(name, val)) throw UndefinedVariable(make_shared<Context>(context), e->right->getToken().getValue(), e->right->getToken().startPos);
        return val;
    }
    shared_obj rightSide = e->right->accept(context, *this);
    switch(e->getToken().type) {
        case Token::Type::PLUS:
            return rightSide->prePlus();
        case Token::Type::MINUS: {
            return rightSide->preMinus();
        }
        case Token::Type::NOT: {
            return rightSide->preNot();
        }
        default:
            throw UndefinedOperationException(e->getToken().startPos, "Visited unknown unary expression: " + e->getToken().getValue());
    }
    return rightSide;
}

shared_obj Visitor::visit(Context& context, PostfixExpression* e) {
    if (e->getToken().isOneOf(Token::Type::INC, Token::Type::DEC)) {
        std::string name = e->left->getToken().getValue();
        std::optional<shared_obj> value = context.symbols->get(name);
        if (!value) throw UndefinedVariable(make_shared<Context>(context), e->left->getToken().getValue(), e->left->getToken().startPos);
        shared_obj val = 0;
        if (e->getToken().is(Token::Type::INC)) val = value->get()->inc();
        else if (e->getToken().is(Token::Type::DEC)) val = value->get()->dec();
        else throw UndefinedOperationException(e->getToken().startPos, e->getToken().getValue(), value->get()->value.getStringType());

        bool success = context.symbols->update(name, val);
        if (!success) throw UndefinedVariable(make_shared<Context>(context), e->left->getToken().getValue(), e->left->getToken().startPos);
        return *value;
    }
    throw UndefinedOperationException(e->getToken().startPos, "Visited unknown unary operation: " + e->getToken().getValue());
}

shared_obj Visitor::visit(Context& context, BinOpExpression* e) {
    shared_obj left = e->left->accept(context, *this);
    shared_obj right = e->right->accept(context, *this);
    switch(e->getToken().type) {
        case Token::Type::PLUS:
            return left->addBy(right);
        case Token::Type::MINUS:
            return left->subBy(right);
        case Token::Type::MULT:
            return left->multBy(right);
        case Token::Type::DIV:
            return left->divBy(right);
        case Token::Type::POWER:
            return left->powBy(right);
        case Token::Type::BAND:
            return left->band(right);
        case Token::Type::BOR:
            return left->bor(right);
        case Token::Type::XOR:
            return left->bxor(right);
        default:
            throw UndefinedOperationException(e->getToken().startPos, e->getToken().getValue());
    }
}

shared_obj Visitor::visit(Context& context, ComparisonExpression* e) {
    shared_obj left = e->left->accept(context, *this);
    shared_obj right = e->right->accept(context, *this);
    switch(e->getToken().type) {
        case Token::Type::NE:
            return left->ne(right);
        case Token::Type::EE:
            return left->ee(right);
        case Token::Type::GE:
            return left->gte(right);
        case Token::Type::LE:
            return left->lte(right);
        case Token::Type::GT:
            return left->gt(right);
        case Token::Type::LT:
            return left->lt(right);
        case Token::Type::AND:
            return std::make_shared<integer_type>(left->toBool()->value && right->toBool()->value);
        case Token::Type::OR:
            return std::make_shared<integer_type>(left->toBool()->value || right->toBool()->value);
        default:
            throw UndefinedOperationException(e->getToken().startPos, e->getToken().getValue());
    }
}

shared_obj Visitor::visit(Context& context, NumberExpression* e) {
    if (e->getToken().is(Token::Type::INT)) return std::make_shared<integer_type>(e->getInt());
    else if (e->getToken().is(Token::Type::DOUBLE)) return std::make_shared<double_type>(e->getDouble());
    throw Error(e->getToken().startPos, "Unknown Error: Not integer or double type" + e->getToken().getValue());
}

shared_obj Visitor::visit(Context& context, StringExpression* e) {
    return std::make_shared<string_type>(e->getValue());
}
shared_obj Visitor::visit(Context& context, ListExpression* e) {
    vector<shared_obj> items;
    for (int i = 0; i < e->getValue().size(); i++) {
        items.push_back(e->getValue()[i]->accept(context, *this));
    }
    return std::make_shared<list_type>(items);
}

shared_obj Visitor::visit(Context& context, AssignmentExpression* e) {
    shared_obj res = e->right->accept(context, *this);
    context.symbols->set(e->name, res);
    return res;
}
shared_obj Visitor::visit(Context& context, UpdateExpression* e) {
    shared_obj res = e->right->accept(context, *this);
    if (context.symbols->update(e->name, res)) return res;
    throw UndefinedVariable(make_shared<Context>(context), e->name, e->getToken().startPos);
}

shared_obj Visitor::visit(Context& context, NameExpression* e) {
    std::optional<shared_obj> value = context.symbols->get(e->name);
    if (value) {
        return *value;
    }
    throw UndefinedVariable(make_shared<Context>(context), e->name, e->getToken().startPos);
}

shared_obj Visitor::visit(Context& context, ConditionalExpression* e) {
    if (e->condition->accept(context, *this)->value) {
        return e->thenBranch->accept(context, *this);
    } 
    for (int i = 0; i< e->elif_conditions.size(); i++) {
        if (e->elif_conditions[i]->accept(context, *this)->value) {
            return e->elif_thens[i]->accept(context, *this);
        }
    }
    return e->elseBranch->accept(context, *this);
}

shared_obj Visitor::visit(Context& parent, CallFunctionExpression* e) {

    Visitor v;
    std::optional<shared_obj> decl = parent.symbols->get(e->getToken().getValue());
    if (!decl) throw UndefinedVariable(make_shared<Context>(parent), e->getToken().getValue(), e->getToken().startPos);
    vector<shared_obj> args;
    for (int i = 0; i < e->params.size(); i++) {
        args.push_back(e->params[i]->accept(parent, v));
    }
    return decl->get()->call(parent, args);
}

shared_obj Visitor::visit(Context& context, IndexExpression* e) {
    std::optional<shared_obj> value = context.symbols->get(e->getToken().getValue());
    if (!value) {
        throw UndefinedVariable(make_shared<Context>(context), e->getToken().getValue(), e->getToken().startPos);
    }
    return value->get()->index(e->index->accept(context, *this));
}
shared_obj Visitor::visit(Context& context, FuncDefExpression* e) {
    shared_ptr<func_type> fun = make_shared<func_type>(e->name, e->params, e->body); 
    if (!e->lambda) context.symbols->set(e->name, fun);
    return fun;
}
