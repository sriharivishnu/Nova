#include <iostream>
#include <stdio.h>
#include <string>

#include "Token.h"
int main() {
    std::string command;
    Token t(Token::Type::FLOAT, "1.23f");
    while (true) {
        std::cout << "nova>> " << t;
        std::getline(std::cin, command);
        std::cout << command << std::endl;
    }
    return 0;
}