#include "Statement.h"
#include "Result.h"

std::optional<Result> simple_statement::execute(Context& context) {
    Visitor v;
    Result res = expr -> accept(context, v);
    if (res.isType<int>()) printf("%d", res.getTypeOrThrow<int>(Position(0,0,0)));
    return res;
};
simple_statement::simple_statement(std::shared_ptr<Expression> expr_) : expr(expr_) {}

while_statement::while_statement(
            expression_ptr condition_,
            statement_ptr statement_
        ) : condition(condition_), statement(statement_) {}

std::optional<Result> while_statement::execute(Context& context) {
    Visitor v;
    while (condition->accept(context, v)) {
        statement->execute(context);
    }
    return {};
};

block_statement::block_statement(vector<statement_ptr> statements) : statements(statements) {}
std::optional<Result> block_statement::execute(Context& context) {
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

std::optional<Result> if_statement::execute(Context& context) {
    Visitor v;
    if (if_condition->accept(context, v)) {
        return if_block->execute(context);
    }
    for (int i = 0; i < elif_conditions.size(); i++) {
        if (elif_conditions[i]->accept(context, v)) {
            return elif_blocks[i]->execute(context);
        }
    }
    if (else_block) {
        return else_block->execute(context);
    }
    return {};
}

function_statement::function_statement(
            std::string name,
            vector<std::string> params,
            statement_ptr toRun, 
            Position& pos) : name(name), params(params), toRun(toRun), pos(pos)
{}
std::optional<Result> function_statement::execute(Context& context) {
    // context.functions->
    printf("GOT NAME: %s\n", name.c_str());
    context.functions->add(name, this);
    return {};
}