#ifndef UTIL
#define UTIL

class Util {
    public:
        /**
         * @param char
         * @return true if the provided character is a digit, false otherwise
         */
        static bool isDigit(char c) {
            return c >= '0' && c <= '9';
        }

        /**
         * @param char
         * @return true if the provided character is a letter, false otherwise
         */
        static bool isLetter(char c) {
            return (c >= 'a' && c <= 'z')
                || (c >= 'A' && c <= 'Z');
        }

        /**
         * @param char
         * @return true if the provided character is a sign as defined by the
         * application, false otherwise.
         */
        static bool isSign(char c) {
            char signs[] = "+-/*<>=!&;:(){}[]";
            return containsChar(signs, c);
        }

    private:
        static bool containsChar(char string[], char c) {
            for (unsigned int i = 0; i < strlen(string); i++) {
                if (string[i] == c) {
                    return true;
                }
            }
            return false;
        }

};



#endif
