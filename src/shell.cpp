#include <iostream>
#include <stdio.h>
#include <string>

#include "Token.h"
int main() {
    std::string command;
    while (true) {
        std::cout << "nova>> ";
        std::getline(std::cin, command);
        std::cout << command << std::endl;
    }
    return 0;
}