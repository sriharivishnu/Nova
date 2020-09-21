#include <string>
#ifndef POSITION_CLASS
#define POSITION_CLASS
class Position {
        public:
            Position() = default;;
            Position(int cur, int ln, int col);
            Position(int cur, int ln, int col, std::string file, std::string fcontent);
            Position* advance(char current);
            Position copy();

            int pos = 0;
            int ln = 0;
            int col = 0;
            std::string file;
            std::string fcontent;
    };
#endif