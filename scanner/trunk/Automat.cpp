#include "Automat.hpp"


Automat::Automat(Buffer* pBuffer) {
    this->buffer = pBuffer;
}

Automat::~Automat() {
    delete buffer;
}

Token* Automat::readChar() {
    return 0;
}

