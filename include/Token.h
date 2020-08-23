#include <string>

#ifndef TOKEN_CLASS
#define TOKEN_CLASS

class Token {
    public: 
        enum class Type {
            INT,
            FLOAT,
            PLUS,
            MINUS,
            MULT,
            DIV,
            LPAREN,
            RPAREN
        };
        Token(Type t);
        Token(Type t, std::string value);
        
        bool is(Type);
        bool isOneOf(Type, Type);
        template<typename... types>
        bool isOneOf(Type t1, Type t2, types... args) {
            return is(t1) || isOneOf(t2, args...);
        }
        friend std::ostream& operator<<(std::ostream& os, const Token& token);
        friend std::ostream& operator<<(std::ostream& os, const Token::Type& token);

        Type type;
        std::string value;
};
    
#endif