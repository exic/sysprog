#ifndef TOKEN
#define TOKEN

#include "TType.hpp"
#include "string.h"


class Token {
    public:
        Token(TType pType, int pLine, int pColumn);
        TType getType();
        int getLine();
        int getColumn();
        char* getLexem();
        void setLexem(char* lexem);
    private:
        TType type;
        int line;
        int column;
        char lexem[128];
};

#endif
