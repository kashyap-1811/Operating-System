#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(){
	int n;
	printf("Give input of number of nodes in list: ");
	scanf("%d", &n);
	
	printf("1st process PID: %d\n", getpid());
	
	for(int i=1; i<n; i++){
		int pid = fork();
		if(pid == -1)
			return 1;
		else if(pid == 0){
			printf("%d process: %d\n", i+1, getpid());
		}
		else{
			wait(NULL);
			break;
		}
	}
	
	printf("Bye from process: %d\n", getpid());
	return 0;
}
