#include "Parser.hpp"


Parser::Parser(Scanner* scanner, Buffer* buffer) {
    this->scanner = scanner;
    this->buffer = buffer;
    end = false;
    checkedNextToken = false;
}

Parser::~Parser() {

}

void Parser::parse() {
    cout << ">> Start Parsing" << endl;
    this->parseTree = new ParseTree(buffer);
    this->parseTree->getRootNode()->addChildNode(prog());
    cout << ">> End Parsing" << endl;
    //cout << ">> Start Printing Tree" << endl;
    //this->parseTree->printTree(this->parseTree->getRootNode());
    //cout << ">> End Printing Tree" << endl;
    cout << ">> Start TypeCheck" << endl;
    this->parseTree->typeCheck(this->parseTree->getRootNode());
    //this->parseTree->printTree2(this->parseTree->getRootNode());
    cout << ">> End TypeCheck" << endl;
    cout << ">> Start MakeCode" << endl;
    this->parseTree->makeCode(this->parseTree->getRootNode());
    cout << ">> End MakeCode" << endl;
}

Node* Parser::prog() {
    Node* prog = new Node(ParseEnums::PROG);

    prog->addChildNode(decls());
    prog->addChildNode(statements());

    return prog;
}

Node* Parser::decls() {
    Node* decls = new Node(ParseEnums::DECLS);

    if (checkNextTokenIsType(INT)) {
    	// DECL
        decls->addChildNode(decl());
        // SEMICOLON
        getNextExpectedToken(SIGN_SEMICOLON);
        decls->addChildNode(new Node(ParseEnums::KEYWORD, this->currentToken));
        // DECLS
        decls->addChildNode(this->decls());
    } else {
    	// EMPTY
    	decls->addChildNode(new Node(ParseEnums::EMPTY));
    }

    return decls;
}

Node* Parser::decl() {
    Node* decl = new Node(ParseEnums::DECL);

    // int
    getNextExpectedToken(INT);
    decl->addChildNode(new Node(ParseEnums::KEYWORD, this->currentToken));
    // ARRAY
    decl->addChildNode(array());
    // identifier
    getNextExpectedToken(IDENTIFIER);
    decl->addChildNode(new Node(ParseEnums::IDENTIFIER, this->currentToken));

    return decl;
}

Node* Parser::statements() {
    Node* statements = new Node(ParseEnums::STATEMENTS);

    if (checkNextTokenIsType(IDENTIFIER) || checkNextTokenIsType(PRINT) ||
    checkNextTokenIsType(T_READ) || checkNextTokenIsType(SIGN_LEFTANGLEBRACKET) ||
    checkNextTokenIsType(IF) || checkNextTokenIsType(WHILE)) {
       	// STATEMENT
    	statements->addChildNode(statement());
    	// SEMICOLON
    	getNextExpectedToken(SIGN_SEMICOLON);
    	statements->addChildNode(new Node(ParseEnums::KEYWORD, this->currentToken));
    	// STATEMENTS
    	statements->addChildNode(this->statements());
    } else {
    	// EMPTY
    	statements->addChildNode(new Node(ParseEnums::EMPTY));
    }

    return statements;
}

Node* Parser::statement() {
    Node* nStatement = new Node(ParseEnums::STATEMENT);

    getNextToken();
    TType ttype = this->currentToken->getType();
    if (ttype == IDENTIFIER) {
        // identifier
        nStatement->addChildNode(new Node(ParseEnums::IDENTIFIER, this->currentToken));
        // opt: INDEX
        nStatement->addChildNode(index());
        // =
        getNextExpectedToken(SIGN_ASSIGN);
        nStatement->addChildNode(new Node(ParseEnums::KEYWORD, this->currentToken));
        // exp
        nStatement->addChildNode(exp());
    } else if (ttype == T_READ) {
        // read
        nStatement->addChildNode(new Node(ParseEnums::KEYWORD, this->currentToken));
        // (
        getNextExpectedToken(SIGN_LEFTBRACKET);
        nStatement->addChildNode(new Node(ParseEnums::KEYWORD, this->currentToken));
        // identifier
        getNextExpectedToken(IDENTIFIER);
        nStatement->addChildNode(new Node(ParseEnums::IDENTIFIER, this->currentToken));
        // opt: INDEX
        nStatement->addChildNode(index());
        // )
        getNextExpectedToken(SIGN_RIGHTBRACKET);
        nStatement->addChildNode(new Node(ParseEnums::KEYWORD, this->currentToken));
    } else if (ttype == PRINT) {
        // print
        nStatement->addChildNode(new Node(ParseEnums::KEYWORD, this->currentToken));
        // (
        getNextExpectedToken(SIGN_LEFTBRACKET);
        nStatement->addChildNode(new Node(ParseEnums::KEYWORD, this->currentToken));
        // exp
        nStatement->addChildNode(exp());
        // )
        getNextExpectedToken(SIGN_RIGHTBRACKET);
        nStatement->addChildNode(new Node(ParseEnums::KEYWORD, this->currentToken));
    } else if (ttype == SIGN_LEFTANGLEBRACKET) {
        // {
        nStatement->addChildNode(new Node(ParseEnums::KEYWORD, this->currentToken));
        // statements
        nStatement->addChildNode(statements());
        // }
        getNextExpectedToken(SIGN_RIGHTANGLEBRACKET);
        nStatement->addChildNode(new Node(ParseEnums::KEYWORD, this->currentToken));
    } else if (ttype == IF) {
        // if
        nStatement->addChildNode(new Node(ParseEnums::KEYWORD, this->currentToken));
        // (
        getNextExpectedToken(SIGN_LEFTBRACKET);
        nStatement->addChildNode(new Node(ParseEnums::KEYWORD, this->currentToken));
        // exp
        nStatement->addChildNode(exp());
        // )
        getNextExpectedToken(SIGN_RIGHTBRACKET);
        nStatement->addChildNode(new Node(ParseEnums::KEYWORD, this->currentToken));
        // statement
        nStatement->addChildNode(statement());
        // else
        getNextExpectedToken(ELSE);
        nStatement->addChildNode(new Node(ParseEnums::KEYWORD, this->currentToken));
        // statement
        nStatement->addChildNode(statement());
    } else if (ttype == WHILE) {
        // while
        nStatement->addChildNode(new Node(ParseEnums::KEYWORD, this->currentToken));
        // (
        getNextExpectedToken(SIGN_LEFTBRACKET);
        nStatement->addChildNode(new Node(ParseEnums::KEYWORD, this->currentToken));
        // exp
        nStatement->addChildNode(exp());
        // )
        getNextExpectedToken(SIGN_RIGHTBRACKET);
        nStatement->addChildNode(new Node(ParseEnums::KEYWORD, this->currentToken));
        // statement
        nStatement->addChildNode(statement());
    } else {
        cerr << "ERROR: Expected: Statement, ";
        printGotTokenInfo();
        cerr << "Stop ..." << endl;
        exit(1);
    }
    return nStatement;
}

Node* Parser::array() {
    Node* array = new Node(ParseEnums::ARRAY);

    if (checkNextTokenIsType(SIGN_LEFTSQUAREBRACKET)) {
        // [
        getNextExpectedToken(SIGN_LEFTSQUAREBRACKET);
        array->addChildNode(new Node(ParseEnums::KEYWORD, this->currentToken));
        // integer
        getNextExpectedToken(INTEGER);
        array->addChildNode(new Node(ParseEnums::INTEGER, this->currentToken));
        // ]
        getNextExpectedToken(SIGN_RIGHTSQUAREBRACKET);
        array->addChildNode(new Node(ParseEnums::KEYWORD, this->currentToken));
    } else {
    	// EMPTY
    	array->addChildNode(new Node(ParseEnums::EMPTY));
    }

    return array;
}

Node* Parser::index() {
    Node* index = new Node(ParseEnums::INDEX);

    if (checkNextTokenIsType(SIGN_LEFTSQUAREBRACKET)) {
        // [
        getNextExpectedToken(SIGN_LEFTSQUAREBRACKET);
        index->addChildNode(new Node(ParseEnums::KEYWORD, this->currentToken));
        // exp
        index->addChildNode(exp());
        // ]
        getNextExpectedToken(SIGN_RIGHTSQUAREBRACKET);
        index->addChildNode(new Node(ParseEnums::KEYWORD, this->currentToken));
    } else {
    	// EMPTY
    	index->addChildNode(new Node(ParseEnums::EMPTY));
    }

    return index;
}

Node* Parser::exp() {
    Node* exp = new Node(ParseEnums::EXP);

    exp->addChildNode(exp2());
    exp->addChildNode(op_exp());

    return exp;
}

Node* Parser::exp2() {
    Node* nExp2 = new Node(ParseEnums::EXP2);

    getNextToken();
    if (this->currentToken->getType() == INTEGER) {
        // integer
        nExp2->addChildNode(new Node(ParseEnums::INTEGER, this->currentToken));
    } else if (this->currentToken->getType() == SIGN_SUBTRACTION
               || this->currentToken->getType() == SIGN_EXCLAMATION) {
        // - || !
        nExp2->addChildNode(new Node(ParseEnums::KEYWORD, this->currentToken));
        // exp2
        nExp2->addChildNode(exp2());
    } else if (this->currentToken->getType() == SIGN_LEFTBRACKET) {
        // (
        nExp2->addChildNode(new Node(ParseEnums::KEYWORD, this->currentToken));
        // EXP
        nExp2->addChildNode(exp());
        // )
        getNextExpectedToken(SIGN_RIGHTBRACKET);
        nExp2->addChildNode(new Node(ParseEnums::KEYWORD, this->currentToken));
    } else if (this->currentToken->getType() == IDENTIFIER) {
        // identifier
        nExp2->addChildNode(new Node(ParseEnums::IDENTIFIER, this->currentToken));
        // opt: [exp]
        nExp2->addChildNode(index());
    } else {
        cerr << "ERROR: Expected: Exp2, ";
        printGotTokenInfo();
        cerr << "Stopping..." << endl;
        exit(1);
    }

    return nExp2;
}

Node* Parser::op_exp() {
    Node* op_exp = new Node(ParseEnums::OP_EXP);

    if (checkNextTokenOp()) {
        getNextToken();
        // OP
        op_exp->addChildNode(this->op());
        // EXP
        op_exp->addChildNode(exp());
    } else {
    	op_exp->addChildNode(new Node(ParseEnums::EMPTY));
    }

    return op_exp;
}

Node* Parser::op() {
    Node* op = new Node(ParseEnums::OP);

    op->addChildNode(new Node(ParseEnums::KEYWORD, this->currentToken));

    return op;
}


bool Parser::checkNextTokenExists() {
    if (!checkedNextToken) {
        getNextToken();
    }

    checkedNextToken = true;
    if (!this->currentToken) {
        return false;
    }
    return true;
}

bool Parser::checkNextTokenOp() {
    if (checkNextTokenExists()) {
        return isOp(this->currentToken->getType());
    }
    return false;
}

bool Parser::checkNextTokenIsType(TType ttype) {
    if (checkNextTokenExists()) {
        return this->currentToken->getType() == ttype;
    }
    return false;
}

bool Parser::isOp(TType type) {
    return type == SIGN_ADDITITON || type == SIGN_SUBTRACTION
           || type == SIGN_MULTIPLICATION || type == SIGN_DIVISION
           || type == SIGN_LT || type == SIGN_GT
           || type == SIGN_ASSIGN || type == SIGN_NE
           || type == SIGN_AMPERSAND;
}

void Parser::scannerNextToken() {
    if (!checkedNextToken) {
        this->currentToken = scanner->nextToken();
    } else {
        checkedNextToken = false;
    }
}

bool Parser::getNextToken() {
    scannerNextToken();
    if (!this->currentToken) {
        end = true;
        return false;
    }

    writeScannerOutput();

    if (this->currentToken->getType() == NO_TYPE) {
        cerr << "Ignoring NO_TYPE token." << endl;
        return getNextToken();
    }

    return true;
}


void Parser::getNextExpectedToken(TType ttype) {
    scannerNextToken();
    if (!this->currentToken) {
        cerr << "ERROR: Expected: " << getTokenString(ttype) << ", Got: EOF" << endl;
        cerr << "Stopping..." << endl;
        exit(1);
    } else if (this->currentToken->getType() != ttype) {
        cerr << "ERROR: Expected: " << getTokenString(ttype) << ", ";
        printGotTokenInfo();
        cerr << "Stopping..." << endl;
        exit(1);
    }

    writeScannerOutput();
}

void Parser::printGotTokenInfo() {
    cerr << "Got: " << getTokenString(this->currentToken->getType())
         << " in Line " << this->currentToken->getLine() << ", Column " << this->currentToken->getColumn() << endl;
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

void Parser::writeScannerOutput() {
    return;
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
