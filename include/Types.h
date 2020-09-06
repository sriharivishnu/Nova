#ifndef __TYPES_DEFINE__
#define __TYPES_DEFINE__
#include "Error.h"
#include <any>
#include <optional>
#include <variant>
using std::string;
// using type = std::variant<string, int, double, bool>;
// struct Result {
//     type getResult() {return mResult;}
//     private:
//         type mResult;
// };

// template<typename T> 
// std::string getStringType() {
//     if constexpr(std::is_same_v<T, std::string>) return "string";
//     else if constexpr(std::is_same_v<T, int>) return "integer";
//     else if constexpr(std::is_same_v<T, bool>) return "boolean";
//     else if constexpr(std::is_same_v<T, double>) return "double";
//     else return "null";
// }

// std::string getStringType(type a) {
//     return std::visit([&](auto&& arg) {
//         using T = std::decay_t<decltype(arg)>;
//         return getStringType<T>();
//     }, a);
// }
// template<typename T> 
// T getTypeOrThrow(Result r1) {
//     if (auto i = std::get_if<T>(r1.getResult())) return *i;
//     else {
//         throw TypeException("Expected type: '" + getStringType<T>() + "', but instead got '" + getStringType(r1.getResult()) + "'");
//     }
// }
// template<typename T>
// bool isType(Result var) {
//     if (auto i = std::get_if<T>(var.getResult())) return true;
//     else return false;
// }
// class Object {
//     public:
//         virtual std::optional<Result> getValue() {
//             return {};
//         }
//         std::string getType() {
//             return getStringType(mResult.getResult());
//         }
//         virtual Object addedTo(shared_ptr<Object> other) {
//             throw UndefinedOperationException(getType(), other->getType());
//         }
//         virtual Object subbedBy(shared_ptr<Object> other) {
//             throw UndefinedOperationException(getType(), other->getType());
//         }
//         virtual Object multBy(shared_ptr<Object> other) {
//             throw UndefinedOperationException(getType(), other->getType());
//         }
//         virtual Object divBy(shared_ptr<Object> other) {
//             throw UndefinedOperationException(getType(), other->getType());
//         }
//     protected:
//         Result mResult;
// };

// class Number : public Object {
//     public:
//         int value;
//         std::optional<std::any> getValue() override {
//             return value;
//         }
//         // Number(double a) {};
//         Number addedTo(shared_ptr<Number> other) override {
//             return Number(this->value + other.value);
//         }
//         Number subbedBy(Number other) {
//             return Number(this->value - other.value);
//         }
//         Number multBy(Number other) {
//             return Number(this->value * other.value);
//         }
//         Number divBy(Number other) {
//             return Number(this->value / other.value);
//         }

//         friend const std::ostream& operator<<(std::ostream& os, Number& n) {
//             os << std::to_string(n.value);
//             return os;
//         } 
// };
#endif