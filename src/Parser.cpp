#include "Parser.h"
#include "iostream"
#include <string>
using namespace std;
Parser::Parser(vector<Token> tokens) : tokens(tokens) {
    addType(Token::Type::IDENTIFIER, std::make_shared<NameParser>());
    addType(Token::Type::INT, std::make_shared<NumberParser>());
    addType(Token::Type::DOUBLE, std::make_shared<NumberParser>());
    addType(Token::Type::STRING, std::make_shared<StringParser>());
    addType(Token::Type::BOOL, std::make_shared<NameParser>());
    addType(Token::Type::LPAREN, std::make_shared<GroupParser>());
    addType(Token::Type::LSQUARE, std::make_shared<ListParser>());

    addType(Token::Type::PLUS, std::make_shared<PrefixOperatorParser>(Precedence::PREFIX));
    addType(Token::Type::MINUS, std::make_shared<PrefixOperatorParser>(Precedence::PREFIX));
    addType(Token::Type::NOT, std::make_shared<PrefixOperatorParser>(Precedence::PREFIX));
    addType(Token::Type::BNOT, std::make_shared<PrefixOperatorParser>(Precedence::PREFIX));

    addType(Token::Type::INC, std::make_shared<PrefixOperatorParser>(Precedence::PREFIX));
    addType(Token::Type::DEC, std::make_shared<PrefixOperatorParser>(Precedence::PREFIX));

    addType(Token::Type::PLUS, std::make_shared<BinaryOperatorParser>(Precedence::SUM, false));            
    addType(Token::Type::MINUS, std::make_shared<BinaryOperatorParser>(Precedence::SUM, false));            
    addType(Token::Type::MULT, std::make_shared<BinaryOperatorParser>(Precedence::PRODUCT, false));            
    addType(Token::Type::DIV, std::make_shared<BinaryOperatorParser>(Precedence::PRODUCT, false));    
    addType(Token::Type::POWER, std::make_shared<BinaryOperatorParser>(Precedence::EXPONENT, true));
    addType(Token::Type::BAND, std::make_shared<BinaryOperatorParser>(Precedence::SUM, true));
    addType(Token::Type::XOR, std::make_shared<BinaryOperatorParser>(Precedence::SUM, true));
    addType(Token::Type::BOR, std::make_shared<BinaryOperatorParser>(Precedence::SUM, true));

    addType(Token::Type::VAR, std::make_shared<AssignmentParser>());
    addType(Token::Type::EQUALS, std::make_shared<UpdateOrAssignParser>());
    addType(Token::Type::INC, std::make_shared<PostfixOperatorParser>(Precedence::POSTFIX));
    addType(Token::Type::DEC, std::make_shared<PostfixOperatorParser>(Precedence::POSTFIX));

    addType(Token::Type::EE, std::make_shared<ComparisonParser>());
    addType(Token::Type::NE, std::make_shared<ComparisonParser>());
    addType(Token::Type::GE, std::make_shared<ComparisonParser>());
    addType(Token::Type::LE, std::make_shared<ComparisonParser>());
    addType(Token::Type::GT, std::make_shared<ComparisonParser>());
    addType(Token::Type::LT, std::make_shared<ComparisonParser>());
    addType(Token::Type::AND, std::make_shared<ComparisonParser>());
    addType(Token::Type::OR, std::make_shared<ComparisonParser>());

    addType(Token::Type::IF, std::make_shared<ConditionalParser>());

    addType(Token::Type::FUNCTION, std::make_shared<FuncDefParser>());
};

shared_ptr<statement> Parser::parse() {
    return parseStatement();
}

shared_ptr<Expression> Parser::parseExpression(int precedence) {
    Token token = consume();
    auto it = mPrefixParsables.find(token.type);
    if (it == mPrefixParsables.end()) {
        if (token.is(Token::Type::END)) throw ParseException(token.startPos, "Unexpected End of File while Parsing");
        else if (token.is(Token::Type::ELIF)) throw SyntaxError(token.startPos, "'elif' without an 'if' statement");
        else if (token.is(Token::Type::ELSE)) throw SyntaxError(token.startPos, "'else' without an 'if' statement");
        else if (token.is(Token::Type::STMT_END)) throw SyntaxError(token.startPos, "unexpected end of statement");
        throw SyntaxError(token.startPos, "Could not parse: '" + token.getValue() + "'");
    }

    shared_ptr<PrefixParser> prefix = it->second;
    shared_ptr<Expression> left = prefix->parse(*this, token);
    while (precedence < getPrecedence()) {
        token = consume();
        auto it2 = mInfixParsables.find(token.type);
        if (it2 == mInfixParsables.end()) throw UndefinedOperationException(token.startPos, token.getValue());
        shared_ptr<InfixParser> infix = it2->second;
        left = infix->parse(*this, left, token);
    }
    return left;
}

shared_ptr<Expression> Parser::parseExpression() {
    return parseExpression(0);
}

#define ENSURE_END if (!lookAhead(0).isOneOf(Token::Type::STMT_END, Token::Type::END)\
        && !lookAhead(0).is(Token::Type::RCURL)) {\
        throw SyntaxError(lookAhead(0).startPos, "Expected end of statement, instead got '"+lookAhead(0).getValue() + "'");\
    }

shared_ptr<statement> Parser::parseStatement() {
    Token curToken = lookAhead(0);
    shared_ptr<statement> stmt = make_shared<statement>();
    switch(curToken.type) {
        case Token::Type::IF: {
                consume();
                consume(Token::Type::LPAREN, ", expected a '('");
                shared_ptr<Expression> ifCondition = parseExpression();
                consume(Token::Type::RPAREN, ", expected a ')'");
                shared_ptr<statement> ifBlock = parseStatement();
                vector<shared_ptr<Expression>> elifConditions;
                vector<shared_ptr<statement>> elifBlocks;
                while (lookAhead(0).is(Token::Type::ELIF)) {
                    consume();
                    consume(Token::Type::LPAREN, ", expected a '('");
                    elifConditions.push_back(parseExpression());
                    consume(Token::Type::RPAREN, ", expected a ')'");
                    elifBlocks.push_back(parseStatement());
                }
                shared_ptr<statement> elseBlock = nullptr;
                if (lookAhead(0).is(Token::Type::ELSE)) {
                    consume();
                    elseBlock = parseStatement();
                }

                stmt = make_shared<if_statement>(ifCondition, ifBlock, elifConditions, elifBlocks, elseBlock);
                break;
            }
        case Token::Type::STMT_END:
            consume();
            return nullptr;
        case Token::Type::LCURL: {
                consume(Token::Type::LCURL);
                vector<shared_ptr<statement>> statements;
                while (!lookAhead(0).isOneOf(Token::Type::RCURL, Token::Type::END)) {
                    shared_ptr<statement> s = parseStatement();
                    if (s) statements.push_back(s);
                }
                consume(Token::Type::RCURL, ", expected a '}'");
                stmt = make_shared<block_statement>(statements);
                break;
            }
        case Token::Type::WHILE: {
            consume(Token::Type::WHILE);
            consume(Token::Type::LPAREN, ", expected a '('");
            shared_ptr<Expression> condition = parseExpression();
            consume(Token::Type::RPAREN, ", expected a ')'");
            shared_ptr<statement> statement = parseStatement();
            stmt = make_shared<while_statement>(condition, statement);
            break;
        }
            
        default: {
            shared_ptr<Expression> expression = parseExpression();
            stmt = make_shared<simple_statement>(expression);
            ENSURE_END
            break;
        }
            
    }
    return stmt;
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
Token Parser::consume(Token::Type expected, std::string expectedStr) {
    Token token = lookAhead(0);
    if (token.type != expected) {
        if (token.is(Token::Type::END) && expectedStr.empty()) throw ParseException(token.startPos, "Unexpected EOF while parsing");
        throw SyntaxError(token.startPos, "Unexpected token: " + token.getValue() + expectedStr);
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

