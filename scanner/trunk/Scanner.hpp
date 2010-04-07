#ifndef SCANNER
#define SCANNER

#include "Token.hpp"
#include "Buffer.hpp"
#include "Automat.hpp"
#include "Symtable.hpp"

class Scanner {
    public:
        Scanner(char* filename);
        Token* nextToken();
    private:
        Buffer* buffer;
        Automat* automat;
        Symtable* symtable;
};

#endif
