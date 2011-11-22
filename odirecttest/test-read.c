#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <linux/fs.h>

main()
{
        printf("got: %i\n", BLKSSZGET);
        int BUFSIZE = 4096;
        char *buf;

        posix_memalign((void**)&buf, 1024, BUFSIZE+1);

        int fd = open("buffer/tests/buffertestfile", O_RDONLY | O_DIRECT);

        int last_char = read(fd, buf, BUFSIZE);
        buf[last_char] = '\0';
        printf("read: %i\n", last_char);
        printf("size: %lu\n", sizeof(buf));
        printf("size: %lu\n", sizeof(*buf));
        printf("size: %lu\n", sizeof(&buf));

        printf("got: %s\n", buf);
//        printf("got: %s\n", &&buf);
        printf("got: %i\n", *buf);

        close(fd);
        free(buf);
} /* main */

