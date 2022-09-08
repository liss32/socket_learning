#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#define MAX_LINE 9234
int parse(char* buf,char* argv[]){
	char* delim;
	int argc=0;
	buf[strlen(buf)-1]=' ';
	while(*buf&&(*buf==' '))
		buf++;
	while((delim=strchr(buf,' '))){
		argv[argc++]=buf;
		*delim='\0';
		buf=delim+1;
		while(*buf&&(*buf==' '))
			buf++;
	}
	
	argv[argc]=NULL;
	if(argc==0)
		return 1;
	return 0;
}
int builtin_command(char **argv){
	if(!strcmp(argv[0],"ls"))
		return 1;
	if(!strcmp(argv[0],"quit"))
		exit(0);
	if(!strcmp(argv[0],"cat"))
		return 1;
	return 0;
}
void eval(char* buf){
	pid_t pid;
	char* argv[MAX_LINE];
	if(parse(buf,argv))
		exit(0);
	
	if(builtin_command(argv)){
//		int status;
		if((pid=fork())==0){
			if(execvp(argv[0],argv)<0){
				printf("error execve");
				exit(0);
			}
			exit(0);
		}
		else if(pid<0)
			printf("error fork");
		printf("end eval\n");
//else
//		waitpid(pid,&status,0);
	}	
}
int main(){
	char buf[MAX_LINE];
	while(1){
 		write(1,">",1);
		fgets(buf,MAX_LINE,stdin);
		if(feof(stdin))
			printf("\n");
		eval(buf);
		printf("after eval\n");
	}
	exit(0);
}	
