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
                std::optional<shared_obj> res = stmt->execute(context);
                if (res) std::cout << res->get()->toString() << std::endl;
            } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
                return 1;
            }
        }
        return 0;
    }
}
#endif