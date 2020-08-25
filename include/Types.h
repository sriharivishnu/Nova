#ifndef __TYPES_DEFINE__
#define __TYPES_DEFINE__
enum struct types {
    INT,
    FLOAT,
    STRING
};
template<typename T>
class Type {
    T value;
    Type(T value) : value(value) {};
    friend operator+() {}
};
#endif