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
    int run(const std::string& command, Context& context, bool shell = false, std::string fileName = "main") {
        Lexer lex(fileName, command.c_str());
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
        Parser par(a);
        std::shared_ptr<statement> stmt;
        while (!par.lookAhead(0).is(Token::Type::END)) {
            try {
                stmt = par.parse();
                // std::cout << stmt->toString() << std::endl;
            } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
                return 1;
            }
            if (!stmt) continue;
            try {
                flow res = stmt->execute(context);
                if (res.isType(flow::type::RETURN)) {
                    throw SyntaxError("No matching function for return");
                }
                else if (res.isType(flow::type::BREAK)) {
                    throw SyntaxError("Break called outside of loops or structures");
                }
                else if (res.isType(flow::type::CONTINUE)) {
                    throw SyntaxError("Continue called outside of loops or structures");
                }
                else if (res.isType(flow::type::SIMPLE)) {
                    if (shell) std::cout << res.value->get()->toString() << std::endl;
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