#include "Parser.hpp"


Parser::Parser(Scanner* scanner) {
    this->scanner = scanner;
    end = false;
    checkedNextToken = false;
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
        this->currentToken->getType() == T_READ || this->currentToken->getType() == SIGN_LEFTANGLEBRACKET ||
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
    decl->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
    // opt: [integer]
    if (checkNextToken(SIGN_LEFTSQUAREBRACKET)) {
        checkedNextToken = false;
        Node* nArray = array();
        decl->addChildNode(nArray);
    }
    // identifier
    getNextExpectedToken(IDENTIFIER);
    decl->addChildNode(new Node(Rule::IDENTIFIER, this->currentToken));
    // semicolon
    getNextExpectedToken(SIGN_SEMICOLON);
    decl->addChildNode(new Node(Rule::KEYWORD, this->currentToken));

    return decl;
}

Node* Parser::statements() {
    Node* statements = new Node(Rule::STATEMENTS);
    while (!end) {
        Node* nStatement = statement();
        statements->addChildNode(nStatement);
        getNextStatementToken(false, true);
    }
    return statements;
}

Node* Parser::statement() {
    Node* nStatement = new Node(Rule::STATEMENT);
    if (this->currentToken->getType() == IDENTIFIER) {
        // identifier
        nStatement->addChildNode(new Node(Rule::IDENTIFIER, this->currentToken));
        // opt: INDEX
        if (checkNextToken(SIGN_LEFTSQUAREBRACKET)) {
            checkedNextToken = false;
            Node* nIndex = index();
            nStatement->addChildNode(nIndex);
        }
        // =
        getNextExpectedToken(SIGN_ASSIGN);
        nStatement->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
        // exp
        Node* nExp = exp();
        nStatement->addChildNode(nExp);
        // ;
        getNextExpectedToken(SIGN_SEMICOLON);
        nStatement->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
    } else if (this->currentToken->getType() == T_READ) {
        // read
        nStatement->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
        // (
        getNextExpectedToken(SIGN_LEFTBRACKET);
        nStatement->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
        // identifier
        getNextExpectedToken(IDENTIFIER);
        nStatement->addChildNode(new Node(Rule::IDENTIFIER, this->currentToken));
        // opt: INDEX
        if (checkNextToken(SIGN_LEFTSQUAREBRACKET)) {
            checkedNextToken = false;
            Node* nIndex = index();
            nStatement->addChildNode(nIndex);
        }
        // )
        getNextExpectedToken(SIGN_RIGHTBRACKET);
        nStatement->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
        // ;
        getNextExpectedToken(SIGN_SEMICOLON);
        nStatement->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
    } else if (this->currentToken->getType() == PRINT) {
        // print
        nStatement->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
        // (
        getNextExpectedToken(SIGN_LEFTBRACKET);
        nStatement->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
        // exp
        Node* nExp = exp();
        nStatement->addChildNode(nExp);
        // )
        getNextExpectedToken(SIGN_RIGHTBRACKET);
        nStatement->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
        // ;
        getNextExpectedToken(SIGN_SEMICOLON);
        nStatement->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
    } else if (this->currentToken->getType() == SIGN_LEFTANGLEBRACKET) {
        // {
        nStatement->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
        // statements
        Node* nStatements = new Node(Rule::STATEMENTS);
        getNextStatementToken(true, false);
        while (this->currentToken->getType() != SIGN_RIGHTANGLEBRACKET) {
            Node* nStatement = statement();
            nStatements->addChildNode(nStatement);
            getNextStatementToken(true, false);
        }
        if (nStatements->getChildNodesCount() > 0)
            nStatement->addChildNode(nStatements);
        // }
        nStatement->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
    } else if (this->currentToken->getType() == IF) {
        // if
        nStatement->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
        // (
        getNextExpectedToken(SIGN_LEFTBRACKET);
        nStatement->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
        // exp
        Node* nExp = exp();
        nStatement->addChildNode(nExp);
        // )
        getNextExpectedToken(SIGN_RIGHTBRACKET);
        nStatement->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
        // statement
        getNextStatementToken(false, false);
        Node* nnStatement = statement();
        nStatement->addChildNode(nnStatement);
        // else
        getNextExpectedToken(ELSE);
        nStatement->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
        // statement
        getNextStatementToken(false, false);
        Node* nnnStatement = statement();
        nStatement->addChildNode(nnnStatement);
        // ;
        getNextExpectedToken(SIGN_SEMICOLON);
        nStatement->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
    } else if (this->currentToken->getType() == WHILE) {
        // while
        nStatement->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
        // (
        getNextExpectedToken(SIGN_LEFTBRACKET);
        nStatement->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
        // exp
        Node* nExp = exp();
        nStatement->addChildNode(nExp);
        // )
        getNextExpectedToken(SIGN_RIGHTBRACKET);
        nStatement->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
        // statement
        getNextStatementToken(false, false);
        Node* nnStatement = statement();
        nStatement->addChildNode(nnStatement);
        // ;
        getNextExpectedToken(SIGN_SEMICOLON);
        nStatement->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
    }
    return nStatement;
}

Node* Parser::array() {
    Node* array = new Node(Rule::ARRAY);
    // [
    array->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
    // integer
    getNextExpectedToken(INTEGER);
    array->addChildNode(new Node(Rule::INTEGER, this->currentToken));
    // ]
    getNextExpectedToken(SIGN_RIGHTSQUAREBRACKET);
    array->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
    return array;
}

Node* Parser::index() {
    Node* index = new Node(Rule::INDEX);
    // [
    index->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
    // exp
    Node* nExp = exp();
    index->addChildNode(nExp);
    // ]
    getNextExpectedToken(SIGN_RIGHTSQUAREBRACKET);
    index->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
    return index;
}

Node* Parser::exp() {
    Node* exp = new Node(Rule::EXP);
    // exp2
    getNextExp2Token();
    Node* nExp2 = exp2();
    exp->addChildNode(nExp2);
    // op_exp
    if (checkNextTokenOp()) {
        checkedNextToken = false;
        Node* nOp_exp = op_exp();
        exp->addChildNode(nOp_exp);
    }
    return exp;
}

Node* Parser::exp2() {
    Node* nExp2 = new Node(Rule::EXP2);
    if (this->currentToken->getType() == INTEGER) {
        // integer
        nExp2->addChildNode(new Node(Rule::INTEGER, this->currentToken));
    } else if (this->currentToken->getType() == SIGN_SUBTRACTION
               || this->currentToken->getType() == SIGN_EXCLAMATION) {
        // - || !
        nExp2->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
        // exp2
        getNextExp2Token();
        Node* nnExp2 = exp2();
        nExp2->addChildNode(nnExp2);
    } else if (this->currentToken->getType() == SIGN_LEFTBRACKET) {
        // (
        nExp2->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
        // EXP
        Node* nExp = exp();
        nExp2->addChildNode(nExp);
        // )
        getNextExpectedToken(SIGN_RIGHTBRACKET);
        nExp2->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
    } else if (this->currentToken->getType() == IDENTIFIER) {
        // identifier
        nExp2->addChildNode(new Node(Rule::IDENTIFIER, this->currentToken));
        // opt: [exp]
        if (checkNextToken(SIGN_LEFTSQUAREBRACKET)) {
            checkedNextToken = false;
            // [
            nExp2->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
            // exp
            Node* nExp = exp();
            nExp2->addChildNode(nExp);
            // ]
            getNextExpectedToken(SIGN_RIGHTSQUAREBRACKET);
            nExp2->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
        }
    }

    return nExp2;
}

Node* Parser::op_exp() {
    Node* op_exp = new Node(Rule::OP_EXP);
    // op
    op_exp->addChildNode(new Node(Rule::KEYWORD, this->currentToken));
    // exp
    Node* nExp = exp();
    op_exp->addChildNode(nExp);

    return op_exp;
}

bool Parser::checkNextToken(TType ttype) {
    if (!checkedNextToken) {
        this->currentToken = scanner->nextToken();
    }
    checkedNextToken = true;
    if (!this->currentToken) {
        return false;
    } else if (this->currentToken->getType() == ttype) {
        writeScannerOutput();
        return true;
    } else {
        return false;
    }
}

bool Parser::checkNextTokenOp() {
    if (!checkedNextToken) {
        this->currentToken = scanner->nextToken();
    }
    checkedNextToken = true;
    if (!this->currentToken) {
        return false;
    } else if (this->currentToken->getType() == SIGN_ADDITITON || this->currentToken->getType() == SIGN_SUBTRACTION
               || this->currentToken->getType() == SIGN_MULTIPLICATION || this->currentToken->getType() == SIGN_DIVISION
               || this->currentToken->getType() == SIGN_LT || this->currentToken->getType() == SIGN_GT
               || this->currentToken->getType() == SIGN_ASSIGN || this->currentToken->getType() == SIGN_NE
               || this->currentToken->getType() == SIGN_AMPERSAND) {
        writeScannerOutput();
        return true;
    } else {
        return false;
    }
}

void Parser::scannerNextToken() {
    if (!checkedNextToken) {
        this->currentToken = scanner->nextToken();
    } else {
        checkedNextToken = false;
    }
}

void Parser::getNextToken() {
    scannerNextToken();
    if (!this->currentToken) {
        end = true;
        return;
    }

    writeScannerOutput();
}

void Parser::getNextStatementToken(bool inner, bool optional) {
    scannerNextToken();
    if (!this->currentToken && optional) {
        end = true;
        return;
    } else if (!this->currentToken && !optional) {
        cout << "ERROR: Expected: Statement, Got: EOF" << endl;
        cout << "Stop ..." << endl;
        exit(0);
    } else if (!(inner && this->currentToken->getType() == SIGN_RIGHTANGLEBRACKET) &&
               !(this->currentToken->getType() == IDENTIFIER || this->currentToken->getType() == PRINT ||
               this->currentToken->getType() == T_READ || this->currentToken->getType() == SIGN_LEFTANGLEBRACKET ||
               this->currentToken->getType() == IF || this->currentToken->getType() == WHILE)) {
        cout << "ERROR: Expected: Statement, Got: " << getTokenString(this->currentToken->getType())
             << " in Line " << this->currentToken->getLine() << ", Column " << this->currentToken->getColumn() << endl;
        cout << "Stop ..." << endl;
        exit(0);
    }

    writeScannerOutput();
}

void Parser::getNextExp2Token() {
    scannerNextToken();
    if (!this->currentToken) {
        cout << "ERROR: Expected: Exp2, Got: EOF" << endl;
        cout << "Stop ..." << endl;
        exit(0);
    } else if (!(this->currentToken->getType() == SIGN_LEFTBRACKET || this->currentToken->getType() == IDENTIFIER ||
           this->currentToken->getType() == INTEGER || this->currentToken->getType() == SIGN_SUBTRACTION ||
           this->currentToken->getType() == SIGN_EXCLAMATION)) {
        cout << "ERROR: Expected: Exp2, Got: " << getTokenString(this->currentToken->getType())
                     << " in Line " << this->currentToken->getLine() << ", Column " << this->currentToken->getColumn() << endl;
        cout << "Stop ..." << endl;
        exit(0);
    }

    writeScannerOutput();
}

void Parser::getNextExpectedToken(TType ttype) {
    scannerNextToken();
    if (!this->currentToken) {
        cout << "ERROR: Expected: " << getTokenString(ttype) << ", Got: EOF" << endl;
        cout << "Stop ..." << endl;
        exit(0);
    } else if (this->currentToken->getType() != ttype) {
        cout << "ERROR: Expected: " << getTokenString(ttype) << ", Got: "
             << getTokenString(this->currentToken->getType())
             << " in Line " << this->currentToken->getLine() << ", Column " << this->currentToken->getColumn() << endl;
        cout << "Stop ..." << endl;
        exit(0);
    }

    writeScannerOutput();
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
