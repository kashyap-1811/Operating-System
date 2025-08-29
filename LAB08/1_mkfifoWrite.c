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

    if (mkfifo(argv[1], 0666) == -1) {
        perror("mkfifo");
        // if fifo already exists, that’s not fatal
    }

    int fd;
    if ((fd = open(argv[1], O_WRONLY)) == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char arr[] = "Hello from Parent process\n";
    write(fd, arr, strlen(arr));

    close(fd);
    
    // remove FIFO after writing
    unlink(argv[1]);
    
    return 0;
}

