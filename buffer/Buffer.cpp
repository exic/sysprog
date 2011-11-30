#include "Buffer.hpp"

using namespace std;

Buffer::Buffer(char* filename, bool read) {
    this->is_read = read;

    if (read) {
        if ( (fd = open(filename, O_DIRECT | O_RDONLY)) < 0) {
            perror("Opening file for read failed");
            exit(1);
        }
    } else {
        if ( (fd = open(filename,
                    O_WRONLY | O_CREAT | O_DIRECT,
                    00644)) < 0) {
            perror("Opening file for write failed");
            exit(1);
        }
    }

    blockIndex = 0;
    current = 0;

    if (read) {
        readBlock();
    }
//    cout << "read that.\n";
//    cout << buffer[blockIndex] << endl;
}



Buffer::~Buffer() {
    if (! this->is_read) {
        memset(buffer[blockIndex]+current, ' ', (BUFSIZE-current));
        buffer[blockIndex][BUFSIZE-1] = '\n';
        writeBlock();
    }
    close(fd);
}

char Buffer::getchar() {
    if (current >= BUFSIZE) {
        blockIndex = (blockIndex + 1) % BLOCKS;
        current = 0;
        readBlock();
    }
    if (buffer[blockIndex][current] == '\0') {
        current++;
        return getchar();
    }
    return (char) buffer[blockIndex][current++];
}

void Buffer::addchars(char* c) {
    if (current == 0) {
        posix_memalign((void**)&buffer[blockIndex], ALIGNMENT, BUFSIZE);
    }

//    cout << "got: " << c << endl;
    int string_length = strlen(c);
    if ((current + string_length) < BUFSIZE) {
        strcpy(buffer[blockIndex]+current, c);
        current += string_length;
    } else {
        // fill the current buffer
        int cut_at = (BUFSIZE - current);
        memcpy (buffer[blockIndex]+current, c, cut_at);
        // write it
        writeBlock();
        free(buffer[blockIndex]);
        current = 0;
        // add the rest
        addchars(c+cut_at);
    }
//    cout << "\n\nbuffer[blockIndex]: " << buffer[blockIndex] 
//        << ", length: " << string_length 
//        << ", current index: " << current << endl;
}

void Buffer::addchars(int value) {
    char* buffer = new char[32];
    sprintf(buffer, "%i", value);
    addchars(buffer);
}

void Buffer::addchars(const char* c) {
    addchars(const_cast<char*>(c));
}


void Buffer::ungetchar() {
    current--;
    if (current < 0) {
        current = BUFSIZE;
        blockIndex = (blockIndex - 1) % BLOCKS;
        // TODO: Test
    }
}

void Buffer::readBlock() {
    char *buf;
    posix_memalign((void**)&buf, ALIGNMENT, BUFSIZE);
    int read_chars = read(fd, buf, BUFSIZE);

    buffer[blockIndex] = buf;
    buffer[blockIndex][read_chars] = '\0';
    if (read_chars < BUFSIZE) {
        buffer[blockIndex][read_chars] = -1;
    }
}

void Buffer::writeBlock() {
//    cout << "Running writeBlock!" << endl;
    char *buf;
    posix_memalign((void**)&buf, ALIGNMENT, BUFSIZE);
//    memset(buf, ' ', ps);
    strcpy(buf, buffer[blockIndex]);

    int returncode;
    if ( (returncode = write(fd, buf, BUFSIZE)) < 0) {
        perror("Write failed");
    }
    free(buf);
}
