#include "Parser.h"
using namespace std;
Parser::Parser(vector<Token> tokens) : tokens(tokens) {
    addType(Token::Type::IDENTIFIER, std::make_shared<NameParser>());
    addType(Token::Type::INT, std::make_shared<NumberParser>());
    addType(Token::Type::DOUBLE, std::make_shared<NumberParser>());
    addType(Token::Type::LPAREN, std::make_shared<GroupParser>());

    addType(Token::Type::PLUS, std::make_shared<PrefixOperatorParser>(Precedence::PREFIX));
    addType(Token::Type::MINUS, std::make_shared<PrefixOperatorParser>(Precedence::PREFIX));

    addType(Token::Type::PLUS, std::make_shared<BinaryOperatorParser>(Precedence::SUM, false));            
    addType(Token::Type::MINUS, std::make_shared<BinaryOperatorParser>(Precedence::SUM, false));            
    addType(Token::Type::MULT, std::make_shared<BinaryOperatorParser>(Precedence::PRODUCT, false));            
    addType(Token::Type::DIV, std::make_shared<BinaryOperatorParser>(Precedence::PRODUCT, false));    
    addType(Token::Type::CAROT, std::make_shared<BinaryOperatorParser>(Precedence::EXPONENT, true));

    addType(Token::Type::EQUALS, std::make_shared<AssignmentParser>());
};

shared_ptr<Expression> Parser::parse() {
    return parseExpression();
}

shared_ptr<Expression> Parser::parseExpression(int precedence) {
    Token token = consume();
    auto it = mPrefixParsables.find(token.type);
    if (it == mPrefixParsables.end()) {
        if (token.is(Token::Type::END)) throw ParseException(token.startPos, "Unexpected End of File while Parsing");
        throw SyntaxError(token.startPos, "Could not parse: '" + token.getValue() + "'");
    }

    shared_ptr<PrefixParser> prefix = it->second;
    shared_ptr<Expression> left = prefix->parse(*this, token);
    while (precedence < getPrecedence()) {
        token = consume();
        shared_ptr<InfixParser> infix = mInfixParsables[token.type];
        left = infix->parse(*this, left, token);
    }
    return left;
}

shared_ptr<Expression> Parser::parseExpression() {
    return parseExpression(0);
}

shared_ptr<Statement> Parser::parseStatement() {
    // Statement s;
    // Token curToken = lookAhead(0);
    // switch(curToken.type) {
    //     case Token::Type::IF:
    //         if (curToken.type == Token::Type::LPAREN) {
    //             shared_ptr<Expression> expression = parseExpression();
    //             curToken = consume();
    //             if (curToken.type == Token::Type::RPAREN) {
    //                 return stmt();
    //             } else {
    //                 throw SyntaxError(curToken.startPos, "Expected a ')'");
    //             }
    //         } else {
    //             throw SyntaxError(curToken.startPos, "Expected a '('");
    //         }
    //         break;
    //     case Token::Type::LCURL: {
    //             shared_ptr<Statement> block = stmt();
    //             curToken = consume();
    //             if (curToken.type != Token::Type::RCURL) {
    //                 throw SyntaxError(curToken.startPos, "Expected a '}'");
    //             }
    //             return block;
    //             break;
    //         }
    //     default: {
    //         shared_ptr<Expression> expression = parseExpression();
    //         curToken = consume();
    //         if (curToken.type != Token::Type::STMT_END) {
    //             throw SyntaxError(curToken.startPos, "Expected a ';'");
    //         }
    //         return expression;
    //     }
            
    // }
    return make_shared<Statement>();
}

void Parser::addType(Token::Type type, shared_ptr<PrefixParser> prefix) {
    mPrefixParsables[type] = prefix;
}
void Parser::addType(Token::Type type, shared_ptr<InfixParser> prefix) {
    mInfixParsables[type] = prefix;
}

Token Parser::consume() {
    Token start = lookAhead(0);
    mRead.erase(mRead.begin());
    return start;
}
Token Parser::consume(Token::Type expected) {
    Token token = lookAhead(0);
    if (token.type != expected) {
        if (token.is(Token::Type::END)) throw ParseException(token.startPos, "Unexpected EOF while parsing");
        throw ParseException(token.startPos, "Unexpected token: " + token.getValue());
    }
    return consume();
}
Token Parser::lookAhead(int distance)  {
    while (distance >= mRead.size()) {
        mRead.push_back(tokens[cur++]);
    }
    return mRead[distance];
}     

int Parser::getPrecedence()  {
    Token next = lookAhead(0);
    auto it = mInfixParsables.find(next.type);
    if (it != mInfixParsables.end()) {
        return it->second->getPrecedence();
    }
    // std::cout << "TY{" << next.type << "}" << endl;
    return -1;
}

