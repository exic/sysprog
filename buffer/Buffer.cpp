#include "Buffer.hpp"

Buffer::Buffer(char* filename, bool read) {
    is_read = read;

    for (int i = 0; i < BLOCKS; i++) {
        buffer[i] = 0;
    }
    blockIndex = 0;
    current = 0;
    steppedBackBlock = false;


    if (pthread_mutex_init(&full, NULL) || pthread_mutex_init(&empty, NULL)) {
        perror("mutex init failed\n");
        exit(EXIT_FAILURE);
    }

    // buffer is not full at this moment
    pthread_mutex_lock(&full);
    pthread_mutex_unlock(&empty);


    if (read) {
        reader = new Reader(filename, &full, &empty);
        if (pthread_create(&thread, NULL, &Reader::thread, reader)) {
            perror("Creating thread failed\n");
            exit(EXIT_FAILURE);
        }
    } else {
        writer = new Writer(filename, &full, &empty);
        if (pthread_create(&thread, NULL, &Writer::thread, writer)) {
            perror("Creating thread failed\n");
            exit(EXIT_FAILURE);
        }

        buffer[blockIndex] = writer->getBuffer();
    }

    if (read) {
        getNextBufferPart();
    }

}

Buffer::~Buffer() {

    if (!is_read) {
        while (current < BUFSIZE-1) {
            addchars(" ");
        }
        addchars("\n");

        pthread_mutex_lock(&empty); // otherwise write in progress might be cancelled

        writer->setDone();
    }

    pthread_mutex_unlock(&full);
    pthread_mutex_unlock(&empty);
    pthread_join(thread, NULL);

    if (is_read) {
        delete reader;
        for (int i = 0; i < BLOCKS; i++) {
            if (&buffer[i]) {
                free(buffer[i]);
            }
        }
    } else {
        delete writer;
        free(buffer[blockIndex]);
    }
    pthread_mutex_destroy(&full);
    pthread_mutex_destroy(&empty);
}



// ############ Reading

void Buffer::getNextBufferPart() {
    pthread_mutex_lock(&full);
    buffer[blockIndex] = reader->getBlock();

    // free oldest buffer
    int obsolete = (blockIndex + 1) % BLOCKS;
    if (buffer[obsolete]) {
        free(buffer[obsolete]);
        buffer[obsolete] = 0;
    }
    pthread_mutex_unlock(&empty);
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

    if (buffer[blockIndex][current] == 0) {
        current++;
        return getchar();
    }

    return (char) buffer[blockIndex][current++];
}

void Buffer::ungetchar() {
    current--;
    if (current < 0) {
        current = BUFSIZE - 1;
        blockIndex = (blockIndex + (BLOCKS - 1) ) % BLOCKS; // 1 back
        steppedBackBlock = true;
    }
}


// ############ Writing

void Buffer::setNextBufferPart() {
        pthread_mutex_lock(&empty);

        writer->setBlock(buffer[blockIndex]);
        blockIndex = (blockIndex + 1) % BLOCKS;
        buffer[blockIndex] = writer->getBuffer();

        pthread_mutex_unlock(&full);
}

void Buffer::addchars(char* c) {
    int string_length = strlen(c);
    if ((current + string_length) < BUFSIZE) {
        strcpy(buffer[blockIndex]+current, c);
        current += string_length;
    } else {
        // fill the current buffer
        int cut_at = (BUFSIZE - current);
        memcpy (buffer[blockIndex]+current, c, cut_at);

        setNextBufferPart();

        current = 0;
        // add the rest
        addchars(c+cut_at);
    }
}

void Buffer::addchars(int value) {
    char* buffer = new char[32];
    sprintf(buffer, "%i", value);
    addchars(buffer);
    delete [] buffer;
}

void Buffer::addchars(const char* c) {
    addchars(const_cast<char*>(c));
}
