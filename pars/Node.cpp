#include "Node.hpp"

Node::Node(Rule::Type rule, Token* token) {
    this->init(rule, token);
}

Node::Node(Rule::Type rule) {
    this->init(rule, NULL);
}

void Node::init(Rule::Type rule, Token* token) {
    this->rule = rule;
    this->token = token;
    this->childNodesCount = 0;
}

Node::~Node() {
    for (int i = 0; i < childNodesCount; i++)
        delete childNodes[i];
    delete token;
}

Node* Node::addChildNode(Rule::Type rule) {
    if (childNodesCount < 10) {
        Node* node = new Node(rule);
        this->childNodes[childNodesCount] = node;
        childNodesCount++;
        return node;
    } else {
        cerr << "Maximum an ChildNodes erreicht" << endl;
        return NULL;
    }
}

void Node::addChildNode(Node* node) {
    if (childNodesCount < 10) {
        this->childNodes[childNodesCount] = node;
        childNodesCount++;
    } else {
        cerr << "Maximum an ChildNodes erreicht" << endl;
    }
}

Node* Node::getChildNode(int index) {
    if (index > 0 || index < 10) {
        return childNodes[index];
    } else {
        cerr << "ChildNode Index außer Range" << endl;
        return NULL;
    }
}
