#include "Automat.hpp"

Automat::Automat() {
    line = 1;
    column = 0;
    sign_index = 0;
    lexem_index = 0;
    value_str_index = 0;
    unget = 0;
    status = NONE;
}

Automat::~Automat() {
}

void Automat::readChar(char c) {
    column++;
//    cout << "char: " << c << ", col: " << column << endl;
    unget = 0;

    switch (status) {
        case READING_COMMENT:
            status = statusCOMMENT(c);
            break;
        case READING_IDENTIFIER:
            status = statusIDENTIFIER(c);
            break;
        case READING_INT:
            status = statusINT(c);
            break;
        case READING_SIGN:
            status = statusSIGN(c);
            break;
        case NONE:
        default:
            status = statusNONE(c);
            break;
    }

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
                return NONE;
        }
    }
    return ERROR;
}


Status Automat::statusCOMMENT(char c) {
    if (c == '*') {
        // shameless abuse of sign[] array
//        cout << "sign[0] is: " << (int) sign[0] << endl;
        sign[0] = '*';
    } else if (sign[0] == '*' && c == ')') {
        // reset?
        sign[0] = '\0';
        sign_index = 0;
        return NONE;
    } else {
        sign[0] = '\0';
    }

    if (c == '\n') {
        newline();
    } else if (c == -1) {
        return FINAL_COMMENT_NOT_CLOSED_ERROR;
    }
    return READING_COMMENT;
}

Status Automat::statusIDENTIFIER(char c) {
    if (!isDigit(c) && !isLetter(c)) {
        return READ_IDENTIFIER;
    }
    lexem[lexem_index++] = c;
    return READING_IDENTIFIER;
}

Status Automat::statusINT(char c) {
    if (!isDigit(c)) {
        return READ_INT;
    }
    value_str[value_str_index++] = c;
    return READING_INT;
}

Status Automat::statusSIGN(char c) {
    if (!isSign(c)) {
        return READ_SIGN;
    }

    if (sign_index == 1 && sign[0] != '(' && sign[0] != '<') {
        return READ_SIGN;
    }

    if (sign_index == 1) {
        if (sign[0] == '(') {
            if (c == '*') {
                return READING_COMMENT;
            }
            return READ_SIGN;
        } else if (sign[0] == '<') {
            if (c != '=') {
                return READ_SIGN;
            }
        }
    } else if (sign_index == 2) {
        if (c != '>') {
            unget = 2;
            sign[1] = '\0';
            return READ_SIGN;
        }
    } else if (sign_index == 3) {
        return READ_SIGN;
    }

    sign[sign_index++] = c;
    return READING_SIGN;
}

bool Automat::isTokenRead() {
    return (
        status == TOKEN_READ
        || status == READ_INT
        || status == READ_IDENTIFIER
        || status == READ_SIGN
        || status == FINAL
   );
}

bool Automat::isError() {
    return status == ERROR;
}

bool Automat::isEof() {
    return status == FINAL || status == FINAL_COMMENT_NOT_CLOSED_ERROR;
}

void Automat::newline() {
    line++;
    column = 0;
}

Token* Automat::getToken() {

    const char* status_str[] = { "NONE", "FINAL",
        "FINAL_COMMENT_NOT_CLOSED_ERROR", "ERROR", "READING_COMMENT",
        "READING_IDENTIFIER", "READING_INT", "READING_SIGN", "READ_IDENTIFIER",
        "READ_INT", "READ_SIGN", "TOKEN_READ", "NEWLINE" };

    if (status == NEWLINE) {
        newline();
        return 0;
    }
    if (!isTokenRead() || isError() || isEof()) {
        return 0;
    }

    column--;
    Token* newToken = 0;
    TType ttype = NO_TYPE;

    int token_length = 1;
    if (status == READ_IDENTIFIER) {
        lexem[lexem_index] = '\0';
        lexem_index = 0;

        token_length = strlen(lexem);

        if (strcmp("print", lexem) == 0) {
            ttype = PRINT;
        } else if (strcmp("read", lexem) == 0) {
            ttype = READ;
        } else {
            ttype = IDENTIFIER;
        }
    } else if (status == READ_INT) {
        value_str[value_str_index] = '\0';
        value_str_index = 0;
        token_length = strlen(value_str);
        ttype = INTEGER;
    } else if (status == READ_SIGN) {
        sign[sign_index] = '\0';
        sign_index = 0;
        // cout << "Read sign: " << sign << endl;

        if (strcmp("+", sign) == 0) {
            ttype = SIGN_ADDITITON;
        } else if (strcmp("-", sign) == 0) {
            ttype = SIGN_SUBTRACTION;
        } else if (strcmp("/", sign) == 0) {
            ttype = SIGN_DIVISION;
        } else if (strcmp("*", sign) == 0) {
            ttype = SIGN_MULTIPLICATION;
        } else if (strcmp("<", sign) == 0) {
            ttype = SIGN_LT;
        } else if (strcmp("<=>", sign) == 0) {
            ttype = SIGN_NE;
            token_length = 3;
        } else if (strcmp(">", sign) == 0) {
            ttype = SIGN_GT;
        } else if (strcmp("=", sign) == 0) {
            ttype = SIGN_ASSIGN;
        } else if (strcmp("!", sign) == 0) {
            ttype = SIGN_EXCLAMATION;
        } else if (strcmp("&", sign) == 0) {
            ttype = SIGN_AMPERSAND;
        } else if (strcmp(";", sign) == 0) {
            ttype = SIGN_SEMICOLON;
        } else if (strcmp("(", sign) == 0) {
            ttype = SIGN_LEFTBRACKET;
        } else if (strcmp(")", sign) == 0) {
            ttype = SIGN_RIGHTBRACKET;
        } else if (strcmp("{", sign) == 0) {
            ttype = SIGN_LEFTANGLEBRACKET;
        } else if (strcmp("}", sign) == 0) {
            ttype = SIGN_RIGHTANGLEBRACKET;
        } else if (strcmp("[", sign) == 0) {
            ttype = SIGN_LEFTSQUAREBRACKET;
        } else if (strcmp("]", sign) == 0) {
            ttype = SIGN_RIGHTSQUAREBRACKET;
        } else {
            cout << "Sign token \"" << sign << "\" not found, line " << line << ", column " << column << endl;
        }
    } else {
        cerr << "Not a valid status: " << status_str[status] << endl;
//        newToken = new Token(PRINT, line, column);
    }

    if (ttype != NO_TYPE) {
        // FIXME: pointer + null vs. enum...
//        cout << "newtoken " << ttype << endl;
        newToken = new Token(ttype, line, column - (token_length - 1));
    }

    if (status == READ_INT && newToken != NULL) {
    	char* pEnd;
    	long int value = strtol(value_str, &pEnd, 10);
    	if (errno == ERANGE) {
    		 cerr << "Integer out of Range" << endl;
    	}
        newToken->setValue(value);
    }

    status = NONE;
    if (unget < 1) {
        unget = 1;
    }
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
