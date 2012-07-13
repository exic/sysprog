#include "Buffer.hpp"

Buffer::Buffer(char* filename, bool read) {
    is_read = read;

    blockIndex = 0;
    current = 0;
    done = 0;
    steppedBackBlock = false;


    if (pthread_mutex_init(&full, NULL) || pthread_mutex_init(&empty, NULL)) {
        perror("mutex init failed\n");
        exit(EXIT_FAILURE);
    }

    // buffer is not full at this moment
    pthread_mutex_lock(&full);
    pthread_mutex_unlock(&empty);


    if (read) {
        reader = new Reader(filename);
        if (pthread_create(&thread, NULL, &Buffer::reader_thread, this)) {
            perror("Creating thread failed\n");
            exit(EXIT_FAILURE);
        }
    } else {
        writer = new Writer(filename);
        if (pthread_create(&thread, NULL, &Buffer::writer_thread, this)) {
            perror("Creating thread failed\n");
            exit(EXIT_FAILURE);
        }

        posix_memalign((void**)&buffer[blockIndex], ALIGNMENT, BUFSIZE * sizeof(char));
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
    }


    done = 1;
    pthread_mutex_unlock(&full);
    pthread_mutex_unlock(&empty);
    pthread_join(thread, NULL);

    if (is_read) {
        delete reader;
    } else {
        delete writer;
        free(buffer[blockIndex]);
    }
    pthread_mutex_destroy(&full);
    pthread_mutex_destroy(&empty);
}



// ############ Reading

void* Buffer::reader_thread(void *context) {
    Buffer* buf = (Buffer*) context;
    while (1) {
        pthread_mutex_lock(&buf->empty);
        if (buf->done) {
            break;
        }
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


// ############ Writing


void* Buffer::writer_thread(void *context) {
    Buffer* buf = (Buffer*) context;
    while (1) {
        pthread_mutex_lock(&buf->full);
        if (buf->done) {
            break;
        }
        buf->writer->writeBlock();
        pthread_mutex_unlock(&buf->empty);
    }
    return 0;
}

void Buffer::setNextBufferPart() {
        pthread_mutex_lock(&empty);
        writer->setBlock(buffer[blockIndex]);
        blockIndex = (blockIndex + 1) % BLOCKS;
        // when to free this again?
        posix_memalign((void**)&buffer[blockIndex], ALIGNMENT, BUFSIZE * sizeof(char));
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
}

void Buffer::addchars(const char* c) {
    addchars(const_cast<char*>(c));
}


void Buffer::write() {
    writer->writeBlock();
}
