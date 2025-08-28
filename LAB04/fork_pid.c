#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(){
	int pid = fork();
	
	if(pid == -1)
		return -1;
	else if(pid != 0){
		wait(NULL);
		printf("Hello from Parent: %d having parent: %d\n", getpid(), getppid());
	}else
		printf("Hello from Child: %d having parent: %d\n", getpid(), getppid());
	return 0;
}
