#include "Automat.hpp"

Automat::Automat() {
    line = 1;
    column = 0;
    lastchar = '\0';
    status = NONE;
}

Automat::~Automat() {
}

void Automat::readChar(char c) {
    column++;
    if (c == '\n') {
        status = NEWLINE;
    } else if (c == -1) { // eof
        status = FINAL;
    } else if (c == ' ') {
        status = TOKEN_READ;
    } else {
        lastchar = c;
    }
    return;
}

bool Automat::isTokenRead() {
    return (
            status == TOKEN_READ
            ||
            status == NEWLINE
            ||
            status == FINAL
           );
}

bool Automat::isError() {
    return status == ERROR;
}

bool Automat::isEof() {
    return status == FINAL;
}

Token* Automat::getToken() {
    if (!isTokenRead() || isError() || isEof()) {
        return 0;
    }
    Token* newToken;
    if (lastchar == '=') {
        newToken = new Token(SIGN_EQ, line, column);
    } else if (lastchar == ';') {
        newToken = new Token(SIGN_SEMICOLON, line, column);
    }
    newToken = new Token(PRINT, line, column-1);

    if (status == NEWLINE) {
        line++;
        column = 0;
    }

    status = NONE;
    return newToken;
}
