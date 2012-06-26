#include "Reader.hpp"

Reader::Reader(char* filename) {
    if ( (fd = open(filename, O_DIRECT | O_RDONLY)) < 0) {
        perror("Opening file for read failed");
        exit(1);
    }
}

char* Reader::readBlock() {

    posix_memalign((void**)&buffer, ALIGNMENT, BUFSIZE);

    int read_chars = read(fd, buffer, BUFSIZE);

    buffer[read_chars] = '\0';
    if (read_chars < BUFSIZE) {
        buffer[read_chars] = -1;
    }

    return buffer;
}
