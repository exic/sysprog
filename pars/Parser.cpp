#include "Parser.hpp"

Parser::Parser(Scanner* scanner) {
	this->scanner = scanner;
}

Parser::~Parser() {

}

void Parser::parse() {
	cout << ">> Start Parsing" << endl;
	this->parseTree = new ParseTree();
	prog(this->parseTree->getRootNode());
	cout << ">> End Parsing" << endl;
}

void Parser::prog(Node* node) {
	getNextToken();
	Node* prog = node->addChildNode(Rule::PROG);
	if (this->currentToken->getType() == INT) {
		decls(prog);
	}
	if (this->currentToken->getType() == PRINT) {

	}
}

void Parser::decls(Node* node) {
	while (this->currentToken->getType() == INT) {
		Node* decls = node->addChildNode(Rule::DECLS);
		decl(decls);
		getNextToken();
	}
}

void Parser::decl(Node* node) {
	node->setRule(Rule::DECL);
	// int
	Node* tmp = new Node(Rule::KEYWORD);
	tmp->setToken(this->currentToken);
	node->addChildNode(tmp);
	// identifier
	getNextExpectedToken(IDENTIFIER);
	tmp = new Node(Rule::IDENTIFIER);
	tmp->setToken(this->currentToken);
	node->addChildNode(tmp);
	// semicolon
	getNextExpectedToken(SIGN_SEMICOLON);
	tmp = new Node(Rule::SEMICOLON);
	tmp->setToken(this->currentToken);
	node->addChildNode(tmp);
}

void Parser::getNextToken() {
	this->currentToken = scanner->nextToken();
	if (!this->currentToken) {
		cout << "EOF" << endl;
		exit(1);
	}

	//=========================================================
	// SCANNEROUTPUT
	//=========================================================
	const char* ttype_str[] = { "NO_TYPE", "INTEGER", "IDENTIFIER", "PRINT",
		"READ", "IF", "ELSE", "WHILE", "INT", "ADDITITON", "SUBTRACTION",
		"DIVISION", "MULTIPLICATION", "LT", "GT", "ASSIGN", "NE",
		"EXCLAMATION", "AMPERSAND", "SEMICOLON", "COLON", "LEFTBRACKET",
		"RIGHTBRACKET", "LEFTANGLEBRACKET", "RIGHTANGLEBRACKET",
		"LEFTSQUAREBRACKET", "RIGHTSQUAREBRACKET" };

	if (this->currentToken->getType() == NO_TYPE) {
		cout << "NO_TYPE Token" << endl;
	}

	cout << "Token " << ttype_str[this->currentToken->getType()]
		<< " Line: " << this->currentToken->getLine()
		<< ", Column " << this->currentToken->getColumn();

	if (this->currentToken->getType() == IDENTIFIER) {
		cout << ", Lexem: " << this->currentToken->getEntry()->getLexem();
	} else if (this->currentToken->getType() == INTEGER) {
		cout << ", Value: " << this->currentToken->getValue();
	}

	cout << endl;
	//=========================================================
}

void Parser::getNextExpectedToken(TType ttype) {
	this->currentToken = scanner->nextToken();
	if (!this->currentToken) {
		cout << "ERROR: Expected: TType, Got: EOF" << endl;
		exit(1);
	} else if (this->currentToken->getType() != ttype) {
		cout << "ERROR: Expected: TType, Got: TType" << endl;
		exit(1);
	}

	//=========================================================
	// SCANNEROUTPUT
	//=========================================================
	const char* ttype_str[] = { "NO_TYPE", "INTEGER", "IDENTIFIER", "PRINT",
		"READ", "IF", "ELSE", "WHILE", "INT", "ADDITITON", "SUBTRACTION",
		"DIVISION", "MULTIPLICATION", "LT", "GT", "ASSIGN", "NE",
		"EXCLAMATION", "AMPERSAND", "SEMICOLON", "COLON", "LEFTBRACKET",
		"RIGHTBRACKET", "LEFTANGLEBRACKET", "RIGHTANGLEBRACKET",
		"LEFTSQUAREBRACKET", "RIGHTSQUAREBRACKET" };

	if (this->currentToken->getType() == NO_TYPE) {
		cout << "NO_TYPE Token" << endl;
	}

	cout << "Token " << ttype_str[this->currentToken->getType()]
		<< " Line: " << this->currentToken->getLine()
		<< ", Column " << this->currentToken->getColumn();

	if (this->currentToken->getType() == IDENTIFIER) {
		cout << ", Lexem: " << this->currentToken->getEntry()->getLexem();
	} else if (this->currentToken->getType() == INTEGER) {
		cout << ", Value: " << this->currentToken->getValue();
	}

	cout << endl;
	//=========================================================
}
