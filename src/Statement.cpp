#include "Statement.h"
#include "Result.h"
std::optional<Result> simple_statement::execute(Context& context) {
    Visitor v;
    return expr -> accept(context, v);
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