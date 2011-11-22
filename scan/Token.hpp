#ifndef TOKEN
#define TOKEN

#include "TType.hpp"
#include "Constants.hpp"
#include "string.h"
#include "../symtab/SymtabEntry.hpp"


class Token {
    public:
        Token(TType pType, int pLine, int pColumn);
        TType getType();
        int getLine();
        int getColumn();
        int getValue();
        void setValue(int value);
        SymtabEntry* getEntry() { return entry; };
        void setEntry(SymtabEntry* entry) { this->entry = entry; };
    private:
        TType type;
        SymtabEntry* entry;
        int line;
        int column;
        int value;
};

#endif
