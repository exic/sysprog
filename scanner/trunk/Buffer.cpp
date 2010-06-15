#include "Buffer.hpp"

using namespace std;

Buffer::Buffer(char* filename) {
    file.open(filename);
    int i = 0;
    bufferIndex = 0;
    current = 0;
    while (!file.eof() && i < 128) {
        buffer[bufferIndex][i++] = file.get();
    }
    if (!file.eof()) {
        bufferIndex++;
        i = 0;
        while (!file.eof() && i < 128) {
            buffer[bufferIndex][i++] = file.get();
        }
    }
    // buffer[bufferIndex][i] = '\0';
}

Buffer::~Buffer() {
    file.close();
}

char Buffer::getchar() {
    return (char) buffer[bufferIndex][current++];
}

void Buffer::ungetchar() {
    current--;
}
