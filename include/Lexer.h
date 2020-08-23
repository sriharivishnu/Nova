#include<string>
#include<vector>
#include<Token.h>
#ifndef LEXER_CLASS
#define LEXER_CLASS
    class Lexer {
        public:
            Lexer(std::string _text);
            std::vector<Token> getTokens();
            Token advance();  
            std::string text;
            bool isNumber(char c);
            bool isIdentifier(char c);
            bool isSpace(char c);
            Token makeNumber();
            Token makeIdentifier();

            const char* cur;
        private:
            char peek() const { return *cur;}
            char get() { return *cur++; }
    };
#endif