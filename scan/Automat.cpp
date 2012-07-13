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
    if (!Util::isDigit(c) && !Util::isLetter(c)) {
        return READ_IDENTIFIER;
    }

    if (lexem_index > (MAX_LEXEM_LENGTH - 2)) {
        lexem_index++;
    } else {
        lexem[lexem_index++] = c;
    }
    return READING_IDENTIFIER;
}

Status Automat::statusINT(char c) {
    if (!Util::isDigit(c)) {
        return READ_INT;
    }
    value_str[value_str_index++] = c;
    return READING_INT;
}

Status Automat::statusSIGN(char c) {
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
//            cout << "hereiam" << endl;
            unget = 2;
            sign[1] = '\0';
            return READ_SIGN;
        }
    } else if (sign_index == 3) {
        return READ_SIGN;
    }

    if (!Util::isSign(c)) {
        return READ_SIGN;
    }

    if (sign_index == 1 && sign[0] != '(' && sign[0] != '<') {
        return READ_SIGN;
    }

    sign[sign_index++] = c;
    return READING_SIGN;
}

Status Automat::statusNONE(char c) {
    if (Util::isDigit(c)) {
        return statusINT(c);
    } else if (Util::isLetter(c)) {
        return statusIDENTIFIER(c);
    } else if (Util::isSign(c)) {
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
    lexem[lexem_index++] = c;
    return ERROR;
}


void Automat::newline() {
    line++;
    column = 0;
}


bool Automat::isTokenRead() {
    return (
        status == READ_IDENTIFIER
        || status == READ_INT
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


Token* Automat::getToken() {

    if (status == NEWLINE) {
        newline();
        return 0;
    }
    if (isError()) {
        lexem[lexem_index] = '\0';
//        cerr << " got error symbol: " << lexem << ", index: " << lexem_index << endl;
        lexem_index = 0;
        status = NONE;
        return new Token(NO_TYPE, line, column);
    }
    if (!isTokenRead() || isEof()) {
        return 0;
    }

    if (unget < 1) {
        unget = 1;
    }
    column -= unget;

    Token* newToken = 0;
    TType ttype = NO_TYPE;

    int token_length = 1;
    if (status == READ_IDENTIFIER) {
        token_length = lexem_index;

        if (lexem_index > (MAX_LEXEM_LENGTH - 1)) {
            lexem[MAX_LEXEM_LENGTH - 1] = '\0';
            cerr << "Lexem too long, skipping: "  << lexem 
                << "... Line " << line << ", Column " << ( column - token_length)
                << ". Increase buffer size to read it." << endl;
            lexem[0] = '\0';
        } else {
            lexem[lexem_index] = '\0';
        }

        lexem_index = 0;

        if (strcmp("print", lexem) == 0) {
            ttype = PRINT;
        } else if (strcmp("read", lexem) == 0) {
            ttype = T_READ;
        } else if (strcmp("if", lexem) == 0) {
            ttype = IF;
        } else if (strcmp("else", lexem) == 0) {
            ttype = ELSE;
        } else if (strcmp("while", lexem) == 0) {
            ttype = WHILE;
        } else if (strcmp("int", lexem) == 0) {
            ttype = INT;
        } else if (strcmp("", lexem) != 0) {
            ttype = IDENTIFIER;
        }
    } else if (status == READ_INT) {
        value_str[value_str_index] = '\0';
        value_str_index = 0;
        token_length = strlen(value_str);
        ttype = INTEGER;
    } else if (status == READ_SIGN) {
        sign[sign_index] = '\0';
//        cout << "found sign: " << sign << ", index: " << sign_index << endl;
        sign_index = 0;

        ttype = getTokenTypeBySign();

        if (ttype == SIGN_NE) {
            token_length = 3;
        }
    } else {
        // Should not happen
        cerr << "Not a valid status: " << status << endl;
    }

    if (ttype != NO_TYPE) {
//        cout << "newtoken " << ttype << ", line " << line << ", column " << column << ", token_length " << token_length << endl;
        newToken = new Token(ttype, line, column - (token_length - 1));
    }

    if (status == READ_INT && newToken != NULL) {
        char* pEnd;
        long int value = strtol(value_str, &pEnd, 10);
        if (errno == ERANGE) {
             cerr << "Integer out of Range: "  << value_str << endl;
             newToken = 0;
        } else {
            newToken->setValue(value);
        }
    }

    status = NONE;
    return newToken;
}

TType Automat::getTokenTypeBySign() {
    if (strcmp("+", sign) == 0) {
        return SIGN_ADDITITON;
    } else if (strcmp("-", sign) == 0) {
        return SIGN_SUBTRACTION;
    } else if (strcmp("/", sign) == 0) {
        return SIGN_DIVISION;
    } else if (strcmp("*", sign) == 0) {
        return SIGN_MULTIPLICATION;
    } else if (strcmp("<", sign) == 0) {
        return SIGN_LT;
    } else if (strcmp("<=>", sign) == 0) {
        return SIGN_NE;
    } else if (strcmp(">", sign) == 0) {
        return SIGN_GT;
    } else if (strcmp("=", sign) == 0) {
        return SIGN_ASSIGN;
    } else if (strcmp("!", sign) == 0) {
        return SIGN_EXCLAMATION;
    } else if (strcmp("&", sign) == 0) {
        return SIGN_AMPERSAND;
    } else if (strcmp(";", sign) == 0) {
        return SIGN_SEMICOLON;
    } else if (strcmp(":", sign) == 0) {
        return SIGN_COLON;
    } else if (strcmp("(", sign) == 0) {
        return SIGN_LEFTBRACKET;
    } else if (strcmp(")", sign) == 0) {
        return SIGN_RIGHTBRACKET;
    } else if (strcmp("{", sign) == 0) {
        return SIGN_LEFTANGLEBRACKET;
    } else if (strcmp("}", sign) == 0) {
        return SIGN_RIGHTANGLEBRACKET;
    } else if (strcmp("[", sign) == 0) {
        return SIGN_LEFTSQUAREBRACKET;
    } else if (strcmp("]", sign) == 0) {
        return SIGN_RIGHTSQUAREBRACKET;
    }
    cout << "Sign token \"" << sign << "\" not found, line " << line << ", column " << column << endl;
    return NO_TYPE;
}

int Automat::getLine() {
    return line;
}
int Automat::getColumn() {
    return column;
}
