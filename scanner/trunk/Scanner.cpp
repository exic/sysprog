#include "Scanner.hpp"

Scanner::Scanner(char* filename) {
    automat = new Automat(new Buffer(filename));
    state = 0;
}

Scanner::~Scanner() {
    delete automat;
}

Token* Scanner::nextToken() {
    Token* token = automat->readChar();
    //symtable->insert(token->getLexem(), token->getType());
    if (state == 0) {
        state = 1;
        return new Token(PRINT, 1, 2);
    }
    return token;
}
