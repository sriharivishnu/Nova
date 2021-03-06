#include "Interpreter.h"
#include "optional"
#include "Statement.h"
#include "Error.h"
#include "Token.h"
shared_obj Visitor::visit(Context& context, Expression* e) {
    throw UndefinedOperationException(e->getToken().startPos, "Visited unknown expression " + e->toString());
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
        case Token::Type::BNOT:
            return rightSide->bnot();
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
        shared_obj val = nullptr;
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
        case Token::Type::MOD:
            return left->mod(right);
        case Token::Type::POWER:
            return left->powBy(right);
        case Token::Type::BAND:
            return left->band(right);
        case Token::Type::BOR:
            return left->bor(right);
        case Token::Type::XOR:
            return left->bxor(right);
        case Token::Type::LSHIFT:
            return left->lshift(right);
        case Token::Type::RSHIFT:
            return left->rshift(right);
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
    for (unsigned int i = 0; i < e->getValue().size(); i++) {
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
    if (e->getToken().type == Token::Type::EQUALS) {
        if (context.symbols->update(e->name, res)) return res;
        else throw UndefinedVariable(make_shared<Context>(context), e->name, e->getToken().startPos);
    }
    std::optional<shared_obj> cur = context.symbols->get(e->name);
    if (!cur) throw UndefinedVariable(make_shared<Context>(context), e->name, e->getToken().startPos);
    switch(e->getToken().type) {
        case Token::Type::PLUS_EQUAL:
            cur = cur->get()->addBy(res);
            break;
        case Token::Type::MINUS_EQUAL:
            cur = cur->get()->subBy(res);
            break;
        case Token::Type::MULT_EQUAL:
            cur = cur->get()->multBy(res);
            break;
        case Token::Type::DIV_EQUAL:
            cur = cur->get()->divBy(res);
            break;
        case Token::Type::MOD_EQUAL:
            cur = cur->get()->mod(res);
            break;
        default:
            throw UndefinedOperationException(e->getToken().startPos, "Undefined Operation", e->getToken().getValue());
    }
    context.symbols->update(e->name, *cur);
    return make_shared<null_type>();
}

shared_obj Visitor::visit(Context& context, ObjectIndexUpdateExpression* e) {
    shared_obj res = e->newVal->accept(context, *this);
    shared_obj obj = e->objToUpdate->accept(context, *this);
    shared_obj index = e->index->accept(context, *this);
    shared_obj newValue = e->newVal->accept(context, *this);
    
    return obj->indexUpdate(index, newValue);
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
    for (unsigned int i = 0; i< e->elif_conditions.size(); i++) {
        if (e->elif_conditions[i]->accept(context, *this)->value) {
            return e->elif_thens[i]->accept(context, *this);
        }
    }
    return e->elseBranch->accept(context, *this);
}

shared_obj Visitor::visit(Context& context, CallFunctionExpression* e) {
    shared_obj decl = e->left->accept(context, *this);
    vector<shared_obj> args;
    for (auto & param : e->params) {
        args.push_back(param->accept(context, *this));
    }
    return decl->call(context, args);
}

shared_obj Visitor::visit(Context& context, IndexExpression* e) {
    shared_obj index_obj = e->index->accept(context, *this);
    return e->left->accept(context, *this)->index(index_obj);
}
shared_obj Visitor::visit(Context& context, FuncDefExpression* e) {
    shared_ptr<func_type> fun = make_shared<func_type>(e->name, e->params, e->body); 
    if (!e->lambda) context.symbols->set(e->name, fun);
    return fun;
}

shared_obj Visitor::visit(Context &context, MemberAccessExpression *e) {
    shared_obj left = e->obj->accept(context, *this);
    vector<shared_obj> args;
    for (auto & arg : e->args) args.push_back(arg->accept(context, *this));
    return left->dot(e->name, args);
}
