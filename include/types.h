#ifndef TYPES_H
#define TYPES_H
#include <variant>
#include <optional>
#include <memory>
#include "Error.h"
#include "Result.h"
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

struct object;
using shared_obj = std::shared_ptr<object>;
#define UNDEFINED_OP throw UndefinedOperationException(getValue().getStringType(), obj->getValue().getStringType());

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
    Result getValue() {
        return value;
    }
    Result value;
};

struct string : object {
    shared_obj addBy(shared_obj obj) override {
        // shared_obj ans;
        // std::visit(overloaded{
        //     [&](std::string& arg) {ans.}
        //     [&](auto arg) {UNDEFINED_OP}
        // }, obj->getValue().getResult());
        UNDEFINED_OP
    }
};
#endif