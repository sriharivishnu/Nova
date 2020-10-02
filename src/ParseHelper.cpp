#include "ParseHelper.h"
#include "Statement.h"


int getTokenPrecedence(const Token& tok) {
    switch(tok.type) {
        case Token::Type::PLUS:
        case Token::Type::MINUS:
            return Precedence::SUM;
        case Token::Type::MULT:
        case Token::Type::DIV:
        case Token::Type::MOD:
        case Token::Type::LSHIFT:
        case Token::Type::RSHIFT:
            return Precedence::PRODUCT;
        case Token::Type::POWER:
            return Precedence::EXPONENT;
        case Token::Type::EQUALS:
        case Token::Type::EE:
        case Token::Type::NE:
        case Token::Type::LE:
        case Token::Type::GE:
        case Token::Type::GT:
        case Token::Type::LT:
        case Token::Type::AND:
        case Token::Type::BAND:
        case Token::Type::OR:
        case Token::Type::BOR:
        case Token::Type::XOR:
        case Token::Type::IF:
            return Precedence::CONDITION;
        case Token::Type::DOT:
            return Precedence::CALL;
        case Token::Type::INC:
        case Token::Type::DEC:
            return Precedence::POSTFIX;
        case Token::Type::LSQUARE:
            return Precedence::INDEX;
        case Token::Type::LPAREN:
            return Precedence::CALL;
        default:
            return -1;
    }
}