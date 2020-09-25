#include "types.h"
#include "Error.h"
#include "helper.h"
#include <memory>
#include <utility>
using shared_obj = std::shared_ptr<object>;
using std::visit;
#define UNDEFINED_OP throw UndefinedOperationException(value.getStringType(), obj->value.getStringType());
#define UNDEFINED_UNARY(NAME) throw UndefinedOperationException(NAME, value.getStringType());
#define MAKE_OBJ(ARG, ret) std::make_shared<ret>(ARG)

object::object() : value(0) {}
object::object(Result res) : value(std::move(res)) {}
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
shared_obj object::index(shared_obj obj) {
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
shared_obj object::call(Context& context, std::vector<shared_obj> args){
    throw UndefinedOperationException(value.getStringType(), "()");
}
std::string object::toString() {
    return "<object>";
}

shared_obj object::dot(const std::string& name, const std::vector<shared_obj>& args) {
    throw UndefinedOperationException(value.getStringType(), ".");
}


#define BOOL_NUMBER_OP(t, op) std::visit(overloaded{\
            [&](int arg) {ans = MAKE_OBJ(getValue<t>() op arg, integer_type);},\
            [&](double arg) {ans = MAKE_OBJ(getValue<t>() op arg, integer_type);},\
            [&](auto arg) {UNDEFINED_OP}\
        }, obj->value.getResult());

integer_type::integer_type(int val) : object(Result(val)) {}
shared_obj integer_type::addBy(shared_obj obj) {
    shared_obj ans = nullptr;
    std::visit(overloaded{
        [&](const std::string& arg) {ans = MAKE_OBJ(std::to_string(getValue<int>()).append(arg), string_type);},
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
        [&](const std::string& arg) {
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
        [&](int arg) {ans = MAKE_OBJ((int) pow(getValue<int>(), arg), integer_type);},
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
        [&](int arg) {ans = MAKE_OBJ(pow(getValue<double>(), (double) arg), double_type);},
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
                auto finalString = getValue<std::string>();
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

shared_obj string_type::dot(const std::string& name, const std::vector<shared_obj>& args) {
    if (name == "length" || name == "len" || name == "size") {
        if (!args.empty()) throw Error("Function Call Exception", "Too many Params for " + name + ": expected, " + std::to_string(0) + " params but called with " + std::to_string(args.size()));
        return MAKE_OBJ(getValue<std::string>().length(), integer_type);
    }
    throw Error("Undefined Method", value.getStringType() + " has no member function " + name);
}

shared_obj string_type::index(shared_obj obj) {
    if (!obj->value.isType<int>()) UNDEFINED_OP;
    int toAccess = obj->getValue<int>();
    int size = getValue<std::string>().length();
    if (toAccess >=  size || toAccess < 0) {
        throw Error("Index Out of Bounds", "Attempted to access index: " + std::to_string(toAccess) + ", with string size: " + std::to_string(size));
    }
    return MAKE_OBJ(std::to_string(getValue<std::string>()[toAccess]), string_type);
}


list_type::list_type(std::vector<shared_obj> val) : object(Result(val)) {}

shared_obj list_type::addBy(shared_obj obj) {
    shared_obj ans = nullptr;
    std::visit(overloaded{
        [&](std::vector<shared_obj> arg) {
            std::vector<shared_obj> finalArray;
            finalArray.reserve(getValue<std::vector<shared_obj>>().size());
            for (int i = 0; i < getValue<std::vector<shared_obj>>().size(); i++) {
                finalArray.push_back(getValue<std::vector<shared_obj>>()[i]);
            }
            for (const auto & i : arg) {
                finalArray.push_back(i);
            }
            ans = MAKE_OBJ(finalArray, list_type);
            },
        [&](auto arg) {UNDEFINED_OP}
    }, obj->value.getResult());
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj list_type::multBy(shared_obj obj) {
    UNDEFINED_OP
}
shared_obj list_type::toBool() {
    return MAKE_OBJ(getValue<std::vector<shared_obj>>().empty(), integer_type);
}
shared_obj list_type::index(shared_obj obj) {
    if (!obj->value.isType<int>()) UNDEFINED_OP;
    int toAccess = obj->getValue<int>();
    int size = getValue<std::vector<shared_obj>>().size();
    if (toAccess >=  size || toAccess < 0) {
        throw Error("Index Out of Bounds", "Attempted to access index: " + std::to_string(toAccess) + ", with list size: " + std::to_string(size));
    }
    return getValue<std::vector<shared_obj>>()[toAccess];
}
std::string list_type::toString() {
    auto values = getValue<std::vector<shared_obj>>();
    std::string str("[");
    for (int i = 0 ; i < values.size(); i++) {
        if (values[i]) str += values[i]->toString();
        else str += "null";
        if (i != values.size() - 1) str += ", ";
    }
    str.push_back(']');
    return str;
}

shared_obj list_type::dot(const string &name, const vector<shared_obj> &args) {
    if (name == "size" || name == "length" || name == "len") {
        return MAKE_OBJ(getValue<std::vector<shared_obj>>().size(), integer_type);
    } else if (name == "add" && args.size() == 1) {
        getValue<std::vector<shared_obj>>().push_back(args[0]);
        return std::make_shared<null_type>();
    }
    throw Error("Undefined Method", value.getStringType() + " has no member function " + name);
}

func_type::func_type (std::string name, std::vector<std::string> params, std::shared_ptr<statement> toRun) 
: object(Result(identifier())), name(std::move(name)), params(std::move(params)), toRun(std::move(toRun)) {}
shared_obj func_type::call(Context& parent, vector<shared_obj> args) {
    if (args.size() < params.size()) {
        throw Error("Function Call Exception", "Too few Params for " + name + ": expected, " + std::to_string(params.size()) + " params but called with " + std::to_string(args.size()));
    }
    if (args.size() > params.size()) {
        throw Error("Function Call Exception", "Too many Params for " + name + ": expected, " + std::to_string(params.size()) + " params but called with " + std::to_string(args.size()));
    }
    std::shared_ptr<SymbolTable> symbols = make_shared<SymbolTable>(parent.symbols);
    for (int i = 0; i < params.size(); i++) {
        symbols->set(params[i], args[i]);
    }
    Context child(name, symbols);
    std::optional<shared_obj> temp = toRun->execute(child);
    if (temp) return *temp;
    else return {};
}
std::string func_type::toString() {
    return "function <" + name + ">";
}

#undef MAKE_OBJ

std::string null_type::toString() {
    return "null";
}
