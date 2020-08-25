#include "Parser.h"
#include <iostream>
Parser::Parser(std::vector<Token> tokens) : tokens(tokens) {
    cur = 0;
    if (tokens.size() > 0) curToken = tokens[cur];
};

//Expression -> Operation 
Token Parser::advance() {
    cur += 1;
    if (cur < tokens.size() && !tokens[cur].is(Token::Type::END)) {
        curToken = tokens[cur];
    }
    std::cout << curToken.getValue() << std::endl;
    return curToken;
}

ParseResult Parser::parse() {
    ParseResult res = expr();
    return res;
}

ParseResult Parser::factor() {
    ParseResult res = ParseResult();
    Token tok = curToken;
    if (tok.is(Token::Type::INT)) {
        advance();
        return res.onSuccess(Node(tok));
    }
    else if (tok.is(Token::Type::DOUBLE)) {
        advance();
        return res.onSuccess(Node(tok));
    }
    return res.onError(SyntaxError("Expected an int or a double type"));
}

ParseResult Parser::term() {
    return binOp(std::bind(&Parser::factor, this), {Token::Type::MULT, Token::Type::DIV});
}

ParseResult Parser::expr() {
    return binOp(std::bind(&Parser::term, this), {Token::Type::PLUS, Token::Type::MINUS});
}

ParseResult Parser::binOp(std::function<ParseResult ()> fun, std::vector<Token::Type> ops) {
    ParseResult left = fun();
    if (!left.result) return left;
    while (curToken.isOneOf(ops)) {
        Token opToken(curToken);
        advance();
        ParseResult right = fun();
        if (!right.result) return right;
        left = ParseResult().onSuccess(Node(opToken, {left.node, right.node}));
    }
    return left;
}

