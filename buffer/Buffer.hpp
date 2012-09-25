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
        /**
         * Construct a new buffer.
         *
         * @param char* filename that is to be read or written.
         * @param bool read true if this is a buffer for reading from a file,
         *                  false if it is a buffer for writing to a file.
         */
        Buffer(char* filename, bool read);
        ~Buffer();


        // Functions for read mode
        /**
         * @return char the next char in the buffer.
         */
        char getchar();

        /**
         * Makes the buffer index go back by one so that a character that has
         * already been returned by getchar() will be returned by getchar()
         * again.
         */
        void ungetchar();


        // Functions for write mode
        /**
         * Adds the string to the output buffer.
         *
         * @param char* string to be written.
         */
        void addchars(char* c);

        // (Convenience functions)
        /**
         * Converts the int value to string and adds it to the output buffer.
         * @param int value that will be appended.
         */
        void addchars(int value);
        /**
         * Adds the string to the output buffer.
         *
         * @param const char* string to be written.
         */
        void addchars(const char* c);

    private:
        // Buffer is used for reading: if it is false, this is a write buffer.
        bool is_read;
        Reader* reader;
        Writer* writer;
        void getNextBufferPart();
        void setNextBufferPart();
        // Current position in block
        int current;
        int blockIndex;
        char* buffer[BLOCKS];
        bool steppedBackBlock;

        pthread_t thread;
        pthread_mutex_t full, empty;
};

#endif
