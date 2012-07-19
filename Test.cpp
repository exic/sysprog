#include "scan/Scanner.hpp"
#include "pars/Parser.hpp"
#include "scan/Token.hpp"
#include "scan/TType.hpp"
#include "buffer/Buffer.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using std::cout;
using std::endl;
using std::cerr;

int main(int argc, char* argv[]) {

    if (argc <= 1) {
        cerr << "No input file given." << endl;
        return 1;
    } else if (argc <= 2) {
        cerr << "No output file given." << endl;
        return 1;
    }

    Scanner* scanner = new Scanner(argv[1]);
//    Parser* parser = new Parser(scanner);
    Buffer* buf_out = new Buffer(argv[2], false);

//=========================================================
// SCANNEROUTPUT
//=========================================================
    const char* ttype_str[] = { "NO_TYPE", "INTEGER", "IDENTIFIER", "PRINT",
        "READ", "IF", "ELSE", "WHILE", "INT", "ADDITITON", "SUBTRACTION",
        "DIVISION", "MULTIPLICATION", "LT", "GT", "ASSIGN", "NE",
        "EXCLAMATION", "AMPERSAND", "SEMICOLON", "COLON", "LEFTBRACKET",
        "RIGHTBRACKET", "LEFTANGLEBRACKET", "RIGHTANGLEBRACKET",
        "LEFTSQUAREBRACKET", "RIGHTSQUAREBRACKET" };

    Token* t;
    while ((t  = scanner->nextToken())) {
        if (t->getType() == NO_TYPE) {
            // skip error token for writing.
            continue;
        }
        buf_out->addchars( "Token " );
        buf_out->addchars( ttype_str[t->getType()]);
        buf_out->addchars( " Line: " );
        buf_out->addchars(t->getLine());
        buf_out->addchars( ", Column " );
        buf_out->addchars(t->getColumn());

//        cout << "Token " << ttype_str[t->getType()]
//            << " Line: " << t->getLine()
//            << ", Column " << t->getColumn();

        if (t->getType() == IDENTIFIER) {
            buf_out->addchars(", Lexem: " );
            buf_out->addchars( t->getEntry()->getLexem());
//            cout << ", Lexem: " << t->getEntry()->getLexem();
        } else if (t->getType() == INTEGER) {
            buf_out->addchars(", Value: " );
            buf_out->addchars(t->getValue());
//            cout << ", Value: " << t->getValue();
        }
        buf_out->addchars("\n");
//        cout << endl;
    }
//=========================================================

//    parser->parse();

//    delete parser;
    delete scanner;
    delete buf_out;

    return 0;
}
