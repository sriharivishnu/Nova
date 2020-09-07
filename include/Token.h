#ifndef TOKEN_CLASS
#define TOKEN_CLASS
#include <string>
#include <Position.h>
#include <vector>

class Token {
    public: 
        enum class Type {
            UNKNOWN,
            IDENTIFIER,
            INT,
            DOUBLE,
            BOOL,
            STRING,
            PLUS,
            MINUS,
            MULT,
            DIV,
            EQUALS,
            PLUS_EQUAL,
            MINUS_EQUAL,
            MULT_EQUAL,
            DIV_EQUAL,
            INC,
            DEC,
            LPAREN,
            RPAREN,
            LCURL,
            RCURL,
            CAROT,
            QUESTION,
            LSQUARE,
            RSQUARE,
            IF,
            ELIF,
            ELSE,
            WHILE,
            FOR,
            VAR,
            STMT_END,
            FUNCTION,
            NOT, //!
            EE, //==
            NE, //!=
            LE, //<=
            GE, //>=
            GT, //>
            LT, //<
            END
        };
        Token() {};
        Token(Type t, Position pos);
        Token(Type t, std::string value, Position pos);
        Token(Type t, char value, Position pos);
        Token(Type t, const char* start, const char* end, Position pos);
        Token(Type t, const char* start, size_t length, Position pos);
        
        std::string getValue();
        bool is(Type);
        bool isOneOf(Type, Type);
        template<typename... types>
        bool isOneOf(Type t1, Type t2, types... args) {
            return is(t1) || isOneOf(t2, args...);
        }
        bool isOneOf(std::vector<Type> vec) {
            for (int i = 0; i < vec.size() ; i++) {if (vec[i] == type) return true;}
            return false;
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
        Type type;
        Position startPos;
    private:
        std::string value;
};
    
#endif