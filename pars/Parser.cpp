#include "Parser.hpp"

Parser::Parser(Scanner* scanner) {
	this->scanner = scanner;
}

Parser::~Parser() {

}

void Parser::parse() {
	cout << ">> Start Parsing" << endl;


	cout << ">> End Parsing" << endl;
}
