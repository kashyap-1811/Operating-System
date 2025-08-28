#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct calc_args {
    float a;
    float b;
    char op;
};

void* calculate(void* arg) {
    struct calc_args *args = (struct calc_args*)arg;
    float result;
    switch (args->op) {
        case '+':
            result = args->a + args->b;
            printf("Result: %.2f + %.2f = %.2f\n", args->a, args->b, result);
            break;
        case '-':
            result = args->a - args->b;
            printf("Result: %.2f - %.2f = %.2f\n", args->a, args->b, result);
            break;
        case '*':
            result = args->a * args->b;
            printf("Result: %.2f * %.2f = %.2f\n", args->a, args->b, result);
            break;
        case '/':
            if (args->b == 0) {
                printf("Error: Division by zero!\n");
            } else {
                result = args->a / args->b;
                printf("Result: %.2f / %.2f = %.2f\n", args->a, args->b, result);
            }
            break;
        default:
            printf("Error: Unsupported operator '%c'\n", args->op);
            break;
    }
    return NULL;
}

int main() {
    struct calc_args args;

    printf("Enter first number: ");
    if (scanf("%f", &args.a) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter second number: ");
    if (scanf("%f", &args.b) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter operator (+, -, *, /): ");
    scanf(" %c", &args.op);  // note the space before %c to consume whitespace

    pthread_t tid;
    if (pthread_create(&tid, NULL, calculate, &args) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    pthread_join(tid, NULL);

    return 0;
}

