#include"../src/open_clientfd.h"
#include"../src/rio_readline.h"
#include"../src/rio_writen.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define MAX_URL 2000
int webclient(char* host,char* port){
	int clientfd;
	if((clientfd=open_clientfd(host,port))<0){
		printf("open clientfd fail");
		return -1;
	}

	char output[300],path[50],URL[MAX_URL]={"GET "};
	scanf("%s",path);
	strcat(URL,path);
	strcat(URL," HTTP/1.1\r\nHost: ");
	strcat(URL,host);
	strcat(URL,"\r\n\r\n");
	printf("%s",URL);
	
	rio_t rp;
	rio_readinitb(&rp,clientfd);
printf("before writen\n");	
	if((rio_writen(clientfd,URL,100))<0){
		printf("error write");
		return -1;}
printf("after writen\n");
	if((rio_read(&rp,output,sizeof(output)))<0){
		printf("errror read");
		return -1;}
printf("after read\n");
	if((fputs(output,stdout))<0){
		printf("error fputs");
		return -1;
	} 
}
int main(int argc,char* argv[]){
	if(argc!=3){
		printf("error input");
		exit(1);
	}
	webclient(argv[1],argv[2]);
}
	
