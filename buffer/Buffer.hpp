#define _GNU_SOURCE 1

#ifndef BUFFER
#define BUFFER

#include "Constants.hpp"

// remove me
#include <iostream>
using namespace std;

// open(2)
#include "sys/types.h"
#include "sys/stat.h"

#include <unistd.h>
#include <fcntl.h>

// posix_memalign(3)
#include <stdlib.h>

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
        char* buffer[BLOCKS];
        int fd;
};

#endif
