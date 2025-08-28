#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

void recursiveLS(DIR *dirp, char *path){
	struct dirent *dir = readdir(dirp);
	while(dir){
		if(dir->d_name[0] != '.'){
			printf("%s\n", dir->d_name);
			
			// if directory then recursivly print that
			if(dir->d_type == DT_DIR){
				// generate new path
				char *newpath = malloc(strlen(path) + strlen(dir->d_name) + 2);
				strcpy(newpath, path);
				strcat(strcat(newpath, "/"), dir->d_name);
				
				DIR *newdir = opendir(newpath);
				recursiveLS(newdir, newpath);
				
				free(newpath);
			}
		}
			
		dir = readdir(dirp);
	}
}

int main(int argc, char* argv[]) {
	// DIR *opendir(const char *name);
	DIR *dirp = opendir(argv[1]);
	
	if(!dirp){
		printf("Failure\n");
	}else{
		recursiveLS(dirp, argv[1]);		
	}
	
	return 0;
}

