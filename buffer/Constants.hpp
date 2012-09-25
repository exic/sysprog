#ifndef BUF_CONSTANTS
#define BUF_CONSTANTS

#include <linux/fs.h>

/**
 * Size of the buffer.
 */
#define BUFSIZE    4096

/**
 * Number of block that the buffer will have available (TODO who needs that?)
 */
#define BLOCKS     3

/**
 * Total available size in this buffer.
 */
#define TOTAL_BUFSIZE (BUFSIZE * 2)

#endif
