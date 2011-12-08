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

	void getNextToken();
	void getNextExpectedToken(TType ttype);
	Node* prog();
	Node* decls();
	Node* decl();
};

#endif /* PARSER_H_ */
