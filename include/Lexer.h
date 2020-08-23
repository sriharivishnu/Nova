#include<vector>
#include<Token.h>
#ifndef LEXER_CLASS
#define LEXER_CLASS
    class Lexer {
        public:
            Lexer(const char* text);
            std::vector<Token> getTokens();
            Token advance();  
            bool isDigit(char c);
            bool isIdentifier(char c);
            bool isSpace(char c);
            Token makeNumber();
            Token makeIdentifier();

            const char* cur = nullptr;
        private:
            char peek() const { return *cur;}
            char get() { 
                return *cur++; }
    };
#endif