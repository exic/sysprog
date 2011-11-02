#ifndef SYMTABLE
#define SYMTABLE

#include "TType.hpp"
#include "Token.hpp"
#include "Buffer.hpp"
#include "SymtabEntry.hpp"
#include "StringTab.hpp"
#include "Constants.hpp"

class Symtable {
    public:
        Symtable();
        ~Symtable();
        SymtabEntry* insert(char* lexem, TType type);
    private:
        StringTab* stringTab;
        int hash(char* lexem);
        SymtabEntry* hashTable[SYMTABLE_HASHTABLESIZE];
};

#endif
