#include "Writer.hpp"

Writer::Writer(char* filename) {

    current = 0;

    if ( (fd = open(filename,
                O_WRONLY | O_CREAT | O_DIRECT,
                00644)) < 0) {
        perror("Opening file for write failed");
        exit(EXIT_FAILURE);
    }
    posix_memalign((void**)&buffer, ALIGNMENT, BUFSIZE * sizeof(char));
    if (errno == EINVAL) {
        perror("Well, wrong alignment?"); // wtf doesn't this work?
        exit(EXIT_FAILURE);
    } else if (errno == ENOMEM) {
        perror("Error allocating memory!");
        exit(EXIT_FAILURE);
    }
    // initialize it
    buffer[current] = '\0';
}

Writer::~Writer() {
    free(buffer);
    buffer = NULL;
    close(fd);
}

void Writer::setBlock(char *buffer) {
    this->buffer = buffer;
}

void Writer::writeBlock() {
    if ( (write(fd, buffer, BUFSIZE*sizeof(char))) < 0) {
        perror("Write failed");
    }
}
