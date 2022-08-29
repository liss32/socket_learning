#include<stdio.h>
extern char **environ;
int main(){
	printf("%s",environ[1]);
}
