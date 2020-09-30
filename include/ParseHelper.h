#ifndef PARSER_HELPER
#define PARSER_HELPER
#include "Expression.h"
#include "Parser.h"
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
    CALL = 8
};

#endif