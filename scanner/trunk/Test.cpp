#include "Scanner.hpp"
#include "Token.hpp"
#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
    const char* ttype_str[] =  { "integer", "identifier", "print", "read",
        "addititon", "subtraction", "division", "multiplication", "lt", "gt",
        "eq", "ne", "exclamation", "ampersand", "semicolon", "leftBracket",
        "rightBracket", "leftAngleBracket", "rightAngleBracket",
        "leftSquareBracket", "rightSquareBracket" };
    if (argc <= 1) {
        cout << "No file given" << endl;
        return 1;
    }
    Scanner* s = new Scanner(argv[1]);
    Token* t;
    while ((t  = s->nextToken())) {
        cout << "Token " << ttype_str[t->getType()] << ": Line " << t->getLine() << ", Column " << t->getColumn() << endl;
    }
    delete s;
    return 0;
}
