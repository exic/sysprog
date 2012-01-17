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
    const char* ttype_str[] = { "NO_TYPE", "INTEGER", "IDENTIFIER", "PRINT",
        "READ", "IF", "ELSE", "WHILE", "INT", "ADDITITON", "SUBTRACTION",
        "DIVISION", "MULTIPLICATION", "LT", "GT", "ASSIGN", "NE",
        "EXCLAMATION", "AMPERSAND", "SEMICOLON", "COLON", "LEFTBRACKET",
        "RIGHTBRACKET", "LEFTANGLEBRACKET", "RIGHTANGLEBRACKET",
        "LEFTSQUAREBRACKET", "RIGHTSQUAREBRACKET" };

    for (int i = 0; i < depth; i++) {
        cout << "  ";
    }
    depth++;

    cout << node_str[node->getRule()];
    if (node->getRule() == Rule::IDENTIFIER) {
        cout << " - Lexem: " << node->getToken()->getEntry()->getLexem();
    } else if (node->getRule() == Rule::INTEGER) {
        cout << " - Wert: " << node->getToken()->getValue();
    } else if (node->getRule() == Rule::KEYWORD) {
        cout << " - Art: " << ttype_str[node->getToken()->getType()];
    }
    cout << endl;
    for (int i = 0; i < node->getChildNodesCount(); i++) {
        printTree(node->getChildNode(i));
    }

    depth--;
}
