#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_PATH 1024

// ANSI color codes
#define BLUE  "\033[1;34m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

void listDir(const char *path) {
    DIR *dir;
    struct dirent *entry;
    char entryPath[MAX_PATH];

    printf("%s:\n", path);

    dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return;
    }

    // First pass: print entries with color
    while ((entry = readdir(dir)) != NULL) {
        // skip . and ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(entryPath, sizeof(entryPath), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(entryPath, &st) == 0) {
            if (S_ISDIR(st.st_mode)) {
                printf(BLUE "%s  " RESET, entry->d_name);   // Directory: Blue
            } else {
                printf(GREEN "%s  " RESET, entry->d_name); // File: Green
            }
        }
    }
    printf("\n\n");

    rewinddir(dir); // reset stream for recursion

    // Second pass: recursively process subdirectories
    while ((entry = readdir(dir)) != NULL) {
        // skip . and ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(entryPath, sizeof(entryPath), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(entryPath, &st) == 0 && S_ISDIR(st.st_mode)) {
            listDir(entryPath);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    const char *startPath = "."; // default to current directory
    if (argc > 1)
        startPath = argv[1];

    listDir(startPath);
    return 0;
}

