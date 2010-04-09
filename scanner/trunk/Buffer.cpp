#include "Buffer.hpp"

using namespace std;

Buffer::Buffer(char* filename) {
    file.open(filename);
}

Buffer::~Buffer() {
    file.close();
}

char Buffer::getchar() {
    int out;
    if (!file.eof()) {
        out = file.get();
        return (char) out;
    }
    return 0;
}
