#ifndef PARSETREE_HPP_
#define PARSETREE_HPP_

#include "Node.hpp"
#include <iostream>

using namespace std;

class ParseTree {
public:
    ParseTree();
    virtual ~ParseTree();
    Node* getRootNode() { return root; };
    void setRootNode(Node* root) { this->root = root; };
    void printTree(Node* node);
    void printTree2(Node* node);
    bool typeCheck(Node* node);
    void makeCode(Node* node);
private:
    Node* root;
    int depth;
    int marker;
    void store(Node* node, ParseEnums::Type type);
    ParseEnums::Type get(Node* node);
};

#endif /* PARSETREE_HPP_ */
