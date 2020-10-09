#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>
#include <functional>
#include "nova.h"
#include "stdfuncs.h"
using natFun = std::function<std::optional<std::variant<std::string, int, double, std::vector<shared_obj>, identifier, null>>(std::vector<shared_obj>)>;
int main(int arg_count, char * arg_list[]) {
    std::string toRun;
    std::string command;
    std::shared_ptr<SymbolTable> symbols = std::make_shared<SymbolTable>();
    symbols->set("false", Result(0.0));
    symbols->set("true", Result(1));
    Context global("<main>", symbols);
    addStdFunctions(global);
    if (arg_count == 1) {
        while (true) {
            std::cout << "nova>> ";
            std::getline(std::cin, command);
            if (command == "exit") break;
            nova::run(command, global, true);
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
        nova::run(toRun, global, false);
    }
    return 0;
}