#include "Buffer.hpp"

using namespace std;

Buffer::Buffer(char* filename) {
    std::cout << "Buffer::Buffer\n";
    fstream* file = new fstream();
    file->open(filename);
    if (file->is_open()) {
        std::cout << "offen\n";
    }
}

Buffer::~Buffer() {
    //file->close();
}

char Buffer::getchar() {
    return '0';
}
