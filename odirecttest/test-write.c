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
        int ps = getpagesize();
        posix_memalign((void**)&buf, ps, BUFSIZE);
        memset(buf, -1, 512);
        strcpy(buf, "hallo welt");

        int fd;
        if ( (fd = open("herenewfile", O_WRONLY | O_CREAT | O_DIRECT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0) {
            perror("Open failed");
            exit(1);
        }

        int returncode;
        if ( (returncode = write(fd, buf, 512)) < 0) {
            perror("Write failed");
        }
//        buf[returncode] = '\0';
        printf("returned: %i\n", returncode);
        printf("pagesize: %i\n", ps);
        printf("size: %lu\n", sizeof(buf));
        printf("size: %lu\n", sizeof(*buf));
        printf("size: %lu\n", sizeof(&buf));

        printf("got: %s\n", buf);
//        printf("got: %s\n", &&buf);
        printf("got: %i\n", *buf);

        close(fd);
        free(buf);
} /* main */

