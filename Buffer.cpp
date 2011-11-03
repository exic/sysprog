#include "Buffer.hpp"

using namespace std;

Buffer::Buffer(char* filename) {
    fd = open(filename, O_DIRECT | O_RDONLY);
    blockIndex = 0;
    current = 0;
    fillBlock();
}



Buffer::~Buffer() {
    close(fd);
}

char Buffer::getchar() {
    if (current >= BUFFER__CHARS_PER_BLOCK) {
        blockIndex = (blockIndex + 1) % BUFFER__BLOCKS;
        current = 0;
        fillBlock();
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
//    if (file.eof()) {
//        return;
//    }
    int i = 0;
//    char *buf = buffer[blockIndex];
    char buf[26];
    char *s= buf;
    cout << "running fillBlock\n";
    while (i < BUFFER__CHARS_PER_BLOCK) {
        cout << s << endl;
        cout << read(fd, s, 25) << endl;
        cout << s << endl;
      //  cout << "put at " << (i-1) << ": " << buffer[blockIndex][i-1] << endl;
    }
}


