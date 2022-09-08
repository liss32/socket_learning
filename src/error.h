#ifndef _ERROR_
#define _ERROR_
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<netdb.h>
#include<string.h>
void unix_error(char* msg){
	fprintf(stderr,"%s:%s\n",msg,strerror(errno));
	exit(0);
}
void posix_error(int code,char* msg){
	fprintf(stderr,"%s:%s\n",msg,strerror(code));
	exit(0);	
}
void GAI_error(int code,char* msg){
	fprintf(stderr,"%s:%s\n",msg,gai_strerror(code));
	exit(0);
}
void app_error(char* msg){
	fprintf(stderr,"%s\n",msg);
	exit(0);
}
#endif
