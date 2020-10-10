//
// Created by Srihari Vishnu on 2020-10-04.
//

#include "stdfuncs.h"
#include <vector>
#include <iostream>
#include "types.h"

#define MATH_FUNC(name, func) context.symbols->addFunction(name, [&](std::vector<shared_obj> arg) {\
        if (arg[0]->value.isType<int>()) {\
            return std::func(arg[0]->getValue<int>());\
        }\
        else if (arg[0]->value.isType<double>()) {\
            return std::func(arg[0]->getValue<double>());\
        }\
        throw Error("Value Exception", "Expected an int or double type, but instead got " + arg[0]->value.getStringType());\
    }, 1);
void addStdFunctions(const Context& context) {
    context.symbols->addFunction("print", [&](std::vector<shared_obj> arg) {
        std::string res;
        for (auto i : arg) {
            std::cout << i->toString() << " ";
            res += i->toString();
        }
        std::cout << std::endl;
        return null();
    }, -1);
    context.symbols->addFunction("str", [&](std::vector<shared_obj> arg) {
        return arg[0]->toString();
    }, 1);
    context.symbols->addFunction("input", [&](std::vector<shared_obj> arg) {
        std::string line;
        std::getline(std::cin, line);
        return line;
    }, 0);
    context.symbols->addFunction("getnum", [&](std::vector<shared_obj> arg) {
        int num;
        if (!scanf("%d", &num)) {
            throw Error("Conversion Exception", "Cannot convert string to integer");
        };
        return num;
    }, 0);
    context.symbols->addFunction("getword", [&](std::vector<shared_obj> arg) {
        std::string s;
        std::cin >> s;
        return s;
    }, 0);

    context.symbols->addFunction("int", [&](std::vector<shared_obj> arg) {
        if (arg[0]->value.isType<std::string>()) {
            try {
                return std::stoi(arg[0]->getValue<std::string>());
            } catch (exception& e) {
                throw Error("Conversion Exception", "Cannot convert string to integer");
            }
        }
        else if (arg[0]->value.isType<double>()) {
            return (int) arg[0]->value.getValue<double>();
        }
        else if (arg[0]->value.isType<int>()) {
            return arg[0]->value.getValue<int>();
        }
        throw Error("Conversion Exception", "Cannot convert '" + arg[0]->value.getStringType() + "' to integer");
    }, 1);

    
    MATH_FUNC("sin", sin);
    MATH_FUNC("cos", cos);
    MATH_FUNC("tan", tan);
    MATH_FUNC("asin", asin);
    MATH_FUNC("acos", acos);
    MATH_FUNC("sqrt", sqrt);

//    context.symbols->addFunction("sin", [&](std::vector<shared_obj> arg)) {
//        if (arg[0]->value.isType<int>()) return std::sin(arg[0])
//    }
}
#undef MATH_FUNC

