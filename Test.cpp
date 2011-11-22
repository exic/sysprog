#include "scan/Scanner.hpp"
#include "scan/Token.hpp"
#include "scan/TType.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::cerr;

int main(int argc, char* argv[]) {

const char* ttype_str[] = { "INTEGER", "IDENTIFIER", "PRINT", "READ", "ADDITITON", "SUBTRACTION", "DIVISION", "MULTIPLICATION", "LT", "GT", "ASSIGN", "NE", "EXCLAMATION", "AMPERSAND", "SEMICOLON", "LEFTBRACKET", "RIGHTBRACKET", "LEFTANGLEBRACKET", "RIGHTANGLEBRACKET", "LEFTSQUAREBRACKET", "RIGHTSQUAREBRACKET" };

    if (argc <= 1) {
        cerr << "No input file given." << endl;
        return 1;
    }
    Scanner* s = new Scanner(argv[1]);
    Token* t;
//    ofstream outfile;

    if (argc <= 2) {
        cerr << "No output file given." << endl;
        return 1;
    }

//    if (std::remove(argv[2]) == 0) {
//        cout << "Deleted outfile for new run." <<endl;
//    }

//    outfile.open(argv[2]);
//    if (!outfile.is_open()) {
//        cerr << "Problem opening file " << argv[2] << endl;
//        return 1;
//    }

    while ((t  = s->nextToken())) {
//        outfile << "Token " << ttype_str[t->getType()] << " Line: " << t->getLine() << ", Column " << t->getColumn();
        cout << "Token " << ttype_str[t->getType()] << " Line: " << t->getLine() << ", Column " << t->getColumn();
        if (t->getType() == IDENTIFIER) {
//            outfile << ", Lexem: " << t->getEntry()->getLexem();
            cout << ", Lexem: " << t->getEntry()->getLexem();
        } else if (t->getType() == INTEGER) {
//            outfile << ", Value: " << t->getValue();
            cout << ", Value: " << t->getValue();
        }
//        outfile << endl;
        cout << endl;
    }
//    outfile.close();
    delete s;
    return 0;
}
