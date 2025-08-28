#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	int n;
	printf("Give input of number of childs: ");
	scanf("%d", &n);
	
	printf("Parent processes PID: %d\n\n", getpid());
	
	for(int i=0; i<n; i++){
		int pid = fork();
		
		if(pid == -1)
			return 1;
		else if(pid == 0){
			printf("Child process: %d with parent: %d\n", getpid(), getppid());
			break;
		}
		else{
			wait(NULL);
		}
	}
	
	printf("Bye from process: %d\n\n", getpid());
	return 0;
}
