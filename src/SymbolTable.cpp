#include "SymbolTable.h"

#include <utility>
#include "Statement.h"
SymbolTable::SymbolTable(std::shared_ptr<SymbolTable> parent) : parent(std::move(parent)) {}
std::optional<shared_obj> SymbolTable::get(const std::string& name) {
    auto it = symbols.find(name);
    if (it != symbols.end()) return it->second;
    else if (it == symbols.end() && parent) {
        return parent->get(name);
    }
    return {};
}

void SymbolTable::set(const std::string& name, shared_obj value) {
    symbols[name] = std::move(value);
}

void SymbolTable::set(const std::string& name, Result val) {
    symbols[name] = std::make_shared<object>(val);
}

bool SymbolTable::update(const std::string& name, const shared_obj& value) {
    if (symbols.find(name) != symbols.end()) {
        set(name, value);
        return true;
    }
    else if (parent) {
        return parent->update(name, value);
    }
    return false;
}

void SymbolTable::remove(const std::string& name) {
    symbols.erase(name);
}
using type = std::variant<std::string, int, double, std::vector<std::shared_ptr<object>>, identifier, null>;

void SymbolTable::addFunction(const std::string& name, const natFun& func, int numParams) {
    shared_obj t = make_shared<native_func>(name, func, numParams);
    set(name, t);
}
