#include "Symtable.hpp"

Symtable::Symtable() {  
    stringTab = new StringTab();
    for (int i = 0; i < SYMTABLE_HASHTABLESIZE; i++) {
        hashTable[i] = 0;
    }   
}

Symtable::~Symtable() {
}

SymtabEntry* Symtable::insert(char* lexem, TType type) {
    int iHash = hash(lexem);
    if (hashTable[iHash] == 0) {
        hashTable[iHash] = new SymtabEntry(type, stringTab->insert(lexem, strlen(lexem)));
        return hashTable[iHash];
    } else {
        SymtabEntry* current = hashTable[iHash];
        while (current != 0) {
            if (!strcmp(current->getLexem(), lexem)) {
                return current;
            }
            current = current->getNext();
        }
        current->setNext(new SymtabEntry(type, stringTab->insert(lexem, strlen(lexem))));
        return current->getNext();
    }
}

int Symtable::hash(char* lexem) {
    int counter = 0;
    int firstChar = *lexem;
    while (*(lexem + counter) != '\0') {
        counter++;
    }
    int lastChar = *(lexem + (counter - 1));
    
    return (16 * firstChar + 8 * lastChar + counter) % SYMTABLE_HASHTABLESIZE;
}
