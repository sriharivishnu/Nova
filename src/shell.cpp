#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include "Token.h"
#include "Lexer.h"
#include "Error.h"
#include "Parser.h"
#include "Interpreter.h"
int main() {
    std::string command;
    Token t(Token::Type::DOUBLE, "1.23f", Position());
    while (true) {
        std::cout << "nova>> ";
        std::getline(std::cin, command);
        Lexer lex("shell.cpp", command.c_str());
        std::vector<Token> a;
        try {
            a = lex.getTokens();
            for (Token t : a) {
                std::cout << t << std::endl;
            }
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            continue;
        }
        Parser par(a);
        std::shared_ptr<Expression> expression;
        try {
            expression = par.parse();
            std::cout << expression->toString() << std::endl;
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            continue;
        }
        // Visitor v;
        // int result = v.visit(expression);
        // cout << result << endl;
        // for (Error err : errors) {
        //     std::cout << "\n" << err.toString() << std::endl;
        // }

        // Interpreter interpreter;
        // interpreter.visit(res.node);
    }
    return 0;
}