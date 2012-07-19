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

// pthread
#include <pthread.h>
#include <semaphore.h>

#include "Constants.hpp"
#include "Reader.hpp"
#include "Writer.hpp"

class Buffer {
    public:
        Buffer(char* filename, bool read);
        ~Buffer();

        // Functions for read mode
        char getchar();
        void ungetchar();

        // Functions for write mode
        void addchars(char* c);
        // Convenience functions
        void addchars(int value);
        void addchars(const char* c);

        pthread_mutex_t full, empty;

    private:
        // Buffer is used for reading: if it is false, this is a write buffer.
        bool is_read;
        Reader* reader;
        Writer* writer;
        void getNextBufferPart();
        void setNextBufferPart();
        void write();
        // Current position in block
        int current;
        int blockIndex;
        char* buffer[BLOCKS];
        bool steppedBackBlock;

        pthread_t thread;
};

#endif
