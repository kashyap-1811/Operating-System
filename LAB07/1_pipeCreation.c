#include <stdio.h>
#include <unistd.h>

void pipeCreation(int pipefd[]){
	if(pipe(pipefd) == 0){
		printf("pipe Created Successfully\n");
		printf("Pipe Fds are: %d, %d\n", pipefd[0], pipefd[1]);
	}else{
		printf("Error Occured\n");
	}
}

int main(){
	int pipefd1[2], pipefd2[2];
	
	pipeCreation(pipefd1);
	pipeCreation(pipefd2);
	
	return 0;
}
