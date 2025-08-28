#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <directory_path>\n", argv[0]);
        return 1;
    }

    DIR *d = opendir(argv[1]);

    if (d == NULL) {
        perror("opendir");
        return 1;
    }

    struct dirent *dir;
    while ((dir = readdir(d)) != NULL) {
        printf("%s\n", dir->d_name);
    }

    closedir(d);
    return 0;
}

