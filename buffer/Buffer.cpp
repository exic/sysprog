#include "Buffer.hpp"

using namespace std;

Buffer::Buffer(char* filename) {
    fd = open(filename, O_DIRECT | O_RDONLY);
    blockIndex = 0;
    current = 0;
    fillBlock();
//    cout << "read that.\n";
//    cout << buffer[blockIndex] << endl;
}



Buffer::~Buffer() {
    close(fd);
}

char Buffer::getchar() {
    if (current >= BUFSIZE) {
        blockIndex = (blockIndex + 1) % BLOCKS;
        current = 0;
        fillBlock();
    }
    if (buffer[blockIndex][current] == '\0') {
        current++;
        return getchar();
    }
    return (char) buffer[blockIndex][current++];
}

void Buffer::ungetchar() {
    current--;
}

void Buffer::fillBlock() {
    char *buf;
    posix_memalign((void**)&buf, ALIGNMENT, BUFSIZE);
    int read_chars = read(fd, buf, BUFSIZE);

    buffer[blockIndex] = buf;
    buffer[blockIndex][read_chars] = '\0';
    if (read_chars < BUFSIZE) {
        buffer[blockIndex][read_chars] = -1;
    }
}


