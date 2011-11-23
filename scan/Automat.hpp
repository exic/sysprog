#ifndef AUTOMAT
#define AUTOMAT

#include "Token.hpp"
#include "Status.hpp"
#include "Constants.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>
using namespace std;

class Automat {
    public:
        Automat();
        ~Automat();
        void readChar(char c);
        bool isTokenRead();
        bool isError();
        bool isEof();
        int getLine();
        int getColumn();
        int getUnget() {
            return unget;
        }
        Token* getToken();
        Status getStatus() {
            return status;
        }
        char* getLexem() { return lexem; }
    private:
        bool isDigit(char c);
        bool isLetter(char c);
        bool isSign(char c);
        void newline();
        Status statusNONE(char c);
        Status statusCOMMENT(char c);
        Status statusIDENTIFIER(char c);
        Status statusINT(char c);
        Status statusSIGN(char c);
        int line;
        int column;
        char lastchar;
        int sign_index;
        char sign[MAX_SIGN_LENGTH];
        int lexem_index;
        char lexem[MAX_LEXEM_LENGTH];
        char value_str[MAX_LEXEM_LENGTH];
        int value_str_index;
        int unget;
        Status status;
};

#endif
