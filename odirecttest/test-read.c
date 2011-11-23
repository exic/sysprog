#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <linux/fs.h>

main()
{
        printf("got: %i\n", BLKSSZGET);
        int ps = BLKSSZGET; // getpagesize();
//        int ps = getpagesize();
        int BUFSIZE = ps;
        char *buf;

        posix_memalign((void**)&buf, ps, BUFSIZE);

        int fd;
        if ( (fd = open("../buffer/tests/buffertestfile", O_RDONLY | O_DIRECT)) < 0) {
            perror("Error opening");
            exit(1);
        }

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

