#ifndef _OENLISTEN_
#define _OPENLISTEN_
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#define LISTENQ 5
int open_listenfd(char* port){
	
	struct addrinfo hints,*listp,*p;
	int listenfd,optval=1;
	
	hints.ai_socktype=SOCK_STREAM;
	hints.ai_flags=AI_ADDRCONFIG;
	hints.ai_flags=AI_PASSIVE;
	if((getaddrinfo(NULL,port,&hints,&listp))!=0){
		printf("error getaddrinfo");
		exit(0);
	}
	for(p=listp;p;p=p->ai_next){
		if((listenfd=socket(p->ai_family,p->ai_socktype,p->ai_protocol))<0)
			continue;
		setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,(const void*)&optval,sizeof(int));
		if(bind(listenfd,p->ai_addr,p->ai_addrlen)==0)
			break;
		close(listenfd);
	}
	freeaddrinfo(listp);
	if(!p)
		return -1;
	if(listen(listenfd,LISTENQ)<0){
		close(listenfd);
		return -1;
	}
	return listenfd;
}
#endif









		
