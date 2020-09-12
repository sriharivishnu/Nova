#include "SymbolTable.h"
#include "Statement.h"
SymbolTable::SymbolTable(std::shared_ptr<SymbolTable> parent) : parent(parent) {}
std::optional<type> SymbolTable::get(std::string name) {
    auto it = symbols.find(name);
    if (it != symbols.end()) return it->second;
    else if (it == symbols.end() && parent) {
        return parent->get(name);
    }
    return {};
}

void SymbolTable::set(std::string name, type value) {
    symbols[name] = value;
}

void SymbolTable::remove(std::string name) {
    symbols.erase(name);
}

FunctionTable::FunctionTable(std::shared_ptr<FunctionTable> parent) : parent(parent) {}

std::shared_ptr<function_statement> FunctionTable::get(std::string name) {
    auto it = funcs.find(name);
    if (it != funcs.end()) return it->second;
    else if (it == funcs.end() && parent) {
        return parent->get(name);
    }
    return nullptr;
}

void FunctionTable::add(std::string name, std::shared_ptr<function_statement> value) {
    funcs[name] = value;
}

void FunctionTable::remove(std::string name) {
    funcs.erase(name);
}