#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int cnt = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* counter(void* arg){
	// lock the critical section
	pthread_mutex_lock(&lock);
	
	cnt++;
	printf("%d ", cnt);
	
	// unlock critical section
	pthread_mutex_unlock(&lock);
	return NULL;
}

int main(){
	int n = 9;
	pthread_t t[n];
	for(int i=0; i<n; i++){
		pthread_create(&t[i], NULL, counter, NULL);
	}
	
	for(int i=0; i<n; i++){
		pthread_join(t[i], NULL);
	}
	printf("\n");
	return 0;
}
