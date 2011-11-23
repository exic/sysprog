#include "StringTab.hpp"

StringTab::StringTab() {
    first = new StringTabNode();
    actual = first;
    freeP = first->getVector();
    freeSpace = STRINGTABNODE_VECTORSIZE;
}

StringTab::~StringTab() {
}

char* StringTab::insert(char* lexem, int size) {
    char* tmp = freeP;
    if (size < freeSpace) {
        memcpy(freeP, lexem, size + 1);
        freeP[size] = '\0';
        freeP += size + 1;
//        std::cout << "Freespace vor dem Einfuegen von '" << lexem << "': " << freeSpace << std::endl;
        freeSpace -= size + 1;
//        std::cout << "Freespace nach dem Einfuegen von '" << lexem << "': " << freeSpace << std::endl;
        return tmp;
    } else {
        addStringTabNode();
        return insert(lexem, size);
    }
}

void StringTab::addStringTabNode() {
    StringTabNode* previous = actual;
    actual = new StringTabNode();
    previous->setNext(actual);
    freeP = actual->getVector();
    freeSpace = STRINGTABNODE_VECTORSIZE;
}

