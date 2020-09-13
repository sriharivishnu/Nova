#ifndef TYPES_H
#define TYPES_H
#include <variant>
#include <optional>
#include <memory>
#include "Error.h"
#include "Result.h"
#include "Interpreter.h"
// template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
// template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

struct object;
using shared_obj = std::shared_ptr<object>;
#define UNDEFINED_OP throw UndefinedOperationException(value.getStringType(), obj->value.getStringType());
#define UNDEFINED_UNARY(NAME) throw UndefinedOperationException(NAME, value.getStringType());
#define MAKE_OBJ(ARG) std::make_shared<object>(Result(ARG));

struct object {
    object(Result res) : value(res) {}
    virtual shared_obj addBy(shared_obj obj) {
        UNDEFINED_OP
    }
    virtual shared_obj subBy(shared_obj obj) {
        UNDEFINED_OP
    }
    virtual shared_obj multBy(shared_obj obj) {
        UNDEFINED_OP
    }
    virtual shared_obj divBy(shared_obj obj) {
        UNDEFINED_OP
    }
    virtual shared_obj powBy(shared_obj obj) {
        UNDEFINED_OP
    }
    virtual int toBool() {
        UNDEFINED_UNARY("Conversion to boolean")
    }
    virtual shared_obj band() {
        UNDEFINED_UNARY("&")
    }
    virtual shared_obj bxor() {
        UNDEFINED_UNARY("xor")
    }
    virtual shared_obj inc() {
        UNDEFINED_UNARY("++")
    }
    virtual shared_obj dec() {
        UNDEFINED_UNARY("--")
    }

    template <typename T>
    T getValue() {
        return value.getValue<T>();
    }
    virtual ~object() = default;
    Result value;
};
struct integer_type : object {
    shared_obj addBy(shared_obj obj) override {
        shared_obj ans = nullptr;
        std::visit(overloaded{
            [&](std::string& arg) {ans = MAKE_OBJ(std::to_string(getValue<int>()).append(arg));},
            [&](int arg) {ans = MAKE_OBJ(getValue<int>() + arg);},
            [&](double arg) {ans = MAKE_OBJ(((double) getValue<int>()) + arg);},
            [&](auto arg) {UNDEFINED_OP}
        }, obj->value.getResult());
        if (ans) return ans;
        UNDEFINED_OP

    }
    shared_obj subBy(shared_obj obj) override {
        shared_obj ans = nullptr;
        std::visit(overloaded{
            [&](int arg) {ans = MAKE_OBJ(getValue<int>() - arg);},
            [&](double arg) {ans = MAKE_OBJ(((double) getValue<int>()) - arg);},
            [&](auto arg) {UNDEFINED_OP}
        }, obj->value.getResult());
        if (ans) return ans;
        UNDEFINED_OP

    }
    shared_obj multBy(shared_obj obj) override {
        shared_obj ans = nullptr;
        std::visit(overloaded{
            [&](std::string& arg) {
                    std::string finalString = arg;
                    for (int i = 0; i < getValue<int>(); i++) {
                        finalString += arg;
                    }
                    ans = MAKE_OBJ(finalString);
                },
            [&](int arg) {ans = MAKE_OBJ(getValue<int>() * arg);},
            [&](double arg) {ans = MAKE_OBJ(((double) getValue<int>()) * arg);},
            [&](auto arg) {UNDEFINED_OP}
        }, obj->value.getResult());
        if (ans) return ans;
        UNDEFINED_OP

    }
    shared_obj divBy(shared_obj obj) override {
        shared_obj ans = nullptr;
        std::visit(overloaded{
            [&](int arg) {ans = MAKE_OBJ(getValue<int>() / arg);},
            [&](double arg) {ans = MAKE_OBJ(((double) getValue<int>()) / arg);},
            [&](auto arg) {UNDEFINED_OP}
        }, obj->value.getResult());
        if (ans) return ans;
        UNDEFINED_OP
    }
    shared_obj powBy(shared_obj obj) override {
        shared_obj ans = nullptr;
        std::visit(overloaded{
            [&](int arg) {ans = MAKE_OBJ((int) pow(getValue<int>(), arg))},
            [&](double arg) {ans = MAKE_OBJ((pow(getValue<int>(), arg)));},
            [&](auto arg) {UNDEFINED_OP}
        }, obj->value.getResult());
        if (ans) return ans;
        UNDEFINED_OP
    }

    shared_obj inc() override {
        return MAKE_OBJ(getValue<int>() + 1);
    }
    shared_obj dec() override {
        return MAKE_OBJ(getValue<int>() - 1);
    }

    int toBool() override {
        return getValue<int>() != 0;
    }

};

struct double_type : object {
    shared_obj addBy(shared_obj obj) override {
        shared_obj ans = nullptr;
        std::visit(overloaded{
            [&](std::string& arg) {ans = MAKE_OBJ(std::to_string(getValue<double>()).append(arg));},
            [&](int arg) {ans = MAKE_OBJ(getValue<double>() + ((double) arg));},
            [&](double arg) {ans = MAKE_OBJ(getValue<double>() + arg);},
            [&](auto arg) {UNDEFINED_OP}
        }, obj->value.getResult());
        if (ans) return ans;
        UNDEFINED_OP

    }
    shared_obj subBy(shared_obj obj) override {
        shared_obj ans = nullptr;
        std::visit(overloaded{
            [&](int arg) {ans = MAKE_OBJ(getValue<double>() - ((double) arg));},
            [&](double arg) {ans = MAKE_OBJ((double) getValue<double>() - arg);},
            [&](auto arg) {UNDEFINED_OP}
        }, obj->value.getResult());
        if (ans) return ans;
        UNDEFINED_OP

    }
    shared_obj multBy(shared_obj obj) override {
        shared_obj ans = nullptr;
        std::visit(overloaded{
            [&](int arg) {ans = MAKE_OBJ(getValue<double>() * ((double) arg));},
            [&](double arg) {ans = MAKE_OBJ((double) getValue<double>() * arg);},
            [&](auto arg) {UNDEFINED_OP}
        }, obj->value.getResult());
        if (ans) return ans;
        UNDEFINED_OP

    }
    shared_obj divBy(shared_obj obj) override {
        shared_obj ans = nullptr;
        std::visit(overloaded{
            [&](int arg) {ans = MAKE_OBJ(getValue<double>() / ((double) arg));},
            [&](double arg) {ans = MAKE_OBJ(getValue<double>() / arg);},
            [&](auto arg) {UNDEFINED_OP}
        }, obj->value.getResult());
        if (ans) return ans;
        UNDEFINED_OP
    }
    shared_obj powBy(shared_obj obj) override {
        shared_obj ans = nullptr;
        std::visit(overloaded{
            [&](int arg) {ans = MAKE_OBJ(pow(getValue<double>(), (double) arg))},
            [&](double arg) {ans = MAKE_OBJ((pow(getValue<double>(), arg)));},
            [&](auto arg) {UNDEFINED_OP}
        }, obj->value.getResult());
        if (ans) return ans;
        UNDEFINED_OP
    }
    int toBool() override {
        return getValue<double>() != 0;
    }

};

struct string_type : object {
    shared_obj addBy(shared_obj obj) override {
        shared_obj ans = nullptr;
        std::visit(overloaded{
            [&](std::string& arg) {ans = MAKE_OBJ(getValue<std::string>().append(arg));},
            [&](int arg) {ans = MAKE_OBJ(getValue<std::string>().append(std::to_string(arg)));},
            [&](double arg) {ans = MAKE_OBJ(getValue<std::string>().append(std::to_string(arg)));},
            [&](auto arg) {UNDEFINED_OP}
        }, obj->value.getResult());
        if (ans) return ans;
        UNDEFINED_OP

    }
    shared_obj multBy(shared_obj obj) override {
        shared_obj ans = nullptr;
        std::visit(overloaded{
            [&](int arg) {
                    std::string finalString = getValue<std::string>();
                    for (int i = 0; i < arg; i++) {
                        finalString += getValue<std::string>();
                    }
                    ans = MAKE_OBJ(finalString);
                },
            [&](auto arg) {UNDEFINED_OP}
        }, obj->value.getResult());
        if (ans) return ans;
        UNDEFINED_OP
    }
    int toBool() override {
        return !getValue<std::string>().empty();
    }
};

#undef MAKE_OBJ
#undef UNDEFINED_OP
#endif