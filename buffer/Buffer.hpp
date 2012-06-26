#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#ifndef BUFFER
#define BUFFER

// open(2)
#include <sys/types.h>
#include <sys/stat.h>

// posix_memalign(3)
#include <stdlib.h>

// perror(3)
#include <stdio.h>

// strcpy(3)
#include <string.h>

#include "Constants.hpp"
#include "Reader.hpp"

class Buffer {
    public:
        Buffer(char* filename, bool read);
        ~Buffer();

        // Functions in read mode
        char getchar();
        void ungetchar();

        // Functions for write mode
        void addchars(char* c);
        // Convenience functions
        void addchars(int value);
        void addchars(const char* c);

    private:
        // Buffer is used for reading: if it is false, this is a write buffer.
        bool is_read;
        Reader* reader;
        void read();
        void writeBlock();
        // Current position in block
        int current;
        int blockIndex;
        char* buffer[BLOCKS];
        int fd;
        bool steppedBackBlock;
};

#endif
