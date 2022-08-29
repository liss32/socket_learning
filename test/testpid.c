#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include"../src/error.h"
int main(){
	int x;
	pid_t pid;
/*	if((pid=fork())<0)
		unix_error("fork error");
	else if(pid==0){
		printf("pid:%d child:%d\n",pid,--x);
		printf("child getpid:%d\n",getpid());

}
	printf("pid:%d parent--child: %d\n",pid,++x);
	printf("parent getpid:%d\n",getpid());
	exit(0);*/
	for(x=0;x<2;x++){
		if((pid=fork())==0){
		}
	}
	printf("1\n");
	exit(0);
}		
