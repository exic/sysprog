#ifndef STRINGTAB_HPP
#define    STRINGTAB_HPP

#include "StringTabNode.hpp"
#include "Constants.hpp"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


class StringTab {
public:
    StringTab();
    virtual ~StringTab();
    char* insert(char* lexem, int size);
private:
    StringTabNode* first;
    StringTabNode* actual;
    char* freeP;
    int freeSpace;
    
    void addStringTabNode();
};

#endif    /* STRINGTAB_HPP */

