#include "ParseTree.hpp"

ParseTree::ParseTree(Buffer* buffer) {
    this->root = new Node(ParseEnums::ROOT);
    this->buffer = buffer;

    depth = 0;
    marker = 97;
}

ParseTree::~ParseTree() {

}

bool ParseTree::typeCheck(Node* node) {

    switch (node->getRule()) {
        case ParseEnums::ROOT:
            typeCheck(node->getChildNode(0)); // PROG
            node->setType(ParseEnums::NOTYPE);
            break;

        case ParseEnums::PROG:
            typeCheck(node->getChildNode(0)); // DECLS
            typeCheck(node->getChildNode(1)); // STATEMENTS
            node->setType(ParseEnums::NOTYPE);
            break;

        case ParseEnums::DECLS:
            if (node->getChildNodesCount() != 0) {
                typeCheck(node->getChildNode(0));     // DECL
                                                      // ;
                if (node->getChildNode(2))
                    typeCheck(node->getChildNode(2)); // DECLS
            }
            node->setType(ParseEnums::NOTYPE);
            break;

        case ParseEnums::DECL:
            typeCheck(node->getChildNode(1));   // ARRAY
            if (node->getType() != ParseEnums::NOTYPE) {
                cerr << "identifier " << node->getToken()->getEntry()->getLexem() <<
                        " already used" << endl;
                node->setType(ParseEnums::ERRORTYPE);
            } else if (node->getChildNode(1)->getType() == ParseEnums::ERRORTYPE) {
                node->setType(ParseEnums::ERRORTYPE);
            } else {
                node->setType(ParseEnums::NOTYPE);
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
                } else {
                    cerr << "no valid dimension" << endl;
                    node->setType(ParseEnums::ERRORTYPE);
                }
            } else {
                node->setType(ParseEnums::NOTYPE);
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
            break;

        case ParseEnums::STATEMENT:
            if (node->getChildNode(0)->getRule() == ParseEnums::IDENTIFIER) {
                typeCheck(node->getChildNode(3));
                typeCheck(node->getChildNode(1));
                if (get(node->getChildNode(0)) == ParseEnums::ERRORTYPE ||
                        get(node->getChildNode(0)) == ParseEnums::NOTYPE) {
                    cerr << "Identifier " << node->getChildNode(0)->getToken()->getEntry()->getLexem() << " not defined" << endl;
                    node->setType(ParseEnums::ERRORTYPE);
                } else if (node->getChildNode(3)->getType() == ParseEnums::INTTYPE
                           &&
                           ((get(node->getChildNode(0)) == ParseEnums::INTTYPE
                             && node->getChildNode(1)->getType() == ParseEnums::NOTYPE)
                            ||
                            (get(node->getChildNode(0)) == ParseEnums::INTARRAYTYPE
                             && node->getChildNode(1)->getType() == ParseEnums::ARRAYTYPE))) {
                    node->setType(ParseEnums::NOTYPE);
                } else {
                    cerr << "Identifier " << node->getChildNode(0)->getToken()->getEntry()->getLexem() << " incompatible types" << endl;
                    node->setType(ParseEnums::ERRORTYPE);
                }
            } else {
                switch (node->getChildNode(0)->getToken()->getType()) {
                    case PRINT:     // print ( EXP )
                        typeCheck(node->getChildNode(2));
                        node->setType(ParseEnums::NOTYPE);
                        break;

                    case T_READ:    // read ( identifier INDEX )
                        typeCheck(node->getChildNode(3));

                        if (get(node->getChildNode(2)) == ParseEnums::ERRORTYPE
                                || get(node->getChildNode(2)) == ParseEnums::NOTYPE) {
                            cerr << "Identifier " << node->getChildNode(2)->getToken()->getEntry()->getLexem() << " not defined" << endl;
                            node->setType(ParseEnums::ERRORTYPE);
                        } else if ((get(node->getChildNode(2)) == ParseEnums::INTTYPE
                                    && node->getChildNode(3)->getType() == ParseEnums::NOTYPE)
                                   ||
                                   (get(node->getChildNode(2)) == ParseEnums::INTARRAYTYPE
                                    && node->getChildNode(3)->getType() == ParseEnums::ARRAYTYPE)) {
                            node->setType(ParseEnums::NOTYPE);
                        } else {
                            cerr << "Identifier " << node->getChildNode(2)->getToken()->getEntry()->getLexem() << " incompatible types" << endl;
                            node->setType(ParseEnums::ERRORTYPE);
                        }

                        break;

                    case SIGN_LEFTANGLEBRACKET:     // { statements }
                        typeCheck(node->getChildNode(1));
                        node->setType(ParseEnums::NOTYPE);
                        break;

                    case IF:        // if ( EXP ) STATEMENT else STATEMENT
                        typeCheck(node->getChildNode(2));
                        typeCheck(node->getChildNode(4));
                        typeCheck(node->getChildNode(6));
                        if (node->getChildNode(2)->getType() == ParseEnums::ERRORTYPE) {
                            node->setType(ParseEnums::ERRORTYPE);
                        } else {
                            node->setType(ParseEnums::NOTYPE);
                        }
                        break;

                    case WHILE:     // while ( EXP ) STATEMENT
                        typeCheck(node->getChildNode(2));
                        typeCheck(node->getChildNode(4));
                        if (node->getChildNode(2)->getType() == ParseEnums::ERRORTYPE) {
                            node->setType(ParseEnums::ERRORTYPE);
                        } else {
                            node->setType(ParseEnums::NOTYPE);
                        }
                        break;

                    default:
                        node->setType(ParseEnums::NOTYPE);
                        break;
                }
            }
            break;

        case ParseEnums::INDEX:
            if (node->getChildNodesCount() > 1) {
                typeCheck(node->getChildNode(1));
                if (node->getChildNode(1)->getType() == ParseEnums::ERRORTYPE) {
                    node->setType(ParseEnums::ERRORTYPE);
                } else {
                    node->setType(ParseEnums::ARRAYTYPE);
                }
            } else {
                node->setType(ParseEnums::NOTYPE);
            }
            break;

        case ParseEnums::EXP:
            typeCheck(node->getChildNode(0));
            typeCheck(node->getChildNode(1));
            if (node->getChildNode(1)->getType() == ParseEnums::NOTYPE) {
                node->setType(node->getChildNode(0)->getType());
            } else if (node->getChildNode(0)->getType() != node->getChildNode(1)->getType()) {
                node->setType(ParseEnums::ERRORTYPE);
            } else {
                node->setType(node->getChildNode(0)->getType());
            }
            break;

        case ParseEnums::EXP2:
            switch (node->getChildNode(0)->getToken()->getType()) {
                case SIGN_LEFTBRACKET:
                    typeCheck(node->getChildNode(1));
                    node->setType(node->getChildNode(1)->getType());
                    break;

                case IDENTIFIER:
                    typeCheck(node->getChildNode(1));

                    if (get(node->getChildNode(0)) == ParseEnums::NOTYPE) {
                        cerr << "Identifier " << node->getChildNode(0)->getToken()->getEntry()->getLexem() << " not defined" << endl;
                        node->setType(ParseEnums::ERRORTYPE);
                    } else if (get(node->getChildNode(0)) == ParseEnums::INTTYPE
                                && node->getChildNode(1)->getType() == ParseEnums::NOTYPE) {
                        node->setType(get(node->getChildNode(0)));
                    } else if (get(node->getChildNode(0)) == ParseEnums::INTARRAYTYPE
                                && node->getChildNode(1)->getType() == ParseEnums::ARRAYTYPE) {
                        node->setType(ParseEnums::INTTYPE);
                    }
                    else {
                        cerr << "Identifier " << node->getChildNode(0)->getToken()->getEntry()->getLexem() << " no primitive types" << endl;
                        node->setType(ParseEnums::ERRORTYPE);
                    }

                    break;

                case INTEGER:
                    node->setType(ParseEnums::INTTYPE);
                    break;

                case SIGN_SUBTRACTION:
                    typeCheck(node->getChildNode(1));
                    node->setType(node->getChildNode(1)->getType());
                    break;

                case SIGN_EXCLAMATION:
                    typeCheck(node->getChildNode(1));
                    if (node->getChildNode(1)->getType() != ParseEnums::INTTYPE) {
                        node->setType(ParseEnums::ERRORTYPE);
                    } else {
                        node->setType(ParseEnums::INTTYPE);
                    }
                    break;

                default:
                    node->setType(ParseEnums::ERRORTYPE);
                    break;
            }
            break;

        case ParseEnums::OP_EXP:
            if (node->getChildNodesCount() > 1) {
                typeCheck(node->getChildNode(0));
                typeCheck(node->getChildNode(1));
                node->setType(node->getChildNode(1)->getType());
            } else {
                node->setType(ParseEnums::NOTYPE);
            }
            break;

        case ParseEnums::OP:
        	switch (node->getChildNode(0)->getToken()->getType()) {
            case SIGN_ADDITITON:
                node->setType(ParseEnums::OPPLUS);
                break;

            case SIGN_SUBTRACTION:
                node->setType(ParseEnums::OPMINUS);
                break;

            case SIGN_MULTIPLICATION:
                node->setType(ParseEnums::OPMULT);
                break;

            case SIGN_DIVISION:
                node->setType(ParseEnums::OPDIV);
                break;

            case SIGN_LT:
                node->setType(ParseEnums::OPLESS);
                break;

            case SIGN_GT:
                node->setType(ParseEnums::OPGREATER);
                break;

            case SIGN_ASSIGN:
                node->setType(ParseEnums::OPEQUAL);
                break;

            case SIGN_NE:
                node->setType(ParseEnums::OPUNEQUAL);
                break;

            case SIGN_AMPERSAND:
                node->setType(ParseEnums::OPAND);
                break;

            default:
                node->setType(ParseEnums::ERRORTYPE);
                break;
            }
            break;

        default:
            break;
    }

    return true;
}

void ParseTree::store(Node* node, ParseEnums::Type type) {
    node->getToken()->getEntry()->setParseType(type);
}

ParseEnums::Type ParseTree::get(Node* node) {
    return node->getToken()->getEntry()->getParseType();
}

void ParseTree::makeCode(Node* node) {
    if (!node)
        return;

    switch (node->getRule()) {

        // ROOT ::= PROG
        case ParseEnums::ROOT:
            makeCode(node->getChildNode(0));
            break;

        // PROG ::= DECLS STATEMENTS
        case ParseEnums::PROG:
            makeCode(node->getChildNode(0));
            makeCode(node->getChildNode(1));
            buffer->addchars("STP\r\n");
            break;

        // DECLS ::= DECL; DECLS
        case ParseEnums::DECLS:
            makeCode(node->getChildNode(0));
            if (node->getChildNode(2))
                makeCode(node->getChildNode(2));
            break;

        // DECL ::= int ARRAY identifier
        case ParseEnums::DECL:
            buffer->addchars("DS $");
                 buffer->addchars(node->getChildNode(2)->getToken()->getEntry()->getLexem());
                 buffer->addchars(" ");
            makeCode(node->getChildNode(1));
            break;

        // ARRAY ::= [ integer ]
        case ParseEnums::ARRAY:
            if (node->getChildNodesCount() != 1) {
                buffer->addchars(node->getChildNode(1)->getToken()->getValue());
                buffer->addchars("\r\n");
            } else {
                buffer->addchars("1\r\n");
            }
            break;

        // STATEMENTS ::= STATEMENT; STATEMENTS
        case ParseEnums::STATEMENTS:
            makeCode(node->getChildNode(0));
            if (node->getChildNode(2))
                makeCode(node->getChildNode(2));
            else
                buffer->addchars("NOP\r\n");
            break;

        // STATEMENT
        case ParseEnums::STATEMENT:
            char m1, m2;
            switch (node->getChildNode(0)->getToken()->getType()) {

                // STATEMENT ::= identifier INDEX = EXP
                case IDENTIFIER:
                    makeCode(node->getChildNode(3));
                    buffer->addchars("LA $");
                    buffer->addchars(node->getChildNode(0)->getToken()->getEntry()->getLexem());
                    buffer->addchars("\r\n");
                    makeCode(node->getChildNode(1));
                    buffer->addchars("STR\r\n");
                    break;

                // STATEMENT ::= print ( EXP )
                case PRINT:
                    makeCode(node->getChildNode(2));
                    buffer->addchars("PRI\r\n");
                    break;

                // STATEMENT ::= read ( identifier INDEX )
                case T_READ:
                    buffer->addchars("REA\r\n");
                    buffer->addchars("LA $");
                    buffer->addchars(node->getChildNode(2)->getToken()->getEntry()->getLexem());
                    buffer->addchars("\r\n");
                    makeCode(node->getChildNode(3));
                    buffer->addchars("STR\r\n");
                    break;

                // STATEMENT ::= { STATEMENTS }
                case SIGN_LEFTANGLEBRACKET:
                    makeCode(node->getChildNode(1));
                    break;

                // STATEMENT ::= if ( EXP ) STATEMENT else STATEMENT
                case IF:
                    m1 = marker++;
                    m2 = marker++;
                    makeCode(node->getChildNode(2));
                    buffer->addchars("JIN #");
                    buffer->addchars(m1);
                    buffer->addchars("\r\n");
                    makeCode(node->getChildNode(4));
                    buffer->addchars("JMP #");
                    buffer->addchars(m2);
                    buffer->addchars("\r\n");
                    buffer->addchars("#");
                    buffer->addchars(m1);
                    buffer->addchars(" NOP\r\n");
                    makeCode(node->getChildNode(6));
                    buffer->addchars("#");
                    buffer->addchars(m2);
                    buffer->addchars(" NOP\r\n");
                    break;

                // STATEMENT ::= while ( EXP ) STATEMENT
                case WHILE:
                    m1 = marker++;
                    m2 = marker++;
                    buffer->addchars("#");
                    buffer->addchars(m1);
                    buffer->addchars(" NOP\r\n");
                    makeCode(node->getChildNode(2));
                    buffer->addchars("JIN #");
                    buffer->addchars(m2);
                    buffer->addchars("\r\n");
                    makeCode(node->getChildNode(4));
                    buffer->addchars("JMP #");
                    buffer->addchars(m1);
                    buffer->addchars("\r\n");
                    buffer->addchars("#");
                    buffer->addchars(m2);
                    buffer->addchars(" NOP\r\n");
                    break;

                default:
                    break;
            }
            break;

        // EXP ::= EXP2 OP_EXP
        case ParseEnums::EXP:
            if(node->getChildNode(1)->getType() == ParseEnums::NOTYPE) {
                makeCode(node->getChildNode(0));
            } else if (node->getChildNode(1)->getChildNode(0)->getType() == ParseEnums::OPGREATER) {
                makeCode(node->getChildNode(1));
                makeCode(node->getChildNode(0));
                buffer->addchars("LES\r\n");
            } else if (node->getChildNode(1)->getChildNode(0)->getType() == ParseEnums::OPUNEQUAL) {
                makeCode(node->getChildNode(0));
                makeCode(node->getChildNode(1));
                buffer->addchars("NOT\r\n");
            } else {
                makeCode(node->getChildNode(0));
                makeCode(node->getChildNode(1));
            }
            break;

        // INDEX ::= [ EXP ] | empty
        case ParseEnums::INDEX:
            if (node->getChildNodesCount() > 1) {
                makeCode(node->getChildNode(1));
                buffer->addchars("ADD\r\n");
            }
            break;

        // EXP2
        case ParseEnums::EXP2:
            switch (node->getChildNode(0)->getToken()->getType()) {

                // EXP2 ::= ( EXP )
                case SIGN_LEFTBRACKET:
                    makeCode(node->getChildNode(1));
                    break;

                // EXP2 ::= identifier INDEX
                case IDENTIFIER:
                    buffer->addchars("LA $");
                    buffer->addchars(node->getChildNode(0)->getToken()->getEntry()->getLexem());
                    buffer->addchars("\r\n");
                    makeCode(node->getChildNode(1));
                    buffer->addchars("LV\r\n");
                    break;

                // EXP2 ::= integer
                case INTEGER:
                    buffer->addchars("LC ");
                    buffer->addchars(node->getChildNode(0)->getToken()->getValue());
                    buffer->addchars("\r\n");
                    break;

                // EXP2 ::= - EXP2
                case SIGN_SUBTRACTION:
                    buffer->addchars("LC 0\r\n");
                    makeCode(node->getChildNode(1));
                    buffer->addchars("SUB\r\n");
                    break;

                // EXP2 ::= ! EXP2
                case SIGN_EXCLAMATION:
                    makeCode(node->getChildNode(1));
                    buffer->addchars("NOT\r\n");
                    break;

                default:
                    break;
            }
            break;

        // OP_EXP ::= OP EXP | empty
        case ParseEnums::OP_EXP:
            if (node->getChildNodesCount() > 1) {
                makeCode(node->getChildNode(1));
                makeCode(node->getChildNode(0));
            }
            break;

        // OP
        case ParseEnums::OP:
            switch (node->getChildNode(0)->getToken()->getType()) {

                // OP ::= +
                case SIGN_ADDITITON:
                    buffer->addchars("ADD\r\n");
                    break;

                // OP ::= -
                case SIGN_SUBTRACTION:
                    buffer->addchars("SUB\r\n");
                    break;

                // OP ::= *
                case SIGN_MULTIPLICATION:
                    buffer->addchars("MUL\r\n");
                    break;

                // OP ::= /
                case SIGN_DIVISION:
                    buffer->addchars("DIV\r\n");
                    break;

                // OP ::= <
                case SIGN_LT:
                    buffer->addchars("LES\r\n");
                    break;

                // OP ::= >
                case SIGN_GT:

                    break;

                // OP ::= =
                case SIGN_ASSIGN:
                    buffer->addchars("EQU\r\n");
                    break;

                // OP ::= <=>
                case SIGN_NE:
                    buffer->addchars("EQU\r\n");
                    break;

                // OP ::= &
                case SIGN_AMPERSAND:
                    buffer->addchars("AND\r\n");
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    }
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

void ParseTree::printTree2(Node* node) {
    const char* node_str[] = { "ROOT", "PROG", "DECLS", "DECL", "ARRAY", "STATEMENTS", "STATEMENT", "EXP",
            "EXP2", "INDEX", "OP_EXP", "OP", "INTEGER", "IDENTIFIER", "KEYWORD", "SEMICOLON", "EMPTY" };
    const char* ttype_str[] = { "NO_TYPE", "INTEGER", "IDENTIFIER", "PRINT",
        "READ", "IF", "ELSE", "WHILE", "INT", "ADDITITON", "SUBTRACTION",
        "DIVISION", "MULTIPLICATION", "LT", "GT", "ASSIGN", "NE",
        "EXCLAMATION", "AMPERSAND", "SEMICOLON", "COLON", "LEFTBRACKET",
        "RIGHTBRACKET", "LEFTANGLEBRACKET", "RIGHTANGLEBRACKET",
        "LEFTSQUAREBRACKET", "RIGHTSQUAREBRACKET" };
    const char* type_str[] = { "INTTYPE", "INTARRAYTYPE", "ARRAYTYPE", "NOTYPE", "ERRORTYPE",
                        "OPPLUS", "OPMINUS", "OPMULT", "OPDIV", "OPLESS", "OPGREATER",
                        "OPEQUAL", "OPUNEQUAL", "OPAND" };


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
    cout << " Type: " << type_str[node->getType()];
    cout << endl;
    for (int i = 0; i < node->getChildNodesCount(); i++) {
        printTree2(node->getChildNode(i));
    }

    depth--;
}
