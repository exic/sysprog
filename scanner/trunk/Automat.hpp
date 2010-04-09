#ifndef AUTOMAT
#define AUTOMAT

#include "Token.hpp"

class Automat {
    public:
        Automat();
        ~Automat();
        void readChar(char c);
        bool isFinal();
        bool isError();
        bool isEof();
        Token* getToken();
    private:
        bool final;
        bool error;
        bool eof;
        int line;
        int column;
};

#endif
