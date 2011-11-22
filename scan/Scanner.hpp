#ifndef SCANNER
#define SCANNER

#include "Automat.hpp"
#include "../buffer/Buffer.hpp"
#include "Token.hpp"
#include "TType.hpp"
#include "../symtab/Symtable.hpp"

class Scanner {
    public:
        Scanner(char* filename);
        ~Scanner();
        Token* nextToken();
    private:
        Automat* automat;
        Buffer* buffer;
        Symtable* symtable;
};

#endif
