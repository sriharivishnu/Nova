#ifndef __TYPES_DEFINE__
#define __TYPES_DEFINE__
#include "Error.h"
#include <any>
#include <optional>
#include <variant>
enum struct types {
    INT,
    FLOAT,
    STRING, 
    UNDEF
};
class Object {
    public:
        Error error;
        types type = types::UNDEF;
        bool isError = false;
        virtual std::optional<std::any> getValue() {
            return {};
        }
        virtual types getType() {
            return type;
        }
        virtual Object addedTo(Object other) {
            Object result = Object(UndefinedOperationException(getStringType(getType()), getStringType(other.getType())));
            return result;
        }
        virtual Object subbedBy(Object other) {
            Object result = Object(UndefinedOperationException(getStringType(getType()), getStringType(other.getType())));
            return result;
        }
        virtual Object multBy(Object other) {
            Object result = Object(UndefinedOperationException(getStringType(getType()), getStringType(other.getType())));
            return result;
        }
        virtual Object divBy(Object other) {
            Object result = Object(UndefinedOperationException(getStringType(getType()), getStringType(other.getType())));
            return result;
        }
        
        Object(types t) : type(t) {};
        Object(Error e) : error(e) {isError = true;};
    private:
        std::string getStringType(types t) {
            switch(t) {
                case types::INT:
                    return "Int";
                case types::FLOAT:
                    return "Float";
                case types::STRING:
                    return "String";
                default:
                    return "Unknown Type";
            }
        }
};

class Number : public Object {
    public:
        int value;
        Number(int val) : Object(types::INT), value(val) {};
        std::optional<std::any> getValue() override {
            return value;
        }
        // Number(double a) {};
        Number addedTo(Number other) {
            return Number(this->value + other.value);
        }
        Number subbedBy(Number other) {
            return Number(this->value - other.value);
        }
        Number multBy(Number other) {
            return Number(this->value * other.value);
        }
        Number divBy(Number other) {
            return Number(this->value / other.value);
        }

        friend const std::ostream& operator<<(std::ostream& os, Number& n) {
            os << std::to_string(n.value);
            return os;
        } 
};
#endif