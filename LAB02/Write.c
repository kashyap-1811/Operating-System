#include<stdio.h>
#include<unistd.h>

int main(){
	char arr[50] = "Hello World";
	write(1, arr, 11); // don't use sizeof
	return 0;
}
