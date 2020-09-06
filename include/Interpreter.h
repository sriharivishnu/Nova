#ifndef INTERPRETER_CLASS
#define INTERPRETER_CLASS
#include <string>
#include <math.h>
#include <memory>
#include <variant>
#include "Expression.h"
#include "Types.h"
#include "Error.h"
#include "Token.h"
using std::string;
using type = std::variant<string, int, double, bool>;
struct Result {
    public:
        Result(type a) : mResult(a) {};
        type getResult() {return mResult;}
        std::string getStringType() {
            return std::visit([&](auto&& arg) {
                using T = std::decay_t<decltype(arg)>;
                return getStringType<T>();
            }, getResult());
        }

        template<typename T> 
        T getTypeOrThrow(Position pos) {
            if (auto i = std::get_if<T>(&mResult)) return *i;
            else {
                std::string r = "Expected type: '" + getStringType<T>() + "', but instead got '" + getStringType() + "'";
                throw TypeException(pos, r);
            }
        }

        template<typename T> 
        T getValue() {
            return std::get<T>(mResult);
        }

        template<typename T>
        bool isType() {
            if (auto i = std::get_if<T>(&mResult)) return true;
            else return false;
        }

    private:
        type mResult;
        template<class T>
        std::string getStringType() {
            if constexpr(std::is_same_v<T, std::string>) return "string";
            else if constexpr(std::is_same_v<T, int>) return "integer";
            else if constexpr(std::is_same_v<T, bool>) return "boolean";
            else if constexpr(std::is_same_v<T, double>) return "double";
            else return "null";
        }
};

class Interpreter {
    // public:
    //     Object visit(std::shared_ptr<Expression> n);
};
class OperatorExpression;
class NumberExpression;
class Expression;
class Visitor {
    public:
        Result visit(OperatorExpression* e);
        Result visit(NumberExpression* e);
        Result visit(Expression* e);
    private:
};

// template<class T> 
// class Value {
//     public:
//         virtual Value<T> addBy(Value<T> other) {
//             throw UndefinedOperationException(other.toString());
//         }
//         virtual Value<T> subBy(Value<T> other) {
//             throw UndefinedOperationException(other.toString());
//         }
//         virtual Value<T> multBy(Value<T> other) {
//             throw UndefinedOperationException(other.toString());
//         }
//         virtual Value<T> divBy(Value<T> other) {
//             throw UndefinedOperationException(other.toString());
//         }
//         virtual std::string toString() {
//             return "";
//         }
//         virtual T eval() {
//             return mValue;
//         };
//     protected:
//         T mValue;
// };

// class IntLiteral : public Value<int> {
//     public:
//         IntLiteral(int n) {
//             mValue = n;
//         }
//         Value<int> addBy(Value<int> other) override {
//             return IntLiteral(eval() + other.eval());
//         }
//         Value<int> subBy(Value<int> other) override {
//             return IntLiteral(eval() - other.eval());
//         }
//         Value<int> multBy(Value<int> other) override {
//             return IntLiteral(eval() * other.eval());
//         }
//         Value<int> divBy(Value<int> other) override {
//             return IntLiteral(eval() / other.eval());
//         }
// };

    
// };
#endif