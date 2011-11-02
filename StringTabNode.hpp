#ifndef STRINGTABNODE_HPP
#define	STRINGTABNODE_HPP

#include "Constants.hpp"

class StringTabNode {
public:
    StringTabNode();
    virtual ~StringTabNode();
    char* getVector() { return vector; };
    void setNext(StringTabNode* next) { this->next = next; };
private:
    char* vector;
    StringTabNode* next;
};

#endif	/* STRINGTABNODE_HPP */

