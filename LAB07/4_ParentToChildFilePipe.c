#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
    Program to pass filename
    from parent process to
    child process and child displays
    file content.
*/

int main(int argc, char *argv[]) {
    int pipefd[2];
    pid_t cpid;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid != 0) {        // Parent
        close(pipefd[0]);
        write(pipefd[1], argv[1], strlen(argv[1]));
        close(pipefd[1]);
        wait(NULL);         // wait for child
    } else {                // Child
        close(pipefd[1]);

        char fileName[250];
        int bytesRead = read(pipefd[0], fileName, sizeof(fileName) - 1);
        fileName[bytesRead] = '\0';  // null terminate string
        close(pipefd[0]);

        int fd;
        if ((fd = open(fileName, O_RDONLY)) == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        char arr[500];
        while ((bytesRead = read(fd, arr, sizeof(arr))) > 0) {
            write(1, arr, bytesRead);   // write to stdout
        }
        printf("\n");

        close(fd);
    }

    return 0;
}

