#include "Reader.hpp"

Reader::Reader(char* filename, pthread_mutex_t* full, pthread_mutex_t* empty) {
    done = 0;

    this->full = full;
    this->empty = empty;

    if ( (fd = open(filename, O_DIRECT | O_RDONLY)) < 0) {
        perror("Opening file for read failed");
        exit(EXIT_FAILURE);
    }

    struct stat file_stat;
    if (fstat(fd, &file_stat) == -1) {
        perror("stat");
        exit(1);
    }
    size = file_stat.st_blksize;
}

Reader::~Reader() {
    close(fd);
}

void Reader::readBlock() {
    if (done) {
        return;
    }

    if (posix_memalign((void**)&buffer, size, BUFSIZE) != 0) {
        printf("Aligning memory failed\n");
        exit(EXIT_FAILURE);
    }

    int read_chars;
    if ( (read_chars = read(fd, buffer, BUFSIZE)) < 0) {
        perror("Reading from file failed");
        exit(EXIT_FAILURE);
    }

    if (read_chars < BUFSIZE) {
        buffer[read_chars] = -1;
        done = 1;
    }
}

char* Reader::getBlock() {
    return buffer;
}

void* Reader::thread(void *context) {
    Reader* reader = (Reader*) context;
    while (1) {
        pthread_mutex_lock(reader->empty);
        if (reader->done) {
            break;
        }
        reader->readBlock();
        pthread_mutex_unlock(reader->full);
    }
    return 0;
}
