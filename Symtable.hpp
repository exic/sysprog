#ifndef SYMTABLE
#define SYMTABLE

#include "TType.hpp"
#include "Token.hpp"
#include "Buffer.hpp"

class Symtable {
    public:
        Symtable();
        ~Symtable();
        char* insert(char* lexem, TType type);
        Token* lookup(char* key);
};

#endif
