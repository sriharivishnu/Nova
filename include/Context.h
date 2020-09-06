#ifndef CONTEXT_H
#define CONTEXT_H
#include <string>
#include <memory>
#include "Position.h"
struct Context;
struct Context {
    Context() {};
    Context(std::string _name) : name(_name), parent(nullptr) {}
    Context(std::string _name, std::shared_ptr<Context> _parent, Position& _entry_pos) 
    : name(_name), entry_pos(_entry_pos), parent(_parent) {}
    std::string name;
    Position entry_pos;
    std::shared_ptr<Context> parent;
};
#endif