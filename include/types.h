#ifndef TYPES_H
#define TYPES_H
#include <variant>
#include <optional>
#include <memory>
#include "Statement.h"
#include "Result.h"
#include "Context.h"
// class function_statement;
struct object;
class statement;
using shared_obj = std::shared_ptr<object>;

struct object {
    object();
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
    virtual shared_obj band(shared_obj obj);
    virtual shared_obj bor(shared_obj obj);
    virtual shared_obj bxor(shared_obj obj);
    virtual shared_obj index(shared_obj obj);
    virtual shared_obj inc();
    virtual shared_obj dec();
    virtual shared_obj prePlus();
    virtual shared_obj preMinus();
    virtual shared_obj preNot();
    virtual shared_obj dot(const std::string& name, const std::vector<shared_obj>& args);
    virtual shared_obj call(Context& context, std::vector<shared_obj> args);
    virtual std::string toString();

    template <typename T>
    T getValue() {
        return value.getValue<T>();
    }
    virtual ~object() = default;
    Result value;
};

struct null_type : object {
    std::string toString() override;
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
    shared_obj band(shared_obj obj) override;
    shared_obj bor(shared_obj obj) override;
    shared_obj bxor(shared_obj obj) override;
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
    shared_obj index(shared_obj obj) override;
    shared_obj dot(const std::string& name, const std::vector<shared_obj>& args) override;
};

struct list_type : object {
    list_type(std::vector<shared_obj> val);
    shared_obj addBy(shared_obj obj) override;
    shared_obj multBy(shared_obj obj) override;
    shared_obj toBool() override;
    shared_obj index(shared_obj obj) override;
    std::string toString() override;
};

struct func_type : object {
    func_type (std::string name, std::vector<std::string> params, std::shared_ptr<statement> toRun);
    shared_obj call(Context& context, std::vector<shared_obj> args) override;
    std::string toString() override;
    std::string name;
    std::vector<std::string> params; 
    std::shared_ptr<statement> toRun;
    bool anonymous = false;
};

//struct user_obj : object {
//    std::string name;
//    std::unordered_map<std::string, func_type> member_functions;
//    std::unordered_map<std::string, shared_obj> member_variables;
//    std::vector<std::string> toString() override;
//};
#endif