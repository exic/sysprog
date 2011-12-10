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
private:
	Node* root;

	int depth;
};

#endif /* PARSETREE_HPP_ */
