#ifndef _READN_
#define _READN_
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<stdio.h>
ssize_t rio_readn(int fd,void* usrbuf,size_t n){
	size_t leftn=n;
	ssize_t readn;
	char* ptr=usrbuf;
	while(leftn>0){
		if((readn=read(fd,ptr,n))<0){
			if(errno=EINTR)
				continue;
			else
				return -1;
		}
		else if(readn==0)
			break;
		leftn-=readn;
		ptr+=readn;
	}
	return (n-leftn);
}
#endif
