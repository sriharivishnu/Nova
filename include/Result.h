#ifndef RESULT_H
#define RESULT_H
#include <memory>
#include <variant>
#include <string>
#include "Position.h"
#include "Error.h"
// using std::string;
class TypeException;

using type = std::variant<std::string, int, double>;
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

        operator int() const { 
            return std::visit([&](auto&& arg) {
                using T = std::decay_t<decltype(arg)>;
                if constexpr(std::is_same_v<T, int>) return std::get<int>(mResult);
                else if constexpr(std::is_same_v<T, std::string>) {
                    if (std::get<std::string>(mResult).empty()) {
                        return 1;
                    } else return 0;
                }
                else if constexpr(std::is_same_v<T, double>) {
                    if (std::get<double>(mResult) != 0) return 1; else return 0;
                }
                return 0;
            }, mResult);
        }

    private:
        type mResult;
        template<class T>
        std::string getStringType() {
            if constexpr(std::is_same_v<T, std::string>) return "string";
            else if constexpr(std::is_same_v<T, int>) return "integer";
            else if constexpr(std::is_same_v<T, double>) return "double";
            else return "null";
        }
};
#endif