#include "Parser.hpp"

Parser::Parser(Scanner* scanner) {
	this->scanner = scanner;
}

Parser::~Parser() {

}

void Parser::parse() {
	cout << ">> Start Parsing" << endl;
	this->parseTree = new ParseTree();
	Node* nProg = prog();
	this->parseTree->setRootNode(nProg);
	cout << ">> End Parsing" << endl;
}

Node* Parser::prog() {
	getNextToken();
	Node* prog = new Node(Rule::PROG);
	if (this->currentToken->getType() == INT) {
		Node* nDecls = decls();
		prog->addChildNode(nDecls);
	}
	if (this->currentToken->getType() == IDENTIFIER || this->currentToken->getType() == PRINT ||
		this->currentToken->getType() == READ || this->currentToken->getType() == SIGN_LEFTANGLEBRACKET ||
		this->currentToken->getType() == IF || this->currentToken->getType() == WHILE) {

	}
	return prog;
}

Node* Parser::decls() {
	Node* decls = new Node(Rule::DECLS);
	while (this->currentToken->getType() == INT) {
		Node* nDecl = decl();
		decls->addChildNode(nDecl);
		getNextToken();
	}
	return decls;
}

Node* Parser::decl() {
	Node* decl = new Node(Rule::DECL);
	// int
	Node* tmp = new Node(Rule::KEYWORD);
	tmp->setToken(this->currentToken);
	decl->addChildNode(tmp);
	// identifier
	getNextExpectedToken(IDENTIFIER);
	tmp = new Node(Rule::IDENTIFIER);
	tmp->setToken(this->currentToken);
	decl->addChildNode(tmp);
	// semicolon
	getNextExpectedToken(SIGN_SEMICOLON);
	tmp = new Node(Rule::SEMICOLON);
	tmp->setToken(this->currentToken);
	decl->addChildNode(tmp);
	return decl;
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
