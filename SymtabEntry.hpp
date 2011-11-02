#ifndef SYMTABENTRY_HPP
#define	SYMTABENTRY_HPP

#include "TType.hpp"

class SymtabEntry {
public:
    SymtabEntry(TType type, char* lexem);
    virtual ~SymtabEntry();
    SymtabEntry* getNext() { return next; };
    void setNext(SymtabEntry* next) { this->next = next; };
    char* getLexem() { return lexem; };
    void setLexem(char* lexem) { this->lexem = lexem; };
private:
    char* lexem;
    TType type;
    SymtabEntry* next;
};

#endif	/* SYMTABENTRY_HPP */

