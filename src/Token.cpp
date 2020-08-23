#include "Token.h"
#include <string>
bool Token::is(Type t) {
    return this->type == t;
}

bool Token::isOneOf(Type t1, Type t2) {
    return is(t1) || is(t2);
}

Token::Token(Type t) : type(t) {}
Token::Token(Type t, std::string value) : type(t), value(value) {}

Token::Token(Type t, const char* start, const char* end) : type(t) {
    value = std::string(start, end);
    if (t == Type::END) printf("GOT END TOKEN");
    else if (t == Type::UNKNOWN) printf("UNKNOWN TOKEN");
    printf("HEREEE: %s", value.c_str());
}

Token::Token(Type t, const char* start, size_t length) : type(t) {
    value = std::string(start, length);
    printf("HERE#@# %s", value.c_str());
}

