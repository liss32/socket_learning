
#include"../src/open_listenfd.h"
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/select.h>
#include<time.h>
#define MAXLINE 4567
int main(int argc,char* argv[]){
	if(argc!=2){
		fprintf(stderr,"input right port");
		exit(1);
	}

	int listenfd,connfd,maxi=0,maxfd,nready,client[FD_SETSIZE];
	struct sockaddr_in cliaddr;
	socklen_t len=sizeof(cliaddr);

	int i;
	for(i=0;i<FD_SETSIZE;i++){
		client[i]=-1;
	}
	if((listenfd=open_listenfd(argv[1]))<0){
		printf("error open_listen");
		exit(1);
	}
	maxfd=listenfd;
	fd_set rset,ready;
	FD_ZERO(&rset);
	FD_SET(listenfd,&rset);

	while(1){
		ready=rset;

		nready=select(maxfd+1,&ready,NULL,NULL,NULL);

		if(nready>0){
			if(FD_ISSET(listenfd,&ready)){
					connfd=accept(listenfd,(struct sockaddr*)&cliaddr,&len);					
					for(i=0;i<FD_SETSIZE;i++){
						if(client[i]==-1){
								
							client[i]=connfd;
							if((i+1)>maxi)
								maxi=i+1;
							break;		
						}
					}

					FD_SET(connfd,&ready);
					if(i==FD_SETSIZE)
						fprintf(stderr,"too many clients");
					if(connfd>maxfd)
						maxfd=connfd;
			}
			
			int socket,n;
			char buff[MAXLINE];
			for(i=0;i<maxi;i++){

				if((socket=client[i])<0)
					continue;
				if(FD_ISSET(socket,&ready)){

					if((n=read(socket,buff,sizeof(buff)))==0){
						
						close(socket);
						FD_CLR(socket,&ready);
						client[i]=-1;
					}else{
printf("%s\n",buff);
						write(socket,buff,strlen(buff));
						}
				}
			}
		}
	}
	close(listenfd);
	return 0;
}
