#ifndef INTERPRETER_CLASS
#define INTERPRETER_CLASS
#include "Expression.h"
#include "Types.h"
#include <string>
#include <math.h>
#include <memory>
class Interpreter {
    // public:
    //     Object visit(std::shared_ptr<Expression> n);
};

// class Visitor {
//     public:
//         int visit(std::shared_ptr<OperatorExpression> e) {
//             switch(e->op.type) {
//                 case Token::Type::PLUS:
//                     return visit(e->left) + visit(e->right);
//                 case Token::Type::MINUS:
//                     return visit(e->left) - visit(e->right);
//                 case Token::Type::MULT:
//                     return visit(e->left) * visit(e->right);
//                 case Token::Type::DIV:
//                     return visit(e->left) / visit(e->right);
//                 case Token::Type::CAROT:
//                     return pow(visit(e->left), visit(e->right));
//                 default:
//                     throw UndefinedOperationException(e->op.getValue());
//             }
//         }
//         int visit(std::shared_ptr<NumberExpression> e) {
//             return e->getInt();
//         }

//         int visit(std::shared_ptr<Expression> e) {return 0;}
// };
// template<class T>
// class Visitor {
//     public:
//         virtual T visit(Expression e);
// };

// class Result {
//     union S {
//         int int_data;
//         bool bool_data;
//         std::cstring* string_data;
//     }
    
// };
#endif