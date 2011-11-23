#define _GNU_SOURCE

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

// perror(3)
#include <stdio.h>

// strcpy(3)
#include <string.h>

class Buffer {
    public:
        Buffer(char* filename, bool read);
        ~Buffer();
        char getchar();
        void addchars(char* c);
        void ungetchar();
    private:
        bool is_read;
        void readBlock();
        void writeBlock();
        int i;
        int current;
        int blockIndex;
        char* buffer[BLOCKS];
        int fd;
};

#endif
