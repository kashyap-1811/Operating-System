#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void* msg(void* arg){
    char *c = (char*)arg;
    printf("Message from thread: %s\n", c);
    free(c);  // Free the allocated memory after printing
    return NULL;
}

int main(){
    pthread_t t1;
    char *c = malloc(100);  // allocate memory for input string
    if (c == NULL) {
        perror("malloc failed");
        return 1;
    }

    printf("Please give msg to pass: ");
    if (fgets(c, 100, stdin) == NULL) {
        printf("Failed to read input.\n");
        free(c);
        return 1;
    }

    // Remove newline character if present
    c[strcspn(c, "\n")] = '\0';

    pthread_create(&t1, NULL, msg, (void*)c);
    pthread_join(t1, NULL);

    printf("Bye from Main\n");
    return 0;
}

