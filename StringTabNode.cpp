#include "StringTabNode.hpp"

StringTabNode::StringTabNode() {
    this->vector = new char[STRINGTABNODE_VECTORSIZE];
    this->next = 0;
}

StringTabNode::~StringTabNode() {
}

