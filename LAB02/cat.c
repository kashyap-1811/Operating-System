#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
	if(argc == 1){
		while(1){
			char arr[5000];
			int bytesRead = read(0, arr, sizeof(arr));
			write(1, arr, bytesRead);
		}
	}else{
		for(int i=1; i<argc; i++){
			int fd = open(argv[i], O_RDONLY); //argv[1] will get the file name
			char arr[5000];
			int bytesRead = read(fd, arr, sizeof(arr));
			write(1, arr, bytesRead);
			close(fd);
		}
	}
	return 0;
}
