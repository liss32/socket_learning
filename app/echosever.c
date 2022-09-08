#include"../src/rio_readline.h"
#include"../src/open_listenfd.h"
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include"../src/rio_writen.h"
#include<signal.h>
typedef void (*sighandler_t)(int);
void sig_handler(int sig){
	while(waitpid(-1,NULL,WNOHANG)>0);
	return;

}
int main(int argc,char* argv[]){
	if(argc!=2){
		fprintf(stderr,"input right port");
		exit(1);
	}
	pid_t pid;
	int listenfd,connfd;
	struct sockaddr_in cliaddr;
	socklen_t len=sizeof(cliaddr);

	if((listenfd=open_listenfd(argv[1]))<0){
		printf("error open_listen");
		exit(1);
	}
	signal(SIGCHLD,sig_handler);
	while(1){
/*		if((connfd=accept(listenfd,(struct sockaddr*)&cliaddr,&len))<0){
			fprintf(stderr,"error accept");
			exit(1);
		}
		if((pid=fork())<0){
			fprintf(stderr,"fork error");
			exit(0);
		}
		if(pid==0){
			close(listenfd);
			printf("connect success\n");
			rio_t rp;
			int cnt;
			char buf[50];
			rio_readinitb(&rp,connfd);
			if((cnt=rio_read(&rp,buf,50))<0){
				printf("error rio_read");
				exit(1);
			}
			printf("%s\n",buf);
			rio_writen(connfd,buf,sizeof(buf));
			close(connfd);
			exit(0);
		}
		close(connfd);*/
	}
	close(listenfd);
	return 0;
}
