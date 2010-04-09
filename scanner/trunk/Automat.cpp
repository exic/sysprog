#include "Automat.hpp"

Automat::Automat() {
    line = 1;
    column = 0;
    eof = false;
    error = false;
    final = true;
}

Automat::~Automat() {
}

// todo
void Automat::readChar(char c) {
    column++;
    if (c == 10) { // newline
        line++;
        column = 0;
    } else if (c == -1) {
        eof = true;
    }
    final = true;
    return;
}

bool Automat::isFinal() {
    return final;
}

bool Automat::isError() {
    return error;
}

bool Automat::isEof() {
    return eof;
}

Token* Automat::getToken() {
    final = false;
    if (eof) {
        return 0;
    }
    return new Token(SIGN_AMPERSAND, line, column);
}
