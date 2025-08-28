#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    char *cwd = getcwd(NULL, 0);  // dynamically allocates memory

    if (cwd == NULL) {
        perror("getcwd");
        return 1;
    }

    printf("Current working directory: %s\n", cwd);
    free(cwd);  // don't forget to free

    return 0;
}

