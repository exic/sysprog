#include "Buffer.hpp"

Buffer::Buffer(char* filename, bool read) {
    is_read = read;

    blockIndex = 0;
    current = 0;
    steppedBackBlock = false;


    if (pthread_mutex_init(&full, NULL) || pthread_mutex_init(&empty, NULL)) {
        perror("mutex init failed\n");
        exit(EXIT_FAILURE);
    }

    if (read) {

        // Buffer reader block is not full at this moment
        pthread_mutex_lock(&full);

        reader = new Reader(filename);
        if (pthread_create(&thread, NULL, &Buffer::reader_thread, this)
        ) {
            perror("Creating thread failed\n");
            exit(EXIT_FAILURE);
        }
    } else {
        writer = new Writer(filename);
    }

    if (read) {
        getNextBufferPart();
    }
}

void* Buffer::reader_thread(void *context) {
    Buffer* buf = (Buffer*) context;
    while (1) {
        pthread_mutex_lock(&buf->empty);
        buf->reader->readBlock();
        pthread_mutex_unlock(&buf->full);
    }
    return 0;
}

void Buffer::getNextBufferPart() {
    pthread_mutex_lock(&full);
    buffer[blockIndex] = reader->getBlock();
    pthread_mutex_unlock(&empty);
}



Buffer::~Buffer() {
    if (is_read) {
        pthread_cancel(thread);
        pthread_mutex_destroy(&full);
        pthread_mutex_destroy(&empty);
        delete reader;
    } else {
        delete writer;
    }
}

char Buffer::getchar() {
    if (current >= BUFSIZE) {
        blockIndex = (blockIndex + 1) % BLOCKS;
        current = 0;
        if (steppedBackBlock) {
            steppedBackBlock = false;
        } else {
            getNextBufferPart();
        }
    }

    if (buffer[blockIndex][current] == '\0') {
        current++;
        return getchar();
    }

    return (char) buffer[blockIndex][current++];
}

void Buffer::addchars(char* c) {
    writer->addchars(c);
}
void Buffer::addchars(int value) {
    writer->addchars(value);
}
void Buffer::addchars(const char* c) {
    writer->addchars(c);
}


void Buffer::ungetchar() {
    current--;
    if (current < 0) {
        current = BUFSIZE - 1;
        blockIndex = (blockIndex - 1) % BLOCKS;
        if (blockIndex < 0) {
            blockIndex *= -1;
        }
        steppedBackBlock = true;
    }
}

void Buffer::write() {
    writer->writeBlock();
}
