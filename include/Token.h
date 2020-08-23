#include <string>

#ifndef TOKEN_CLASS
#define TOKEN_CLASS

class Token {
    public: 
        enum class Type {
            IDENTIFIER,
            INT,
            FLOAT,
            PLUS,
            MINUS,
            MULT,
            DIV,
            LPAREN,
            RPAREN,
            UNKNOWN,
            END
        };
        Token(Type t);
        Token(Type t, std::string value);
        Token(Type t, const char* start, const char* end);
        Token(Type t, const char* start, size_t length);
        
        bool is(Type);
        bool isOneOf(Type, Type);
        template<typename... types>
        bool isOneOf(Type t1, Type t2, types... args) {
            return is(t1) || isOneOf(t2, args...);
        }
        friend std::ostream& operator<<(std::ostream& os, const Token& token) {
            os << std::string("TYPE: <") << token.type << std::string(">");
            if (!token.value.empty()) {
                os << std::string(" Value: ") << token.value;
            }
            return os;
        }
        friend std::ostream& operator<<(std::ostream& os, const Token::Type& obj) {
            os << std::to_string(static_cast<std::underlying_type<Token::Type>::type>(obj));
            return os;
        }
    private:
        Type type;
        std::string value;
};
    
#endif