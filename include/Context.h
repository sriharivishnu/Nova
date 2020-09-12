#ifndef CONTEXT_H
#define CONTEXT_H
#include <string>
#include <memory>
#include "Position.h"
#include "SymbolTable.h"
struct Context;
using symbol_table = std::shared_ptr<SymbolTable>;
using func_table = std::shared_ptr<FunctionTable>;
struct Context {
    Context() {};
    Context(std::string _name, symbol_table _symbols, func_table _funcs) : name(_name), parent(nullptr), symbols(_symbols), functions(_funcs) {}
    Context(std::string _name, std::shared_ptr<Context> _parent, Position& _entry_pos, symbol_table _symbols, func_table _funcs) 
    : name(_name), entry_pos(_entry_pos), parent(_parent), symbols(_symbols), functions(_funcs) {}
    std::string name;
    Position entry_pos;
    std::shared_ptr<Context> parent;
    symbol_table symbols = nullptr;
    func_table functions = nullptr;
};
#endif