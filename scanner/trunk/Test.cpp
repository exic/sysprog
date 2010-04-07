#include "Scanner.hpp"
#include "Token.hpp"
#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        cout << "No file given" << endl;
        return 1;
    }
    Scanner* s = new Scanner(argv[1]);
    Token* t;
    while ((t  = s->nextToken())) {
        cout << "Token " << t->getType().getName() << ": Line " << t->getLine() << ", Column " << t->getColumn() << endl;
    }
    return 0;
}
