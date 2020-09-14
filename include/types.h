#ifndef TYPES_H
#define TYPES_H
#include <variant>
#include <optional>
#include <memory>
#include "Result.h"

struct object;
using shared_obj = std::shared_ptr<object>;

struct object {
    object(Result res);
    virtual shared_obj addBy(shared_obj obj);
    virtual shared_obj subBy(shared_obj obj);
    virtual shared_obj multBy(shared_obj obj);
    virtual shared_obj divBy(shared_obj obj);
    virtual shared_obj powBy(shared_obj obj);
    virtual shared_obj toBool();
    virtual shared_obj gt(shared_obj obj);
    virtual shared_obj lt(shared_obj obj);
    virtual shared_obj gte(shared_obj obj);
    virtual shared_obj lte(shared_obj obj);
    virtual shared_obj ee(shared_obj obj);
    virtual shared_obj ne(shared_obj obj);
    virtual shared_obj band();
    virtual shared_obj bxor();
    virtual shared_obj inc();
    virtual shared_obj dec();
    virtual shared_obj prePlus();
    virtual shared_obj preMinus();

    virtual std::string toString();

    template <typename T>
    T getValue() {
        return value.getValue<T>();
    }
    virtual ~object() = default;
    Result value;
};

struct integer_type : object {
    integer_type(int val);
    shared_obj addBy(shared_obj obj) override;
    shared_obj subBy(shared_obj obj) override;
    shared_obj multBy(shared_obj obj) override;
    shared_obj divBy(shared_obj obj) override;
    shared_obj powBy(shared_obj obj) override;
    shared_obj ee(shared_obj obj) override;
    shared_obj ne(shared_obj obj) override;
    shared_obj gt(shared_obj obj) override;
    shared_obj lt(shared_obj obj) override;
    shared_obj gte(shared_obj obj) override;
    shared_obj lte(shared_obj obj) override;
    shared_obj inc() override;
    shared_obj dec() override;
    shared_obj prePlus() override;
    shared_obj preMinus() override;
    shared_obj toBool() override;

    std::string toString() override;

};
        
struct double_type : object {
    double_type(double val);
    shared_obj addBy(shared_obj obj) override;
    shared_obj subBy(shared_obj obj) override;
    shared_obj multBy(shared_obj obj) override;
    shared_obj divBy(shared_obj obj) override;
    shared_obj powBy(shared_obj obj) override;
    shared_obj inc() override;
    shared_obj dec() override;
    shared_obj toBool() override;
    shared_obj ee(shared_obj obj) override;
    shared_obj ne(shared_obj obj) override;
    shared_obj gt(shared_obj obj) override;
    shared_obj lt(shared_obj obj) override;
    shared_obj gte(shared_obj obj) override;
    shared_obj lte(shared_obj obj) override;

    std::string toString() override;
};

struct string_type : object {
    string_type(std::string val);
    shared_obj addBy(shared_obj obj) override;
    shared_obj multBy(shared_obj obj) override;
    shared_obj toBool() override;
    std::string toString() override;

};
#endif