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
        Type type;
        std::string value;
};
    
#endif