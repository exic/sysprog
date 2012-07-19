#include "Writer.hpp"

Writer::Writer(char* filename, pthread_mutex_t* full, pthread_mutex_t* empty) {

    done = 0;
    current = 0;

    this->full = full;
    this->empty = empty;

    if ( (fd = open(filename,
                O_WRONLY | O_CREAT | O_DIRECT,
                00644)) < 0) {
        perror("Opening file for write failed");
        exit(EXIT_FAILURE);
    }

    struct stat file_stat;
    if (fstat(fd, &file_stat) == -1) {
        perror("stat");
        exit(1);
    }
    size = file_stat.st_blksize;
}

char* Writer::getBuffer() {
    char* buffer;
    if (posix_memalign((void**)&buffer, size, BUFSIZE) != 0) {
        printf("Aligning memory failed\n");
        exit(EXIT_FAILURE);
    }
    return buffer;
}

Writer::~Writer() {
    close(fd);
}

void Writer::setBlock(char *buffer) {
    this->buffer = buffer;
}

void Writer::writeBlock() {
    if ( (write(fd, buffer, BUFSIZE)) < 0) {
        perror("Write failed");
    }
    free(buffer);
}

void Writer::setDone() {
    this->done = 1;
}

void* Writer::thread(void *context) {
    Writer* writer = (Writer*) context;
    while (1) {
        pthread_mutex_lock(writer->full);
        if (writer->done) {
            break;
        }
        writer->writeBlock();
        pthread_mutex_unlock(writer->empty);
    }
    return 0;
}


