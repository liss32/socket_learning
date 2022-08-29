#include<stdlib.h>
#include<stdio.h>
int main(int argc,char* argv[]){
	int i=argc;
	if(argv[i]==NULL)
		printf("argv[i]==0");
	else
		printf("!=0");
	exit(0);
}
