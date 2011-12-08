#include "ParseTree.hpp"

ParseTree::ParseTree() {
	this->root = new Node(Rule::ROOT);

	depth = 0;
}

ParseTree::~ParseTree() {

}

void ParseTree::printTree(Node* node) {
	const char* node_str[] = { "ROOT", "PROG", "DECLS", "DECL", "ARRAY", "STATEMENTS", "STATEMENT", "EXP",
			"EXP2", "INDEX", "OP_EXP", "OP", "INTEGER", "IDENTIFIER", "KEYWORD", "SEMICOLON", "EMPTY" };

	for (int i = 0; i < depth; i++) {
		cout << " ";
	}
	depth++;

	cout << node_str[node->getRule()] << endl;
	for (int i = 0; i < node->getChildNodesCount(); i++) {
		printTree(node->getChildNode(i));
	}

	depth--;
}
