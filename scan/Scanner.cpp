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

        int unget = automat->getUnget();
        while (unget-- > 0) {
//            cout << "unget" << endl;
            buffer->ungetchar();
        }

        char c = buffer->getchar();
//        cerr << "Lese Zeichen \"" << c << "\"" << endl;
        automat->readChar(c);

//const char* status_str[] = { "NONE", "FINAL", "ERROR", "READING_COMMENT", "READING_IDENTIFIER", "READING_INT", "READING_SIGN", "READ_IDENTIFIER", "READ_INT", "READ_SIGN", "TOKEN_READ", "NEWLINE" };
        if (automat->getStatus() == ERROR) {
            cerr << "Unknown character at line " << automat->getLine() << ", column " << automat->getColumn() << endl;
        }
//        cout << "Automat-Status: " << status_str[automat->getStatus()] << endl;
    }
    
    if (token && token->getType() == IDENTIFIER) {
        SymtabEntry* entry = symtable->insert(automat->getLexem(), token->getType());
        token->setEntry(entry);        
    }
    
    return token;
}
