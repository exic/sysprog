#include "Buffer.hpp"

using namespace std;

Buffer::Buffer(char* filename) {
    std::cout << "Buffer::Buffer\n";
    std::cout << "offen: " << file.is_open() << endl;
    file.open(filename);
    std::cout << "offen: " << file.is_open() << endl;
}

Buffer::~Buffer() {
    file.close();
    std::cout << "offen: " << file.is_open() << endl;
}

char Buffer::getchar() {
    int out;
    if (!file.eof()) {
        out = file.get();
        if (out == 10) { // newline
            //linecounter++;
        }
        if (out != -1) { // not eof
            //cout << out << endl;
            return (char) out;
        }
    }
    return 0;
}
