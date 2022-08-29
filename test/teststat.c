
#include<sys/stat.h>
#include<stdlib.h>
#include<stdio.h>
#include"/root/stdlib/stdlibn.h"
int main(int argc,char* argv[]){
	struct stat buf;
	if(stat(argv[1],&buf)<0){
		printf("error stat");
		exit(1);
	}
	if(S_ISREG(buf.st_mode))
		printf("type regular\n");
	else if(S_ISDIR(buf.st_mode))
		printf("type dir\n");
	else
		printf("other");
	char buff[40];
	itoa(buf.st_mode);
	if(buf.st_mode&S_IRUSR)
		printf("usr read\n");		
	if(buf.st_mode&S_IROTH)
		printf("other read\n");


	exit(0);
}
