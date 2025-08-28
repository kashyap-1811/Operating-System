#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int N;
pthread_t *tid;
int counter;
pthread_mutex_t lock;

void* trythis(void* arg)
{
    pthread_mutex_lock(&lock);

    unsigned long i = 0;
    counter += 1;
    printf("\n Job %d has started\n", counter);

    for (i = 0; i < (0xFFFFFFFF); i++)
        ; // Busy loop (just waste time)

    printf("\n Job %d has finished\n", counter);

    pthread_mutex_unlock(&lock);

    return NULL;
}

int main(void)
{
    printf("Enter the number of jobs: ");
    scanf("%d", &N);
    tid = malloc(N * sizeof(pthread_t));
    int i = 0;
    int error;

    // Initialize the mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }

    while (i < N) {
        error = pthread_create(&tid[i], NULL, &trythis, NULL);
        if (error != 0)
            printf("\nThread can't be created :[%s]", strerror(error));
        i++;
    }

     i = 0;
    while(i < N){
    	pthread_join(tid[i], NULL);
    	i++;
    }

    pthread_mutex_destroy(&lock);

    return 0;
}

