#include <string>
#include "Position.h"

#ifndef ERROR_GUARD
#define ERROR_GUARD
class Error {
    public:
        std::string cause;
        std::string details;
        Position pos;
        Error() {};
        Error (std::string cause) : cause(cause), details(""), pos(Position(0,0,0)) {};
        Error (std::string cause, std::string details) : cause(cause), details(details), pos(Position(0,0,0)) {};
        Error (Position pos, std::string cause) : cause(cause), details(""), pos(pos) {};
        Error (Position pos, std::string cause, std::string details) : cause(cause), details(details), pos(pos) {};
        std::string toString() {
            return 
            "File<" + pos.file + ">" + 
            " Line " + std::to_string(pos.ln) + " Col " + std::to_string(pos.col) + 
            ": " + cause + ": "+ details;
        }
};

class IllegalCharException : public Error {
    public:
        IllegalCharException(Position pos, std::string details) : Error(pos, "IllegalCharException", details) {}
};

class SyntaxError : public Error {
    public:
        SyntaxError(std::string details) : Error("SyntaxError", details) {};
        SyntaxError(Position pos, std::string details) : Error(pos, "SytaxError", details) {};
};
#endif