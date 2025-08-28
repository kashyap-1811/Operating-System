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
            strcpy(path, "/proc/");
            strcat(path, dptr->d_name);
            strcat(path, "/stat");

            FILE *fp = fopen(path, "r");
            if (fp) {
                int pid;
                char cmd[256];
                if (fscanf(fp, "%d (%[^)])", &pid, cmd) == 2) {
                    printf("%d\t%s\n", pid, cmd);
                }
                fclose(fp);
            }
        }
    }

    closedir(d);
    return 0;
}

