#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*  
	program to pass string read using 
	keyboard from parent process to 
	child process
*/

int main(){
	int pipefd[2];
	char buf[100];
	pid_t cpid; // child pid
	
	if(pipe(pipefd) == -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	
	cpid = fork();
	if(cpid == -1){
		perror("fork");
		exit(EXIT_FAILURE);
	}
	
	if(cpid != 0){  // parent
		wait(NULL);
		close(pipefd[1]);
		int bytesRead = read(pipefd[0], buf, sizeof(buf));
		write(0, buf, bytesRead);
		close(pipefd[0]);	
	}else{		// child
		close(pipefd[0]);
		int bytesRead = read(0, buf, sizeof(buf));
		write(pipefd[1], buf, bytesRead);
		printf("\n");
		close(pipefd[1]);
	}
	
	return 0;
}
