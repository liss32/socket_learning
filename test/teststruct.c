#include<stdio.h>
struct rio{
	int a;
	int b;
};
int test(struct rio sa){
	printf("%d",sa.a);
}
int main(){
	struct rio kl={1,2};
	test(kl);
	
	}
