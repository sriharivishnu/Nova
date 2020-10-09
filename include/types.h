#ifndef TYPES_H
#define TYPES_H
#include <variant>
#include <optional>
#include <memory>
#include <functional>
#include "Statement.h"
#include "Result.h"
#include "Context.h"
struct object;
class statement;
using shared_obj = std::shared_ptr<object>;

struct object {
    object();
    object(Result res);
    virtual shared_obj addBy(const shared_obj& obj);
    virtual shared_obj subBy(const shared_obj& obj);
    virtual shared_obj multBy(const shared_obj& obj);
    virtual shared_obj divBy(const shared_obj& obj);
    virtual shared_obj powBy(const shared_obj& obj);
    virtual shared_obj mod(const shared_obj& obj);
    virtual shared_obj toBool();
    virtual shared_obj gt(const shared_obj& obj);
    virtual shared_obj lt(const shared_obj& obj);
    virtual shared_obj gte(const shared_obj& obj);
    virtual shared_obj lte(const shared_obj& obj);
    virtual shared_obj ee(const shared_obj& obj);
    virtual shared_obj ne(const shared_obj& obj);
    virtual shared_obj band(const shared_obj& obj);
    virtual shared_obj bor(const shared_obj& obj);
    virtual shared_obj bxor(const shared_obj& obj);
    virtual shared_obj lshift(const shared_obj& obj);
    virtual shared_obj rshift(const shared_obj& obj);
    virtual shared_obj index(const shared_obj& obj);
    virtual shared_obj indexUpdate(const shared_obj& index, const shared_obj& newObj);
    virtual shared_obj bnot();
    virtual shared_obj inc();
    virtual shared_obj dec();
    virtual shared_obj prePlus();
    virtual shared_obj preMinus();
    virtual shared_obj preNot();
    virtual shared_obj dot(const std::string& name, const std::vector<shared_obj>& args);
    virtual shared_obj call(Context& context, std::vector<shared_obj> args);
    virtual std::string toString();

    template <typename T>
    T& getValue() {
        return value.getValue<T>();
    }
    virtual ~object() = default;
    Result value;
};

struct null_type : object {
    null_type();
    std::string toString() override;
};

struct integer_type : object {
    integer_type(int val);
    shared_obj addBy(const shared_obj& obj) override;
    shared_obj subBy(const shared_obj& obj) override;
    shared_obj multBy(const shared_obj& obj) override;
    shared_obj divBy(const shared_obj& obj) override;
    shared_obj mod(const shared_obj& obj) override;
    shared_obj powBy(const shared_obj& obj) override;
    shared_obj ee(const shared_obj& obj) override;
    shared_obj ne(const shared_obj& obj) override;
    shared_obj gt(const shared_obj& obj) override;
    shared_obj lt(const shared_obj& obj) override;
    shared_obj gte(const shared_obj& obj) override;
    shared_obj lte(const shared_obj& obj) override;
    shared_obj band(const shared_obj& obj) override;
    shared_obj bor(const shared_obj& obj) override;
    shared_obj bxor(const shared_obj& obj) override;
    shared_obj lshift(const shared_obj& obj) override;
    shared_obj rshift(const shared_obj& obj) override;
    shared_obj bnot() override;
    shared_obj inc() override;
    shared_obj dec() override;
    shared_obj prePlus() override;
    shared_obj preMinus() override;
    shared_obj toBool() override;

    std::string toString() override;

};
        
struct double_type : object {
    double_type(double val);
    shared_obj addBy(const shared_obj& obj) override;
    shared_obj subBy(const shared_obj& obj) override;
    shared_obj multBy(const shared_obj& obj) override;
    shared_obj divBy(const shared_obj& obj) override;
    shared_obj powBy(const shared_obj& obj) override;
    shared_obj inc() override;
    shared_obj dec() override;
    shared_obj toBool() override;
    shared_obj ee(const shared_obj& obj) override;
    shared_obj ne(const shared_obj& obj) override;
    shared_obj gt(const shared_obj& obj) override;
    shared_obj lt(const shared_obj& obj) override;
    shared_obj gte(const shared_obj& obj) override;
    shared_obj lte(const shared_obj& obj) override;

    std::string toString() override;
};

struct string_type : object {
    string_type(std::string val);
    shared_obj addBy(const shared_obj& obj) override;
    shared_obj multBy(const shared_obj& obj) override;
    shared_obj toBool() override;
    std::string toString() override;
    shared_obj index(const shared_obj& obj) override;
    shared_obj dot(const std::string& name, const std::vector<shared_obj>& args) override;
};

struct list_type : object {
    list_type(std::vector<shared_obj> val);
    shared_obj addBy(const shared_obj& obj) override;
    shared_obj multBy(const shared_obj& obj) override;
    shared_obj toBool() override;
    shared_obj index(const shared_obj& obj) override;
    shared_obj indexUpdate(const shared_obj& obj, const shared_obj& newObj) override;
    shared_obj dot(const std::string& name, const std::vector<shared_obj>& args) override;
    std::string toString() override;
};

struct func_type : object {
    func_type (std::string name, std::vector<std::string> params, std::shared_ptr<statement> toRun);
    shared_obj call(Context& context, std::vector<shared_obj> args) override;
    std::string toString() override;
    std::string name;
    std::vector<std::string> params; 
    std::shared_ptr<statement> toRun;
};

using type = std::variant<std::string, int, double, std::vector<std::shared_ptr<object>>, identifier, null>;

struct native_func : object {
    native_func(std::string name_, std::function<std::optional<type>(std::vector<shared_obj>)>  func_, int numParams);
    shared_obj call(Context& context, std::vector<shared_obj> args) override;
    std::string name;
    int numberOfParams = 0;
    std::function<std::optional<type>(std::vector<shared_obj>)> toRun;
};
//struct user_obj : object {
//    std::string name;
//    std::unordered_map<std::string, func_type> member_functions;
//    std::unordered_map<std::string, shared_obj> member_variables;
//    std::vector<std::string> toString() override;
//};
#endif