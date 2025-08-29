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
    child process and child puts
    file content in another pipe.
*/

int main(int argc, char *argv[]) {
    int pipe1[2];
    int pipe2[2];
    pid_t cpid;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (pipe(pipe1) == -1) {
        perror("pipe1");
        exit(EXIT_FAILURE);
    }
    
    if (pipe(pipe2) == -1) {
        perror("pipe2");
        exit(EXIT_FAILURE);
    }

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid != 0) {        // Parent
        close(pipe1[0]);
        close(pipe2[1]);
        write(pipe1[1], argv[1], strlen(argv[1])); // write filename to pipe1
        close(pipe1[1]);
        wait(NULL);
        
        int bytesRead;
        char arr[500];	
        while((bytesRead = read(pipe2[0], arr, sizeof(arr))) > 0){ // read from pipe2
        	write(1, arr, bytesRead);	// display on stdout
        }
        printf("\n");
        
        close(pipe2[0]);
    } else {                // Child
        close(pipe1[1]);
        close(pipe2[0]);

        char fileName[250];
        int bytesRead = read(pipe1[0], fileName, sizeof(fileName) - 1); // read filename from pipe1
        fileName[bytesRead] = '\0';  // null terminate string
        close(pipe1[0]);

        int fd;
        if ((fd = open(fileName, O_RDONLY)) == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        char arr[500];
        while ((bytesRead = read(fd, arr, sizeof(arr))) > 0) {	  // write to pipe2
            write(pipe2[1], arr, bytesRead); 
        }
	
	close(pipe2[1]);
        close(fd);
    }

    return 0;
}

