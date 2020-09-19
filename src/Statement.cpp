#include "Statement.h"
#include "Result.h"

std::optional<shared_obj> simple_statement::execute(Context& context) {
    Visitor v;
    return expr->accept(context, v);
};
simple_statement::simple_statement(std::shared_ptr<Expression> expr_) : expr(expr_) {}

while_statement::while_statement(
            expression_ptr condition_,
            statement_ptr statement_
        ) : condition(condition_), statement(statement_) {}

std::optional<shared_obj> while_statement::execute(Context& context) {
    Visitor v;
    while (condition->accept(context, v)->value) {
        statement->execute(context);
    }
    return {};
};

block_statement::block_statement(vector<statement_ptr> statements) : statements(statements) {}
std::optional<shared_obj> block_statement::execute(Context& context) {
    for (int i = 0; i < statements.size(); i++) {
        statements[i]->execute(context);
    }
    return {};
}

if_statement::if_statement(
    expression_ptr ifCondition, 
    statement_ptr ifBlock, 
    std::vector<expression_ptr> elifConditions, 
    std::vector<statement_ptr> elifBlocks, 
    statement_ptr elseBlock) : if_condition(ifCondition), if_block(ifBlock), elif_conditions(elifConditions),
    elif_blocks(elifBlocks), else_block(elseBlock)
{

}

std::optional<shared_obj> if_statement::execute(Context& context) {
    Visitor v;
    if (if_condition->accept(context, v)->value) {
        return if_block->execute(context);
    }
    for (int i = 0; i < elif_conditions.size(); i++) {
        if (elif_conditions[i]->accept(context, v)->value) {
            return elif_blocks[i]->execute(context);
        }
    }
    if (else_block) {
        return else_block->execute(context);
    }
    return {};
}