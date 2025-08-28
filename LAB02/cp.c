#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]){

	char arr[5000];
	int fd1 = open(argv[1], O_RDONLY); //argv[1] will get the file name
	int bytesRead = read(fd1, arr, sizeof(arr));
	
	int fd2 = open(argv[2], O_RDWR | O_CREAT | O_APPEND, 0777); //this will append not override, 0777 will give all permission to all
	write(fd2, arr, bytesRead);
	close(fd1);
	close(fd2);
	
	return 0;
}
