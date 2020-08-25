#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include "Token.h"
#include "Lexer.h"
#include "Error.h"
#include "Parser.h"

int main() {
    std::string command;
    Token t(Token::Type::DOUBLE, "1.23f", Position());
    while (true) {
        std::cout << "nova>> ";
        std::getline(std::cin, command);
        Lexer lex("shell.cpp", command.c_str());
        std::vector<Token> a = lex.getTokens();
        std::vector<Error> errors = lex.getErrors();
        for (Token t : a) {
            std::cout << t << std::endl;
        }

        Parser par(a);
        ParseResult res = par.parse();
        if (!res.result) errors.push_back(res.error);
        else {
            std::cout << "\n" << res.node.toString() << std::endl;
        }
        for (Error err : errors) {
            std::cout << "\n" << err.toString() << std::endl;
        }
    }
    return 0;
}