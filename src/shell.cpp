#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>

#include "nova.h"
int main(int arg_count, char * arg_list[]) {
    std::string toRun;
    std::string command;
    std::shared_ptr<SymbolTable> symbols = std::make_shared<SymbolTable>();
    std::shared_ptr<FunctionTable> funcs = std::make_shared<FunctionTable>();
    symbols->set("false", 0.0);
    symbols->set("true", 1);
    Context global("<main>", symbols, funcs);
    if (arg_count == 1) {
        while (true) {
            std::cout << "nova>> ";
            std::getline(std::cin, command);
            nova::run(command, global);
        }
    }
    else if (arg_count == 2) {
        ifstream myfile (arg_list[1]);
        if (myfile.is_open())
        {
            while ( std::getline (myfile,command) )
            {
                toRun += command +  '\n';
            }
            myfile.close();
        } else {
            std::cout << "Could not open file";
        }
        nova::run(toRun, global);
    }
    return 0;
}