#ifndef RULE_HPP_
#define RULE_HPP_

class Rule {
public:
    enum Type { ROOT, PROG, DECLS, DECL, ARRAY,    STATEMENTS,    STATEMENT, EXP,
                EXP2, INDEX, OP_EXP, OP, INTEGER, IDENTIFIER, KEYWORD, SEMICOLON, EMPTY };
};

#endif /* RULE_HPP_ */
