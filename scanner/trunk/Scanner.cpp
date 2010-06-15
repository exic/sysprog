#include "Scanner.hpp"

#include <iostream>
using namespace std;

Scanner::Scanner(char* filename) {
    automat = new Automat();
    buffer = new Buffer(filename);
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
        char c = buffer->getchar();
        // cout << "Lese Zeichen \"" << c << "\"" << endl;
        automat->readChar(c);
        // cout << "Automat-Status: " << automat->getStatus() << endl;
    }
    //symtable->insert(token->getLexem(), token->getType());
    return token;
}
