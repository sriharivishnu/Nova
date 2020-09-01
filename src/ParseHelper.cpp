#include "ParseHelper.h"

shared_ptr<Expression> PrefixParser::parse(Parser& parser, Token token) {
    return make_shared<Expression>();
}

shared_ptr<Expression> InfixParser::parse(Parser& parser, shared_ptr<Expression> left, Token token) {
    return make_shared<Expression>();
}
int InfixParser::getPrecedence() {return -1;}


shared_ptr<Expression> NameParser::parse(Parser& parser, Token token) {
    return make_shared<NameExpression>(token.getValue());
}

shared_ptr<Expression> NumberParser::parse(Parser& parser, Token token) {
    return make_shared<NumberExpression>(token);
}

PrefixOperatorParser::PrefixOperatorParser(int precedence) : precedence(precedence) {}
shared_ptr<Expression> PrefixOperatorParser::parse(Parser& parser, Token token) {
    shared_ptr<Expression> right = parser.parseExpression(precedence);
    return make_shared<PrefixExpression>(token, right);
}
int PrefixOperatorParser::getPrecedence() {
    return precedence;
}


PostfixOperatorParser::PostfixOperatorParser(int precedence) : precedence(precedence) {}
int PostfixOperatorParser::getPrecedence() {return precedence;}


BinaryOperatorParser::BinaryOperatorParser(int precedence, bool isRight) : precedence(precedence), isRight(isRight){}
shared_ptr<Expression> BinaryOperatorParser::parse(Parser& parser, shared_ptr<Expression> left, Token tok) {
    shared_ptr<Expression> right = parser.parseExpression(
        precedence - (isRight ? 1 : 0)
    );
    return make_shared<OperatorExpression>(left, tok, right);
}
int BinaryOperatorParser::getPrecedence() {return precedence;}

shared_ptr<Expression> GroupParser::parse(Parser& parser, Token token) {
    shared_ptr<Expression> expression = parser.parseExpression();
    parser.consume(Token::Type::RPAREN);
    return expression;
}