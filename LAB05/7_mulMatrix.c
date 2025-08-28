#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int **mat1, **mat2, **res;
int N;   // dimension (user input)

struct index {
    int i;
    int j;
};

void* mul(void* arg) {
    struct index *idx = (struct index*)arg;
    int i = idx->i, j = idx->j;
    
    for (int k = 0; k < N; k++)
        res[i][j] += mat1[i][k] * mat2[k][j];
    
    free(arg); // free allocated memory for indices
    return NULL;
}

int main() {
    printf("Enter dimension N of the matrices: ");
    scanf("%d", &N);

    // Allocate memory for matrices
    mat1 = malloc(N * sizeof(int*));
    mat2 = malloc(N * sizeof(int*));
    res  = malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        mat1[i] = malloc(N * sizeof(int));
        mat2[i] = malloc(N * sizeof(int));
        res[i]  = calloc(N, sizeof(int)); // initialized to 0
    }

    // Input matrix 1
    printf("Enter elements for Matrix 1 (%dx%d):\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &mat1[i][j]);
        }
    }

    // Input matrix 2
    printf("Enter elements for Matrix 2 (%dx%d):\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &mat2[i][j]);
        }
    }

    // Create N*N threads
    pthread_t *threads = malloc(N * N * sizeof(pthread_t));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            struct index *idx = malloc(sizeof(struct index));
            idx->i = i;
            idx->j = j;
            pthread_create(&threads[i * N + j], NULL, mul, (void*)idx);
        }
    }

    // Wait for all threads
    for (int i = 0; i < N * N; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print result
    printf("Resultant Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d\t", res[i][j]);
        }
        printf("\n");
    }

    // Free memory
    for (int i = 0; i < N; i++) {
        free(mat1[i]);
        free(mat2[i]);
        free(res[i]);
    }
    free(mat1);
    free(mat2);
    free(res);
    free(threads);

    return 0;
}

