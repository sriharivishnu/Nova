#include "../include/Token.h"

bool Token::is(Type t) {
    return this->type == t;
}

bool Token::isOneOf(Type t1, Type t2) {
    return is(t1) || is(t2);
}

Token::Token(Type t) : type(t) {}
Token::Token(Type t, std::string value) : type(t), value(value) {}

std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << std::string("TYPE: <") << token.type << std::string(">");
    if (token.value != "") {
        os << std::string(" Value: ") << token.value;
    }
    return os;
}

std::ostream& operator << (std::ostream& os, const Token::Type& obj)
{
   os << std::to_string(static_cast<std::underlying_type<Token::Type>::type>(obj));
   return os;
}
