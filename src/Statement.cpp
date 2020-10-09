#include "Statement.h"

#include <utility>
#include "Result.h"
bool flow::isType(type a) {
    return flow_type == a;
}
flow::flow(type t, shared_obj obj) : flow_type(t), value(obj) {};
flow::flow(type t) : flow_type(t) {}

flow simple_statement::execute(Context& context) {
    Visitor v;
    return flow(flow::type::SIMPLE, expr->accept(context, v));
};
simple_statement::simple_statement(std::shared_ptr<Expression> expr_) : expr(std::move(expr_)) {}

while_statement::while_statement(
            expression_ptr condition_,
            statement_ptr statement_
        ) : condition(std::move(condition_)), statement(std::move(statement_)) {}

flow while_statement::execute(Context& context) {
    Visitor v;
    while (condition->accept(context, v)->value) {
        flow ret = statement->execute(context);
        if (ret.isType(flow::type::BREAK)) break;
        else if (ret.isType(flow::type::RETURN)) return ret;
    }
    return flow(flow::type::NONE);
};

block_statement::block_statement(vector<statement_ptr> statements) : statements(std::move(statements)) {}
flow block_statement::execute(Context& context) {
    for (auto & statement : statements) {
        flow ret = statement->execute(context);
        switch(ret.flow_type) {
            case flow::type::RETURN:
            case flow::type::BREAK:
            case flow::type::CONTINUE:
                return ret;
            default:
                continue;
        }
    }
    return flow(flow::type::NONE);
}

if_statement::if_statement(
    expression_ptr ifCondition, 
    statement_ptr ifBlock, 
    std::vector<expression_ptr> elifConditions, 
    std::vector<statement_ptr> elifBlocks, 
    statement_ptr elseBlock) : if_condition(std::move(ifCondition)), if_block(std::move(ifBlock)), elif_conditions(std::move(elifConditions)),
    elif_blocks(std::move(elifBlocks)), else_block(std::move(elseBlock))
{}

flow if_statement::execute(Context& context) {
    Visitor v;
    if (if_condition->accept(context, v)->value) {
        return if_block->execute(context);
    }
    for (unsigned int i = 0; i < elif_conditions.size(); i++) {
        if (elif_conditions[i]->accept(context, v)->value) {
            return elif_blocks[i]->execute(context);
        }
    }
    if (else_block) {
        return else_block->execute(context);
    }
    return flow(flow::type::NONE);
}
return_statement::return_statement() = default;
return_statement::return_statement(expression_ptr toReturn) : toReturn(toReturn) {}
flow return_statement::execute(Context& context) {
    Visitor v;
    if (toReturn) {
        return flow(flow::type::RETURN, toReturn->get()->accept(context, v));
    }
    else {
        return flow(flow::type::RETURN, std::make_shared<null_type>());
    }
}

break_statement::break_statement() = default;
flow break_statement::execute(Context& context) {
    return flow(flow::type::BREAK);
}

continue_statement::continue_statement() = default;
flow continue_statement::execute(Context& context) {
    return flow(flow::type::CONTINUE);
}