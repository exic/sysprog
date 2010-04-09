#ifndef SCANNER
#define SCANNER

#include "Token.hpp"
#include "Automat.hpp"
#include "Symtable.hpp"
#include "TType.hpp"

class Scanner {
    public:
        Scanner(char* filename);
        ~Scanner();
        Token* nextToken();
    private:
        Automat* automat;
        Buffer* buffer;
        Symtable* symtable;
        int state;
};

#endif
