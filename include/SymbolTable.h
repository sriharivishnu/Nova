#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include <unordered_map>
#include <string>
#include <variant>
#include <optional>
using type = std::variant<std::string, int, double, bool>;
class SymbolTable {
    public:
        SymbolTable() {}
        SymbolTable* parent = nullptr;
        std::optional<type> get(std::string name) {
            auto it = symbols.find(name);
            if (it != symbols.end()) return it->second;
            else if (it == symbols.end() && parent) {
                return parent->get(name);
            }
            return {};
        }
        void set(std::string name, type value) {
            symbols[name] = value;
        }
        void remove(std::string name) {
            symbols.erase(name);
        }
    private:
        std::unordered_map<std::string, type> symbols;
};
#endif