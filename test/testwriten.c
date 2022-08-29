#include"rio_writen.h"
#include<stdio.h>
#include<stdlib.h>
int main(){
	int fd,writen;
	char ptr[10];
	if((fd=open("foo.txt",O_WRONLY,0))<0){
		printf("error open fd");
		exit(1);
	}

	scanf("%s",ptr);
	if((writen=rio_writen(fd,ptr,10))<0){
		printf("error writen %d",writen);
		exit(1);
	}
	printf("%d",writen);
}
