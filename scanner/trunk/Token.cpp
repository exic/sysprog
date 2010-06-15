#include "Token.hpp"

Token::Token(TType pType, int pLine, int pColumn) {
    type = pType;
    line = pLine;
    column = pColumn;
}

TType Token::getType() {
    return type;
}

int Token::getLine() {
    return line;
}

int Token::getColumn() {
    return column;
}

char* Token::getLexem() {
    return lexem;
}
void Token::setLexem(char* lexem) {
    strcpy(this->lexem, lexem);
}
