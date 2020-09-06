#ifndef ERROR_GUARD
#define ERROR_GUARD
#include <string>
#include <exception>
#include "Position.h"
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
        virtual const char* what() const throw() { 
            std::string msg = "File<" + pos.file + ">" + 
            " Line " + std::to_string(pos.ln) + " Col " + std::to_string(pos.col) + 
            ": " + cause + ": "+ details;
            return msg.c_str();
        }
};


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
#endif