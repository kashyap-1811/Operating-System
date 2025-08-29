#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <fifo_name>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd;
    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char arr[500];
    int bytesRead;
    while ((bytesRead = read(fd, arr, sizeof(arr))) > 0) {
        write(1, arr, bytesRead);  // write to stdout
    }

    close(fd);
    
    // remove FIFO after writing
    unlink(argv[1]);
    
    return 0;
}

