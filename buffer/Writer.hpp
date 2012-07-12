#ifndef WRITER
#define WRITER

// O_DIRECT, O_RDONLY
#include <unistd.h>
#include <fcntl.h>

// open(2)
#include <sys/types.h>
#include <sys/stat.h>

// perror(3)
#include <stdio.h>

// posix_memalign(3)
#include <stdlib.h>

// strcpy(3)
#include <string.h>

// Errors
#include <errno.h>

#include "Constants.hpp"


class Writer {
    public:
        Writer(char* filename);
        ~Writer();

        void writeBlock();
        void setBlock(char *buffer);

    private:
        int fd;
        char* buffer;
        int current;
};


#endif
