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
    Parser* parser = new Parser(scanner);
    Buffer* buf_out = new Buffer(argv[2], false);

    parser->parse();

    delete parser;
    delete scanner;
    delete buf_out;

    return 0;
}
