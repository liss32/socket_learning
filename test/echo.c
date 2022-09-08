#include"../src/open_clientfd.h"
#include"../src/rio_readline.h"
#include<stdio.h>
int main(int argc,char* argv[]){
	int fd;
	if(argc!=3)
		printf("input right host and port");
	if((fd=open_clientfd(argv[1],argv[2]))>0)
	
	while(1){
		fget
}
