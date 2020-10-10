#include "Parser.h"
#include "iostream"
#include <string>
#include <utility>
using namespace std;
Parser::Parser(vector<Token> tokens) : tokens(std::move(tokens)) {};

#define GET_PARAMS vector<shared_ptr<Expression>> params;\
    if (!lookAhead(0).is(Token::Type::RPAREN)) {\
        params.push_back(parseExpression());\
        while (lookAhead(0).is(Token::Type::COMMA))\
            {\
                consume();\
                params.push_back(parseExpression());\
            }\
    }\
    consume(Token::Type::RPAREN, ", expected ')'");
shared_ptr<Expression> Parser::getPrefixExpression(const Token& tok) {
    switch (tok.type) {
        case Token::Type::BOOL:
        case Token::Type::IDENTIFIER:
            return make_shared<NameExpression>(tok.getValue(), tok);
        case Token::Type::INT:
        case Token::Type::DOUBLE:
            return make_shared<NumberExpression>(tok);
        case Token::Type::STRING:
            return make_shared<StringExpression>(tok);
        case Token::Type::PLUS:
        case Token::Type::MINUS:
        case Token::Type::BNOT:
        case Token::Type::NOT:
        case Token::Type::INC:
        case Token::Type::DEC: {
            shared_ptr<Expression> right = parseExpression(getTokenPrecedence(tok));
            if (tok.isOneOf(Token::Type::INC, Token::Type::DEC) && !right->getToken().is(Token::Type::IDENTIFIER)) {
                throw SyntaxError(right->getToken().startPos, "Expected an identifier");
            }
            return make_shared<PrefixExpression>(tok, right);
        }
        case Token::Type::LPAREN: {
            shared_ptr<Expression> expression = parseExpression();
            consume(Token::Type::RPAREN, ", expected ')'");
            return expression;
        }
        case Token::Type::LSQUARE: {
            vector<shared_ptr<Expression>> items;
            if (!lookAhead(0).is(Token::Type::RSQUARE)) {
                shared_ptr<Expression> item = parseExpression();
                items.push_back(item);
                while (lookAhead(0).is(Token::Type::COMMA)) {
                    consume(Token::Type::COMMA);
                    items.push_back(parseExpression());
                }
            }
            consume(Token::Type::RSQUARE, "expected ']'");
            return make_shared<ListExpression>(tok, items);
        }
        case Token::Type::IF: {
            //IF
            consume(Token::Type::LPAREN, ", expected '(");
            shared_ptr<Expression> condition = parseExpression(Precedence::CONDITION -1 );
            consume(Token::Type::RPAREN, ", expected ')'");
            shared_ptr<Expression> then = parseExpression(Precedence::CONDITION - 1);

            //ELIF
            Token next = consume();
            vector<shared_ptr<Expression>> elif_conditions;
            vector<shared_ptr<Expression>> elif_thens;
            while (next.is(Token::Type::ELIF)) {
                consume(Token::Type::LPAREN, ", expected '(");
                elif_conditions.push_back(parseExpression(Precedence::CONDITION -1 ));
                consume(Token::Type::RPAREN, ", expected ')'");
                elif_thens.push_back(parseExpression(Precedence::CONDITION -1));
                next = consume();
            }

            //ELSE
            if (!next.is(Token::Type::ELSE)) throw SyntaxError(next.startPos, "Unexpected token: " +  next.getValue() + ", expected 'else' or 'elif'");
            shared_ptr<Expression> elseBranch = parseExpression(Precedence::CONDITION - 1);
            return make_shared<ConditionalExpression>(tok, condition, then, elif_conditions, elif_thens, elseBranch);
        }
        case Token::Type::VAR: {
            Token name = consume(Token::Type::IDENTIFIER, ", expected an identifier");
            Token equals = consume(Token::Type::EQUALS, ", expected '='");
            shared_ptr<Expression> right = parseExpression(getTokenPrecedence(equals) - 1);
            return make_shared<AssignmentExpression>(name.getValue(), right, equals);
        }
        case Token::Type::FUNCTION: {
            std::string name;
            bool anonymous = false;
            if (lookAhead(0).is(Token::Type::IDENTIFIER)) name = consume(Token::Type::IDENTIFIER).getValue();
            else {
                name = "anonymous";
                anonymous = true;
            }

            consume(Token::Type::LPAREN, "expected '(' for function definition of " + name);
            vector<std::string> params;
            if (!lookAhead(0).is(Token::Type::RPAREN)) {
                Token p = consume(Token::Type::IDENTIFIER);
                params.push_back(p.getValue());
                while (lookAhead(0).is(Token::Type::COMMA)) {
                    consume();
                    p = consume(Token::Type::IDENTIFIER);
                    params.push_back(p.getValue());
                }
            }
            consume(Token::Type::RPAREN, ", expected ')'");
            shared_ptr<statement> toRun;
            if (lookAhead(0).is(Token::Type::ARROW)) {
                consume(Token::Type::ARROW);
                toRun = make_shared<simple_statement>(parseExpression());
            } else {
                toRun = parseStatement();
            }
            return make_shared<FuncDefExpression>(tok, name, params, toRun, anonymous);
        }
        default:
            if (tok.is(Token::Type::END)) throw ParseException(tok.startPos, "Unexpected End of File while Parsing");
            else if (tok.is(Token::Type::ELIF)) throw SyntaxError(tok.startPos, "'elif' without an 'if' statement");
            else if (tok.is(Token::Type::ELSE)) throw SyntaxError(tok.startPos, "'else' without an 'if' statement");
            else if (tok.is(Token::Type::STMT_END)) throw SyntaxError(tok.startPos, "unexpected end of statement");
            throw SyntaxError(tok.startPos, "Could not parse: '" + tok.getValue() + "'");
    }
}

shared_ptr<Expression> Parser::getInfixExpression(const shared_ptr<Expression>& left, const Token& tok) {
    switch(tok.type) {
        case Token::Type::PLUS:
        case Token::Type::MINUS:
            return make_shared<BinOpExpression>(left, tok, parseExpression(getTokenPrecedence(tok)));
        case Token::Type::MULT:
        case Token::Type::DIV:
        case Token::Type::MOD:
        case Token::Type::LSHIFT:
        case Token::Type::RSHIFT:
            return make_shared<BinOpExpression>(left, tok, parseExpression(getTokenPrecedence(tok)));
        case Token::Type::POWER:
            return make_shared<BinOpExpression>(left, tok, parseExpression(getTokenPrecedence(tok) - 1));
        case Token::Type::BAND:
        case Token::Type::XOR:
        case Token::Type::BOR:
            return make_shared<BinOpExpression>(left, tok, parseExpression(getTokenPrecedence(tok) - 1));
        case Token::Type::EQUALS:
        case Token::Type::PLUS_EQUAL:
        case Token::Type::MINUS_EQUAL:
        case Token::Type::MULT_EQUAL:
        case Token::Type::DIV_EQUAL:
        case Token::Type::MOD_EQUAL: {
            if (left->getToken().is(Token::Type::IDENTIFIER)) {
                shared_ptr<Expression> right = parseExpression(getTokenPrecedence(tok) - 1);
                return make_shared<UpdateExpression>(left->getToken().getValue(), right, tok);
            }
            throw SyntaxError(left->getToken().startPos, "Expected an identifier but instead got " + left->getToken().getValue());
        }
        case Token::Type::INC:
        case Token::Type::DEC:
            if (tok.isOneOf(Token::Type::INC, Token::Type::DEC) && !left->getToken().is(Token::Type::IDENTIFIER)) {
                throw SyntaxError(left->getToken().startPos, "Expected an identifier");
            }
            return make_shared<PostfixExpression>(left, tok);
        case Token::Type::EE:
        case Token::Type::NE:
        case Token::Type::GE:
        case Token::Type::LE:
        case Token::Type::GT:
        case Token::Type::LT:
        case Token::Type::AND:
        case Token::Type::OR: {
            shared_ptr<Expression> right = parseExpression(getTokenPrecedence(tok));
            return make_shared<ComparisonExpression>(left, tok, right);
        }
        case Token::Type::LSQUARE: {
            shared_ptr<Expression> index = parseExpression();
            consume(Token::Type::RSQUARE, ", expected ']'");
            if (lookAhead(0).is(Token::Type::EQUALS)) {
                consume(Token::Type::EQUALS);
                shared_ptr<Expression> newObj = parseExpression();
                return make_shared<ObjectIndexUpdateExpression>(tok, left, index, newObj);
            }
            
            return make_shared<IndexExpression>(left, tok, index);
        }
        case Token::Type::LPAREN: {
            GET_PARAMS
            return make_shared<CallFunctionExpression>(left, tok, params);

        }
        case Token::Type::DOT: {
            Token name = consume(Token::Type::IDENTIFIER, ", expected an member name");
            consume(Token::Type::LPAREN);
            GET_PARAMS
            return make_shared<MemberAccessExpression>(left, name, params);
        }
        default:
            throw UndefinedOperationException(tok.startPos, tok.getValue());
    }
}

shared_ptr<statement> Parser::parse() {
    return parseStatement();
}

shared_ptr<Expression> Parser::parseExpression(int precedence) {
    Token token = consume();
    shared_ptr<Expression> left = getPrefixExpression(token);
    while (precedence < getPrecedence()) {
        token = consume();
        left = getInfixExpression(left, token);
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
        case Token::Type::RETURN: {
            consume();
            if (lookAhead(0).is(Token::Type::STMT_END)) {
                stmt = make_shared<return_statement>();
            }
            else {
                shared_ptr<Expression> toReturn = parseExpression();
                stmt = make_shared<return_statement>(toReturn);
            }
            ENSURE_END
            consume();
            break;
        }
        case Token::Type::CONTINUE: {
            consume();
            stmt = make_shared<continue_statement>();
            break;
        }
        case Token::Type::BREAK: {
            consume();
            stmt = make_shared<break_statement>();
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
        case Token::Type::FOR: {
            consume(Token::Type::FOR);
            Token identifier = consume(Token::Type::IDENTIFIER, ", expected an identifier");
            consume(Token::Type::IN, ", expected 'in'");
            if (lookAhead(0).is(Token::Type::LPAREN)) {
                consume();
                shared_ptr<Expression> start = parseExpression();
                consume(Token::Type::COMMA, ", expected ','");
                shared_ptr<Expression> end = parseExpression();
                shared_ptr<Expression> step = nullptr;
                if (lookAhead(0).is(Token::Type::COMMA)) {
                    consume();
                    step = parseExpression();
                }
                consume(Token::Type::RPAREN, ", expected ')'");
                shared_ptr<statement> toRun = parseStatement();
                stmt = make_shared<for_statement>(identifier, start, end, toRun, step);
            }
            else {
                throw SyntaxError(lookAhead(0).startPos, "Unexpected token in for loop");
            }
            break;
        }
        default: {
            shared_ptr<Expression> expression = parseExpression();
            stmt = make_shared<simple_statement>(expression);
            ENSURE_END
            if (lookAhead(0).is(Token::Type::STMT_END)) consume();
            break;
        }
            
    }
    return stmt;
}

Token Parser::consume() {
    Token start = lookAhead(0);
    mRead.erase(mRead.begin());
    return start;
}
Token Parser::consume(Token::Type expected, const std::string& expectedStr) {
    Token token = lookAhead(0);
    if (token.type != expected) {
        if (token.is(Token::Type::END) && expectedStr.empty()) throw ParseException(token.startPos, "Unexpected EOF while parsing");
        throw SyntaxError(token.startPos, "Unexpected token: " + token.getValue() + expectedStr);
    }
    return consume();
}
Token Parser::lookAhead(unsigned int distance)  {
    while (distance >= mRead.size()) {
        mRead.push_back(tokens[cur++]);
    }
    return mRead[distance];
}     

int Parser::getPrecedence()  {
    Token next = lookAhead(0);
    return getTokenPrecedence(next);
}
#undef GET_PARAMS

