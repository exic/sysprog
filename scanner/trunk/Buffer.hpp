#ifndef BUFFER
#define BUFFER

#include <fstream>
#include <iostream>

using std::ifstream;

class Buffer {
    public:
        Buffer(char* filename);
        ~Buffer();
        char getchar();
        void ungetchar();
        bool isOpen();
    private:
        int i;
        int current;
        int bufferIndex;
        char buffer[2][128];
        ifstream file;
};

#endif
