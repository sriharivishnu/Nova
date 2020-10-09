#ifndef RESULT_H
#define RESULT_H
#include <memory>
#include <utility>
#include <variant>
#include <string>
#include <vector>
#include "Position.h"
#include "Error.h"
#include "types.h"
class TypeException;
struct object;
class identifier {
    public:
        identifier() = default;
};
struct null {
    null() = default;
};
using type = std::variant<std::string, int, double, std::vector<std::shared_ptr<object>>, identifier, null>;
struct Result {
    public:
        explicit Result(type a) : mResult(std::move(a)) {};
        type getResult() {return mResult;}
        std::string getStringType() {
            return std::visit([&](auto&& arg) {
                using T = std::decay_t<decltype(arg)>;
                return getStringType<T>();
            }, getResult());
        }

        template<typename T> 
        T getTypeOrThrow(const Position& pos) {
            if (auto i = std::get_if<T>(&mResult)) return *i;
            else {
                std::string r = "Expected type: '" + getStringType<T>() + "', but instead got '" + getStringType() + "'";
                // throw TypeException(pos, r);
                throw std::runtime_error("TYPE EXCEPTION");
            }
        }

        template<typename T> 
        T& getValue() {
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
            else if constexpr(std::is_same_v<T, identifier>) return "function";
            else if constexpr(std::is_same_v<T, std::shared_ptr<object>>) return "object";
            else if constexpr(std::is_same_v<T,std::vector<std::shared_ptr<object>>>) return "list";
            else if constexpr(std::is_same_v<T, null>) return "null";
            else return "unknown";
        }
};
#endif