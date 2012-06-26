#include "Buffer.hpp"

Buffer::Buffer(char* filename, bool read) {
    is_read = read;

    blockIndex = 0;
    current = 0;
    steppedBackBlock = false;

    if (read) {
        reader = new Reader(filename);
    } else {
        writer = new Writer(filename);
    }

    if (read) {
        this->read();
    }
}



Buffer::~Buffer() {
    if (is_read) {
        delete reader;
    } else {
        delete writer;
    }
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
    writer->addchars(c);
}
void Buffer::addchars(int value) {
    writer->addchars(value);
}
void Buffer::addchars(const char* c) {
    writer->addchars(c);
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

void Buffer::write() {
    writer->writeBlock();
}
