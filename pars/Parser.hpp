#ifndef PARSER_H_
#define PARSER_H_

#include "../scan/Scanner.hpp"
#include "../scan/TType.hpp"
#include "../buffer/Buffer.hpp"
#include "ParseTree.hpp"
#include "Node.hpp"
#include "ParseEnums.hpp"
#include <iostream>

using namespace std;

class Parser {
public:
    Parser(Scanner* scanner, Buffer* buffer);
    virtual ~Parser();
    void parse();
private:
    Scanner* scanner;
    ParseTree* parseTree;
    Token* currentToken;

    Buffer* buffer;

    bool end;
    bool checkedNextToken;

    char* getTokenString(TType ttype);

    void scannerNextToken();
    // Returns, if there is a next token at all
    bool getNextToken();
    void getNextExpectedToken(TType ttype);
    void getNextStatementToken(bool inner, bool optional);
    void getNextExp2Token();
    bool checkNextTokenExists();
    bool checkNextTokenOp();
    bool checkNextTokenIsType(TType ttype);
    bool isOp(TType type);
    void writeScannerOutput();
    void printGotTokenInfo();
    Node* prog();
    Node* decls();
    Node* decl();
    Node* statements();
    Node* statement();
    Node* index();
    Node* array();
    Node* emptyArray();
    Node* exp();
    Node* exp2();
    Node* op_exp();
};

#endif /* PARSER_H_ */
