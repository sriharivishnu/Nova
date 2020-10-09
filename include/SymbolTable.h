#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include <unordered_map>
#include <string>
#include <variant>
#include <memory>
#include <optional>
#include "types.h"
// class function_statement;
struct object;
struct Result;
class identifier;
struct null;
using shared_obj = std::shared_ptr<object>;
using natFun = std::function<std::optional<std::variant<std::string, int, double, std::vector<std::shared_ptr<object>>, identifier, null>>(std::vector<shared_obj>)>;
class SymbolTable {
    public:
        SymbolTable() {}
        SymbolTable(std::shared_ptr<SymbolTable> parent);
        std::shared_ptr<SymbolTable> parent = nullptr;
        bool update(const std::string& name, const shared_obj& value);
        std::optional<shared_obj> get(const std::string& name);
        void set(const std::string& name, shared_obj value);
        void set(const std::string& name, Result val);
        void remove(const std::string& name);
        void addFunction(const std::string& name, const natFun& func, int numParams);
    private:
        std::unordered_map<std::string, shared_obj> symbols;
};
#endif