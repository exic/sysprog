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
        Writer(char* filename, pthread_mutex_t* full, pthread_mutex_t* empty);
        ~Writer();

        void writeBlock();
        void setBlock(char *buffer);
        char* getBuffer();
        void setDone();
        static void* thread(void *ptr);

    private:
        int fd;
        char* buffer;
        int current;
        int size;
        bool done;

        pthread_mutex_t *full, *empty;
};


#endif
