#ifndef TOKEN
#define TOKEN

#include "TType.hpp"
#include "Constants.hpp"
#include "string.h"
#include "../symtab/SymtabEntry.hpp"


class Token {
    public:
        /**
         * Constructs a new Token
         *
         * @param TType the type of this token
         * @param int pLine the line in which this token was found
         * @param int pColumn the column in which this token was found
         */
        Token(TType pType, int pLine, int pColumn);

        /**
         * @return TType this tokens type.
         */
        TType getType();

        /**
         * @return int the line this token was found in.
         */
        int getLine();

        /**
         * @return int the column this token was found in.
         */
        int getColumn();

        /**
         * For integer tokens.
         *
         * @return int the value of this token, if available.
         */
        long int getValue();

        /**
         * For integer tokens.
         *
         * @param long int this tokens value
         */
        void setValue(long int value);

        SymtabEntry* getEntry() { return entry; };

        void setEntry(SymtabEntry* entry) { this->entry = entry; };
    private:
        TType type;
        SymtabEntry* entry;
        int line;
        int column;
        long int value;
};

#endif
