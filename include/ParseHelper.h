#ifndef PARSER_HELPER
#define PARSER_HELPER
#include "Token.h"
#include <memory>
#include <vector>
#include <unordered_map>
using namespace std;

enum Precedence {
    ASSIGNMENT = 1,
    CONDITION = 2,
    OR = 4,
    AND = 5,
    BOR = 6,
    XOR = 7,
    BAND = 8,
    EQUALITY = 9,
    INEQUALITY = 10,
    SHIFT = 11,
    SUM = 12, 
    PRODUCT = 13,
    EXPONENT = 14, 
    PREFIX = 14,
    POSTFIX = 15,
    INDEX = 15,
    CALL = 15
};
//Infix
int getTokenPrecedence(const Token& tok);

#endif