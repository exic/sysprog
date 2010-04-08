#include "Scanner.hpp"

Scanner::Scanner(char* filename) {
    automat = new Automat(new Buffer(filename));
}

Scanner::~Scanner() {
    delete automat;
}

Token* Scanner::nextToken() {
    Token* token = automat->readChar();
    //symtable->insert(token->getLexem(), token->getType());
    return token;
}
