#include <vector>
#include "Lexer.h"

Lexer::Lexer(std::string _text) {
    this->text = _text;
    cur = text.c_str();
}

bool Lexer::isIdentifier(char c) {
    if (isNumber(c)) return true;
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

bool Lexer::isNumber(char c) {
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

Token Lexer::advance() {
    while(isSpace(peek())) get();
    switch (peek()) {
        case '\0':
            return Token(Token::Type::END);
        case '+':
            return Token(Token::Type::PLUS);
        case '-':
            return Token(Token::Type::MINUS);
        case '*':
            return Token(Token::Type::MULT);
        case '/':
            return Token(Token::Type::DIV);
        case '(':
            return Token(Token::Type::LPAREN);
        case ')':
            return Token(Token::Type::LPAREN);
        default:
            return Token(Token::Type::UNKNOWN);
    }
}
std::vector<Token> Lexer::getTokens() {
    std::vector<Token> tokens;
    Token next = advance();
    while (next.type != Token::Type::END && next.type != Token::Type::UNKNOWN) {
        tokens.push_back(next);
        next = advance();
    }
}
