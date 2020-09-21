#include "ParseHelper.h"
#include "Statement.h"
shared_ptr<Expression> PrefixParser::parse(Parser& parser, const Token& token) {
    return make_shared<Expression>();
}

shared_ptr<Expression> InfixParser::parse(Parser& parser, shared_ptr<Expression> left, const Token& token) {
    return make_shared<Expression>();
}
int InfixParser::getPrecedence() {return -1;}


shared_ptr<Expression> NameParser::parse(Parser& parser, const Token& token) {
    if (parser.lookAhead(0).is(Token::Type::LPAREN)) {
        parser.consume();
        vector<shared_ptr<Expression>> params;
        if (!parser.lookAhead(0).is(Token::Type::RPAREN)) {
            params.push_back(parser.parseExpression());
            while (parser.lookAhead(0).is(Token::Type::COMMA))
            {   
                parser.consume();
                params.push_back(parser.parseExpression());
            }
        }
        parser.consume(Token::Type::RPAREN, ", expected ')'");
        return make_shared<CallFunctionExpression>(token, params);
    } else if (parser.lookAhead(0).is(Token::Type::LSQUARE)) {
        parser.consume();
        shared_ptr<Expression> index = parser.parseExpression();
        parser.consume(Token::Type::RSQUARE, ", expected ']'");
        return make_shared<IndexExpression>(token, index);
    }
    return make_shared<NameExpression>(token.getValue(), token);
}

shared_ptr<Expression> NumberParser::parse(Parser& parser, const Token& token) {
    return make_shared<NumberExpression>(token);
}

shared_ptr<Expression> StringParser::parse(Parser& parser, const Token& token) {
    return make_shared<StringExpression>(token);
}

shared_ptr<Expression> ListParser::parse(Parser& parser, const Token& token) {
    vector<shared_ptr<Expression>> items;
    if (!parser.lookAhead(0).is(Token::Type::RSQUARE)) {
        shared_ptr<Expression> item = parser.parseExpression();
        items.push_back(item);
        while (parser.lookAhead(0).is(Token::Type::COMMA)) {
            parser.consume(Token::Type::COMMA);
            items.push_back(parser.parseExpression());
        }
    }
    parser.consume(Token::Type::RSQUARE, "expected ']'");
    return make_shared<ListExpression>(token, items);
}

PrefixOperatorParser::PrefixOperatorParser(int precedence) : precedence(precedence) {}
shared_ptr<Expression> PrefixOperatorParser::parse(Parser& parser, const Token& token) {
    shared_ptr<Expression> right = parser.parseExpression(precedence);
    if (token.isOneOf(Token::Type::INC, Token::Type::DEC) && !right->getToken().is(Token::Type::IDENTIFIER)) {
        throw SyntaxError(right->getToken().startPos, "Expected an identifier"); 
    }
    return make_shared<PrefixExpression>(token, right);
}
int PrefixOperatorParser::getPrecedence() const {
    return precedence;
}


PostfixOperatorParser::PostfixOperatorParser(int precedence) : precedence(precedence) {}
shared_ptr<Expression> PostfixOperatorParser::parse(Parser& parser, shared_ptr<Expression> left, const Token& token) {
    if (token.isOneOf(Token::Type::INC, Token::Type::DEC) && !left->getToken().is(Token::Type::IDENTIFIER)) {
        throw SyntaxError(left->getToken().startPos, "Expected an identifier"); 
    }
    return make_shared<PostfixExpression>(left, token);
}
int PostfixOperatorParser::getPrecedence() {return precedence;}


BinaryOperatorParser::BinaryOperatorParser(int precedence, bool isRight) : precedence(precedence), isRight(isRight){}
shared_ptr<Expression> BinaryOperatorParser::parse(Parser& parser, shared_ptr<Expression> left, const Token& token) {
    shared_ptr<Expression> right = parser.parseExpression(
        precedence - (isRight ? 1 : 0)
    );
    return make_shared<BinOpExpression>(left, token, right);
}
int BinaryOperatorParser::getPrecedence() {return precedence;}

ComparisonParser::ComparisonParser() = default;

shared_ptr<Expression> ComparisonParser::parse(Parser& parser, shared_ptr<Expression> left, const Token& token) {
    shared_ptr<Expression> right = parser.parseExpression(getPrecedence());
    return make_shared<ComparisonExpression>(left, token, right);
}
int ComparisonParser::getPrecedence() {
    return Precedence::CONDITION;
}

AssignmentParser::AssignmentParser() = default;
shared_ptr<Expression> AssignmentParser::parse(Parser& parser, const Token& tok) {
    Token name = parser.consume(Token::Type::IDENTIFIER, ", expected an identifier");
    Token equals = parser.consume(Token::Type::EQUALS, ", expected '='");
    shared_ptr<Expression> right = parser.parseExpression(
        Precedence::ASSIGNMENT - 1
    );
    return make_shared<AssignmentExpression>(name.getValue(), right, equals);

}

UpdateOrAssignParser::UpdateOrAssignParser() = default;
shared_ptr<Expression> UpdateOrAssignParser::parse(Parser& parser, shared_ptr<Expression> left, const Token& token) {
    if (!left->getToken().is(Token::Type::IDENTIFIER)) {
        throw SyntaxError(left->getToken().startPos, "Expected an identifier"); 
    }
    shared_ptr<Expression> right = parser.parseExpression(Precedence::ASSIGNMENT - 1);
    return make_shared<UpdateExpression>(left->getToken().getValue(), right, token);
}
int UpdateOrAssignParser::getPrecedence() {
    return Precedence::ASSIGNMENT;
}

ConditionalParser::ConditionalParser() = default;
shared_ptr<Expression> ConditionalParser::parse(Parser& parser, const Token& token) {
    //IF
    parser.consume(Token::Type::LPAREN, ", expected '(");
    shared_ptr<Expression> condition = parser.parseExpression(Precedence::CONDITION -1 );
    parser.consume(Token::Type::RPAREN, ", expected ')'");
    shared_ptr<Expression> then = parser.parseExpression(Precedence::CONDITION - 1);

    //ELIF
    Token next = parser.consume();
    vector<shared_ptr<Expression>> elif_conditions;
    vector<shared_ptr<Expression>> elif_thens;
    while (next.is(Token::Type::ELIF)) {
        parser.consume(Token::Type::LPAREN, ", expected '(");
        elif_conditions.push_back(parser.parseExpression(Precedence::CONDITION -1 ));
        parser.consume(Token::Type::RPAREN, ", expected ')'");
        elif_thens.push_back(parser.parseExpression(Precedence::CONDITION -1));
        next = parser.consume();
    }

    //ELSE
    if (!next.is(Token::Type::ELSE)) throw SyntaxError(next.startPos, "Unexpected token: " +  next.getValue() + ", expected 'else' or 'elif'");
    shared_ptr<Expression> elseBranch = parser.parseExpression(Precedence::CONDITION - 1);
    return make_shared<ConditionalExpression>(token, condition, then, elif_conditions, elif_thens, elseBranch);
}

shared_ptr<Expression> GroupParser::parse(Parser& parser, const Token& token) {
    shared_ptr<Expression> expression = parser.parseExpression();
    parser.consume(Token::Type::RPAREN, ", expected '}'");
    return expression;
}

shared_ptr<Expression> FuncDefParser::parse(Parser& parser, const Token& token) {
    std::string name;
    bool anonymous = false;
    if (parser.lookAhead(0).is(Token::Type::IDENTIFIER)) name = parser.consume(Token::Type::IDENTIFIER).getValue();
    else {
        name = "anonymous";
        anonymous = true;
    }

    parser.consume(Token::Type::LPAREN, "expected '(' for function definition of " + name);
    vector<std::string> params;
    if (!parser.lookAhead(0).is(Token::Type::RPAREN)) {
        Token p = parser.consume(Token::Type::IDENTIFIER);
        params.push_back(p.getValue());
        while (parser.lookAhead(0).is(Token::Type::COMMA)) {
            parser.consume();
            p = parser.consume(Token::Type::IDENTIFIER);
            params.push_back(p.getValue());
        }
    }
    parser.consume(Token::Type::RPAREN, ", expected ')'");
    shared_ptr<statement> toRun;
    if (parser.lookAhead(0).is(Token::Type::ARROW)) {
        parser.consume(Token::Type::ARROW);
        toRun = make_shared<simple_statement>(parser.parseExpression());
    } else {
        toRun = parser.parseStatement();
    }
    return make_shared<FuncDefExpression>(token, name, params, toRun, anonymous);
}
