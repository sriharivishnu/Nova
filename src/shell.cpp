#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include "nova.h"
int main() {
    std::string command;
    while (true) {
        std::cout << "nova>> ";
        std::getline(std::cin, command);
        nova::run(command);
    }
    return 0;
}