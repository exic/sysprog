#ifndef AUTOMAT
#define AUTOMAT

#include "Token.hpp"
#include "Buffer.hpp"

class Automat {
    public:
        Automat(Buffer* buffer);
        ~Automat();
        Token* readChar();
    private:
        Buffer* buffer;
};

#endif
