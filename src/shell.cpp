#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include "nova.h"
int main() {
    std::string command;
    std::shared_ptr<SymbolTable> symbols = std::make_shared<SymbolTable>();
    symbols->set("false", 0);
    symbols->set("true", 1);
    Context global("<main>", symbols);
    while (true) {
        std::cout << "nova>> ";
        std::getline(std::cin, command);
        nova::run(command, global);
    }
    return 0;
}