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

Token::Token(Type t) : type(t) {}
Token::Token(Type t, std::string value) : type(t), value(value) {}
Token::Token(Type t, char value) : type(t), value(std::string(1, value)) {}
Token::Token(Type t, const char* start, const char* end) : type(t), value(std::string(start, end)) {}
Token::Token(Type t, const char* start, size_t length) : type(t), value(std::string(start, length)) {}

