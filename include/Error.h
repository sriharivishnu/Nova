#ifndef ERROR_GUARD
#define ERROR_GUARD
#include <string>
#include <exception>
#include "Position.h"
#include "Context.h"
class Error : public std::exception {
    public:
        std::string cause;
        std::string details;
        Position pos;
        Error() {};
        Error (std::string cause) : cause(cause), details(""), pos(Position(0,0,0)) {};
        Error (std::string cause, std::string details) : cause(cause), details(details), pos(Position(0,0,0)) {};
        Error (Position pos, std::string cause) : cause(cause), details(""), pos(pos) {};
        Error (Position pos, std::string cause, std::string details) : cause(cause), details(details), pos(pos) {};
        virtual const char* what() const throw() override { 
            std::string msg = "File<" + pos.file + ">" + 
            " Line " + std::to_string(pos.ln) + " Col " + std::to_string(pos.col) + 
            ": " + cause + ": "+ details;
            return msg.c_str();
        }
};

class RunTimeError : public Error {
    public:
        RunTimeError (Context& context, Position pos, std::string cause, std::string details) 
        : Error(pos, cause, details), context(context) {};
        virtual const char* what() const throw() override { 
            std::string traceback;
            Context tmp_ctx = context;
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
    protected:
        Context context;
};

/*
EXCEPTIONS
*/

class IllegalCharException : public Error {
    public:
        IllegalCharException(Position pos, std::string details) : Error(pos, "IllegalCharException", details) {}
};

class ParseException : public Error {
    public:
        ParseException(Position pos, std::string details) : Error(pos, "ParseException", details) {}
};

class SyntaxError : public Error {
    public:
        SyntaxError(std::string details) : Error("SyntaxError", details) {};
        SyntaxError(Position pos, std::string details) : Error(pos, "SyntaxError", details) {};
};

class TypeException: public Error {
    public:
        TypeException(Position pos, std::string details) : Error(pos, "TypeException", details) {};
};

class UndefinedOperationException : public Error {
    public:
        UndefinedOperationException(std::string t1, std::string t2) : Error("Undefined Operation") {
            details = "Between " + t1 + " and " + t2;
        }
        UndefinedOperationException(Position pos, std::string op) : Error(pos, "Undefined Operation") {
            details = "Unknown Operation Found: " + op;
        }        
};

class UndefinedVariable : public Error {
    public:
        UndefinedVariable(std::string name, Position pos) 
        : Error(pos, "Undefined Identifier", name + " is not defined") {}
};
/*
RUNTIME ERRORS 
*/

class DivisionByZero : public RunTimeError {
    public:
        DivisionByZero(Context& context, Position pos) 
        : RunTimeError(context, pos, "Division By Zero", "Attempted division by zero") {}
};
#endif