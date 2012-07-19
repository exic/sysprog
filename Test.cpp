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

void usage();

int main(int argc, char* argv[]) {

    if (argc <= 1) {
        usage();
        return 1;
    }

    int parse;
    if (strcmp(argv[1], "parse") == 0) {
        parse = 1;
    } else if (strcmp(argv[1], "scan") == 0) {
        parse = 0;
    } else {
        usage();
        return 1;
    }

    if (argc <= 2) {
        usage();
        cerr << "No input file given." << endl;
        return 1;
    } else if (argc <= 3) {
        usage();
        cerr << "No output file given." << endl;
        return 1;
    }


    Scanner* scanner = new Scanner(argv[2]);

    if (!parse) {
        //=========================================================
        // SCANNEROUTPUT
        //=========================================================

        Buffer* buf_out = new Buffer(argv[3], false);

        const char* ttype_str[] = { "NO_TYPE", "INTEGER", "IDENTIFIER", "PRINT",
            "READ", "IF", "ELSE", "WHILE", "INT", "ADDITITON", "SUBTRACTION",
            "DIVISION", "MULTIPLICATION", "LT", "GT", "ASSIGN", "NE",
            "EXCLAMATION", "AMPERSAND", "SEMICOLON", "COLON", "LEFTBRACKET",
            "RIGHTBRACKET", "LEFTANGLEBRACKET", "RIGHTANGLEBRACKET",
            "LEFTSQUAREBRACKET", "RIGHTSQUAREBRACKET" };

        Token* t;
        while ((t  = scanner->nextToken())) {
            if (t->getType() == NO_TYPE) {
                delete t;
                // skip error token for writing.
                continue;
            }
            buf_out->addchars( "Token " );
            buf_out->addchars( ttype_str[t->getType()]);
            buf_out->addchars( " Line: " );
            buf_out->addchars(t->getLine());
            buf_out->addchars( ", Column " );
            buf_out->addchars(t->getColumn());

//            cout << "Token " << ttype_str[t->getType()]
//                << " Line: " << t->getLine()
//                << ", Column " << t->getColumn();

            if (t->getType() == IDENTIFIER) {
                buf_out->addchars(", Lexem: " );
                buf_out->addchars( t->getEntry()->getLexem());
//                cout << ", Lexem: " << t->getEntry()->getLexem();
            } else if (t->getType() == INTEGER) {
                buf_out->addchars(", Value: " );
                buf_out->addchars(t->getValue());
//                cout << ", Value: " << t->getValue();
            }
            buf_out->addchars("\n");
//            cout << endl;
            delete t;
        }
        delete buf_out;
        //=========================================================
    } else {
        Parser* parser = new Parser(scanner);
        parser->parse();
        delete parser;
    }

    delete scanner;

    return 0;
}

void usage() {
    cerr << "Usage: sysprog parse|scan inputfile outputfile" << endl;
}
