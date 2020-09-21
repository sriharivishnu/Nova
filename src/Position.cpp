#include "Position.h"

#include <utility>
Position::Position(int cur, int ln, int col) : pos(cur), ln(ln), col(col) {};
Position::Position(int cur, int ln, int col, std::string file, std::string fcontent) 
                : pos(cur), ln(ln), col(col), file(std::move(file)), fcontent(std::move(fcontent)) {};

Position* Position::advance(char current) {
    pos += 1;
    col += 1;
    if (current == '\n') {
        ln += 1;
        col = 0;
    }
    return this;
}
Position Position::copy() {
    return Position(pos, ln, col, file, fcontent);
}