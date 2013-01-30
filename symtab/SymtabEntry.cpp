#include "SymtabEntry.hpp"

SymtabEntry::SymtabEntry(TType type, char* lexem) {
    this->type = type;
    this->lexem = lexem;
    this->next = 0;
    this->parseType = ParseEnums::NOTYPE;
}

SymtabEntry::~SymtabEntry() {
    
}

