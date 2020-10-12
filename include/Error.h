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
        std::string msg;
        // std::string cause;
        // std::string details;
        Position pos;
        void makeMessage(const std::string& cause, const std::string& details);
        Error();
        Error (const std::string& cause, const std::string& details);
        Error (Position pos, const std::string& cause);
        Error (Position pos, const std::string& cause, const std::string& details);
        virtual const char* what() const throw() override;
};

class RunTimeError : public Error {
    public:
        RunTimeError (std::shared_ptr<Context> context, Position pos, const std::string& cause, const std::string& details);
        virtual const char* what() const throw() override;
    protected:
        std::shared_ptr<Context> context;
};

/*
EXCEPTIONS
*/

class IllegalCharException : public Error {
    public:
        IllegalCharException(Position pos, const std::string& details);
};

class ParseException : public Error {
    public:
        ParseException(Position pos, const std::string& details);
};

class SyntaxError : public Error {
    public:
        SyntaxError(const std::string& details);
        SyntaxError(Position pos, const std::string& details);
};

class TypeException: public Error {
    public:
        TypeException(Position pos, const std::string& details);
};

class UndefinedOperationException : public Error {
    public:
        UndefinedOperationException(const std::string& t1, const std::string& t2);
        UndefinedOperationException(Position pos, const std::string& op);
        UndefinedOperationException(Position pos, const std::string& t1, const std::string& op);
        UndefinedOperationException(Position pos, const std::string& t1, const std::string& op, const std::string& t2);
};

class UndefinedVariable : public RunTimeError {
    public:
        UndefinedVariable(std::shared_ptr<Context> context, const std::string& name, Position pos);
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
        IndexOutOfBounds(std::shared_ptr<Context> context, Position pos, const std::string& details);
};
#endif