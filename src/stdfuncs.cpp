//
// Created by Srihari Vishnu on 2020-10-04.
//

#include "stdfuncs.h"
#include <vector>
#include <iostream>
#include "types.h"
void addStdFunctions(const Context& context) {
    context.symbols->addFunction("print", [&](std::vector<shared_obj> arg) {
        std::cout << arg[0]->toString() + "\n";
        return arg[0]->toString();
    }, 1);
}

