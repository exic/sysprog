#include "scan/Scanner.hpp"
#include "scan/Token.hpp"
#include "scan/TType.hpp"
#include "buffer/Buffer.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using std::cout;
using std::endl;
using std::cerr;

char* convertToCharArray(int value) {
//    cout << "attempt to convert value " << value << endl;
    char buffer[15];
    sprintf(buffer, "%i", value);
    return buffer;
}

int main(int argc, char* argv[]) {

const char* ttype_str[] = { "NO_TYPE", "INTEGER", "IDENTIFIER", "PRINT", "READ", "ADDITITON", "SUBTRACTION", "DIVISION", "MULTIPLICATION", "LT", "GT", "ASSIGN", "NE", "EXCLAMATION", "AMPERSAND", "SEMICOLON", "LEFTBRACKET", "RIGHTBRACKET", "LEFTANGLEBRACKET", "RIGHTANGLEBRACKET", "LEFTSQUAREBRACKET", "RIGHTSQUAREBRACKET" };

    if (argc <= 1) {
        cerr << "No input file given." << endl;
        return 1;
    }
    Scanner* s = new Scanner(argv[1]);
    Token* t;

    if (argc <= 2) {
        cerr << "No output file given." << endl;
        return 1;
    }

    Buffer* buf_out = new Buffer(argv[2], false);

    while ((t  = s->nextToken())) {
        buf_out->addchars( "Token " ); 
        buf_out->addchars( const_cast<char*>(ttype_str[t->getType()])); 
        buf_out->addchars( " Line: " ); 
//        char* line = itoa();
        buf_out->addchars( convertToCharArray( t->getLine() ) ); 
        buf_out->addchars( ", Column " ); 
        buf_out->addchars( convertToCharArray( t->getColumn() ) );

//        cout << "Token " << ttype_str[t->getType()] 
//            << " Line: " << t->getLine() 
//            << ", Column " << t->getColumn();

        if (t->getType() == IDENTIFIER) {
            buf_out->addchars(", Lexem: " ); 
            buf_out->addchars( t->getEntry()->getLexem());
//            cout << ", Lexem: " << t->getEntry()->getLexem();
        } else if (t->getType() == INTEGER) {
            buf_out->addchars(", Value: " ); 
            buf_out->addchars( convertToCharArray( t->getValue() ) );
//            cout << ", Value: " << t->getValue();
        }
        buf_out->addchars("\n");
//        cout << endl;
    }
//    outfile.close();
    delete s;
    delete buf_out;
    return 0;
}
