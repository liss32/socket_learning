#include<stdio.h>
#include<stdlib.h>
int main(int argc,char* argv[]){
	int i;

	for(i=0;i<argc;i++){
		printf("argv[%d]:%s\n",i,argv[i]);
}
	printf("\n");
	while(argv[++i]!=NULL){
		printf("envp[%d]:%s\n",i-argc-1,argv[i]);
	}
	exit(0);
}
