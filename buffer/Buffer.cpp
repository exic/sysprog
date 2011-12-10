#include "Buffer.hpp"

using namespace std;

Buffer::Buffer(char* filename, bool read) {
    this->is_read = read;

    blockIndex = 0;
    current = 0;
    steppedBackBlock = false;

    if (read) {
        if ( (fd = open(filename, O_DIRECT | O_RDONLY)) < 0) {
            perror("Opening file for read failed");
            exit(1);
        }
    } else {
        if ( (fd = open(filename,
                    O_WRONLY | O_CREAT | O_DIRECT,
                    00644)) < 0) {
            perror("Opening file for write failed");
            exit(1);
        }
        posix_memalign((void**)&buffer[blockIndex], ALIGNMENT, BUFSIZE);
    }

    if (read) {
        readBlock();
    }
}



Buffer::~Buffer() {
    if (! this->is_read && !buffer) {
        memset(buffer[blockIndex]+current, ' ', (BUFSIZE-current));
        buffer[blockIndex][BUFSIZE-1] = '\n';
        writeBlock();
        free(buffer[blockIndex]);
    }
    close(fd);
}

char Buffer::getchar() {
    if (current >= BUFSIZE) {
        blockIndex = (blockIndex + 1) % BLOCKS;
        current = 0;
        if (steppedBackBlock) {
            steppedBackBlock = false;
        } else {
            readBlock();
        }
    }

    if (buffer[blockIndex][current] == '\0') {
        current++;
        return getchar();
    }

    return (char) buffer[blockIndex][current++];
}

void Buffer::addchars(char* c) {

    int string_length = strlen(c);
    if ((current + string_length) < BUFSIZE) {
        strcpy(buffer[blockIndex]+current, c);
        current += string_length;
    } else {
        // fill the current buffer
        int cut_at = (BUFSIZE - current);
        memcpy (buffer[blockIndex]+current, c, cut_at);
        // write it
        writeBlock();

        current = 0;
        // add the rest
        addchars(c+cut_at);
    }
}

void Buffer::addchars(int value) {
    char* buffer = new char[32];
    sprintf(buffer, "%i", value);
    addchars(buffer);
}

void Buffer::addchars(const char* c) {
    addchars(const_cast<char*>(c));
}


void Buffer::ungetchar() {
    current--;
    if (current < 0) {
        current = BUFSIZE - 1;
        blockIndex = (blockIndex - 1) % BLOCKS;
        steppedBackBlock = true;
    }
}

void Buffer::readBlock() {
    posix_memalign((void**)&buffer[blockIndex], ALIGNMENT, BUFSIZE);

    int read_chars = read(fd, buffer[blockIndex], BUFSIZE);

    buffer[blockIndex][read_chars] = '\0';
    if (read_chars < BUFSIZE) {
        buffer[blockIndex][read_chars] = -1;
    }
}

void Buffer::writeBlock() {
    if ( (write(fd, buffer[blockIndex], BUFSIZE)) < 0) {
        perror("Write failed");
    }
}
