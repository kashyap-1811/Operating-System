#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void* hello(void* arg){
	printf("Hello from Thread\n");
	return NULL;
}

int main(){
	// Signature: 
	// int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
	//                    void *(*start_routine) (void *), void *arg);
	pthread_t t1;
	pthread_create(&t1, NULL, hello, NULL);
	
	// int pthread_join(pthread_t thread, void **retval);
	pthread_join(t1, NULL);
	printf("Hello from Main\n");
	return 0;
}
