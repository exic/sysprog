#include "Buffer.hpp"

using namespace std;

Buffer::Buffer(char* filename) {
    file.open(filename);
    blockIndex = 0;
    current = 0;
    fillBlock();
}



Buffer::~Buffer() {
    file.close();
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
    return file.is_open();
}

void Buffer::fillBlock() {
    if (file.eof()) {
        return;
    }
    int i = 0;
    //cout << "running fillBlock\n";
    while (!file.eof() && i < BUFFER__CHARS_PER_BLOCK) {
        buffer[blockIndex][i++] = file.get();
      //  cout << "put at " << (i-1) << ": " << buffer[blockIndex][i-1] << endl;
    }
}


