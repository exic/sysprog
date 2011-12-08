#ifndef PARSETREE_HPP_
#define PARSETREE_HPP_

#include "Node.hpp"

class ParseTree {
public:
	ParseTree();
	virtual ~ParseTree();
	Node* getRootNode() { return root; };
private:
	Node* root;
};

#endif /* PARSETREE_HPP_ */
