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

	Node* tmp;
	bool end;

	char* getTokenString(TType ttype);

	void getNextToken();
	void getNextExpectedToken(TType ttype);
	void getNextStatementToken();
	Node* prog();
	Node* decls();
	Node* decl();
	Node* statements();
	Node* statement();
};

#endif /* PARSER_H_ */
