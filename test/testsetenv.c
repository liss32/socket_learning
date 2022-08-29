#include<stdio.h>
#include<stdlib.h>
int main(int argc,char* argv[]){
	char cgiargs[20]="674&56";
	setenv("QUERY_STRING",cgiargs,1);
	printf("%d\n",argc);
}
