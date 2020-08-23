#include <vector>
#include "Lexer.h"
#include <string.h>
Lexer::Lexer(const char* text) {
    cur = text;
}

bool Lexer::isIdentifier(char c) {
    if (isDigit(c)) return true;
    switch(c) {
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
        case '_':
            return true;
        default:
            return false;
    }
}

bool Lexer::isDigit(char c) {
    switch(c) {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            return true;
        default:
            return false;
    }
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
    return Token(Token::Type::IDENTIFIER, start, cur);
}

Token Lexer::makeNumber() {
    const char* start = cur;
    int dotCount = 0;
    get();
    while (isDigit(peek()) || peek() == '.') {
        if (peek() == '.') dotCount++;
        if (dotCount > 1) break;
        get();
    }
    if (dotCount > 1) return Token(Token::Type::UNKNOWN, start, cur);
    else if (dotCount == 1) return Token(Token::Type::FLOAT, start, cur);
    else return Token(Token::Type::INT, start, cur);
}

Token Lexer::advance() {
    while(isSpace(peek())) get();
    switch (peek()) {
        case '\0':
            return Token(Token::Type::END, "FINISHED", 1);
        case '+':
            return Token(Token::Type::PLUS, cur++, 1);
        case '-':
            return Token(Token::Type::MINUS, cur++, 1);
        case '*':
            return Token(Token::Type::MULT, cur++, 1);
        case '/':
            return Token(Token::Type::DIV, cur++, 1);
        case '(':
            return Token(Token::Type::LPAREN, cur++, 1);
        case ')':
            return Token(Token::Type::LPAREN, cur++, 1);
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
        case 'g':
        case 'h':
        case 'i':
        case 'j':
        case 'k':
        case 'l':
        case 'm':
        case 'n':
        case 'o':
        case 'p':
        case 'q':
        case 'r':
        case 's':
        case 't':
        case 'u':
        case 'v':
        case 'w':
        case 'x':
        case 'y':
        case 'z':
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
        case 'G':
        case 'H':
        case 'I':
        case 'J':
        case 'K':
        case 'L':
        case 'M':
        case 'O':
        case 'P':
        case 'Q':
        case 'R':
        case 'S':
        case 'T':
        case 'U':
        case 'V':
        case 'W':
        case 'X':
        case 'Y':
        case 'Z':
        case '_':
            return makeIdentifier();
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            return makeNumber();
        default:
            return Token(Token::Type::UNKNOWN, cur++, 1);
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
