#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include "Token.h"
#include "Lexer.h"
#include "Error.h"

int main() {
    std::string command;
    Token t(Token::Type::DOUBLE, "1.23f");
    while (true) {
        std::cout << "nova>> ";
        std::getline(std::cin, command);
        Lexer lex("shell.cpp", command.c_str());
        std::vector<Token> a = lex.getTokens();
        std::vector<Error> errors = lex.getErrors();
        for (Error e : errors) {
            std::cout << e.toString() << std::endl;
        }
        // for (Token& token : a) {
        //     std::cout << "\n" << token << std::endl;
        // }
    }
    return 0;
}