#include "ParseTree.hpp"

ParseTree::ParseTree() {
	this->root = new Node(Rule::ROOT);
}

ParseTree::~ParseTree() {

}
