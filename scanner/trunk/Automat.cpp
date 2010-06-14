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

    switch (status) {
        case READING_INT:
            status = statusINT(c);
            break;
        case READING_ID:
            status = statusID(c);
            break;
        case READING_SIGN:
            status = statusSIGN(c);
            break;
        case NONE:
        default:
            status = statusNONE(c);
            break;
    }

    lastchar = c;
    return;
}

Status Automat::statusNONE(char c) {
    if (isDigit(c)) {
        return READING_INT;
    } else if (isLetter(c)) {
        return READING_ID;
    } else {
        switch (c) {
            case '\n':
                return NEWLINE;
            case -1: // eof
                return FINAL;
            case ' ':
                return status;
        }
    }
    return READING_SIGN;
}

Status Automat::statusINT(char c) {
    if (!isDigit(c)) {
        return READ_INT;
    }
    return READING_INT;
}

Status Automat::statusID(char c) {
    if (!isDigit(c) && !isLetter(c)) {
        return READ_ID;
    }
    return READING_ID;
}

Status Automat::statusSIGN(char c) {
    if (!isSign(c)) {
        sign[0] = lastchar;
        return READ_SIGN;
    }
    return READING_SIGN;
}

bool Automat::isTokenRead() {
    return (
        status == TOKEN_READ
        || status == READ_INT
        || status == READ_ID
        || status == READ_SIGN
        || status == NEWLINE
        || status == FINAL
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
    Token* newToken = 0;
    if (status == READ_SIGN) {
        if (sign[0] == '=') {
            newToken = new Token(SIGN_ASSIGN, line, column);
        } else if (sign[0] == ';') {
            newToken = new Token(SIGN_SEMICOLON, line, column);
        }
    } else if (status == READ_INT) {
        newToken = new Token(INTEGER, line, column-1);
    } else if (status == READ_ID) {
        newToken = new Token(IDENTIFIER, line, column-1);
    } else {
        newToken = new Token(PRINT, line, column-1);
    }

    if (status == NEWLINE) {
        line++;
        column = 0;
    }

    status = NONE;
    return newToken;
}

bool Automat::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool Automat::isLetter(char c) {
    return (c >= 'a' && c <= 'z')
        || (c >= 'A' && c <= 'Z');
}

bool Automat::isSign(char c) {
    switch (c) {
        case '+':
        case '-':
        case '/':
        case '*':
        case '<':
        case '>':
        case '=':
        case '!':
        case '&':
        case ';':
        case '(':
        case ')':
        case '{':
        case '}':
        case '[':
        case ']':
            return true;
        default:
            return false;
    }
}
