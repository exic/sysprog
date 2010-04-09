#include "Scanner.hpp"

Scanner::Scanner(char* filename) {
    automat = new Automat();
    buffer = new Buffer(filename);
    symtable = new Symtable();
    state = 0;
}

Scanner::~Scanner() {
    delete automat;
    delete buffer;
    delete symtable;
}

Token* Scanner::nextToken() {
    if (state == 0) {
        state = 1;
        return new Token(PRINT, 1, 2);
    }
    while (!automat->isFinal()) {
        automat->readChar(buffer->getchar());
        if (automat->isError()) {
            return 0;
        }
    }
    Token* token = automat->getToken();
    //symtable->insert(token->getLexem(), token->getType());
    return token;
}
