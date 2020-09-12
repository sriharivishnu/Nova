#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include <unordered_map>
#include <string>
#include <variant>
#include <memory>
#include <optional>
class function_statement;

using type = std::variant<std::string, int, double>;
class SymbolTable {
    public:
        SymbolTable() {}
        SymbolTable(std::shared_ptr<SymbolTable> parent);
        std::shared_ptr<SymbolTable> parent = nullptr;
        std::optional<type> get(std::string name);
        void set(std::string name, type value);
        void remove(std::string name);
    private:
        std::unordered_map<std::string, type> symbols;
};

class FunctionTable {
    public:
        FunctionTable() {}
        FunctionTable(std::shared_ptr<FunctionTable> parent);
        std::shared_ptr<FunctionTable> parent = nullptr;
        function_statement* get(std::string name);
        void add(std::string name, function_statement* value);
        void remove(std::string name);
    private:
        std::unordered_map<std::string, function_statement*> funcs;
};
#endif