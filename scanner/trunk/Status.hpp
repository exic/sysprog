#ifndef STATUS
#define STATUS

enum Status {
    NONE,
    FINAL, ERROR,
    READING_INT, READING_ID,
    NEWLINE, TOKEN_READ
};

#endif
