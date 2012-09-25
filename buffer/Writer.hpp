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

// pthread
#include <pthread.h>
#include <semaphore.h>

#include "Constants.hpp"


class Writer {
    public:
        /**
         * Constructs a new writer.
         *
         * @param char* filename to be written to.
         * @param *pthread_mutex_t full indicating if the writer buffer is full
         *                              and can be flushed to disk.
         * @param *pthread_mutex_t empty indicating if the writer buffer was
         *              flushed and can be filled again.
         */
        Writer(char* filename, pthread_mutex_t* full, pthread_mutex_t* empty);

        /**
         * Deletes this writer. Closes the file handle.
         */
        ~Writer();

        /**
         * Sets the block that can be flushed.
         * Should only be called if the empty mutex was unlocked by the writer.
         *
         * @param char* buffer that will be written to the file.
         */
        void setBlock(char *buffer);

        /**
         * Align memory that can be written to.
         *
         * @return char* pointer to the buffer that an external application can
         *                      write to.
         */
        char* getBuffer();

        /**
         * If the application is done writing to the writer, this function
         * should be called to let the writer know everything is done and the
         * thread can be joined.
         */
        void setDone();

        /**
         * This writer's thread. To be created and joined/stopped by some caller.
         */
        static void* thread(void *ptr);

    private:
        int fd;
        char* buffer;
        int current;
        int size;
        bool done;
        void writeBlock();

        pthread_mutex_t *full, *empty;
};


#endif
