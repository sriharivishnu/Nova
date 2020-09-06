#ifndef RESULT_H
#define RESULT_H
#include <memory>
#include <variant>
#include <string>
#include "Position.h"
#include "Error.h"
// using std::string;
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
//     else return "";
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

class Node {
    virtual void eval();
};
#endif