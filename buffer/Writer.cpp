#include "Writer.hpp"

Writer::Writer(char* filename) {

    current = 0;

    if ( (fd = open(filename,
                O_WRONLY | O_CREAT | O_DIRECT,
                00644)) < 0) {
        perror("Opening file for write failed");
        exit(1);
    }
    posix_memalign((void**)&buffer, ALIGNMENT, BUFSIZE * sizeof(char));
    if (errno == EINVAL) {
        perror("Well, wrong alignment?"); // wtf doesn't this work?
        exit(1);
    } else if (errno == ENOMEM) {
        perror("Error allocating memory!");
        exit(1);
    }
    // initialize it
    buffer[current] = '\0';
}

Writer::~Writer() {
    memset(buffer+current, ' ', (BUFSIZE-current));
    buffer[BUFSIZE-1] = '\n';
    writeBlock();
    free(buffer);
    buffer = NULL;
    close(fd);
}

void Writer::addchars(char* c) {
    int string_length = strlen(c);
    if ((current + string_length) < BUFSIZE) {
        strcpy(buffer+current, c);
        current += string_length;
    } else {
        // fill the current buffer
        int cut_at = (BUFSIZE - current);
        memcpy (buffer+current, c, cut_at);
        // write it
        writeBlock();

        current = 0;
        // add the rest
        addchars(c+cut_at);
    }
}

void Writer::addchars(int value) {
    char* buffer = new char[32];
    sprintf(buffer, "%i", value);
    addchars(buffer);
}

void Writer::addchars(const char* c) {
    addchars(const_cast<char*>(c));
}

void Writer::writeBlock() {
    if ( (write(fd, buffer, BUFSIZE*sizeof(char))) < 0) {
        perror("Write failed");
    }
}
