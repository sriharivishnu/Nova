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
    SUM = 3, 
    PRODUCT = 4,
    EXPONENT = 5, 
    PREFIX = 6,
    POSTFIX = 7,
    INDEX = 8,
    CALL = 9
};
//Infix
int getTokenPrecedence(const Token& tok);

#endif