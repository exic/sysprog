#ifndef AUTOMAT
#define AUTOMAT

#include "Token.hpp"
#include "Status.hpp"

#include <iostream>
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
    private:
        bool isDigit(char c);
        bool isLetter(char c);
        bool isSign(char c);
        Status statusNONE(char c);
        Status statusCOMMENT(char c);
        Status statusIDENTIFIER(char c);
        Status statusINT(char c);
        Status statusSIGN(char c);
        int line;
        int column;
        char lastchar;
        int sign_index;
        char sign[4];
        int lexem_index;
        char lexem[128];
        int value;
        int unget;
        Status status;
};

#endif
