#include "ParseTree.hpp"

ParseTree::ParseTree() {
    this->root = new Node(ParseEnums::ROOT);

    depth = 0;
}

ParseTree::~ParseTree() {

}

bool ParseTree::typeCheck(Node* node) {

	switch (node->getRule()) {
		case ParseEnums::ROOT:
			typeCheck(node->getChildNode(0)); // PROG
			node->setType(ParseEnums::NOTYPE);
			cout << "Root: noType" << endl;
			break;

		case ParseEnums::PROG:
			typeCheck(node->getChildNode(0)); // DECLS
			typeCheck(node->getChildNode(1)); // STATEMENTS
			node->setType(ParseEnums::NOTYPE);
			cout << "Prog: noType" << endl;
			break;

		case ParseEnums::DECLS:
			if (node->getChildNodesCount() != 0) {
				typeCheck(node->getChildNode(0));     // DECL
												      // ;
				if (node->getChildNode(2))
					typeCheck(node->getChildNode(2)); // DECLS
			}
			node->setType(ParseEnums::NOTYPE);
			cout << "Decls: noType" << endl;
			break;

		case ParseEnums::DECL:
			typeCheck(node->getChildNode(1));	// ARRAY
			if (node->getType() != ParseEnums::NOTYPE) {
				cerr << "identifier " << node->getToken()->getEntry()->getLexem() <<
						" already used" << endl;
				node->setType(ParseEnums::ERRORTYPE);
				cout << "Decl: errorType" << endl;
			} else if (node->getChildNode(1)->getType() == ParseEnums::ERRORTYPE) {
				node->setType(ParseEnums::ERRORTYPE);
				cout << "Decl: errorType" << endl;
			} else {
				node->setType(ParseEnums::NOTYPE);
				cout << "Decl: noType" << endl;
				if (node->getChildNode(1)->getType() == ParseEnums::ARRAYTYPE) {
					store(node->getChildNode(2), ParseEnums::INTARRAYTYPE);
				} else {
					store(node->getChildNode(2), ParseEnums::INTTYPE);
				}
			}
			break;

		case ParseEnums::ARRAY:
			if (node->getChildNodesCount() == 3) {
				if (node->getChildNode(1)->getToken()->getValue() > 0) {
					node->setType(ParseEnums::ARRAYTYPE);
					cout << "Array: arrayType" << endl;
				} else {
					cerr << "no valid dimension" << endl;
					node->setType(ParseEnums::ERRORTYPE);
					cout << "Array: errorType" << endl;
				}
			} else {
				node->setType(ParseEnums::NOTYPE);
				cout << "Array: noType" << endl;
			}
			break;

		case ParseEnums::STATEMENTS:
			if (node->getChildNodesCount() != 0) {
				typeCheck(node->getChildNode(0));     // STATEMENT
												      // ;
				if (node->getChildNode(2))
					typeCheck(node->getChildNode(2)); // STATEMENTS
			}
			node->setType(ParseEnums::NOTYPE);
			cout << "Statements: noType" << endl;
			break;

		case ParseEnums::STATEMENT:
			if (node->getChildNode(0)->getRule() == ParseEnums::IDENTIFIER) {

			// TODO

			} else {
				switch (node->getChildNode(0)->getToken()->getType()) {
					case PRINT:		// print ( EXP )
						typeCheck(node->getChildNode(2));
						node->setType(ParseEnums::NOTYPE);
						cout << "Statement: noType" << endl;
						break;

					case T_READ:	// read ( identifier INDEX )
						typeCheck(node->getChildNode(3));

						//TODO

						break;

					case SIGN_LEFTANGLEBRACKET:		// { statements }
						typeCheck(node->getChildNode(1));
						node->setType(ParseEnums::NOTYPE);
						cout << "Statement: noType" << endl;
						break;

					case IF:		// if ( EXP ) STATEMENT else STATEMENT
						typeCheck(node->getChildNode(2));
						typeCheck(node->getChildNode(4));
						typeCheck(node->getChildNode(6));
						if (node->getChildNode(2)->getType() == ParseEnums::ERRORTYPE) {
							node->setType(ParseEnums::ERRORTYPE);
							cout << "Statement: errorType" << endl;
						} else {
							node->setType(ParseEnums::NOTYPE);
							cout << "Statement: noType" << endl;
						}
						break;

					case WHILE:		// while ( EXP ) STATEMENT
						typeCheck(node->getChildNode(2));
						typeCheck(node->getChildNode(4));
						if (node->getChildNode(2)->getType() == ParseEnums::ERRORTYPE) {
							node->setType(ParseEnums::ERRORTYPE);
							cout << "Statement: errorType" << endl;
						} else {
							node->setType(ParseEnums::NOTYPE);
							cout << "Statement: noType" << endl;
						}
						break;

					default:
						node->setType(ParseEnums::NOTYPE);
						cout << "Statement: noType" << endl;
						break;
				}
			}
			break;

		case ParseEnums::INDEX:
			if (node->getChildNode(0) != NULL) {
				typeCheck(node->getChildNode(1));
				if (node->getChildNode(1)->getType() == ParseEnums::ERRORTYPE) {
					node->setType(ParseEnums::ERRORTYPE);
					cout << "INDEX: errorType" << endl;
				} else {
					node->setType(ParseEnums::ARRAYTYPE);
					cout << "INDEX: arrayType" << endl;
				}
			} else {
				node->setType(ParseEnums::NOTYPE);
				cout << "INDEX: noType" << endl;
			}
			break;

		case ParseEnums::EXP:
			typeCheck(node->getChildNode(0));
			typeCheck(node->getChildNode(1));
			if (node->getChildNode(1)->getType() == ParseEnums::NOTYPE) {
				node->setType(node->getChildNode(0)->getType());
				cout << "EXP: <  >" << endl;
			} else if (node->getChildNode(0)->getType() != node->getChildNode(1)->getType()) {
				node->setType(ParseEnums::ERRORTYPE);
				cout << "Statement: errorType" << endl;
			} else {
				node->setType(node->getChildNode(0)->getType());
				cout << "EXP: <  >" << endl;
			}
			break;

		case ParseEnums::EXP2:
			switch (node->getChildNode(0)->getToken()->getType()) {
				case SIGN_LEFTBRACKET:
					typeCheck(node->getChildNode(1));
					node->setType(node->getChildNode(1)->getType());
					cout << "EXP2: <  >" << endl;
					break;

				case IDENTIFIER:

					//TODO

					break;

				case INTEGER:
					node->setType(ParseEnums::INTTYPE);
					cout << "EXP2: intType" << endl;
					break;

				case SIGN_SUBTRACTION:
					typeCheck(node->getChildNode(1));
					node->setType(node->getChildNode(1)->getType());
					cout << "EXP2: <  >" << endl;
					break;

				case SIGN_EXCLAMATION:
					typeCheck(node->getChildNode(1));
					if (node->getChildNode(1)->getType() != ParseEnums::INTTYPE) {
						node->setType(ParseEnums::ERRORTYPE);
						cout << "EXP2: errorType" << endl;
					} else {
						node->setType(ParseEnums::INTTYPE);
						cout << "EXP2: intType" << endl;
					}
					break;

				default:
					node->setType(ParseEnums::ERRORTYPE);
					cout << "EXP2: errorType" << endl;
					break;
			}
			break;

		case ParseEnums::OP_EXP:
			if (node->getChildNode(0) != NULL) {
				typeCheck(node->getChildNode(0));
				typeCheck(node->getChildNode(1));
				node->setType(node->getChildNode(1)->getType());
				cout << "OP_EXP: <  >" << endl;
			} else {
				node->setType(ParseEnums::NOTYPE);
				cout << "OP_EXP: noType" << endl;
			}
			break;

		case ParseEnums::OP:
			switch (node->getChildNode(0)->getToken()->getType()) {
				case SIGN_ADDITITON:
					node->setType(ParseEnums::OPPLUS);
					cout << "OP: opPlus" << endl;
					break;

				case SIGN_SUBTRACTION:
					node->setType(ParseEnums::OPMINUS);
					cout << "OP: opMinus" << endl;
					break;

				case SIGN_MULTIPLICATION:
					node->setType(ParseEnums::OPMULT);
					cout << "OP: opMult" << endl;
					break;

				case SIGN_DIVISION:
					node->setType(ParseEnums::OPDIV);
					cout << "OP: opDiv" << endl;
					break;

				case SIGN_LT:
					node->setType(ParseEnums::OPLESS);
					cout << "OP: opLess" << endl;
					break;

				case SIGN_GT:
					node->setType(ParseEnums::OPGREATER);
					cout << "OP: opGreater" << endl;
					break;

				case SIGN_ASSIGN:
					node->setType(ParseEnums::OPEQUAL);
					cout << "OP: opEqual" << endl;
					break;

				case SIGN_NE:
					node->setType(ParseEnums::OPUNEQUAL);
					cout << "OP: opUnequal" << endl;
					break;

				case SIGN_AMPERSAND:
					node->setType(ParseEnums::OPAND);
					cout << "OP: opAnd" << endl;
					break;

				default:
					node->setType(ParseEnums::ERRORTYPE);
					cout << "OP: errorType" << endl;
			}
			break;

		default:
			break;
	}

	return true;
}

void ParseTree::store(Node* node, ParseEnums::Type type) {
	//TODO
}

void ParseTree::printTree(Node* node) {
    const char* node_str[] = { "ROOT", "PROG", "DECLS", "DECL", "ARRAY", "STATEMENTS", "STATEMENT", "EXP",
            "EXP2", "INDEX", "OP_EXP", "OP", "INTEGER", "IDENTIFIER", "KEYWORD", "SEMICOLON", "EMPTY" };
    const char* ttype_str[] = { "NO_TYPE", "INTEGER", "IDENTIFIER", "PRINT",
        "READ", "IF", "ELSE", "WHILE", "INT", "ADDITITON", "SUBTRACTION",
        "DIVISION", "MULTIPLICATION", "LT", "GT", "ASSIGN", "NE",
        "EXCLAMATION", "AMPERSAND", "SEMICOLON", "COLON", "LEFTBRACKET",
        "RIGHTBRACKET", "LEFTANGLEBRACKET", "RIGHTANGLEBRACKET",
        "LEFTSQUAREBRACKET", "RIGHTSQUAREBRACKET" };

    for (int i = 0; i < depth; i++) {
        cout << "  ";
    }
    depth++;

    cout << node_str[node->getRule()];
    if (node->getRule() == ParseEnums::IDENTIFIER) {
        cout << " - Lexem: " << node->getToken()->getEntry()->getLexem();
    } else if (node->getRule() == ParseEnums::INTEGER) {
        cout << " - Wert: " << node->getToken()->getValue();
    } else if (node->getRule() == ParseEnums::KEYWORD) {
        cout << " - Art: " << ttype_str[node->getToken()->getType()];
    }
    cout << endl;
    for (int i = 0; i < node->getChildNodesCount(); i++) {
        printTree(node->getChildNode(i));
    }

    depth--;
}
