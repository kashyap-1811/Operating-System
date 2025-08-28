#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// Signature: 
// int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
//                    void *(*start_routine) (void *), void *arg);

// int pthread_join(pthread_t thread, void **retval);

void* hello1(void* arg){
	printf("Hello from Thread1\n");
	return NULL;
}

void* hello2(void* arg){
	printf("Hello from Thread2\n");
	return NULL;
}

int main(){
	pthread_t t1, t2;
	
	pthread_create(&t1, NULL, hello1, NULL);
	pthread_create(&t2, NULL, hello2, NULL);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
	printf("Bye from Main\n");
	return 0;
}
