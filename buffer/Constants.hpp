#ifndef BUF_CONSTANTS
#define BUF_CONSTANTS

#include <linux/fs.h>

#define ALIGNMENT  64 * sizeof(void *)
#define BUFSIZE    512
#define BLOCKS     3
#define TOTAL_BUFSIZE BUFSIZE * BLOCKS

#endif
