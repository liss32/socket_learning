#include<signal.h>
#include<stdio.h>
#include<stdlib.h>
//typedef void(*sighandler_t)(int);
void sigint_handler(int sig){
	printf("get sigiint");
	exit(0);
}
int main(){
	
	//	fprintf(stderr,"signal error",10);
	pause();
}
