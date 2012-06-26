#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#ifndef READER
#define READER

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

#include "Constants.hpp"

class Reader {
    public:
        Reader(char* filename);
        ~Reader();
        char* readBlock();

    private:
        int fd;
        char* buffer;
};

#endif
