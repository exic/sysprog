#ifndef NODE_HPP_
#define NODE_HPP_

#include "../scan/Token.hpp"
#include "ParseEnums.hpp"
#include <iostream>

using namespace std;

class Node {
public:
    Node(ParseEnums::Rule rule, Token* token);
    Node(ParseEnums::Rule rule);
    virtual ~Node();

    ParseEnums::Rule getRule() { return this->rule; };
    void setRule(ParseEnums::Rule rule) { this->rule = rule; };
    ParseEnums::Type getType() { return this->type; };
    void setType(ParseEnums::Type type) { this->type = type; };

    Node* getChildNode(int index);
    int getChildNodesCount() { return childNodesCount; };
    Token* getToken() { return token; };
    void setToken(Token* token) { this->token = token; };
    Node* addChildNode(ParseEnums::Rule rule);
    void addChildNode(Node* node);

private:
    ParseEnums::Rule rule;
    ParseEnums::Type type;

    Node* childNodes[10];
    int childNodesCount;
    Token* token;
    void init(ParseEnums::Rule rule, Token* token);
};

#endif /* NODE_HPP_ */
