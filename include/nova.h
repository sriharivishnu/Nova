#ifndef NOVA_H
#define NOVA_H
#include <iostream>
#include "Lexer.h"
#include "Error.h"
#include "Parser.h"
#include "Expression.h"
#include "Token.h"
#include "Context.h"
namespace nova {
    int run(std::string command, Context& context) {
        Lexer lex("main", command.c_str());
        std::vector<Token> a;
        try {
            a = lex.getTokens();
            // for (Token t : a) {
            //     std::cout << t << std::endl;
            // }
        } catch (std::exception& e) {
            std::cout << e.what() << std::endl;
            return 1;
        }
        if (a.size() <= 1) return 0;
        Parser par(a);
        std::shared_ptr<statement> stmt;
        while (!par.lookAhead(0).is(Token::Type::END)) {
            try {
                stmt = par.parse();
                // std::cout << expression->toString() << std::endl;
            } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
                return 1;
            }
            if (!stmt) continue;
            try {
                std::optional<Result> res = stmt->execute(context);
                if (res) {
                    if (res->isType<int>()) {
                        std::cout << res->getValue<int>() << std::endl;
                    } else if (res->isType<double>()) {
                        std::cout << res->getValue<double>() << std::endl;
                    } else if (res->isType<std::string>()) {
                        std::cout << res->getValue<std::string>() << std::endl;
                    }
                }
            } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
                return 1;
            }
        }
        return 0;
    }
}
#endif