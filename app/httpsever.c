
#include"../src/open_listenfd.h"
#include"../src/rio_readline.h"
#include"../src/rio_writen.h"
#include<sys/mman.h>
#include<stdio.h>
#include<string.h>

#include<unistd.h>
#include<sys/stat.h>
#define MAXLINE 150
#define MAXBUF 4567
extern char **environ;

void doit(int connfd);
int parse_uri(char* uri,char* filename,char* cgiargs);
void clienterror(int fd,char* cause,char* errnum,char* shortmsg,char* longmsg);
void serve_static(int fd,char* filename,int filesize);
void serve_dynamic(int fd,char* filename,char* cgiargs);
void getfiletype(char* filename,char* filetype);
int main(int argc,char* argv[]){
	if(argc!=2){
		fprintf(stderr,"usage: %s <port>",argv[0]);
		exit(0);
	}
	int listenfd,connfd;
	socklen_t clientlen;
	struct sockaddr_in clientaddr;
	char hostname[MAXLINE],port[MAXLINE];
	clientlen=sizeof(clientaddr);	
	if((listenfd=open_listenfd(argv[1]))<0){
		fprintf(stderr,"error open_listenfd");
		exit(0);
	}
	while(1){
printf("before accept\n");
		if((connfd=accept(listenfd,(struct sockaddr*)&clientaddr,&clientlen))<0){
			fprintf(stderr,"accept error %d %d",connfd,listenfd);
		//	exit(0);
		}
		else{	
printf("before doit\n");
			getnameinfo((struct sockaddr*)&clientaddr,clientlen,hostname,MAXLINE,port,MAXLINE,0);
			fprintf(stdout,"hostname: %s port: %s\n",hostname,port);
			doit(connfd);		
		}
	}
	return 0;
}
void doit(int connfd){
	struct stat sta;
	char buf[MAXLINE],methon[MAXLINE],uri[MAXLINE],version[MAXLINE],filename[MAXLINE],cgiargs[MAXLINE];
	rio_t rp;
	int is_static;

	rio_readinitb(&rp,connfd);	
	rio_readlinb(&rp,buf,MAXLINE);

	sscanf(buf,"%s %s %s",methon,uri,version);	
	printf("URL: %s\n",buf);
	printf("%s\n",uri);
	if(strcmp(methon,"GET")){
		clienterror(connfd,methon,"501","Not implemented","Tiny does not implement this method");
		return;
	}
	is_static=parse_uri(uri,filename,cgiargs);
	printf("%s\n",filename);
	if(stat(filename,&sta)<0){
		clienterror(connfd,filename,"404","Not found","Tiny couldn't find this file");
		return;
	}
	if(is_static){
		if(!(S_ISREG(sta.st_mode))||!(sta.st_mode&S_IRUSR))
		{}
		printf("home.html \n");	
		serve_static(connfd,filename,sta.st_size);
	}
	else{
		if(!(S_ISREG(sta.st_mode))||!(sta.st_mode&S_IXUSR))
		{}
		serve_dynamic(connfd,filename,cgiargs);
		}
	
}
int parse_uri(char* uri,char* filename,char* cgiargs){
	if(!strstr(uri,"cgi-bin")){
		strcpy(filename,".");
		//strcat(filename,"/");
		strcat(filename,uri);
		if(uri[strlen(uri)-1]=='/')
			strcat(filename,"home.html");
		return 1;
	}else{
		char* ptr;
		ptr=strchr(uri,'?');
		if(ptr){
			strcpy(cgiargs,ptr+1);
			ptr='\0';
		}
		else
			cgiargs=NULL;
		strcpy(filename,".");
		return 0;
	}
}
void clienterror(int fd,char* cause,char* errnum,char *shortmsg,char* longmsg){
	char buf[MAXBUF];
	sprintf(buf,"HTTP/1.0 %s %s\r\n",errnum,shortmsg);
	rio_writen(fd,buf,strlen(buf));
	printf("%s %d",buf,strlen(buf));
	sprintf(buf,"Conten-type:text/html");
	rio_writen(fd,buf,strlen(buf));
}
void serve_static(int fd,char* filename,int filesize){
	char filetype[MAXLINE];
	getfiletype(filename,filetype);
	char buf[MAXLINE];
	sprintf(buf,"HTTP/1.1 200 OK\r\n");
	sprintf(buf,"%sContext-length: %d\r\n",buf,filesize);
	sprintf(buf,"%sContext-type: %s\r\n\r\n",buf,filetype);
	rio_writen(fd,buf,strlen(buf));	
	printf("response headers:\n");
	printf("%s\n",buf);

	int filefd;
	char *map;
	filefd=open(filename,O_RDONLY,0);
	map=mmap(0,filesize,PROT_READ,MAP_PRIVATE,filefd,0);
	close(filefd);
	rio_writen(fd,map,filesize);
	munmap(map,filesize);
}
	
void serve_dynamic(int fd,char* filename,char* cgiargs){
	char buf[MAXLINE],*empty[]={NULL};
	sprintf(buf,"HTTP/1.1 200 OK\r\n");
	sprintf(buf,"%sSever:Tiny Web Sever\r\n",buf);
	rio_writen(fd,buf,strlen(buf));

//	extern char* environ[];

	if(fork==0){
		setenv("QUERY_STRING",cgiargs,1);
		dup2(fd,STDOUT_FILENO);
		execve(filename,empty,environ);	
	}
	wait(NULL);
}	
		
void getfiletype(char* filename,char* filetype){
	if(strstr(filename,"html"))
		strcpy(filetype,"text/html");
	if(strstr(filename,".gif"))
		strcpy(filetype,"image/gif");
	else
		strcpy(filetype,"text/plain");
}	
