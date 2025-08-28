#include<unistd.h>

int main(){
	while(1){
		char arr[5000];
		int bytesRead = read(0, arr, sizeof(arr));
		write(1, arr, bytesRead);
	}
	return 0;
}
