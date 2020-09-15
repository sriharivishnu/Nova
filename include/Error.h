#ifndef ERROR_GUARD
#define ERROR_GUARD
#include <string>
#include <exception>
#include <memory>
#include "Position.h"
#include "Context.h"
struct Context;
class Error : public std::exception {
    public:
        std::string cause;
        std::string details;
        Position pos;
        Error();
        Error (std::string cause, std::string details);
        Error (Position pos, std::string cause);
        Error (Position pos, std::string cause, std::string details);
        virtual const char* what() const throw() override;
};

class RunTimeError : public Error {
    public:
        RunTimeError (std::shared_ptr<Context> context, Position pos, std::string cause, std::string details);
        virtual const char* what() const throw() override;
    protected:
        std::shared_ptr<Context> context;
};

/*
EXCEPTIONS
*/

class IllegalCharException : public Error {
    public:
        IllegalCharException(Position pos, std::string details);
};

class ParseException : public Error {
    public:
        ParseException(Position pos, std::string details);
};

class SyntaxError : public Error {
    public:
        SyntaxError(std::string details);
        SyntaxError(Position pos, std::string details);
};

class TypeException: public Error {
    public:
        TypeException(Position pos, std::string details);
};

class UndefinedOperationException : public Error {
    public:
        UndefinedOperationException(std::string t1, std::string t2);
        UndefinedOperationException(Position pos, std::string op);
        UndefinedOperationException(Position pos, std::string t1, std::string op);
        UndefinedOperationException(Position pos, std::string t1, std::string op, std::string t2);
};

class UndefinedVariable : public RunTimeError {
    public:
        UndefinedVariable(std::shared_ptr<Context> context, std::string name, Position pos);
};
/*
RUNTIME ERRORS 
*/

class DivisionByZero : public RunTimeError {
    public:
        DivisionByZero(std::shared_ptr<Context> context, Position pos);
};

class IndexOutOfBounds : public RunTimeError {
    public:
        IndexOutOfBounds(std::shared_ptr<Context> context, Position pos, std::string details);
};
#endif