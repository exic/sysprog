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

bool Buffer::isOpen() {
    cout << "hi, this is my fd: " << fd << endl;
    return true;
}

void Buffer::fillBlock() {
//    char *buf = buffer[blockIndex];
    cout << "running fillBlock, "
        << "blockIndex: " << blockIndex
        << ", alignment: " << ALIGNMENT 
        << ", bufsize: " << BUFSIZE << "\n";
//    char *s= buffer[blockIndex];
    char *buf;
    posix_memalign((void**)&buf, ALIGNMENT, BUFSIZE);
    int read_chars = read(fd, buf, BUFSIZE);
    cout << "chars: " << read_chars << endl;
    buffer[blockIndex] = buf;
    buffer[blockIndex][read_chars] = '\0';
    if (read_chars < BUFSIZE) {
        buffer[blockIndex][read_chars] = -1;
    }
}


