#define _GNU_SOURCE 1

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <assert.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/sendfile.h>
#include <sys/prctl.h>
#include <sys/personality.h>
#include <arpa/inet.h>

void win()
{
    char flag[256];
    int flag_fd;
    int flag_length;

    flag_fd = open("/flag", 0);
    if (flag_fd < 0)
    {
        printf("\n  ERROR: Failed to open the flag -- %s!\n", strerror(errno));
        if (geteuid() != 0)
        {
            printf("  Your effective user id is not 0!\n");
            printf("  You must directly run the suid binary in order to have the correct permissions!\n");
        }
        exit(-1);
    }
    flag_length = read(flag_fd, flag, sizeof(flag));
    if (flag_length <= 0)
    {
        printf("\n  ERROR: Failed to read the flag -- %s!\n", strerror(errno));
        exit(-1);
    }
    write(1, flag, flag_length);
    printf("\n\n");
}

void read_exact(int fd, void *dst, int size, char *msg, int exitcode)
{
    int n = read(fd, dst, size);
    if (n != size)
    {
        fprintf(stderr, msg);
        fprintf(stderr, "\n");
        exit(exitcode);
    }
}

char desired_output[] = "\x1b[38;2;255;255;255m.\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m.\x1b[0m\x1b[38;2;255;255;255m|\x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;255;255;255m|\x1b[0m\x1b[38;2;255;255;255m|\x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;225;193;012m \x1b[0m\x1b[38;2;225;193;012m \x1b[0m\x1b[38;2;225;193;012m_\x1b[0m\x1b[38;2;225;193;012m_\x1b[0m\x1b[38;2;225;193;012m_\x1b[0m\x1b[38;2;225;193;012m_\x1b[0m\x1b[38;2;225;193;012m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;255;255;255m|\x1b[0m\x1b[38;2;255;255;255m|\x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;225;193;012m \x1b[0m\x1b[38;2;225;193;012m/\x1b[0m\x1b[38;2;225;193;012m \x1b[0m\x1b[38;2;225;193;012m_\x1b[0m\x1b[38;2;225;193;012m_\x1b[0m\x1b[38;2;225;193;012m_\x1b[0m\x1b[38;2;225;193;012m|\x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;255;255;255m|\x1b[0m\x1b[38;2;255;255;255m|\x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;225;193;012m|\x1b[0m\x1b[38;2;225;193;012m \x1b[0m\x1b[38;2;225;193;012m|\x1b[0m\x1b[38;2;225;193;012m \x1b[0m\x1b[38;2;225;193;012m \x1b[0m\x1b[38;2;225;193;012m_\x1b[0m\x1b[38;2;225;193;012m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;255;255;255m|\x1b[0m\x1b[38;2;255;255;255m|\x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;060;055;249m \x1b[0m\x1b[38;2;060;055;249m_\x1b[0m\x1b[38;2;060;055;249m_\x1b[0m\x1b[38;2;060;055;249m_\x1b[0m\x1b[38;2;060;055;249m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;225;193;012m|\x1b[0m\x1b[38;2;225;193;012m \x1b[0m\x1b[38;2;225;193;012m|\x1b[0m\x1b[38;2;225;193;012m_\x1b[0m\x1b[38;2;225;193;012m|\x1b[0m\x1b[38;2;225;193;012m \x1b[0m\x1b[38;2;225;193;012m|\x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;255;255;255m|\x1b[0m\x1b[38;2;255;255;255m|\x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;129;202;111m \x1b[0m\x1b[38;2;129;202;111m \x1b[0m\x1b[38;2;129;202;111m_\x1b[0m\x1b[38;2;129;202;111m_\x1b[0m\x1b[38;2;129;202;111m_\x1b[0m\x1b[38;2;129;202;111m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;060;055;249m|\x1b[0m\x1b[38;2;060;055;249m_\x1b[0m\x1b[38;2;060;055;249m \x1b[0m\x1b[38;2;060;055;249m_\x1b[0m\x1b[38;2;060;055;249m|\x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;253;167;136m \x1b[0m\x1b[38;2;253;167;136m_\x1b[0m\x1b[38;2;253;167;136m_\x1b[0m\x1b[38;2;253;167;136m \x1b[0m\x1b[38;2;253;167;136m \x1b[0m\x1b[38;2;253;167;136m_\x1b[0m\x1b[38;2;253;167;136m_\x1b[0m\x1b[38;2;253;167;136m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;225;193;012m \x1b[0m\x1b[38;2;225;193;012m\\\x1b[0m\x1b[38;2;225;193;012m_\x1b[0m\x1b[38;2;225;193;012m_\x1b[0m\x1b[38;2;225;193;012m_\x1b[0m\x1b[38;2;225;193;012m_\x1b[0m\x1b[38;2;225;193;012m|\x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;255;255;255m|\x1b[0m\x1b[38;2;255;255;255m|\x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;129;202;111m \x1b[0m\x1b[38;2;129;202;111m/\x1b[0m\x1b[38;2;129;202;111m \x1b[0m\x1b[38;2;129;202;111m_\x1b[0m\x1b[38;2;129;202;111m_\x1b[0m\x1b[38;2;129;202;111m|\x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;060;055;249m \x1b[0m\x1b[38;2;060;055;249m|\x1b[0m\x1b[38;2;060;055;249m \x1b[0m\x1b[38;2;060;055;249m|\x1b[0m\x1b[38;2;060;055;249m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;253;167;136m|\x1b[0m\x1b[38;2;253;167;136m \x1b[0m\x1b[38;2;253;167;136m \x1b[0m\x1b[38;2;253;167;136m\\\x1b[0m\x1b[38;2;253;167;136m/\x1b[0m\x1b[38;2;253;167;136m \x1b[0m\x1b[38;2;253;167;136m \x1b[0m\x1b[38;2;253;167;136m|\x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;255;255;255m|\x1b[0m\x1b[38;2;255;255;255m|\x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;129;202;111m|\x1b[0m\x1b[38;2;129;202;111m \x1b[0m\x1b[38;2;129;202;111m(\x1b[0m\x1b[38;2;129;202;111m_\x1b[0m\x1b[38;2;129;202;111m_\x1b[0m\x1b[38;2;129;202;111m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;060;055;249m \x1b[0m\x1b[38;2;060;055;249m|\x1b[0m\x1b[38;2;060;055;249m \x1b[0m\x1b[38;2;060;055;249m|\x1b[0m\x1b[38;2;060;055;249m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;253;167;136m|\x1b[0m\x1b[38;2;253;167;136m \x1b[0m\x1b[38;2;253;167;136m|\x1b[0m\x1b[38;2;253;167;136m\\\x1b[0m\x1b[38;2;253;167;136m/\x1b[0m\x1b[38;2;253;167;136m|\x1b[0m\x1b[38;2;253;167;136m \x1b[0m\x1b[38;2;253;167;136m|\x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;255;255;255m|\x1b[0m\x1b[38;2;255;255;255m|\x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;129;202;111m \x1b[0m\x1b[38;2;129;202;111m\\\x1b[0m\x1b[38;2;129;202;111m_\x1b[0m\x1b[38;2;129;202;111m_\x1b[0m\x1b[38;2;129;202;111m_\x1b[0m\x1b[38;2;129;202;111m|\x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;060;055;249m|\x1b[0m\x1b[38;2;060;055;249m_\x1b[0m\x1b[38;2;060;055;249m_\x1b[0m\x1b[38;2;060;055;249m_\x1b[0m\x1b[38;2;060;055;249m|\x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;253;167;136m|\x1b[0m\x1b[38;2;253;167;136m \x1b[0m\x1b[38;2;253;167;136m|\x1b[0m\x1b[38;2;253;167;136m \x1b[0m\x1b[38;2;253;167;136m \x1b[0m\x1b[38;2;253;167;136m|\x1b[0m\x1b[38;2;253;167;136m \x1b[0m\x1b[38;2;253;167;136m|\x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;255;255;255m|\x1b[0m\x1b[38;2;255;255;255m|\x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;253;167;136m|\x1b[0m\x1b[38;2;253;167;136m_\x1b[0m\x1b[38;2;253;167;136m|\x1b[0m\x1b[38;2;253;167;136m \x1b[0m\x1b[38;2;253;167;136m \x1b[0m\x1b[38;2;253;167;136m|\x1b[0m\x1b[38;2;253;167;136m_\x1b[0m\x1b[38;2;253;167;136m|\x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;255;255;255m|\x1b[0m\x1b[38;2;255;255;255m|\x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;255;255;255m|\x1b[0m\x1b[38;2;255;255;255m|\x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;255;255;255m|\x1b[0m\x1b[38;2;255;255;255m|\x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;000;000;000m \x1b[0m\x1b[38;2;255;255;255m|\x1b[0m\x1b[38;2;255;255;255m'\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m-\x1b[0m\x1b[38;2;255;255;255m'\x1b[0m\x00";

struct cimg_header
{
    char magic_number[4];
    uint16_t version;
    uint8_t width;
    uint8_t height;
    uint32_t remaining_directives;
} __attribute__((packed));

typedef struct
{
    uint8_t ascii;
} pixel_bw_t;
#define COLOR_PIXEL_FMT "\x1b[38;2;%03d;%03d;%03dm%c\x1b[0m"
typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t ascii;
} pixel_color_t;
typedef pixel_color_t pixel_t;

typedef struct
{
    union
    {
        char data[24];
        struct term_str_st
        {
            char color_set[7];   // \x1b[38;2;
            char r[3];          // 255
            char s1;            // ;
            char g[3];          // 255
            char s2;            // ;
            char b[3];          // 255
            char m;            // m
            char c;             // X
            char color_reset[4];     // \x1b[0m
        } str;
    };
} term_pixel_t;

struct cimg
{
    struct cimg_header header;
    unsigned num_pixels;
    term_pixel_t *framebuffer;
};

#define CIMG_NUM_PIXELS(cimg) ((cimg)->header.width * (cimg)->header.height)
#define CIMG_DATA_SIZE(cimg) (CIMG_NUM_PIXELS(cimg) * sizeof(pixel_t))
#define CIMG_FRAMEBUFFER_PIXELS(cimg) ((cimg)->header.width * (cimg)->header.height)
#define CIMG_FRAMEBUFFER_SIZE(cimg) (CIMG_FRAMEBUFFER_PIXELS(cimg) * sizeof(term_pixel_t))

void handle_6331(struct cimg *cimg)
{
    unsigned long data_size = cimg->header.width * cimg->header.height * sizeof(pixel_t);
    pixel_t *data = malloc(data_size);
    if (data == NULL)
    {
        puts("ERROR: Failed to allocate memory for the image data!");
        exit(-1);
    }
    read_exact(0, data, data_size, "ERROR: Failed to read data!", -1);

    for (int i = 0; i < cimg->header.width * cimg->header.height; i++)
    {
        if (data[i].ascii < 0x20 || data[i].ascii > 0x7e)
        {
            fprintf(stderr, "ERROR: Invalid character 0x%x in the image data!\n", data[i].ascii);
            exit(-1);
        }
    }

    int idx = 0;
    for (int y = 0; y < cimg->header.height; y++)
    {
        for (int x = 0; x < cimg->header.width; x++)
        {
            idx = (0+y)*((cimg)->header.width) + ((0+x)%((cimg)->header.width));
            char emit_tmp[24+1];
            snprintf(emit_tmp, sizeof(emit_tmp), "\x1b[38;2;%03d;%03d;%03dm%c\x1b[0m", data[y * cimg->header.width + x].r, data[y * cimg->header.width + x].g, data[y * cimg->header.width + x].b, data[y * cimg->header.width + x].ascii);
            memcpy((cimg)->framebuffer[idx%(cimg)->num_pixels].data, emit_tmp, 24);

        }
    }

}

void display(struct cimg *cimg, pixel_t *data)
{
    for (int i = 0; i < cimg->header.height; i++)
    {
        write(1, cimg->framebuffer+i*cimg->header.width, sizeof(term_pixel_t)*cimg->header.width);
        write(1, "\x1b[38;2;000;000;000m\n\x1b[0m", 24);
    }
}

struct cimg *initialize_framebuffer(struct cimg *cimg)
{
    cimg->num_pixels = CIMG_FRAMEBUFFER_PIXELS(cimg);
    cimg->framebuffer = malloc(CIMG_FRAMEBUFFER_SIZE(cimg)+1);
    if (cimg->framebuffer == NULL)
    {
        puts("ERROR: Failed to allocate memory for the framebuffer!");
        exit(-1);
    }
    for (int idx = 0; idx < cimg->num_pixels; idx += 1)
    {
        char emit_tmp[24+1];
        snprintf(emit_tmp, sizeof(emit_tmp), "\x1b[38;2;%03d;%03d;%03dm%c\x1b[0m", 255, 255, 255, ' ');
        memcpy(cimg->framebuffer[idx].data, emit_tmp, 24);

    }

    return cimg;
}

void __attribute__ ((constructor)) disable_buffering()
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 1);
}

int main(int argc, char **argv, char **envp)
{

    struct cimg cimg = { 0 };
    cimg.framebuffer = NULL;
    int won = 1;

    if (argc > 1)
    {
        if (strcmp(argv[1]+strlen(argv[1])-5, ".cimg"))
        {
            printf("ERROR: Invalid file extension!");
            exit(-1);
        }
        dup2(open(argv[1], O_RDONLY), 0);
    }

    read_exact(0, &cimg.header, sizeof(cimg.header), "ERROR: Failed to read header!", -1);

    if (cimg.header.magic_number[0] != 'c' || cimg.header.magic_number[1] != 'I' || cimg.header.magic_number[2] != 'M' || cimg.header.magic_number[3] != 'G')
    {
        puts("ERROR: Invalid magic number!");
        exit(-1);
    }

    if (cimg.header.version != 3)
    {
        puts("ERROR: Unsupported version!");
        exit(-1);
    }

    initialize_framebuffer(&cimg);

    while (cimg.header.remaining_directives--)
    {
        uint16_t directive_code;
        read_exact(0, &directive_code, sizeof(directive_code), "ERROR: Failed to read &directive_code!", -1);

        switch (directive_code)
        {
        case 6331:
            handle_6331(&cimg);
            break;
        default:
            fprintf(stderr, "ERROR: invalid directive_code %ux\n", directive_code);
            exit(-1);
        }
    }
    display(&cimg, NULL);

    if (cimg.num_pixels != sizeof(desired_output)/sizeof(term_pixel_t))
    {
        won = 0;
    }
    for (int i = 0; i < cimg.num_pixels && i < sizeof(desired_output)/sizeof(term_pixel_t); i++)
    {
        if (cimg.framebuffer[i].str.c != ((term_pixel_t*)&desired_output)[i].str.c)
        {
            won = 0;
        }
        if (
            cimg.framebuffer[i].str.c != ' ' &&
            cimg.framebuffer[i].str.c != '\n' &&
            memcmp(cimg.framebuffer[i].data, ((term_pixel_t*)&desired_output)[i].data, sizeof(term_pixel_t))
        )
        {
            won = 0;
        }
    }

    if (won) win();

}