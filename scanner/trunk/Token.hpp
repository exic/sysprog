#ifndef TOKEN
#define TOKEN

#include "TType.hpp"


class Token {
    public:
        Token(TType pType, int pLine, int pColumn);
        TType getType();
        int getLine();
        int getColumn();
        char* getLexem() {
            return lexem;
        }
    private:
        TType type;
        int line;
        int column;
        char* lexem;
};

#endif
