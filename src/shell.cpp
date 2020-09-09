#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>

#include "nova.h"
int main() {
    std::string toRun;
    std::string command;
    std::shared_ptr<SymbolTable> symbols = std::make_shared<SymbolTable>();
    symbols->set("false", 0);
    symbols->set("true", 1);
    Context global("<main>", symbols);
    ifstream myfile ("src/test.txt");
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
    // while (true) {
    //     std::cout << "nova>> ";
    //     std::getline(std::cin, command);
    //     nova::run(command, global);
    // }

    return 0;
}