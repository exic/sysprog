#ifndef BUFFER
#define BUFFER

#include <fstream>
#include <iostream>

class Buffer {
    public:
        Buffer(char* filename);
        ~Buffer();
        char getchar();
        void ungetchar();
    private:
        int i;
        //fstream* file;
};

#endif
