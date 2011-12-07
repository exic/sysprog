#ifndef PARSER_H_
#define PARSER_H_

#include "../scan/Scanner.hpp"
#include <iostream>

using namespace std;

class Parser {
public:
	Parser(Scanner* scanner);
	virtual ~Parser();
	void parse();
private:
	Scanner* scanner;
};

#endif /* PARSER_H_ */
