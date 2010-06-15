#include "Automat.hpp"

Automat::Automat() {
    line = 1;
    column = 0;
    lastchar = '\0';
    lexem_index = 0;
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
        case READING_IDENTIFIER:
            status = statusIDENTIFIER(c);
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
        return statusINT(c);
    } else if (isLetter(c)) {
        return statusIDENTIFIER(c);
    } else if (isSign(c)) {
        return statusSIGN(c);
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
    return ERROR;
}

Status Automat::statusINT(char c) {
    if (!isDigit(c)) {
        return READ_INT;
    }
    return READING_INT;
}

Status Automat::statusIDENTIFIER(char c) {
    // cout << "index: " << lexem_index <<endl;
    if (!isDigit(c) && !isLetter(c)) {
        lexem[lexem_index] = '\0';
        lexem_index = 0;
        return READ_IDENTIFIER;
    }
    lexem[lexem_index++] = c;
    return READING_IDENTIFIER;
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
        || status == READ_IDENTIFIER
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
const char* status_str[] = { "FINAL", "ERROR", "NONE", "READING_INT", "READING_IDENTIFIER", "READING_SIGN", "READ_INT", "READ_IDENTIFIER", "READ_SIGN", "TOKEN_READ", "NEWLINE" };
    if (!isTokenRead() || isError() || isEof()) {
        return 0;
    } else {
        column--;
    }
    Token* newToken = 0;
    if (status == READ_SIGN) {
        if (sign[0] == '+') {
            newToken = new Token(SIGN_ADDITITON, line, column);
        } else if (sign[0] == '-') {
            newToken = new Token(SIGN_SUBTRACTION, line, column);
        } else if (sign[0] == '*') {
            newToken = new Token(SIGN_MULTIPLICATION, line, column);
        } else if (sign[0] == '<') {
            newToken = new Token(SIGN_LT, line, column);
        } else if (sign[0] == '>') {
            newToken = new Token(SIGN_GT, line, column);
        } else if (sign[0] == '=') {
            newToken = new Token(SIGN_ASSIGN, line, column);
        } else if (sign[0] == '!') {
            newToken = new Token(SIGN_EXCLAMATION, line, column);
        } else if (sign[0] == '&') {
            newToken = new Token(SIGN_AMPERSAND, line, column);
        } else if (sign[0] == ';') {
            newToken = new Token(SIGN_SEMICOLON, line, column);
        } else if (sign[0] == '(') {
            newToken = new Token(SIGN_LEFTBRACKET, line, column);
        } else if (sign[0] == ')') {
            newToken = new Token(SIGN_RIGHTBRACKET, line, column);
        } else if (sign[0] == '{') {
            newToken = new Token(SIGN_LEFTANGLEBRACKET, line, column);
        } else if (sign[0] == '}') {
            newToken = new Token(SIGN_RIGHTANGLEBRACKET, line, column);
        } else if (sign[0] == '[') {
            newToken = new Token(SIGN_LEFTSQUAREBRACKET, line, column);
        } else if (sign[0] == ']') {
            newToken = new Token(SIGN_RIGHTSQUAREBRACKET, line, column);
        }
    } else if (status == READ_INT) {
        newToken = new Token(INTEGER, line, column);
    } else if (status == READ_IDENTIFIER) {
        newToken = new Token(IDENTIFIER, line, column);
        //cout << "lexem: " << lexem << endl;
        newToken->setLexem(lexem);
    } else if (status == NEWLINE) {
        line++;
        column = 0;
    } else {
        cout << "Status: " << status_str[status] << endl;
        newToken = new Token(PRINT, line, column);
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
int Automat::getLine() {
    return line;
}
int Automat::getColumn() {
    return column;
}
