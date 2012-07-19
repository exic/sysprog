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
        Reader(char* filename, pthread_mutex_t*, pthread_mutex_t*);
        ~Reader();
        void readBlock();
        char* getBlock();

        static void* thread(void *ptr);

    private:
        int fd;
        int done;
        pthread_mutex_t *full, *empty;

        char* buffer;
        int size;
};

#endif
