#include "Scanner.hpp"

#include <iostream>
using namespace std;

Scanner::Scanner(char* filename) {
    automat = new Automat();
    buffer = new Buffer(filename, true);
    symtable = new Symtable();
}

Scanner::~Scanner() {
    delete automat;
    delete buffer;
    delete symtable;
}

Token* Scanner::nextToken() {
    Token* token;
    while (!(token = automat->getToken()) && !automat->isEof()) {

        int unget = automat->getUnget();
        while (unget > 0) {
            buffer->ungetchar();
            unget--;
        }

        automat->readChar(buffer->getchar());
    }

    if (token && (token->getType() == IDENTIFIER || token->getType() == NO_TYPE) ) {
        SymtabEntry* entry = symtable->insert(automat->getLexem(), token->getType());
        token->setEntry(entry);
    }

//    cout << "returning token " << token << endl;

    return token;
}
