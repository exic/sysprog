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
        Token* getToken();
        Status getStatus() {
            return status;
        }
    private:
        bool isDigit(char c);
        bool isLetter(char c);
        bool isSign(char c);
        Status statusNONE(char c);
        Status statusINT(char c);
        Status statusID(char c);
        Status statusSIGN(char c);
        int line;
        int column;
        char lastchar;
        char sign[3];
        Status status;
};

#endif
