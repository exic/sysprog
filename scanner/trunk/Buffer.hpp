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
    private:
        int i;
        //int linecounter;
        ifstream file;
};

#endif
