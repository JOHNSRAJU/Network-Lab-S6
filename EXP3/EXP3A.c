#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(){
	int num1,num2,pid;
	pid=getpid();
	printf("Proces id from program 1:- %d\n",pid);
	printf("Enter any two numbers :- ");
	scanf("%d%d",&num1,&num2);
	printf("sum = %d\n",num1+num2);
	char *args[]={"4","Hello",NULL};
	execv("./pg2",args);
	return 0;
}
