#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include "nova.h"
int main() {
    std::string command;
    Context context("<main>", std::make_shared<SymbolTable>());
    while (true) {
        std::cout << "nova>> ";
        std::getline(std::cin, command);
        nova::run(command, context);
    }
    return 0;
}