#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include <unordered_map>
#include <string>
#include <variant>
#include <memory>
#include <optional>
#include "types.h"
class function_statement;
struct object;
using shared_obj = std::shared_ptr<object>;
using type = std::variant<std::string, int, double, std::vector<std::shared_ptr<object>>>;
class SymbolTable {
    public:
        SymbolTable() {}
        SymbolTable(std::shared_ptr<SymbolTable> parent);
        std::shared_ptr<SymbolTable> parent = nullptr;
        bool update(std::string name, shared_obj value);
        std::optional<shared_obj> get(std::string name);
        void set(std::string name, shared_obj value);
        void set(std::string name, type val);
        void remove(std::string name);
    private:
        std::unordered_map<std::string, shared_obj> symbols;
};

class FunctionTable {
    public:
        FunctionTable() {}
        FunctionTable(std::shared_ptr<FunctionTable> parent);
        std::shared_ptr<FunctionTable> parent = nullptr;
        std::shared_ptr<function_statement> get(std::string name);
        void add(std::string name, std::shared_ptr<function_statement> value);
        void remove(std::string name);
    private:
        std::unordered_map<std::string, std::shared_ptr<function_statement>> funcs;
};
#endif