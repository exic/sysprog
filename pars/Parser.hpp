#ifndef PARSER_H_
#define PARSER_H_

#include "../scan/Scanner.hpp"
#include "../scan/TType.hpp"
#include "ParseTree.hpp"
#include "Node.hpp"
#include "Rule.hpp"
#include <iostream>

using namespace std;

class Parser {
public:
    Parser(Scanner* scanner);
    virtual ~Parser();
    void parse();
private:
    Scanner* scanner;
    ParseTree* parseTree;
    Token* currentToken;

    bool end;
    bool checkedNextToken;

    char* getTokenString(TType ttype);

    void scannerNextToken();
    void getNextToken();
    void getNextExpectedToken(TType ttype);
    void getNextStatementToken(bool inner, bool optional);
    void getNextExp2Token();
    bool checkNextTokenOp();
    bool checkNextToken(TType ttype);
    void writeScannerOutput();
    Node* prog();
    Node* decls();
    Node* decl();
    Node* statements();
    Node* statement();
    Node* index();
    Node* array();
    Node* exp();
    Node* exp2();
    Node* op_exp();
};

#endif /* PARSER_H_ */
