#ifndef SCANNER
#define SCANNER

#include "Token.hpp"
#include "Buffer.hpp"
#include "Automat.hpp"
#include "Symtable.hpp"

class Scanner {
    public:
        Scanner(char* filename);
        ~Scanner();
        Token* nextToken();
    private:
        Automat* automat;
        Symtable* symtable;
};

#endif
