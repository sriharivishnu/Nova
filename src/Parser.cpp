#include "Parser.h"

Token Parser::next() {
    cur += 1;
    if (cur < tokens.size()) {
        curToken = tokens[cur];
    }
    return curToken;
}

NumberNode Parser::factor() {
    return NumberNode(curToken);
}

BinaryOpNode Parser::term() {
    return BinaryOpNode(curToken, curToken, curToken);
}