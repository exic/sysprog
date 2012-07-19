#ifndef SYMTABENTRY_HPP
#define    SYMTABENTRY_HPP

#include "../scan/TType.hpp"
#include "../pars/ParseEnums.hpp"

class SymtabEntry {
public:
    SymtabEntry(TType type, char* lexem);
    virtual ~SymtabEntry();
    SymtabEntry* getNext() { return next; };
    void setNext(SymtabEntry* next) { this->next = next; };
    char* getLexem() { return lexem; };
    void setLexem(char* lexem) { this->lexem = lexem; };
    ParseEnums::Type getParseType() { return parseType; };
    void setParseType(ParseEnums::Type parseType) { this->parseType = parseType; };

private:
    char* lexem;
    TType type;  // TODO: Wird des benötigt?
    ParseEnums::Type parseType;
    SymtabEntry* next;
};

#endif    /* SYMTABENTRY_HPP */

