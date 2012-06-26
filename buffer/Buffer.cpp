#include "Buffer.hpp"

Buffer::Buffer(char* filename, bool read) {
    is_read = read;

    blockIndex = 0;
    current = 0;
    steppedBackBlock = false;

    if (read) {
        reader = new Reader(filename);
    } else {
        if ( (fd = open(filename,
                    O_WRONLY | O_CREAT | O_DIRECT,
                    00644)) < 0) {
            perror("Opening file for write failed");
            exit(1);
        }
        posix_memalign((void**)&buffer[blockIndex], ALIGNMENT, BUFSIZE);
        // initialize it
        buffer[blockIndex][current] = '\0';
    }

    if (read) {
        this->read();
    }
}



Buffer::~Buffer() {
    if (!is_read) {
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
            read();
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
        if (blockIndex < 0) {
            blockIndex *= -1;
        }
        steppedBackBlock = true;
    }
}

void Buffer::read() {
    buffer[blockIndex] = reader->readBlock();
}

void Buffer::writeBlock() {
    if ( (write(fd, buffer[blockIndex], BUFSIZE)) < 0) {
        perror("Write failed");
    }
}
