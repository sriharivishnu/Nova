#include <vector>
#include "Lexer.h"
#include <string.h>
#include <exception>

/*
LEXER
*/
Lexer::Lexer(std::string fileName, const char* text) {
    cur = text;
    position = Position(0,0,0, fileName, std::string(text));
}

bool Lexer::isIdentifier(char c) {
    if (isdigit(c)) return true;
    if (isalnum(c) || c == '_') return true;
    return false;
}

bool Lexer::isSpace(char c) {
    switch (c) {
        case ' ':
        case '\n':
        case '\t':
        case '\r':
            return true;
        default:
            return false;
    }
    return false;
}
Token Lexer::makeIdentifier() {
    const char* start = cur;
    get();
    while (isIdentifier(peek())) get();
    std::string value(start, cur);
    if (value == "if") return Token(Token::Type::IF, start ,cur, position);
    else if (value == "else") return Token(Token::Type::ELSE, start, cur, position);
    else if (value == "while") return Token(Token::Type::WHILE, start, cur, position);
    else if (value == "for") return Token(Token::Type::FOR, start, cur, position);
    else if (value == "var") return Token(Token::Type::VAR, start, cur, position);
    else if (value == "func") return Token(Token::Type::FUNCTION, start, cur, position);
    else return Token(Token::Type::IDENTIFIER, start, cur, position);
}

Token Lexer::makeNumber() {
    const char* start = cur;
    int dotCount = 0;
    get();
    while (isdigit(peek()) || peek() == '.') {
        if (peek() == '.') dotCount++;
        if (dotCount > 1) break;
        get();
    }
    if (dotCount > 1) throw ParseException(position, "Could not parse expression: " + std::string(start, cur));
    else if (dotCount == 1) return Token(Token::Type::DOUBLE, start, cur, position);
    else return Token(Token::Type::INT, start, cur, position);
}

Token Lexer::advance() {
    while(isSpace(peek())) get();
    switch (peek()) {
        case '\0':
            return Token(Token::Type::END, "FINISHED", 1, position);
        case '+':
            return Token(Token::Type::PLUS, getLast(), position);
        case '-':
            return Token(Token::Type::MINUS, getLast(), position);
        case '*':
            return Token(Token::Type::MULT, getLast(), position);
        case '/':
            return Token(Token::Type::DIV, getLast(), position);
        case '(':
            return Token(Token::Type::LPAREN, getLast(), position);
        case ')':
            return Token(Token::Type::RPAREN, getLast(), position);
        case ';':
            return Token(Token::Type::STMT_END, getLast(), position);
        case '{':
            return Token(Token::Type::LCURL, getLast(), position);
        case '}':
            return Token(Token::Type::RCURL, getLast(), position);
        case '^':
            return Token(Token::Type::CAROT, getLast(), position);
        case '[':
            return Token(Token::Type::LSQUARE, getLast(), position);
        case ']':
            return Token(Token::Type::RSQUARE, getLast(), position);
        case '=':
            return Token(Token::Type::EQUALS, getLast(), position);
        case 'a' ... 'z':
        case 'A' ... 'Z':
        case '_':
            return makeIdentifier();
        case '0' ... '9':
            return makeNumber();
        default:
            throw IllegalCharException(position, std::string("Unknown Character found while parsing: ") += peek());
    }
}

std::vector<Token> Lexer::getTokens() {
    std::vector<Token> tokens;
    Token next = advance();
    while (!next.is(Token::Type::END)) {
        tokens.push_back(next);
        next = advance();
    }
    tokens.push_back(next);
    return tokens;
}
//123.2 1231.123123 123.1
