#ifndef _WRITEN_
#define _WRITEN_
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
ssize_t rio_writen(int fd,void* usrbuf,size_t n){
	char* ptr=usrbuf;
	ssize_t writen;
	size_t leftn=n;
	while(leftn>0){
		if((writen=write(fd,ptr,n))<=0){
			if(errno==EINTR)
				continue;
			else
				return -1;
		}
		leftn-=writen;
		ptr+=writen;
	}
	return n;
}
#endif
