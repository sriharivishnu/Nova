#include "types.h"
#include "Error.h"
#include <memory>
#include <utility>
using shared_obj = std::shared_ptr<object>;
using std::visit;
#define UNDEFINED_OP throw UndefinedOperationException(value.getStringType(), obj->value.getStringType());
#define UNDEFINED_UNARY(NAME) throw UndefinedOperationException(NAME, value.getStringType());
#define MAKE_OBJ(ARG, ret) std::make_shared<ret>(ARG)

object::object() : value(0) {}
object::object(Result res) : value(std::move(res)) {}
shared_obj object::addBy(const shared_obj& obj) {
    UNDEFINED_OP
}
shared_obj object::subBy(const shared_obj& obj) {
    UNDEFINED_OP
}
shared_obj object::multBy(const shared_obj& obj) {
    UNDEFINED_OP
}
shared_obj object::divBy(const shared_obj& obj) {
    UNDEFINED_OP
}
shared_obj object::powBy(const shared_obj& obj) {
    UNDEFINED_OP
}
shared_obj object::mod(const shared_obj& obj) {
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
shared_obj object::gt(const shared_obj& obj) {
    UNDEFINED_OP
}
shared_obj object::lt(const shared_obj& obj) {
    UNDEFINED_OP
}
shared_obj object::gte(const shared_obj& obj) {
    UNDEFINED_OP
}
shared_obj object::lte(const shared_obj& obj) {
    UNDEFINED_OP
}
shared_obj object::ee(const shared_obj& obj) {
    UNDEFINED_OP
}
shared_obj object::ne(const shared_obj& obj) {
    UNDEFINED_OP
}
shared_obj object::band(const shared_obj& obj) {
    UNDEFINED_OP
}
shared_obj object::bor(const shared_obj& obj) {
    UNDEFINED_OP
}
shared_obj object::bxor(const shared_obj& obj) {
    UNDEFINED_OP
}
shared_obj object::lshift(const shared_obj& obj) {
    UNDEFINED_OP
}

shared_obj object::rshift(const shared_obj& obj) {
    UNDEFINED_OP
}
shared_obj object::index(const shared_obj& obj) {
    UNDEFINED_OP
}
shared_obj object::indexUpdate(const shared_obj& obj, const shared_obj& newObj) {
    UNDEFINED_OP
}
shared_obj object::bnot() {
    UNDEFINED_UNARY("~")
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
shared_obj integer_type::addBy(const shared_obj& obj) {
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
shared_obj integer_type::subBy(const shared_obj& obj) {
    shared_obj ans = nullptr;
    std::visit(overloaded{
        [&](int arg) {ans = MAKE_OBJ(getValue<int>() - arg, integer_type);},
        [&](double arg) {ans = MAKE_OBJ(((double) getValue<int>()) - arg, double_type);},
        [&](auto arg) {UNDEFINED_OP}
    }, obj->value.getResult());
    if (ans) return ans;
    UNDEFINED_OP

}
shared_obj integer_type::multBy(const shared_obj& obj) {
    shared_obj ans = nullptr;
    std::visit(overloaded{
        [&](const std::string& arg) {
                std::string finalString = arg;
                for (unsigned int i = 1; i < getValue<int>(); i++) {
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
shared_obj integer_type::divBy(const shared_obj& obj) {
    shared_obj ans = nullptr;
    std::visit(overloaded{
        [&](int arg) {ans = MAKE_OBJ(getValue<int>() / arg, integer_type);},
        [&](double arg) {ans = MAKE_OBJ(((double) getValue<int>()) / arg, double_type);},
        [&](auto arg) {UNDEFINED_OP}
    }, obj->value.getResult());
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj integer_type::powBy(const shared_obj& obj) {
    shared_obj ans = nullptr;
    std::visit(overloaded{
        [&](int arg) {ans = MAKE_OBJ((int) pow(getValue<int>(), arg), integer_type);},
        [&](double arg) {ans = MAKE_OBJ(pow(getValue<int>(), arg), double_type);},
        [&](auto arg) {UNDEFINED_OP}
    }, obj->value.getResult());
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj integer_type::mod(const shared_obj& obj) {
    if (!obj->value.isType<int>()) UNDEFINED_OP
    return MAKE_OBJ(getValue<int>() % obj->getValue<int>(), integer_type);
}

shared_obj integer_type::ee(const shared_obj& obj) {
    shared_obj ans = nullptr;
    BOOL_NUMBER_OP(int, ==)
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj integer_type::ne(const shared_obj& obj) {
    shared_obj ans = nullptr;
    BOOL_NUMBER_OP(int, !=)
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj integer_type::gt(const shared_obj& obj) {
    shared_obj ans = nullptr;
    BOOL_NUMBER_OP(int, >)
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj integer_type::lt(const shared_obj& obj) {
    shared_obj ans = nullptr;
    BOOL_NUMBER_OP(int, <)
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj integer_type::gte(const shared_obj& obj) {
    shared_obj ans = nullptr;
    BOOL_NUMBER_OP(int, >=)
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj integer_type::lte(const shared_obj& obj) {
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

shared_obj integer_type::band(const shared_obj& obj) {
    BINARY_OP_INT(&)
}
shared_obj integer_type::bor(const shared_obj& obj) {
    BINARY_OP_INT(|)
}
shared_obj integer_type::bxor(const shared_obj& obj) {
    BINARY_OP_INT(^)
}
shared_obj integer_type::lshift(const shared_obj &obj) {
    BINARY_OP_INT(<<)
}
shared_obj integer_type::rshift(const shared_obj& obj) {
    BINARY_OP_INT(>>)
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
shared_obj integer_type::bnot() {
    return MAKE_OBJ(~getValue<int>(), integer_type);
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

double_type::double_type(double val) : object(Result(val)) {}

shared_obj double_type::addBy(const shared_obj& obj) {
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
shared_obj double_type::subBy(const shared_obj& obj) {
    shared_obj ans = nullptr;
    DOUBLE_BIN_OP(-)
    if (ans) return ans;
    UNDEFINED_OP

}
shared_obj double_type::multBy(const shared_obj& obj) {
    shared_obj ans = nullptr;
    DOUBLE_BIN_OP(*)
    if (ans) return ans;
    UNDEFINED_OP

}
shared_obj double_type::divBy(const shared_obj& obj) {
    shared_obj ans = nullptr;
    DOUBLE_BIN_OP(/)
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj double_type::powBy(const shared_obj& obj) {
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
shared_obj double_type::ee(const shared_obj& obj) {
    shared_obj ans = nullptr;
    BOOL_NUMBER_OP(double, ==)
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj double_type::ne(const shared_obj& obj) {
    shared_obj ans = nullptr;
    BOOL_NUMBER_OP(double, !=)
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj double_type::gt(const shared_obj& obj) {
    shared_obj ans = nullptr;
    BOOL_NUMBER_OP(double, >)
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj double_type::lt(const shared_obj& obj) {
    shared_obj ans = nullptr;
    BOOL_NUMBER_OP(double, <)
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj double_type::gte(const shared_obj& obj) {
    shared_obj ans = nullptr;
    BOOL_NUMBER_OP(double, >=)
    if (ans) return ans;
    UNDEFINED_OP
}
shared_obj double_type::lte(const shared_obj& obj) {
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
shared_obj string_type::addBy(const shared_obj& obj) {
    return MAKE_OBJ(getValue<std::string>().append(obj->toString()), string_type);

}
shared_obj string_type::multBy(const shared_obj& obj) {
    shared_obj ans = nullptr;
    std::visit(overloaded{
        [&](int arg) {
                auto finalString = getValue<std::string>();
                for (unsigned int i = 1; i < arg; i++) {
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

shared_obj string_type::index(const shared_obj& obj) {
    if (!obj->value.isType<int>()) UNDEFINED_OP;
    int toAccess = obj->getValue<int>();
    int size = getValue<std::string>().length();
    if (toAccess >=  size || toAccess < 0) {
        throw Error("Index Out of Bounds", "Attempted to access index: " + std::to_string(toAccess) + ", with string size: " + std::to_string(size));
    }
    return MAKE_OBJ(std::string(1, getValue<std::string>()[toAccess]), string_type);
}


list_type::list_type(std::vector<shared_obj> val) : object(Result(val)) {}

shared_obj list_type::addBy(const shared_obj& obj) {
    shared_obj ans = nullptr;
    std::visit(overloaded{
        [&](std::vector<shared_obj> arg) {
            std::vector<shared_obj> finalArray;
            finalArray.reserve(getValue<std::vector<shared_obj>>().size());
            for (const auto & i : getValue<std::vector<shared_obj>>()) {
                finalArray.push_back(i);
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
shared_obj list_type::multBy(const shared_obj& obj) {
    UNDEFINED_OP
}
shared_obj list_type::toBool() {
    return MAKE_OBJ(getValue<std::vector<shared_obj>>().empty(), integer_type);
}
shared_obj list_type::index(const shared_obj& obj) {
    if (!obj->value.isType<int>()) UNDEFINED_OP
    int toAccess = obj->getValue<int>();
    int size = getValue<std::vector<shared_obj>>().size();
    if (toAccess >=  size || toAccess < 0) {
        throw Error("Index Out of Bounds", "Attempted to access index: " + std::to_string(toAccess) + ", with list size: " + std::to_string(size));
    }
    return getValue<std::vector<shared_obj>>()[toAccess];
}
shared_obj list_type::indexUpdate(const shared_obj& obj, const shared_obj& newObj) {
    if (!obj->value.isType<int>()) UNDEFINED_OP
    int toAccess = obj->getValue<int>();
    int size = getValue<std::vector<shared_obj>>().size();
    if (toAccess >=  size || toAccess < 0) {
        throw Error("Index Out of Bounds", "Attempted to access index: " + std::to_string(toAccess) + ", with list size: " + std::to_string(size));
    }
    getValue<std::vector<shared_obj>>()[toAccess] = newObj;
    return std::make_shared<null_type>();
}
std::string list_type::toString() {
    auto values = getValue<std::vector<shared_obj>>();
    std::string str("[");
    for (unsigned int i = 0 ; i < values.size(); i++) {
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
    for (unsigned int i = 0; i < params.size(); i++) {
        symbols->set(params[i], args[i]);
    }
    Context child(name, symbols);
    flow temp = toRun->execute(child);
    if (temp.value) return *temp.value;
    else return std::make_shared<null_type>();
}
std::string func_type::toString() {
    return "function <" + name + ">";
}

std::string null_type::toString() {
    return "null";
}

native_func::native_func(std::string name_, std::function<std::optional<type>(std::vector<shared_obj>)>  func_, int numParams = -1) :
name(std::move(name_)), numberOfParams(numParams), toRun(std::move(func_)) {}

shared_obj native_func::call(Context &context, std::vector<shared_obj> args) {
    if (numberOfParams != -1) {
        if (args.size() > numberOfParams) {
            throw Error("Function Call Exception", "Too many Params for " + name + ": expected, " + std::to_string(numberOfParams) + " params but called with " + std::to_string(args.size()));
        }
        else if (args.size() < numberOfParams) {
            throw Error("Function Call Exception", "Too few Params for " + name + ": expected, " + std::to_string(numberOfParams) + " params but called with " + std::to_string(args.size()));
        }
    }
    std::optional<type> got = toRun(args);
    if (!got) return make_shared<null_type>();
    shared_obj ret;
    std::visit(overloaded{
            [&](std::vector<shared_obj> arg) {
                ret = MAKE_OBJ(arg, list_type);
            },
            [&](int arg) {
                ret = MAKE_OBJ(arg, integer_type);
            },
            [&](double arg) {
                ret = MAKE_OBJ(arg, double_type);
            },
            [&](std::string arg) {
                ret = MAKE_OBJ(arg, string_type);
            },
            [&](auto arg) {
                throw Error("Unknown Error", "Unknown return type when running: " + name);
            }
    }, *got);
    return ret;
}


#undef MAKE_OBJ

