#include "Writer.hpp"

Writer::Writer(char* filename) {

    current = 0;

    if ( (fd = open(filename,
                O_WRONLY | O_CREAT | O_DIRECT,
                00644)) < 0) {
        perror("Opening file for write failed\n");
        exit(EXIT_FAILURE);
    }
}

Writer::~Writer() {
    close(fd);
}

void Writer::setBlock(char *buffer) {
    this->buffer = buffer;
}

void Writer::writeBlock() {
    if ( (write(fd, buffer, BUFSIZE*sizeof(char))) < 0) {
        perror("Write failed");
    }
    free(buffer);
}
