#ifndef AUTOMAT
#define AUTOMAT

#include "Token.hpp"
#include "Status.hpp"

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
        int line;
        int column;
        char lastchar;
        Status status;
};

#endif
