#include "Reader.hpp"

Reader::Reader(char* filename) {
    done = 0;

    if ( (fd = open(filename, O_DIRECT | O_RDONLY)) < 0) {
        perror("Opening file for read failed");
        exit(1);
    }
}

Reader::~Reader() {
    close(fd);
}

void Reader::readBlock() {
    if (done) {
        return;
    }

    posix_memalign((void**)&buffer, ALIGNMENT, BUFSIZE * sizeof(char));

    int read_chars = read(fd, buffer, BUFSIZE);

    if (read_chars < BUFSIZE) {
        printf("done, at pos: %d\n", read_chars);
        buffer[read_chars] = -1;
        done = 1;
    }
}

char* Reader::getBlock() {
    return buffer;
}
