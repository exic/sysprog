#ifndef SYMTABLE
#define SYMTABLE

#include "TType.hpp"
#include "Token.hpp"

class Symtable {
    public:
        char* insert(char* lexem, TType type);
        Token* lookup(char* key);
};

#endif
