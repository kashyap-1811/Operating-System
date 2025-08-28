#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	printf("Hello\n"); // always use \n with printf to clear the buffer
	int pid = fork();
	
	if(pid == -1){
		return 1;
	}
	else if(pid == 0)
		printf("Hi from Child\n");
	return 0;
}
