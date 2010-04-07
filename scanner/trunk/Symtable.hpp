#ifndef SYMTABLE
#define SYMTABLE

#include "TType.hpp"

class Symtable {
    public:
        char* insert(char* lexem, TType type);
        lookup(char* key);
};

#endif
