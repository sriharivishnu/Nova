#ifndef STATEMENT_H
#define STATEMENT_H
#include "Context.h"
#include "Expression.h"
#include "Token.h"
#include <vector>
#include <memory>
#include <optional>
using expression_ptr = std::shared_ptr<Expression>;
class statement {
	public:
		statement() = default;
		virtual std::optional<Result> execute(Context& context) {
            return {};
        };
		virtual ~statement() = default;
};
using statement_ptr = std::shared_ptr<statement>;

class simple_statement : public statement {
    public:
        std::optional<Result> execute(Context& context) override;
        simple_statement(expression_ptr expr);
    private:
        expression_ptr expr;
};

// class if_statement : public statement {
//     public:
//         if_statement(
//             expression_ptr ifCondition, 
//             statement_ptr ifBlock, 
//             std::vector<expression_ptr> elifConditions, 
//             std::vector<statement_ptr> elifBlocks, 
//             statement_ptr elseBlock);

//         std::optional<Result> execute(Context& context) override;
//     private:
//         expression_ptr if_condition;
//         statement_ptr if_block;
//         std::vector<expression_ptr> elif_conditions;
//         std::vector<statement_ptr> elif_blocks;
//         statement_ptr else_block;
// };

class while_statement : public statement {
    public:
        while_statement(
            expression_ptr condition_,
            statement_ptr statement_
        );
        std::optional<Result> execute(Context& context) override;
    private:
        expression_ptr condition;
        statement_ptr statement; 
};

// class for_statement : public statement {
//     public:
//         for_statement(

//         );
//         std::optional<Result> execute(Context& context) override;
//     private:
//         Token identifier; 
//         expression_ptr start;
//         expression_ptr end;
        
// };

class block_statement : public statement {
    public:
        block_statement(vector<statement_ptr> statements);
        std::optional<Result> execute(Context& context) override;
    private:
        vector<statement_ptr> statements;
};
    
#endif