#ifndef BUFFER
#define BUFFER

#include "Constants.hpp"
#include <fstream>
#include <iostream>

using std::ifstream;

class Buffer {
    public:
        Buffer(char* filename);
        ~Buffer();
        char getchar();
        void ungetchar();
        bool isOpen();
    private:
        void fillBlock();
        int i;
        int current;
        int blockIndex;
        char buffer[BUFFER__BLOCKS][BUFFER__CHARS_PER_BLOCK];
        ifstream file;
};

#endif
