#ifndef STATEMENT_H
#define STATEMENT_H
#include "Context.h"
#include "Expression.h"
#include "Token.h"
#include "Result.h"
#include "types.h"
#include <vector>
#include <memory>
#include <optional>
class Expression;
struct Context;
using expression_ptr = std::shared_ptr<Expression>;
using shared_obj = std::shared_ptr<object>;

class flow {
    public:
        enum class type {
            SIMPLE,
            RETURN,
            CONTINUE,
            BREAK,
            NONE
        };
        type flow_type;
        std::optional<shared_obj> value;
        bool isType(type a);
        flow(type, shared_obj obj);
        flow(type);
};

class statement {
	public:
		statement() = default;
		virtual flow execute(Context& context) {
            return flow(flow::type::NONE);
        };
		virtual ~statement() = default;
};
using statement_ptr = std::shared_ptr<statement>;

class simple_statement : public statement {
    public:
        flow execute(Context& context) override;
        simple_statement(expression_ptr expr);
    private:
        expression_ptr expr;
};

class if_statement : public statement {
    public:
        if_statement(
            expression_ptr ifCondition, 
            statement_ptr ifBlock, 
            std::vector<expression_ptr> elifConditions, 
            std::vector<statement_ptr> elifBlocks, 
            statement_ptr elseBlock);

        flow execute(Context& context) override;
    private:
        expression_ptr if_condition;
        statement_ptr if_block;
        std::vector<expression_ptr> elif_conditions;
        std::vector<statement_ptr> elif_blocks;
        statement_ptr else_block;
};

class while_statement : public statement {
    public:
        while_statement(
            expression_ptr condition_,
            statement_ptr statement_
        );
        flow execute(Context& context) override;
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
        block_statement(std::vector<statement_ptr> statements);
        flow execute(Context& context) override;
    private:
        std::vector<statement_ptr> statements;
};

class return_statement : public statement {
    public:
        return_statement(expression_ptr toReturn);
        return_statement();
        flow execute(Context& context) override;
    private:
        std::optional<expression_ptr> toReturn;
};

class break_statement : public statement {
    public:
        break_statement();
        flow execute(Context& context) override;
};

class continue_statement : public statement {
    public:
            continue_statement();
            flow execute(Context& context) override;
};
#endif