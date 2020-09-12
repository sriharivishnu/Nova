#include "Error.h"

const char* Error::what() const throw() {
    std::string msg = "File<" + pos.file + ">" + 
    " Line " + std::to_string(pos.ln) + " Col " + std::to_string(pos.col) + 
    ": " + cause + ": "+ details;
    return msg.c_str();
}

Error::Error() {};
Error::Error (std::string cause, std::string details) : cause(cause), details(details), pos(Position(0,0,0)) {};
Error::Error (Position pos, std::string cause) : cause(cause), details(""), pos(pos) {};
Error::Error (Position pos, std::string cause, std::string details) : cause(cause), details(details), pos(pos) {};

const char* RunTimeError::what() const throw() { 
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
: Error(pos, cause, details), context(context) {};



IllegalCharException::IllegalCharException(Position pos, std::string details) : Error(pos, "IllegalCharException", details) {}


ParseException::ParseException(Position pos, std::string details) : Error(pos, "ParseException", details) {}


SyntaxError::SyntaxError(std::string details) : Error("SyntaxError", details) {};
SyntaxError::SyntaxError(Position pos, std::string details) : Error(pos, "SyntaxError", details) {};


TypeException::TypeException(Position pos, std::string details) : Error(pos, "TypeException", details) {};



UndefinedOperationException::UndefinedOperationException(std::string t1, std::string t2) : Error("Undefined Operation", "") {
    details = "Between " + t1 + " and " + t2;
}
UndefinedOperationException::UndefinedOperationException(Position pos, std::string op) : Error(pos, "Undefined Operation") {
    details = "Unknown Operation Found: " + op;
}        



UndefinedVariable::UndefinedVariable(std::string name, Position pos) 
: Error(pos, "Undefined Identifier", name + " is not defined") {}

/*
RUNTIME ERRORS 
*/


DivisionByZero::DivisionByZero(std::shared_ptr<Context> context, Position pos) 
: RunTimeError(context, pos, "Division By Zero", "Attempted division by zero") {}
