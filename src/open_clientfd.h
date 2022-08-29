#ifndef _OPENCLIENT__
#define _OPENCLIENT__
#include<sys/socket.h>
#include<stdlib.h>
#include<netdb.h>
#include<string.h>
#include<stdio.h>
int open_clientfd(char* hostname,char* port){
	struct addrinfo hints,*listp,*p;
	int clientfd;
	
	memset(&hints,0,sizeof(struct addrinfo));
	hints.ai_socktype=SOCK_STREAM;
	hints.ai_flags=AI_ADDRCONFIG;
	hints.ai_flags=AI_NUMERICSERV;
	if((getaddrinfo(hostname,port,&hints,&listp))!=0){
		printf("error getaddrinfo");
		exit(0);
	}
	for(p=listp;p;p=p->ai_next){
		if((clientfd=socket(p->ai_family,p->ai_socktype,p->ai_protocol))<0)
			continue;
		if((connect(clientfd,p->ai_addr,p->ai_addrlen))!=-1)
			break;
		close(clientfd);
	}
	freeaddrinfo(listp);
	if(!p)
		return -1;
	return clientfd;
}
#endif

	

	
	
