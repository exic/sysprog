#ifndef UTIL
#define UTIL

class Util {
    public:
        static bool isDigit(char c) {
            return c >= '0' && c <= '9';
        }

        static bool isLetter(char c) {
            return (c >= 'a' && c <= 'z')
                || (c >= 'A' && c <= 'Z');
        }

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
