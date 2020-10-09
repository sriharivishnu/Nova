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
            return Precedence::PRODUCT;
        case Token::Type::LSHIFT:
        case Token::Type::RSHIFT:
            return Precedence::SHIFT;
        case Token::Type::POWER:
            return Precedence::EXPONENT;
        case Token::Type::EQUALS:
        case Token::Type::PLUS_EQUAL:
        case Token::Type::MINUS_EQUAL:
        case Token::Type::MULT_EQUAL:
        case Token::Type::DIV_EQUAL:
        case Token::Type::MOD_EQUAL:
            return Precedence::ASSIGNMENT;
        case Token::Type::EE:
        case Token::Type::NE:
            return Precedence::EQUALITY;
        case Token::Type::LE:
        case Token::Type::GE:
        case Token::Type::GT:
        case Token::Type::LT:
            return Precedence::INEQUALITY;
        case Token::Type::AND:
            return Precedence::AND;
        case Token::Type::BAND:
            return Precedence::BAND;
        case Token::Type::OR:
            return Precedence::OR;
        case Token::Type::BOR:
            return Precedence::BOR;
        case Token::Type::XOR:
            return Precedence::XOR;
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