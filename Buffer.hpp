#ifndef BUFFER
#define BUFFER

#include "Constants.hpp"

// remove me
#include <iostream>
using namespace std;

// as said in man 2 open
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
// man 2 close
#include "unistd.h"

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
        int fd;
};

#endif
