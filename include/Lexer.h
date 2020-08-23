#include <string> 

#include "vector"
#include "Token.h"
#include "Error.h"
#include "Position.h"

#ifndef LEXER_CLASS
#define LEXER_CLASS
    class Lexer {
        public:
            Lexer(std::string fileName, const char* text);
            std::vector<Token> getTokens();
            std::vector<Error> getErrors();
            Token advance();  
            bool isDigit(char c);
            bool isIdentifier(char c);
            bool isSpace(char c);
            Token makeNumber();
            Token makeIdentifier();            
            const char* cur = nullptr;
        private:
            std::vector<Error> errors;
            Position position {0,0,0};
            char peek() const { return *cur;}
            char get() { 
                position.advance(*cur++);
                return *cur; 
            }
            char getLast() {
                char a = *cur;
                get();
                return a;
            }
    };
#endif