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

int Token::getValue() {
    return value;
}

void Token::setValue(int value) {
    this->value = value;
}
