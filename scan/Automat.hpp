#ifndef AUTOMAT
#define AUTOMAT

#include "Token.hpp"
#include "Status.hpp"
#include "Constants.hpp"
#include "Util.hpp"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <error.h>
using namespace std;

class Automat {
    public:
        /**
         * Initializes a new Automat
         */
        Automat();

        /**
         * Read the next character.
         *
         * @param char Character to be read by the automat.
         *
         * The character is evaluated by the automat and internal states may change.
         * To access the current state, use below functions.
         */
        void readChar(char c);

        /**
         * The last read character was EOF, scanning is probably over now.
         *
         * Status may now be FINAL or FINAL_COMMENT_NOT_CLOSED_ERROR. Calling
         * program should handle it accordingly.
         */
        bool isEof();

        /**
         * Returns line number.
         *
         * A new line starts if a '\n' char was read. Counting starts at 1.
         */
        int getLine();

        /**
         * Returns current character count in current line.
         *
         * A new column starts at each read which is no '\n' character. Counting starts at 1.
         */
        int getColumn();

        /**
         * Returns number of characters that need to be re-read.
         *
         * This should be used to go back steps inside some buffer.
         * Automat was "thinking" that some token would appear, but it wasn't.
         * We have to take a second attempt without the previous assumption.
         * 
         * @return int Number of characters that need to be re-read, 0 if none to be reread.
         */
        int getUnget() {
            return unget;
        }

        /**
         * Constructs and returns the current token.
         *
         * Prints on stderr if something went wrong, e. g. problems with lexems or ints.
         *
         * @return Token if done reading some token. null, if there was no token read yet.
         */
        Token* getToken();

        /**
         * Returns the lexem of the last read token.
         *
         * If the lexem exceeded MAX_LEXEM_LENGTH, an empty string will be returned.
         *
         * @return char* the current lexem.
         */
        char* getLexem() {
            return lexem;
        }
    private:
        void newline();
        Status statusNONE(char c);
        Status statusCOMMENT(char c);
        Status statusIDENTIFIER(char c);
        Status statusINT(char c);
        Status statusSIGN(char c);
        TType getTokenTypeBySign();
        bool isTokenRead();
        bool isError();
        Status getStatus() {
            return status;
        }
        int line;
        int column;
        char lastchar;
        int sign_index;
        char sign[MAX_SIGN_LENGTH];
        int lexem_index;
        char lexem[MAX_LEXEM_LENGTH];
        char value_str[MAX_LEXEM_LENGTH];
        int value_str_index;
        int unget;
        Status status;
};

#endif
