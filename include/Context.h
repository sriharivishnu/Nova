#ifndef CONTEXT_H
#define CONTEXT_H
#include <string>
#include <memory>
#include "Position.h"
#include "SymbolTable.h"
struct Context;
struct Context {
    Context() {};
    Context(std::string _name, std::shared_ptr<SymbolTable> _symbols) : name(_name), parent(nullptr), symbols(_symbols) {}
    Context(std::string _name, std::shared_ptr<Context> _parent, Position& _entry_pos, std::shared_ptr<SymbolTable> _symbols) 
    : name(_name), entry_pos(_entry_pos), parent(_parent), symbols(_symbols) {}
    std::string name;
    Position entry_pos;
    std::shared_ptr<Context> parent;
    std::shared_ptr<SymbolTable> symbols = nullptr;
};
#endif