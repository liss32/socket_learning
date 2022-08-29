#include"../src/rio_readline.h"
#include"../src/open_listenfd.h"
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include"../src/rio_writen.h"
int main(int argc,char* argv[]){
	if(argc!=2){
		printf("input right port");
		exit(1);
	}
	int listenfd,connfd;
	struct sockaddr_in cliaddr;
	if((listenfd=open_listenfd(argv[1]))<0){
		printf("error open_listen");
		exit(1);
	}
	socklen_t len=sizeof(cliaddr);
	if((connfd=accept(listenfd,(struct sockaddr*)&cliaddr,&len))<0){
		printf("error accept");
		exit(1);
	}
	printf("connect success\n");
	rio_t rp;
	int cnt;
	char buf[50];
	while(1){
	rio_readinitb(&rp,connfd);
	if((cnt=rio_read(&rp,buf,50))<0){
		printf("error rio_read");
		exit(1);
	}
	printf("%s",buf);
	rio_writen(connfd,buf,sizeof(buf));
}
	close(listenfd);
	return 0;
}
