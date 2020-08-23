#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include "Token.h"
#include "Lexer.h"

int main() {
    std::string command;
    Token t(Token::Type::FLOAT, "1.23f");
    while (true) {
        std::cout << "nova>> ";
        std::getline(std::cin, command);
        Lexer lex(command.c_str());
        std::vector<Token> a = lex.getTokens();
        for (Token& token : a) {
            std::cout << "\n" << token << "END of " << std::to_string(a.size()) << std::endl;
        }
    }
    return 0;
}