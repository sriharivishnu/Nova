#include "Parser.h"

Token Parser::advance() {
    cur += 1;
    if (cur < tokens.size()) {
        curToken = tokens[cur];
    }
    return curToken;
}

ParseResult Parser::factor() {
    ParseResult res = ParseResult();
    if (curToken.is(Token::Type::INT)) {
        advance();
        return res.onSuccess(IntegerLiteral(curToken));
    }
    else if (curToken.is(Token::Type::DOUBLE)) {
        advance();
        return res.onSuccess(DoubleLiteral(curToken));
    }
    return res.onError(SyntaxError("Expected an int or a double type"));
}

ParseResult Parser::term() {
    return binOp();
}

ParseResult Parser::binOp() {
    ParseResult left = factor();
    if (!left.result) return left;
    
    return left.onSuccess(BinaryOpNode(curToken, curToken, curToken));
}

// ParseResult Parser::nextExpr() {
    
// }

// ParseResult Parser::parse() {

// }

