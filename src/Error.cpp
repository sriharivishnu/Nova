#include "Error.h"

#include <utility>

const char* Error::what() const noexcept {
    return msg.c_str();
}
void Error::makeMessage(const std::string& cause, const std::string& details) {
    msg = "File<" + pos.file + ">" + 
    " Line " + std::to_string(pos.ln) + " Col " + std::to_string(pos.col) + 
    ": " + cause + ": "+ details;
}
Error::Error() = default;
Error::Error (const std::string& cause, const std::string& details) : pos(Position(0,0,0)) {
    makeMessage(cause, details);
};
Error::Error (Position pos, const std::string& cause) : pos(std::move(pos)) {
    makeMessage(cause, "");
};
Error::Error (Position pos, const std::string& cause, const std::string& details) : pos(std::move(pos)) {
    makeMessage(cause, details);
};

const char* RunTimeError::what() const noexcept {
    return msg.c_str();
}

RunTimeError::RunTimeError(std::shared_ptr<Context> context_, Position pos, const std::string& cause, const std::string& details) 
: Error(std::move(pos), std::move(cause), std::move(details)), context(std::move(context_))
{   
    Context tmp_ctx = *context;
    Position tmp_pos = pos;
    while (true) {
        msg = "   File<"+pos.file+">"+", Line "+std::to_string(tmp_pos.ln)+", in " + tmp_ctx.name + "\n" + msg;
        if (!tmp_ctx.parent) break;
        tmp_ctx = *tmp_ctx.parent;
        tmp_pos = tmp_ctx.entry_pos;
    };
    msg = cause + ": "+ details + "\nTraceback (most recent call last): \n" + msg;
};

IllegalCharException::IllegalCharException(Position pos, const std::string& details) : Error(std::move(pos), "IllegalCharException", std::move(details)) {}


ParseException::ParseException(Position pos, const std::string& details) : Error(std::move(pos), "ParseException", std::move(details)) {}


SyntaxError::SyntaxError(const std::string& details) : Error("SyntaxError", std::move(details)) {};
SyntaxError::SyntaxError(Position pos, const std::string& details) : Error(std::move(pos), "SyntaxError", std::move(details)) {};


TypeException::TypeException(Position pos, const std::string& details) : Error(std::move(pos), "TypeException", std::move(details)) {};



UndefinedOperationException::UndefinedOperationException(const std::string& t1, const std::string& t2) : Error("Undefined Operation", "Between " + t1 + " and " + t2) {}
UndefinedOperationException::UndefinedOperationException(Position pos, const std::string& t1, const std::string& op, const std::string& t2) 
: Error(std::move(pos), "Undefined Operation", "No operator " + op + " between " + t1 + " and " + t2) {}
UndefinedOperationException::UndefinedOperationException(Position pos, const std::string& op, const std::string& t1) : Error(std::move(pos), "Undefined Operation", "No operator " + op + " and " + t1) {
}
UndefinedOperationException::UndefinedOperationException(Position pos, const std::string& op) : Error(std::move(pos), "Undefined Operation", "Unknown Operation Found: " + op) {}        



UndefinedVariable::UndefinedVariable(std::shared_ptr<Context> context, const std::string& name, Position pos)
: RunTimeError(context, std::move(pos), "Undefined Identifier", name + " is not defined") {}

/*
RUNTIME ERRORS 
*/


DivisionByZero::DivisionByZero(std::shared_ptr<Context> context, Position pos) 
: RunTimeError(std::move(context), std::move(pos), "Division By Zero", "Attempted division by zero") {}

IndexOutOfBounds::IndexOutOfBounds(std::shared_ptr<Context> context, Position pos, const std::string& details)
: RunTimeError(std::move(context), std::move(pos), "IndexOutOfBounds", std::move(details)) {}