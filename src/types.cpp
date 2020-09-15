#include "types.h"
#include "Error.h"
#include "helper.h"
#include <memory>
using shared_obj = std::shared_ptr<object>;
using std::visit;
#define UNDEFINED_OP throw UndefinedOperationException(value.getStringType(), obj->value.getStringType());
#define UNDEFINED_UNARY(NAME) throw UndefinedOperationException(NAME, value.getStringType());
#define MAKE_OBJ(ARG, ret) std::make_shared<ret>(ARG);

object::object(Result res) : value(res) {}
shared_obj object::addBy(shared_obj obj) {
    UNDEFINED_OP
}
shared_obj object::subBy(shared_obj obj) {
    UNDEFINED_OP
}
shared_obj object::multBy(shared_obj obj) {
    UNDEFINED_OP
}
shared_obj object::divBy(shared_obj obj) {
    UNDEFINED_OP
}
shared_obj object::powBy(shared_obj obj) {
    UNDEFINED_OP
}
shared_obj object::toBool() {
    if (value) {
        return MAKE_OBJ(1, integer_type);
    }
    else {
        return MAKE_OBJ(0, integer_type);
    }
}
shared_obj object::gt(shared_obj obj) {
    UNDEFINED_OP
}
shared_obj object::lt(shared_obj obj) {
    UNDEFINED_OP
}
shared_obj object::gte(shared_obj obj) {
    UNDEFINED_OP
}
shared_obj object::lte(shared_obj obj) {
    UNDEFINED_OP
}
shared_obj object::ee(shared_obj obj) {
    UNDEFINED_OP
}
shared_obj object::ne(shared_obj obj) {
    UNDEFINED_OP
}
shared_obj object::band(shared_obj obj) {
    UNDEFINED_OP
}
shared_obj object::bor(shared_obj obj) {
    UNDEFINED_OP
}
shared_obj object::bxor(shared_obj obj) {
    UNDEFINED_OP
}
shared_obj object::inc() {
    UNDEFINED_UNARY("++")
}
shared_obj object::dec() {
    UNDEFINED_UNARY("--")
}
shared_obj object::prePlus() {
    UNDEFINED_UNARY("+")
}
shared_obj object::preMinus() {
    UNDEFINED_UNARY("-")
}
shared_obj object::preNot() {
    return MAKE_OBJ(!toBool()->value, integer_type);
}
std::string object::toString() {
    return "<object>";
}

#define BOOL_NUMBER_OP(t, op) std::visit(overloaded{\
            [&](int arg) {ans = MAKE_OBJ(getValue<t>() op arg, integer_type)},\
            [&](double arg) {ans = MAKE_OBJ(getValue<t>() op arg, integer_type)},\
            [&](auto arg) {UNDEFINED_OP}\
        }, obj->value.getResult());

integer_type::integer_type(int val) : object(Result(val)) {}
shared_obj integer_type::addBy(shared_obj obj) {
    shared_obj ans = nullptr;
    std::visit(overloaded{
        [&](std::string arg) {ans = MAKE_OBJ(std::to_string(getValue<int>()).append(arg), string_type);},
        [&](int arg) {ans = MAKE_OBJ(getValue<int>() + arg, integer_type);},
        [&](double arg) {ans = MAKE_OBJ(((double) getValue<int>()) + arg, double_type);},
        [&](auto arg) {UNDEFINED_OP}
    }, obj->value.getResult());
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj integer_type::subBy(shared_obj obj) {
    shared_obj ans = nullptr;
    std::visit(overloaded{
        [&](int arg) {ans = MAKE_OBJ(getValue<int>() - arg, integer_type);},
        [&](double arg) {ans = MAKE_OBJ(((double) getValue<int>()) - arg, double_type);},
        [&](auto arg) {UNDEFINED_OP}
    }, obj->value.getResult());
    if (ans) return ans;
    UNDEFINED_OP

}
shared_obj integer_type::multBy(shared_obj obj) {
    shared_obj ans = nullptr;
    std::visit(overloaded{
        [&](std::string arg) {
                std::string finalString = arg;
                for (int i = 1; i < getValue<int>(); i++) {
                    finalString += arg;
                }
                ans = MAKE_OBJ(finalString, string_type);
            },
        [&](int arg) {ans = MAKE_OBJ(getValue<int>() * arg, integer_type);},
        [&](double arg) {ans = MAKE_OBJ(((double) getValue<int>()) * arg, double_type);},
        [&](auto arg) {UNDEFINED_OP}
    }, obj->value.getResult());
    if (ans) return ans;
    UNDEFINED_OP

}
shared_obj integer_type::divBy(shared_obj obj) {
    shared_obj ans = nullptr;
    std::visit(overloaded{
        [&](int arg) {ans = MAKE_OBJ(getValue<int>() / arg, integer_type);},
        [&](double arg) {ans = MAKE_OBJ(((double) getValue<int>()) / arg, double_type);},
        [&](auto arg) {UNDEFINED_OP}
    }, obj->value.getResult());
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj integer_type::powBy(shared_obj obj) {
    shared_obj ans = nullptr;
    std::visit(overloaded{
        [&](int arg) {ans = MAKE_OBJ((int) pow(getValue<int>(), arg), integer_type)},
        [&](double arg) {ans = MAKE_OBJ(pow(getValue<int>(), arg), double_type);},
        [&](auto arg) {UNDEFINED_OP}
    }, obj->value.getResult());
    if (ans) return ans;
    UNDEFINED_OP
}

shared_obj integer_type::ee(shared_obj obj) {
    shared_obj ans = nullptr;
    BOOL_NUMBER_OP(int, ==)
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj integer_type::ne(shared_obj obj) {
    shared_obj ans = nullptr;
    BOOL_NUMBER_OP(int, !=)
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj integer_type::gt(shared_obj obj) {
    shared_obj ans = nullptr;
    BOOL_NUMBER_OP(int, >)
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj integer_type::lt(shared_obj obj) {
    shared_obj ans = nullptr;
    BOOL_NUMBER_OP(int, <)
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj integer_type::gte(shared_obj obj) {
    shared_obj ans = nullptr;
    BOOL_NUMBER_OP(int, >=)
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj integer_type::lte(shared_obj obj) {
    shared_obj ans = nullptr;
    BOOL_NUMBER_OP(int, <=)
    if (ans) return ans;
    UNDEFINED_OP
}
#define BINARY_OP_INT(op) shared_obj ans = nullptr;\
    if (obj->value.isType<int>()) {\
        ans = MAKE_OBJ(getValue<int>() op obj->getValue<int>(), integer_type);\
    }\
    if (ans) return ans;\
    UNDEFINED_OP

shared_obj integer_type::band(shared_obj obj) {
    BINARY_OP_INT(&)
}
shared_obj integer_type::bor(shared_obj obj) {
    BINARY_OP_INT(|)
}
shared_obj integer_type::bxor(shared_obj obj) {
    BINARY_OP_INT(^)
}
#undef BINARY_OP_INT

shared_obj integer_type::inc() {
    return MAKE_OBJ(getValue<int>() + 1, integer_type);
}
shared_obj integer_type::dec() {
    return MAKE_OBJ(getValue<int>() - 1, integer_type);
}
shared_obj integer_type::prePlus() {
    return MAKE_OBJ(getValue<int>(), integer_type);
}
shared_obj integer_type::preMinus() {
    return MAKE_OBJ(getValue<int>() * -1, integer_type);
}

shared_obj integer_type::toBool() {
    return MAKE_OBJ(getValue<int>() != 0, integer_type);
}
std::string integer_type::toString() {
    return std::to_string(getValue<int>());
}


#define DOUBLE_BIN_OP(op) std::visit(overloaded{\
        [&](int arg) {ans = MAKE_OBJ(getValue<double>() op ((double) arg), double_type);},\
        [&](double arg) {ans = MAKE_OBJ(getValue<double>() op arg, double_type);},\
        [&](auto arg) {UNDEFINED_OP}\
    }, obj->value.getResult());

double_type::double_type(double val) : object(Result(val)) {};

shared_obj double_type::addBy(shared_obj obj) {
    shared_obj ans = nullptr;
    std::visit(overloaded{
        [&](std::string& arg) {ans = MAKE_OBJ(std::to_string(getValue<double>()).append(arg), string_type);},
        [&](int arg) {ans = MAKE_OBJ(getValue<double>() + ((double) arg), double_type);},
        [&](double arg) {ans = MAKE_OBJ(getValue<double>() + arg, double_type);},
        [&](auto arg) {UNDEFINED_OP}
    }, obj->value.getResult());
    if (ans) return ans;
    UNDEFINED_OP

}
shared_obj double_type::subBy(shared_obj obj) {
    shared_obj ans = nullptr;
    DOUBLE_BIN_OP(-)
    if (ans) return ans;
    UNDEFINED_OP

}
shared_obj double_type::multBy(shared_obj obj) {
    shared_obj ans = nullptr;
    DOUBLE_BIN_OP(*)
    if (ans) return ans;
    UNDEFINED_OP

}
shared_obj double_type::divBy(shared_obj obj) {
    shared_obj ans = nullptr;
    DOUBLE_BIN_OP(/)
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj double_type::powBy(shared_obj obj) {
    shared_obj ans = nullptr;
    std::visit(overloaded{
        [&](int arg) {ans = MAKE_OBJ(pow(getValue<double>(), (double) arg), double_type)},
        [&](double arg) {ans = MAKE_OBJ((pow(getValue<double>(), arg)), double_type);},
        [&](auto arg) {UNDEFINED_OP}
    }, obj->value.getResult());
    if (ans) return ans;
    UNDEFINED_OP
}

shared_obj double_type::inc() {
    return MAKE_OBJ(getValue<double>() + 1, double_type);
}
shared_obj double_type::dec() {
    return MAKE_OBJ(getValue<double>() - 1, double_type);
}
shared_obj double_type::toBool() {
    return MAKE_OBJ(getValue<double>() != 0, double_type);
}
shared_obj double_type::ee(shared_obj obj) {
    shared_obj ans = nullptr;
    BOOL_NUMBER_OP(double, ==)
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj double_type::ne(shared_obj obj) {
    shared_obj ans = nullptr;
    BOOL_NUMBER_OP(double, !=)
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj double_type::gt(shared_obj obj) {
    shared_obj ans = nullptr;
    BOOL_NUMBER_OP(double, >)
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj double_type::lt(shared_obj obj) {
    shared_obj ans = nullptr;
    BOOL_NUMBER_OP(double, <)
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj double_type::gte(shared_obj obj) {
    shared_obj ans = nullptr;
    BOOL_NUMBER_OP(double, >=)
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj double_type::lte(shared_obj obj) {
    shared_obj ans = nullptr;
    BOOL_NUMBER_OP(double, <=)
    if (ans) return ans;
    UNDEFINED_OP
}
std::string double_type::toString() {
    std::string str = std::to_string(getValue<double>());
    str.erase ( str.find_last_not_of('0') + 1, std::string::npos );
    if (str.back() == '.') str.push_back('0');
    return str;
}

#undef DOUBLE_BIN_OP
#undef BOOL_NUMBER_OP
string_type::string_type(std::string val) : object(Result(val)) {}
shared_obj string_type::addBy(shared_obj obj) {
    shared_obj ans = nullptr;
    std::visit(overloaded{
        [&](std::string& arg) {ans = MAKE_OBJ(getValue<std::string>().append(arg), string_type);},
        [&](int arg) {ans = MAKE_OBJ(getValue<std::string>().append(std::to_string(arg)), string_type);},
        [&](double arg) {ans = MAKE_OBJ(getValue<std::string>().append(std::to_string(arg)), string_type);},
        [&](auto arg) {UNDEFINED_OP}
    }, obj->value.getResult());
    if (ans) return ans;
    UNDEFINED_OP

}
shared_obj string_type::multBy(shared_obj obj) {
    shared_obj ans = nullptr;
    std::visit(overloaded{
        [&](int arg) {
                std::string finalString = getValue<std::string>();
                for (int i = 1; i < arg; i++) {
                    finalString += getValue<std::string>();
                }
                ans = MAKE_OBJ(finalString, string_type);
            },
        [&](auto arg) {UNDEFINED_OP}
    }, obj->value.getResult());
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj string_type::toBool() {
    return MAKE_OBJ(!getValue<std::string>().empty(), integer_type);
}

std::string string_type::toString() {
    return getValue<std::string>();
}
