#include"../src/rio_readn.h"
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
int main(){
	int fd,readn;
	char* ptr;
	if((fd=open("foo.txt",O_RDONLY,0))<0){
		printf("error");
		exit(1);
	}
	if((readn=rio_readn(fd,ptr,20))<0){
		printf("error rio_readn");
		exit(1);
	}
	printf("%d",readn);
	return 0;
}
