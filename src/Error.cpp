#include "Error.h"

#include <utility>

const char* Error::what() const noexcept {
    std::string msg = "File<" + pos.file + ">" + 
    " Line " + std::to_string(pos.ln) + " Col " + std::to_string(pos.col) + 
    ": " + cause + ": "+ details;
    return msg.c_str();
}

Error::Error() {};
Error::Error (std::string cause, std::string details) : cause(std::move(cause)), details(std::move(details)), pos(Position(0,0,0)) {};
Error::Error (Position pos, std::string cause) : cause(std::move(cause)), details(""), pos(std::move(pos)) {};
Error::Error (Position pos, std::string cause, std::string details) : cause(std::move(cause)), details(std::move(details)), pos(std::move(pos)) {};

const char* RunTimeError::what() const noexcept {
    std::string traceback;
    Context tmp_ctx = *context;
    Position tmp_pos = pos;
    while (true) {
        traceback = "   File<"+pos.file+">"+", Line "+std::to_string(tmp_pos.ln)+", in " + tmp_ctx.name + "\n" + traceback;
        if (!tmp_ctx.parent) break;
        tmp_ctx = *tmp_ctx.parent;
        tmp_pos = tmp_ctx.entry_pos;
    };
    traceback = cause + ": "+ details + "\nTraceback (most recent call last): \n" + traceback;
    return traceback.c_str();
}

RunTimeError::RunTimeError(std::shared_ptr<Context> context, Position pos, std::string cause, std::string details) 
: Error(std::move(pos), std::move(cause), std::move(details)), context(std::move(context)) {};



IllegalCharException::IllegalCharException(Position pos, std::string details) : Error(std::move(pos), "IllegalCharException", std::move(details)) {}


ParseException::ParseException(Position pos, std::string details) : Error(std::move(pos), "ParseException", std::move(details)) {}


SyntaxError::SyntaxError(std::string details) : Error("SyntaxError", details) {};
SyntaxError::SyntaxError(Position pos, std::string details) : Error(std::move(pos), "SyntaxError", std::move(details)) {};


TypeException::TypeException(Position pos, std::string details) : Error(std::move(pos), "TypeException", std::move(details)) {};



UndefinedOperationException::UndefinedOperationException(const std::string& t1, const std::string& t2) : Error("Undefined Operation", "") {
    details = "Between " + t1 + " and " + t2;
}
UndefinedOperationException::UndefinedOperationException(Position pos, const std::string& t1, const std::string& op, const std::string& t2) : Error(std::move(pos), "Undefined Operation", "") {
    details = "No operator " + op + " between " + t1 + " and " + t2;
}
UndefinedOperationException::UndefinedOperationException(Position pos, std::string op, const std::string& t1) : Error(std::move(pos), "Undefined Operation", "") {
    details = "No operator " + op + " and " + t1;
}
UndefinedOperationException::UndefinedOperationException(Position pos, std::string op) : Error(std::move(pos), "Undefined Operation") {
    details = "Unknown Operation Found: " + op;
}        



UndefinedVariable::UndefinedVariable(std::shared_ptr<Context> context, const std::string& name, Position pos)
: RunTimeError(std::move(context), std::move(pos), "Undefined Identifier", name + " is not defined") {}

/*
RUNTIME ERRORS 
*/


DivisionByZero::DivisionByZero(std::shared_ptr<Context> context, Position pos) 
: RunTimeError(std::move(context), std::move(pos), "Division By Zero", "Attempted division by zero") {}

IndexOutOfBounds::IndexOutOfBounds(std::shared_ptr<Context> context, Position pos, std::string details)
: RunTimeError(std::move(context), std::move(pos), "IndexOutOfBounds", std::move(details)) {}