#ifndef TOKEN
#define TOKEN

#include "TType.hpp"
#include "Constants.hpp"
#include "string.h"


class Token {
    public:
        Token(TType pType, int pLine, int pColumn);
        TType getType();
        int getLine();
        int getColumn();
        char* getLexem();
        void setLexem(char* lexem);
        int getValue();
        void setValue(int value);
    private:
        TType type;
        int line;
        int column;
        char lexem[MAX_LEXEM_LENGTH];
        int value;
};

#endif
