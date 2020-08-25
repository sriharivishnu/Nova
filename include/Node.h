#include <vector>

#include "Token.h"
#include "Error.h"
#ifndef NODE_CLASSES
#define NODE_CLASSES

enum struct Operation {
    UNARY,
    BINARY,
    LITERAL
};
//Generic Node Class
class Node {
    public:
        Node() {};
        Node(Token t, std::vector<Node> children) : children(children), tok(t) {
            assignType(t);
        }
        Node(Token t) : tok(t) {
            assignType(t);
        };
        std::vector<Node> children;
        Operation op = Operation::LITERAL;
        Token tok; 
        std::string toString() {
            switch(op) {
                case Operation::LITERAL:
                    return tok.getValue();
                case Operation::BINARY:
                    if (children.size() == 2) {
                        return "(" + children[0].toString() + tok.getValue() + children[1].toString() + ")";
                    }
                case Operation::UNARY:
                    if (children.size() == 1) {
                        return tok.getValue() + children[0].toString();
                    }
            }
            return "("+ tok.getValue() + ")";
        }
    private:
        void assignType(Token t) {
            switch(t.type) {
                case Token::Type::DIV:
                case Token::Type::MULT:
                case Token::Type::MINUS:
                case Token::Type::PLUS:
                    op = Operation::BINARY;
                    break;
                default:
                    op = Operation::LITERAL;
                    break;
            }
        }

};
// //Generic Expression Class (Produces a value)
// class Expression : public Node {
//     public:
//         Expression(Token t) : Node(t) {};
// };

// //Generic Statement Class
// class Statement : public Node {
//     public:
//         Statement(Token t) : Node(t) {};
// };
// /*
// LITERALS
// */
// class LiteralNode : public Expression {
//     public: 
//         LiteralNode(Token t) : Expression(t) {};
// };
// /*
// NUMBERS
// */
// class NumberNode : public LiteralNode {
//     public:
//         NumberNode(Token t) : LiteralNode(t) {};
// };

// class IntegerLiteral : public NumberNode {
//     public:
//         int value = 0;
//         IntegerLiteral(Token t) : NumberNode(t) {
//             value = std::stoi(t.getValue());
//         };
// };

// class DoubleLiteral : public NumberNode {
//     public:
//         double value = 0.0f;
//         DoubleLiteral(Token t) : NumberNode(t) {
//             value = std::stod(t.getValue());
//         };
// };

// /*
// Operators
// */
// class Operator : public Expression {
//     public:
//         Operator(Token t) : Expression(t) {}
// };

// class BinaryOpNode : public Operator {
//     Node left;
//     Node right;
//     public:
//         BinaryOpNode(Node left, Token op, Node right) 
//         : Operator(op), left(left), right(right) {};
// };

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