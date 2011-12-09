#include "Parser.hpp"


Parser::Parser(Scanner* scanner) {
	this->scanner = scanner;
	tmp = new Node(Rule::EMPTY);
	end = false;
}

Parser::~Parser() {

}

void Parser::parse() {
	cout << ">> Start Parsing" << endl;
	this->parseTree = new ParseTree();
	Node* nProg = prog();
	this->parseTree->getRootNode()->addChildNode(nProg);
	cout << ">> End Parsing" << endl;
	cout << ">> Start Printing Tree" << endl;
	this->parseTree->printTree(this->parseTree->getRootNode());
	cout << ">> End Printing Tree" << endl;
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
		Node* nStatements = statements();
		prog->addChildNode(nStatements);
	}
	return prog;
}

Node* Parser::decls() {
	Node* decls = new Node(Rule::DECLS);
	while (!end && (this->currentToken->getType() == INT)) {
		Node* nDecl = decl();
		decls->addChildNode(nDecl);
		getNextToken();
	}
	return decls;
}

Node* Parser::decl() {
	Node* decl = new Node(Rule::DECL);

	// int
	tmp = new Node(Rule::KEYWORD);
	tmp->setToken(this->currentToken);
	decl->addChildNode(tmp);
	// identifier
	getNextExpectedToken(IDENTIFIER);
	tmp = new Node(Rule::IDENTIFIER);
	tmp->setToken(this->currentToken);
	decl->addChildNode(tmp);
	// semicolon
	getNextExpectedToken(SIGN_SEMICOLON);
	tmp = new Node(Rule::KEYWORD);
	tmp->setToken(this->currentToken);
	decl->addChildNode(tmp);

	return decl;
}

Node* Parser::statements() {
	Node* statements = new Node(Rule::STATEMENTS);
	while (!end && (this->currentToken->getType() == IDENTIFIER || this->currentToken->getType() == PRINT ||
		   /*this->currentToken->getType() == READ ||*/ this->currentToken->getType() == SIGN_LEFTANGLEBRACKET ||
		   this->currentToken->getType() == IF || this->currentToken->getType() == WHILE)) {
		Node* nStatement = statement();
		statements->addChildNode(nStatement);
		getNextToken();
	}
	return statements;
}

Node* Parser::statement() {
	Node* statement = new Node(Rule::STATEMENT);
	if (this->currentToken->getType() == PRINT) {
		// print
		tmp = new Node(Rule::KEYWORD);
		tmp->setToken(this->currentToken);
		statement->addChildNode(tmp);
		// (
		getNextExpectedToken(SIGN_LEFTBRACKET);
		tmp = new Node(Rule::KEYWORD);
		tmp->setToken(this->currentToken);
		statement->addChildNode(tmp);
		// )
		getNextExpectedToken(SIGN_RIGHTBRACKET);
		tmp = new Node(Rule::KEYWORD);
		tmp->setToken(this->currentToken);
		statement->addChildNode(tmp);
		// ;
		getNextExpectedToken(SIGN_SEMICOLON);
		tmp = new Node(Rule::KEYWORD);
		tmp->setToken(this->currentToken);
		statement->addChildNode(tmp);
	}
	return statement;
}

void Parser::getNextToken() {
	this->currentToken = scanner->nextToken();
	if (!this->currentToken) {
		end = true;
		return;
	}

	//=========================================================
	// SCANNEROUTPUT
	//=========================================================
	if (this->currentToken->getType() == NO_TYPE) {
		cout << "NO_TYPE Token" << endl;
	}

	cout << "Token " << getTokenString(this->currentToken->getType())
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
		cout << "ERROR: Expected: " << getTokenString(ttype) << ", Got: EOF" << endl;
		cout << "Stop ..." << endl;
		exit(0);
	} else if (this->currentToken->getType() != ttype) {
		cout << "ERROR: Expected: " << getTokenString(ttype) << ", Got: "
		     << getTokenString(this->currentToken->getType()) << endl;
		cout << "Stop ..." << endl;
		exit(0);
	}

	//=========================================================
	// SCANNEROUTPUT
	//=========================================================
	if (this->currentToken->getType() == NO_TYPE) {
		cout << "NO_TYPE Token" << endl;
	}

	cout << "Token " << getTokenString(this->currentToken->getType())
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

char* Parser::getTokenString(TType ttype) {
	char* ttype_str[30] = { (char*)"NO_TYPE", (char*)"INTEGER", (char*)"IDENTIFIER", (char*)"PRINT",
		(char*)"READ", (char*)"IF", (char*)"ELSE", (char*)"WHILE", (char*)"INT", (char*)"ADDITITON", (char*)"SUBTRACTION",
		(char*)"DIVISION", (char*)"MULTIPLICATION", (char*)"LT", (char*)"GT", (char*)"ASSIGN", (char*)"NE",
		(char*)"EXCLAMATION", (char*)"AMPERSAND", (char*)"SEMICOLON", (char*)"COLON", (char*)"LEFTBRACKET",
		(char*)"RIGHTBRACKET", (char*)"LEFTANGLEBRACKET", (char*)"RIGHTANGLEBRACKET",
		(char*)"LEFTSQUAREBRACKET", (char*)"RIGHTSQUAREBRACKET" };
	return ttype_str[ttype];
}
