#include "Token.h"
#include <vector>
#ifndef PARSER_CLASS
#define PARSER_CLASS
class Node {
    public:
        Node(Token t) : tok(t) {};
        Token tok; 
};
class NumberNode : public Node {
    public:
        NumberNode(Token t) : Node(t) {};
};
class IntNode : public NumberNode {
    public:
        int value = 0;
        IntNode(Token t) : NumberNode(t) {
            value = std::stoi(t.getValue());
        };
};
class DoubleNode : public NumberNode {
    public:
        double value = 0.0f;
        DoubleNode(Token t) : NumberNode(t) {
            value = std::stod(t.getValue());
        }
};
class BinaryOpNode : public Node {
    Node leftNode;
    Node rightNode;
    public:
        BinaryOpNode(Node leftNode, Token op, Node rightNode) : Node(op), leftNode(leftNode), rightNode(rightNode) {
        }
};
class Parser {
    public:
        std::vector<Token> tokens;
        int cur;
        Token curToken {Token::Type::UNKNOWN, ""};

        Parser() { cur = 0; }
        
        Token next();

        NumberNode factor();

        BinaryOpNode term();
};
#endif