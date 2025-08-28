#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    DIR *d;
    struct dirent *dptr;

    d = opendir("/proc");
    if (!d) {
        perror("opendir");
        return 1;
    }

    printf("PID\tCMD\n");

    while ((dptr = readdir(d)) != NULL) {
        // Only consider numeric directories (which are PIDs)
        if (isdigit(dptr->d_name[0])) {
            char path[256];
            snprintf(path, sizeof(path), "/proc/%s/comm", dptr->d_name);

            FILE *fp = fopen(path, "r");
            if (fp) {
                char cmd[256];
                if (fgets(cmd, sizeof(cmd), fp) != NULL) {
                    // remove trailing newline
                    cmd[strcspn(cmd, "\n")] = 0;
                    printf("%s\t%s\n", dptr->d_name, cmd);
                }
                fclose(fp);
            }
        }
    }

    closedir(d);
    return 0;
}

