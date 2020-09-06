#include "Token.h"
#include <string>
std::string Token::getValue() {
    return value;
}
bool Token::is(Type t) {
    return this->type == t;
}

bool Token::isOneOf(Type t1, Type t2) {
    return is(t1) || is(t2);
}

Token::Token(Type t, Position pos) 
    : type(t), startPos(pos) {}
Token::Token(Type t, std::string value, Position pos) 
    : type(t), startPos(pos), value(value) {}
Token::Token(Type t, char value, Position pos) 
    : type(t), startPos(pos), value(std::string(1, value)) {}
Token::Token(Type t, const char* start, const char* end, Position pos) 
    : type(t), startPos(pos), value(std::string(start, end)) {}
Token::Token(Type t, const char* start, size_t length, Position pos) 
    : type(t), startPos(pos), value(std::string(start, length)) {}