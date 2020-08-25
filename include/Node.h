#include "Token.h"
#include "Error.h"
#ifndef NODE_CLASSES
#define NODE_CLASSES
//Generic Node Class
class Node {
    public:
        Node() {};
        Node(Token t) : tok(t) {};
        Token tok; 
        std::string toString() {
            return tok.getValue();
        }
};
//Generic Expression Class (Produces a value)
class Expression : public Node {
    public:
        Expression(Token t) : Node(t) {};
};

//Generic Statement Class
class Statement : public Node {
    public:
        Statement(Token t) : Node(t) {};
};
/*
LITERALS
*/
class LiteralNode : public Expression {
    public: 
        LiteralNode(Token t) : Expression(t) {};
};
/*
NUMBERS
*/
class NumberNode : public LiteralNode {
    public:
        NumberNode(Token t) : LiteralNode(t) {};
};

class IntegerLiteral : public NumberNode {
    public:
        int value = 0;
        IntegerLiteral(Token t) : NumberNode(t) {
            value = std::stoi(t.getValue());
        };
};

class DoubleLiteral : public NumberNode {
    public:
        double value = 0.0f;
        DoubleLiteral(Token t) : NumberNode(t) {
            value = std::stod(t.getValue());
        };
};

/*
Operators
*/
class Operator : public Expression {
    public:
        Operator(Token t) : Expression(t) {}
};

class BinaryOpNode : public Operator {
    Expression left;
    Expression right;
    public:
        BinaryOpNode(Expression left, Token op, Expression right) 
        : Operator(op), left(left), right(right) {};
};

// class AddOpNode : public BinaryOpNode {
//     AddOpNode (NumberNode left, Token op, NumberNode right) : BinaryOpNode(left, op, right) {};
// };
// class SubtractOpNode : public BinaryOpNode {
//     SubtractOpNode (NumberNode left, Token op, NumberNode right) : BinaryOpNode(left, op, right) {};
// };
// class MultiplyOpNode : public BinaryOpNode {
//     MultiplyOpNode (NumberNode left, Token op, NumberNode right) : BinaryOpNode(left, op, right) {};
// };
// class DivideOpNode : public BinaryOpNode {
//     DivideOpNode (NumberNode left, Token op, NumberNode right) : BinaryOpNode(left, op, right) {};
// };
#endif