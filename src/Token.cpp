#include "../include/Token.h"

bool Token::is(Type t) {
    return this->type == t;
}

bool Token::isOneOf(Type t1, Type t2) {
    return is(t1) || is(t2);
}