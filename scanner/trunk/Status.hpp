#ifndef STATUS
#define STATUS

enum Status {
    FINAL,
    ERROR,

    NONE,

    READING_INT,
    READING_ID,
    READING_SIGN,

    READ_INT,
    READ_ID,
    READ_SIGN,
    TOKEN_READ,

    NEWLINE,
};

#endif
