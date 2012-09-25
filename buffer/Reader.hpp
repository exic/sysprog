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

// stat
#include <sys/stat.h>
#include <stdint.h>

// perror(3)
#include <stdio.h>

// posix_memalign(3)
#include <stdlib.h>

// pthread
#include <pthread.h>
#include <semaphore.h>

#include "Constants.hpp"

class Reader {
    public:
        /**
         * Constructs a new reader.
         *
         * @param char* filename to be read from.
         * @param *pthread_mutex_t full indicating if the reader buffer is full.
         * @param *pthread_mutex_t empty indicating if the reader buffer was
         *              read and can be filled again.
         */
        Reader(char* filename, pthread_mutex_t* full, pthread_mutex_t* empty);

        /**
         * Deletes this reader. Closes the file handle.
         */
        ~Reader();

        /**
         * Returns the block that was read.
         * Should only be called if the full mutex was unlocked by the reader.
         *
         * It's the applications responsibility to free this space after usage.
         *
         * @return the current read block.
         */
        char* getBlock();

        /**
         * This reader's thread. To be created and joined/stopped by some caller.
         */
        static void* thread(void *ptr);

    private:
        int fd;
        int done;
        pthread_mutex_t *full, *empty;
        void readBlock();

        char* buffer;
        int size;
};

#endif
