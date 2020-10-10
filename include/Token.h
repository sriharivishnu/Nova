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
            MOD,
            EQUALS,
            PLUS_EQUAL,
            MINUS_EQUAL,
            MULT_EQUAL,
            DIV_EQUAL,
            MOD_EQUAL,
            DOT,
            INC,
            DEC,
            LPAREN,
            RPAREN,
            LCURL,
            RCURL,
            POWER,
            EXIT,
            QUESTION,
            LSQUARE,
            RSQUARE,
            IF,
            ELIF,
            ELSE,
            WHILE,
            FOR,
            IN,
            COLON,//:
            VAR,
            STMT_END,
            FUNCTION,
            RETURN,
            CONTINUE,
            BREAK,
            ARROW, //->
            COMMA, //,
            NOT, //!
            EE, //==
            NE, //!=
            LE, //<=
            GE, //>=
            GT, //>
            LT, //<
            AND, 
            BAND,
            OR,
            BOR,
            XOR,
            BNOT,
            LSHIFT,
            RSHIFT,
            END
        };
        Token() = default;;
        Token(Type t, Position pos);
        Token(Type t, std::string value, Position pos);
        Token(Type t, char value, Position pos);
        Token(Type t, const char* start, const char* end, Position pos);
        Token(Type t, const char* start, size_t length, Position pos);
        
        [[nodiscard]] std::string getValue() const;
        [[nodiscard]] bool is(Type) const;
        [[nodiscard]] bool isOneOf(Type, Type) const;
        template<typename... types>
        bool isOneOf(Type t1, Type t2, types... args) const {
            return is(t1) || isOneOf(t2, args...);
        }
        [[nodiscard]] bool isOneOf(std::vector<Type> vec) const {
            for (auto & i : vec) {if (i == type) return true;}
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