#ifndef SCANNER
#define SCANNER

#include "Automat.hpp"
#include "../buffer/Buffer.hpp"
#include "Token.hpp"
#include "TType.hpp"
#include "../symtab/Symtable.hpp"

class Scanner {
    public:

        /**
         * Construct a new Scanner instance by opening the file as passed by the argument.
         *
         * @param char* name of the file that will be scanned.
         */
        Scanner(char* filename);

        /**
         * Deletes this Scanner instance.
         */
        ~Scanner();

        /**
         * Return the next token that was scanned.
         *
         * @return Token next token, null if scanning is over.
         */
        Token* nextToken();
    private:
        Automat* automat;
        Buffer* buffer;
        Symtable* symtable;
};

#endif
