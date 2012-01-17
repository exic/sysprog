#ifndef NODE_HPP_
#define NODE_HPP_

#include "../scan/Token.hpp"
#include "Rule.hpp"
#include <iostream>

using namespace std;

class Node {
public:
    Node(Rule::Type rule);
    virtual ~Node();

    Rule::Type getRule() { return rule; };
    void setRule(Rule::Type rule) { this->rule = rule; };
    Node* getChildNode(int index);
    int getChildNodesCount() { return childNodesCount; };
    Token* getToken() { return token; };
    void setToken(Token* token) { this->token = token; };
    Node* addChildNode(Rule::Type rule);
    void addChildNode(Node* node);

private:
    Rule::Type rule;
    Node* childNodes[10];
    int childNodesCount;
    Token* token;
};

#endif /* NODE_HPP_ */
